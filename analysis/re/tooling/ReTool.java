// Shared headless annotation and focused decompilation entry point.
//@category RE
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.*;
import com.google.gson.*;
import ghidra.app.util.headless.HeadlessScript;
import ghidra.app.decompiler.*;
import ghidra.app.util.cparser.C.CParser;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.cmd.function.FunctionRenameOption;
import ghidra.program.database.mem.FileBytes;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.SourceType;

public class ReTool extends HeadlessScript {
    private final Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();
    private JsonObject req;
    private Path out;
    private final DataTypeConflictHandler strictTypes = new DataTypeConflictHandler() {
        @Override public ConflictResult resolveConflict(DataType added, DataType existing) {
            if (existing.isEquivalent(added)) return ConflictResult.USE_EXISTING;
            throw new IllegalArgumentException("Conflicting type dependency: " + existing.getPathName());
        }
        @Override public boolean shouldUpdate(DataType source, DataType local) { return false; }
        @Override public DataTypeConflictHandler getSubsequentHandler() { return this; }
    };

    private void keys(JsonObject obj, String... allowed) throws Exception {
        Set<String> valid = Set.of(allowed);
        for (String key : obj.keySet()) if (!valid.contains(key))
            throw new Exception("Unsupported annotation field: " + key);
    }

    private String text(JsonObject o, String key) {
        return !o.has(key) || o.get(key).isJsonNull() ? null : o.get(key).getAsString();
    }
    private JsonArray array(JsonObject o, String key) {
        return o.has(key) ? o.getAsJsonArray(key) : new JsonArray();
    }
    private void writeJson(String name, Object obj) throws Exception {
        Files.writeString(out.resolve(name), gson.toJson(obj) + "\n", StandardCharsets.UTF_8);
    }
    private String va(Address a) { return "0x" + a.toString(); }
    private String shaBytes() throws Exception {
        List<FileBytes> files = currentProgram.getMemory().getAllFileBytes();
        if (files.size() != 1 || files.get(0).getFileOffset() != 0)
            throw new Exception("Expected one complete imported file byte source");
        FileBytes fb = files.get(0);
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] buf = new byte[65536];
        for (long p = 0; p < fb.getSize();) {
            int count = (int)Math.min(buf.length, fb.getSize() - p);
            int got = fb.getOriginalBytes(p, buf, 0, count);
            if (got != count) throw new Exception("Incomplete stored original bytes");
            md.update(buf, 0, got); p += got;
        }
        return HexFormat.of().formatHex(md.digest());
    }
    private Function anchor(String raw) throws Exception {
        // Addresses are instruction VAs, not ELF symbol values with a Thumb tag.
        long n = Long.decode(raw);
        if ((n & 1) != 0) throw new Exception("Odd/Thumb-tagged anchor: use even instruction VA: " + raw);
        Address a = toAddr(n);
        Function f = currentProgram.getFunctionManager().getFunctionAt(a);
        Instruction ins = currentProgram.getListing().getInstructionAt(a);
        MemoryBlock b = currentProgram.getMemory().getBlock(a);
        if (f == null || ins == null || b == null || !b.isExecute())
            throw new Exception("Absent/ambiguous function entry or non-executable anchor: " + raw);
        return f;
    }
    private Map<String,Object> functionInfo(Function f, boolean detail) throws Exception {
        Map<String,Object> m = new LinkedHashMap<>();
        Address a = f.getEntryPoint();
        m.put("address", va(a)); m.put("name", f.getName());
        m.put("qualified_name", f.getName(true));
        m.put("name_source", f.getSymbol().getSource().toString());
        m.put("signature", f.getPrototypeString(false, false));
        m.put("signature_source", f.getSignatureSource().toString());
        m.put("plate_comment", currentProgram.getListing().getComment(CommentType.PLATE, a));
        m.put("body", f.getBody().toString());
        var reg = currentProgram.getRegister("TMode");
        m.put("thumb_mode", reg == null ? null : currentProgram.getProgramContext().getValue(reg, a, false));
        if (detail) {
            List<Long> fileOffsets = new ArrayList<>();
            MemoryBlock block = currentProgram.getMemory().getBlock(a);
            for (MemoryBlockSourceInfo source : block.getSourceInfos()) {
                long offset = source.getFileBytesOffset(a);
                if (offset >= 0) fileOffsets.add(offset + source.getFileBytes().orElseThrow().getFileOffset());
            }
            m.put("entry_file_offsets", fileOffsets);
            List<String> callers = new ArrayList<>();
            for (Function c : f.getCallingFunctions(monitor)) callers.add(va(c.getEntryPoint()));
            Collections.sort(callers); m.put("callers", callers);
            List<Map<String,Object>> instructions = new ArrayList<>();
            var it = currentProgram.getListing().getInstructions(f.getBody(), true);
            while (it.hasNext()) {
                Instruction i = it.next();
                Map<String,Object> row = new LinkedHashMap<>();
                row.put("address", va(i.getAddress())); row.put("instruction", i.toString());
                row.put("bytes", HexFormat.of().formatHex(i.getBytes()));
                List<String> flows = new ArrayList<>();
                for (Address flow : i.getFlows()) flows.add(va(flow));
                row.put("flows", flows); instructions.add(row);
            }
            m.put("instructions", instructions);
        }
        return m;
    }
    private Map<String,Object> inventory(String hash) throws Exception {
        Map<String,Object> m = new LinkedHashMap<>();
        m.put("program", currentProgram.getName()); m.put("sha256", hash);
        m.put("language", currentProgram.getLanguageID().toString());
        m.put("compiler", currentProgram.getCompilerSpec().getCompilerSpecID().toString());
        m.put("image_base", va(currentProgram.getImageBase()));
        List<Object> blocks = new ArrayList<>();
        for (MemoryBlock b : currentProgram.getMemory().getBlocks()) {
            Map<String,Object> row = new LinkedHashMap<>();
            row.put("name", b.getName()); row.put("start", va(b.getStart())); row.put("end", va(b.getEnd()));
            row.put("executable", b.isExecute()); row.put("initialized", b.isInitialized());
            List<Object> sources = new ArrayList<>();
            for (MemoryBlockSourceInfo s : b.getSourceInfos()) {
                Map<String,Object> sm = new LinkedHashMap<>();
                sm.put("start", va(s.getMinAddress())); sm.put("end", va(s.getMaxAddress()));
                sm.put("file_offset", s.getFileBytesOffset() < 0 ? null : s.getFileBytesOffset() + s.getFileBytes().orElseThrow().getFileOffset());
                sources.add(sm);
            }
            row.put("sources", sources); blocks.add(row);
        }
        m.put("memory_blocks", blocks);
        List<Object> functions = new ArrayList<>();
        var it = currentProgram.getFunctionManager().getFunctions(true);
        while (it.hasNext()) functions.add(functionInfo(it.next(), false));
        m.put("functions", functions); return m;
    }
    private void guard(String field, String actual, String desired, JsonObject expected) throws Exception {
        if (Objects.equals(actual, desired)) return;
        if (!expected.has(field) || !Objects.equals(actual, text(expected, field)))
            throw new Exception("Conflicting " + field + ": actual=" + actual + ", expected=" + text(expected, field));
    }
    private void applyTypes(JsonObject ann) throws Exception {
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        Set<String> seen = new HashSet<>();
        for (JsonElement item : array(ann, "types")) {
            JsonObject p = item.getAsJsonObject();
            keys(p, "name", "declaration");
            String name = text(p, "name");
            if (name == null || !name.matches("[A-Za-z_][A-Za-z0-9_]*") || !seen.add(name))
                throw new Exception("Absent/duplicate/invalid shared type name: " + name);
            List<DataType> named = new ArrayList<>();
            dtm.findDataTypes(name, named);
            if (named.stream().anyMatch(d -> !d.getPathName().equals("/shared/" + name)))
                throw new Exception("Ambiguous shared type name already present outside /shared: " + name);
            try (StandAloneDataTypeManager temp = new StandAloneDataTypeManager("proposal", dtm.getDataOrganization())) {
                DataType dt = new CParser(temp, true, new DataTypeManager[]{dtm}).parse(text(p, "declaration"));
                if (dt == null || !dt.getName().equals(name)) throw new Exception("Type declaration must yield " + name);
                dt = dt.copy(temp);
                dt.setCategoryPath(new CategoryPath("/shared"));
                DataType old = dtm.getDataType("/shared/" + name);
                if (old != null && !old.isEquivalent(dt)) throw new Exception("Conflicting shared type: " + name);
                if (old == null) dtm.addDataType(dt, strictTypes);
            }
        }
    }
    private void apply(JsonObject ann) throws Exception {
        applyTypes(ann);
        Set<String> seen = new HashSet<>();
        for (JsonElement item : array(ann, "functions")) {
            JsonObject p = item.getAsJsonObject();
            keys(p, "address", "name", "signature", "plate_comment", "expect");
            Function f = anchor(text(p, "address"));
            String key = va(f.getEntryPoint());
            if (!seen.add(key)) throw new Exception("Conflicting duplicate function anchor: " + key);
            JsonObject expected = p.has("expect") ? p.getAsJsonObject("expect") : new JsonObject();
            keys(expected, "name", "signature", "plate_comment");
            if (p.has("signature")) {
                String sig = text(p, "signature");
                DataTypeManager dtm = currentProgram.getDataTypeManager();
                try (StandAloneDataTypeManager temp = new StandAloneDataTypeManager("signature", dtm.getDataOrganization())) {
                    DataType parsed = new CParser(temp, false, new DataTypeManager[]{dtm}).parse(sig + ";");
                    if (!(parsed instanceof FunctionDefinition def)) throw new Exception("Not a C function signature: " + sig);
                    // Compare parameter names too: equivalence alone only compares types.
                    String actual = f.getPrototypeString(false, false);
                    String ledgerKey = "signature:" + key;
                    var opts = currentProgram.getOptions("RE annotations");
                    String saved = opts.getString(ledgerKey, null);
                    String savedActual = opts.getString(ledgerKey + ":actual", null);
                    boolean replay = sig.equals(saved) && actual.equals(savedActual);
                    if (!replay) {
                        guard("signature", actual, sig, expected);
                        var cmd = new ApplyFunctionSignatureCmd(f.getEntryPoint(), def, SourceType.USER_DEFINED,
                            true, false, strictTypes, FunctionRenameOption.NO_CHANGE);
                        if (!cmd.applyTo(currentProgram, monitor)) throw new Exception("Signature failed: " + cmd.getStatusMsg());
                        opts.setString(ledgerKey, sig);
                    }
                }
            }
            if (p.has("name")) {
                String name = text(p, "name");
                if (name == null || !name.matches("[A-Za-z_][A-Za-z0-9_]*")) throw new Exception("Invalid function name");
                guard("name", f.getName(), name, expected);
                var existing = currentProgram.getSymbolTable().getSymbols(name, f.getParentNamespace());
                for (var symbol : existing) if (!symbol.getAddress().equals(f.getEntryPoint()))
                    throw new Exception("Ambiguous function name: " + name);
                f.setName(name, SourceType.USER_DEFINED);
            }
            if (p.has("plate_comment")) {
                String comment = text(p, "plate_comment");
                guard("plate_comment", currentProgram.getListing().getComment(CommentType.PLATE, f.getEntryPoint()), comment, expected);
                currentProgram.getListing().setComment(f.getEntryPoint(), CommentType.PLATE, comment);
            }
            if (p.has("signature")) currentProgram.getOptions("RE annotations").setString(
                "signature:" + key + ":actual", f.getPrototypeString(false, false));
        }
    }
    private List<Object> exportC(String hash) throws Exception {
        List<Object> selected = new ArrayList<>();
        DecompInterface dec = new DecompInterface();
        try {
            if (!dec.openProgram(currentProgram)) throw new Exception("Decompiler open failed: " + dec.getLastMessage());
            for (JsonElement entry : array(req, "export")) {
                Function f = anchor(entry.getAsString());
                DecompileResults r = dec.decompileFunction(f, 120, monitor);
                if (!r.decompileCompleted() || r.getDecompiledFunction() == null)
                    throw new Exception("Decompile failed at " + va(f.getEntryPoint()) + ": " + r.getErrorMessage());
                String filename = va(f.getEntryPoint()) + ".c";
                String header = "/* Decompiled C, NOT recovered source; need not compile.\n * Binary: " + currentProgram.getName() +
                    "\n * SHA256: " + hash + "\n * Function VA: " + va(f.getEntryPoint()) + "\n */\n";
                Files.writeString(out.resolve(filename), header + r.getDecompiledFunction().getC(), StandardCharsets.UTF_8);
                Map<String,Object> info = functionInfo(f, true); info.put("c_file", filename); selected.add(info);
            }
        } finally { dec.dispose(); }
        return selected;
    }
    @Override public void run() throws Exception {
        String[] args = getScriptArgs();
        req = JsonParser.parseString(Files.readString(Path.of(args[0]))).getAsJsonObject();
        out = Path.of(args[1]); Files.createDirectories(out);
        int tx = -1;
        try {
            String hash = shaBytes();
            if (!hash.equals(text(req, "sha256")) || !hash.equalsIgnoreCase(currentProgram.getExecutableSHA256()))
                throw new Exception("HASH_MISMATCH before mutation: stored=" + hash + ", requested=" + text(req, "sha256"));
            JsonObject ann = req.has("annotations") ? req.getAsJsonObject("annotations") : null;
            if (ann != null && (!hash.equals(text(ann, "sha256")) || ann.get("version").getAsInt() != 1))
                throw new Exception("HASH_MISMATCH or annotation version mismatch before mutation");
            if (ann != null) {
                keys(ann, "version", "sha256", "types", "functions");
                tx = currentProgram.startTransaction("Replay RE annotations");
                apply(ann);
            }
            List<Object> selected = exportC(hash);
            writeJson("selected.json", selected);
            if (req.has("inventory") && req.get("inventory").getAsBoolean()) writeJson("inventory.json", inventory(hash));
            List<Object> types = new ArrayList<>();
            var allTypes = currentProgram.getDataTypeManager().getAllDataTypes();
            while (allTypes.hasNext()) {
                DataType dt = allTypes.next();
                if (dt.getCategoryPath().toString().equals("/shared"))
                    types.add(Map.of("path", dt.getPathName(), "definition", dt.toString(), "length", dt.getLength()));
            }
            writeJson("types.json", types);
            if (tx != -1) { currentProgram.endTransaction(tx, true); tx = -1; }
            writeJson("result.json", Map.of("status", "ok", "sha256", hash, "program", currentProgram.getName()));
        } catch (Exception e) {
            if (tx != -1) currentProgram.endTransaction(tx, false);
            writeJson("result.json", Map.of("status", "error", "error", e.toString(), "annotations_committed", false));
            throw e;
        }
    }
}
