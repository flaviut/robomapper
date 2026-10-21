// Read-only discovery: named map-flow strings and their referencing functions.
//@category RE
import ghidra.app.util.headless.HeadlessScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.util.*;
import com.google.gson.*;

public class FlowDiscover extends HeadlessScript {
 public void run() throws Exception {
  List<Object> rows = new ArrayList<>();
  var data = currentProgram.getListing().getDefinedData(true);
  while (data.hasNext()) {
   Data d = data.next(); Object value = d.getValue();
   if (!(value instanceof String)) continue;
   String s = (String)value;
   if (!(s.contains("RequestNavToLoadMap") || s.contains("LoadMapResponseLoop") ||
         s.contains("RequestNavToSaveMap") || s.contains("MapHandleResult") ||
         s.contains("MapsHandleResult") || s.contains("WaitNavLoadMap"))) continue;
   List<Object> refs = new ArrayList<>();
   var ri = currentProgram.getReferenceManager().getReferencesTo(d.getAddress());
   while (ri.hasNext()) {
    Reference r = ri.next(); Function f = getFunctionContaining(r.getFromAddress());
    refs.add(Map.of("from", "0x"+r.getFromAddress(), "type", r.getReferenceType().toString(),
     "entry", f == null ? "none" : "0x"+f.getEntryPoint(), "function", f == null ? "none" : f.getName(true)));
   }
   rows.add(Map.of("address", "0x"+d.getAddress(), "string", s, "references", refs));
  }
  List<Object> constants = new ArrayList<>();
  var ii = currentProgram.getListing().getInstructions(true);
  while (ii.hasNext()) {
   Instruction i = ii.next(); String s = i.toString();
   if (!(s.contains("0x3204") || s.contains("0x3203") || s.contains("0x3212") ||
         s.contains("0x2106") || s.contains("0x2107") || s.contains("0x2128"))) continue;
   Function f = getFunctionContaining(i.getAddress());
   constants.add(Map.of("address", "0x"+i.getAddress(), "instruction", s,
     "entry", f == null ? "none" : "0x"+f.getEntryPoint()));
  }
  Files.writeString(Path.of(getScriptArgs()[0]), new GsonBuilder().setPrettyPrinting().create().toJson(
    Map.of("program", currentProgram.getName(), "sha256", currentProgram.getExecutableSHA256(), "strings", rows, "constants", constants))+"\n");
 }
}
