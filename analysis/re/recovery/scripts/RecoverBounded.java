// Narrow reviewed recovery only. No analysis, clearing, patching or signature changes.
//@category RE
import ghidra.app.util.headless.HeadlessScript;
import ghidra.program.disassemble.Disassembler;
import ghidra.program.database.mem.FileBytes;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.math.BigInteger;
import java.util.*;
import com.google.gson.*;

public class RecoverBounded extends HeadlessScript {
 private final Gson gson=new GsonBuilder().setPrettyPrinting().serializeNulls().create();
 private String hex(byte[] b){return HexFormat.of().formatHex(b);}
 private void need(boolean ok,String message)throws Exception{if(!ok)throw new Exception(message);}
 private String digest(String s)throws Exception{return hex(MessageDigest.getInstance("SHA-256").digest(s.getBytes(java.nio.charset.StandardCharsets.UTF_8)));}
 private String originalHash()throws Exception{
  var files=currentProgram.getMemory().getAllFileBytes();need(files.size()==1 && files.get(0).getFileOffset()==0,"original file mapping");
  FileBytes f=files.get(0);MessageDigest md=MessageDigest.getInstance("SHA-256");byte[] buf=new byte[65536];
  for(long p=0;p<f.getSize();){int n=(int)Math.min(buf.length,f.getSize()-p);need(f.getOriginalBytes(p,buf,0,n)==n,"original read");md.update(buf,0,n);p+=n;}return hex(md.digest());
 }
 private String memoryHash()throws Exception{
  MessageDigest md=MessageDigest.getInstance("SHA-256");byte[] buf=new byte[65536];
  for(MemoryBlock b:currentProgram.getMemory().getBlocks())if(b.isInitialized()){
   md.update((b.getName()+b.getStart()+b.getEnd()).getBytes(java.nio.charset.StandardCharsets.UTF_8));
   for(long p=0;p<b.getSize();){int n=(int)Math.min(buf.length,b.getSize()-p);need(currentProgram.getMemory().getBytes(b.getStart().add(p),buf,0,n)==n,"memory read");md.update(buf,0,n);p+=n;}
  }return hex(md.digest());
 }
 private SortedMap<String,String> functions(){
  SortedMap<String,String> m=new TreeMap<>();var it=currentProgram.getFunctionManager().getFunctions(true);
  while(it.hasNext()){Function f=it.next();m.put(f.getEntryPoint().toString(),f.getName(true)+"|"+f.getSymbol().getSource()+"|"+f.getPrototypeString(false,false)+"|"+f.getSignatureSource()+"|"+f.getBody()+"|"+f.hasNoReturn()+"|"+f.getCallingConventionName()+"|"+f.getComment()+"|"+f.getRepeatableComment()+"|"+currentProgram.getListing().getComment(CommentType.PLATE,f.getEntryPoint()));}return m;
 }
 // Whole-program code/data, context ranges, symbols and references supplement byte/function checks on rejection.
 private String semanticHash()throws Exception{
  StringBuilder s=new StringBuilder(memoryHash()).append(functions());var listing=currentProgram.getListing();
  var ii=listing.getInstructions(true);while(ii.hasNext()){Instruction i=ii.next();s.append(i.getAddress()).append(i).append(hex(i.getBytes())).append(i.getFlowOverride());}
  var di=listing.getDefinedData(true);while(di.hasNext()){Data d=di.next();s.append(d.getAddress()).append(d.getLength()).append(d.getDataType().getPathName());}
  var sy=currentProgram.getSymbolTable().getAllSymbols(true);while(sy.hasNext()){Symbol x=sy.next();s.append(x.getAddress()).append(x.getName(true)).append(x.getSymbolType()).append(x.getSource()).append(x.isPrimary());}
  var rm=currentProgram.getReferenceManager();var rs=rm.getReferenceSourceIterator(currentProgram.getMemory(),true);while(rs.hasNext())for(Reference r:rm.getReferencesFrom(rs.next()))s.append(r);
  var ctx=currentProgram.getProgramContext();for(var reg:ctx.getRegisters()){
   var ranges=ctx.getRegisterValueAddressRanges(reg);while(ranges.hasNext()){var r=ranges.next();s.append(reg.getName()).append(r).append(ctx.getRegisterValue(reg,r.getMinAddress()));}
  }return digest(s.toString());
 }
 private String bytes(Address a,int n)throws Exception{byte[] b=new byte[n];need(currentProgram.getMemory().getBytes(a,b)==n,"entry read");return hex(b);}
 private long num(JsonObject o,String k){return Long.decode(o.get(k).getAsString());}
 private String str(JsonObject o,String k){return o.get(k).getAsString();}
 private Map<String,Object> recover(JsonObject q)throws Exception{
  Set<String> keys=Set.of("version","program","sha256","entry","entry_bytes","bound_end","bound_bytes","expected_context","instructions","unwind","nonreturn_call");
  need(keys.equals(q.keySet()),"request keys");need(q.get("version").getAsInt()==1,"request version");
  String program=currentProgram.getName();need(program.equals(str(q,"program")),"PROGRAM_MISMATCH");
  String hash=originalHash();need(hash.equals(str(q,"sha256")),"HASH_MISMATCH");
  need(currentProgram.getLanguageID().toString().equals("ARM:LE:32:v8") && currentProgram.getCompilerSpec().getCompilerSpecID().toString().equals("default"),"unexpected language/compiler");
  long entry=num(q,"entry"), end=num(q,"bound_end");need((entry&1)==0,"ODD_ENTRY");
  boolean app=program.equals("AppProxy");
  need((app && hash.equals("24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457") && entry==0x3c5b4 && end==0x3c5e9) ||
   (program.equals("WatchDoge") && hash.equals("3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6") && entry==0x1af18 && end==0x1af69),"UNREVIEWED_ENTRY_OR_BOUND");
  Address start=toAddr(entry), stop=toAddr(end);AddressSet bound=new AddressSet(start,stop);
  need(str(q,"expected_context").equals("RegisterValue(contextreg): mask=0xc000000000000000 value=0x0000000000000000"),"unreviewed expected context");
  need(str(q,"entry_bytes").length()==24,"expected twelve entry bytes");
  need(bytes(start,str(q,"entry_bytes").length()/2).equals(str(q,"entry_bytes")),"ENTRY_BYTES_MISMATCH");
  need(bytes(start,(int)(end-entry+1)).equals(str(q,"bound_bytes")),"BOUND_BYTES_MISMATCH");
  var memory=currentProgram.getMemory();var listing=currentProgram.getListing();var fm=currentProgram.getFunctionManager();var ctx=currentProgram.getProgramContext();
  MemoryBlock block=memory.getBlock(start);need(block!=null && block.isExecute() && block.contains(stop),"non-executable/cross-block bound");
  // Check the loader's stored ORIGINAL bytes, not merely current memory at the candidate.
  for(Address a=start;a.compareTo(stop)<=0;a=a.add(1)){
   need(listing.getInstructionContaining(a)==null && listing.getDefinedDataContaining(a)==null,"CODE_OR_DATA_CONFLICT "+a);
   need(fm.getFunctionContaining(a)==null,"FUNCTION_CONFLICT "+a);
   need(str(q,"expected_context").equals(String.valueOf(ctx.getRegisterValue(ctx.getBaseContextRegister(),a))),"CONTEXT_MISMATCH "+a);
   int matches=0;for(var source:block.getSourceInfos()){
    long off=source.getFileBytesOffset(a);if(off>=0 && source.getFileBytes().isPresent()){
     byte[] original=new byte[1];need(source.getFileBytes().get().getOriginalBytes(off,original)==1,"original candidate mapping");
     need(original[0]==memory.getByte(a),"IMPORTED_BYTE_MISMATCH "+a);matches++;
    }
   }need(matches==1,"ambiguous original candidate mapping");
  }
  // Guard the independent EHABI start/next-start evidence against transcription errors.
  JsonObject uw=q.getAsJsonObject("unwind");
  long uwva=app?0x10df28:0x230b0, next=app?0x3c5ec:0x1af6c;
  need(num(uw,"table_va")==uwva && num(uw,"next_entry")==next,"unwind metadata");
  int pre=memory.getInt(toAddr(uwva));long signed=((long)(pre<<1))>>1;
  need(uwva+signed==entry,"unwind start mismatch");
  int nxt=memory.getInt(toAddr(uwva+8));need(uwva+8+(((long)(nxt<<1))>>1)==next,"next unwind mismatch");
  if(app){JsonObject nr=q.getAsJsonObject("nonreturn_call");need(num(nr,"site")==0x3c5e6 && num(nr,"target")==0x182b0 && str(nr,"symbol").equals("__stack_chk_fail"),"nonreturn metadata");Function target=fm.getFunctionAt(toAddr(0x182b0));need(target!=null && target.getName().equals("__stack_chk_fail"),"nonreturn symbol mismatch");}
  else need(q.get("nonreturn_call").isJsonNull(),"unexpected nonreturn");
  SortedMap<String,String> before=functions();String memBefore=memoryHash();
  ctx.setValue(currentProgram.getRegister("TMode"),start,stop,BigInteger.ONE);
  AddressSet discovered=Disassembler.getDisassembler(currentProgram,monitor,null).disassemble(start,bound,true);
  need(discovered!=null && bound.contains(discovered),"disassembler escaped/failed");
  // Walk only the newly discovered reachable CFG; never assign the reviewed bound as the body.
  AddressSet body=new AddressSet();Set<Address> visited=new HashSet<>();Deque<Address> todo=new ArrayDeque<>();todo.add(start);
  while(!todo.isEmpty()){
   Address a=todo.removeFirst();if(!visited.add(a))continue;need(bound.contains(a),"CFG escape "+a);
   Instruction i=listing.getInstructionAt(a);need(i!=null && bound.contains(i.getMinAddress(),i.getMaxAddress()),"missing/truncated instruction "+a);
   body.add(i.getMinAddress(),i.getMaxAddress());var flow=i.getFlowType();
   need(!flow.isComputed() || flow.isTerminal(),"unreviewed computed flow");
   if(!flow.isCall())for(Address target:i.getFlows()){need(bound.contains(target),"external branch");todo.add(target);}
   boolean nonreturn=app && a.equals(toAddr(0x3c5e6));
   if(nonreturn)need(i.getFlows().length==1 && i.getFlows()[0].equals(toAddr(0x182b0)),"nonreturn target");
   Address fall=i.getFallThrough();if(fall!=null && !nonreturn){need(bound.contains(fall),"fallthrough escape "+a);todo.add(fall);}
  }
  need(discovered.equals(body),"disassembled non-body instructions");
  JsonArray expected=q.getAsJsonArray("instructions");need(expected.size()==visited.size(),"instruction count mismatch");
  for(JsonElement e:expected){JsonObject row=e.getAsJsonObject();Address a=toAddr(num(row,"address"));Instruction i=listing.getInstructionAt(a);
   need(visited.remove(a) && i!=null && bytes(a,i.getLength()).equals(str(row,"bytes")) && i.toString().equals(str(row,"instruction")),"instruction mismatch "+a);
  }need(visited.isEmpty(),"unexpected instructions");
  // Preserve any actual primary symbol instead of inventing an original name.
  Symbol symbol=currentProgram.getSymbolTable().getPrimarySymbol(start);
  String name=symbol!=null && symbol.getSource()!=SourceType.DEFAULT?symbol.getName():null;
  Function f=fm.createFunction(name,start,body,symbol!=null && name!=null?symbol.getSource():SourceType.ANALYSIS);
  SortedMap<String,String> after=functions();need(after.remove(start.toString())!=null && before.equals(after),"EXISTING_FUNCTION_CHANGED");
  need(memBefore.equals(memoryHash()) && hash.equals(originalHash()),"BYTE_IDENTITY_FAILURE");
  Map<String,Object> result=new LinkedHashMap<>();result.put("entry","0x"+start);result.put("body",body.toString());result.put("name",f.getName());result.put("signature",f.getPrototypeString(false,false));result.put("plate_comment",listing.getComment(CommentType.PLATE,start));result.put("instruction_count",expected.size());result.put("memory_sha256",memBefore);result.put("original_sha256",hash);result.put("existing_functions_sha256",digest(before.toString()));result.put("no_existing_function_change",true);result.put("byte_identity",true);return result;
 }
 public void run()throws Exception{
  String[] a=getScriptArgs();Path out=Path.of(a[1]);JsonObject q=JsonParser.parseString(Files.readString(Path.of(a[0]))).getAsJsonObject();
  // GhidraScript.start() opens an outer FlatProgramAPI transaction. Close that EMPTY
  // wrapper first: a nested rollback is not visible until its outer transaction ends.
  end(true);
  Map<String,Object> result=new LinkedHashMap<>();String pre=semanticHash();int tx=currentProgram.startTransaction("reviewed bounded recovery");boolean commit=false;
  try{result.putAll(recover(q));commit=true;result.put("status","ok");}
  catch(Exception ex){result.put("status","rejected");result.put("error",ex.toString());}
  finally{currentProgram.endTransaction(tx,commit);}
  result.put("committed",commit);result.put("semantic_before",pre);String post=semanticHash();result.put("semantic_after",post);result.put("rejection_no_semantic_mutation",!commit && pre.equals(post));
  Files.writeString(out,gson.toJson(result)+"\n");
  if(!commit && !pre.equals(post))throw new Exception("ROLLBACK_SEMANTIC_MISMATCH");
 }
}
