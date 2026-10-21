// Bounded existing listing only; no disassembly, entry recovery, or metadata mutation.
//@category RE
import ghidra.app.util.headless.HeadlessScript;
import ghidra.program.model.listing.*;
import ghidra.app.util.PseudoDisassembler;
import ghidra.app.util.PseudoDisassemblerContext;
import java.math.BigInteger;
import java.nio.file.*;
import java.util.*;
import com.google.gson.*;
public class RouteBounded extends HeadlessScript {
 public void run() throws Exception {
  List<Object> ranges=new ArrayList<>();
  for(long[] r: new long[][]{{0x18e848,0x18edb3},{0x190908,0x190deb},{0x68398,0x68427},{0x18edb4,0x18f047}}) {
   List<Object> rows=new ArrayList<>(); var it=currentProgram.getListing().getInstructions(toAddr(r[0]),true);
   while(it.hasNext()){Instruction i=it.next();if(i.getAddress().getOffset()>r[1])break;
    StringBuilder b=new StringBuilder();for(byte v:i.getBytes())b.append(String.format("%02x",v&255));
    List<String> flows=new ArrayList<>();for(var a:i.getFlows())flows.add("0x"+a);
    rows.add(Map.of("address","0x"+i.getAddress(),"instruction",i.toString(),"bytes",b.toString(),"flows",flows));
   }
   byte[] raw=getBytes(toAddr(r[0]),(int)(r[1]-r[0]+1));StringBuilder b=new StringBuilder();for(byte v:raw)b.append(String.format("%02x",v&255));
   ranges.add(Map.of("start",String.format("0x%08x",r[0]),"end",String.format("0x%08x",r[1]),"raw_bytes",b.toString(),"instructions",rows));
  }
  List<Object> pseudo=new ArrayList<>();
  var pd=new PseudoDisassembler(currentProgram);
  for(long a=0x683e0;a<0x68420;){var ctx=new PseudoDisassemblerContext(currentProgram.getProgramContext());var i=pd.disassemble(toAddr(a|1),ctx,false);if(i==null)throw new Exception("null pseudo instruction at "+Long.toHexString(a));StringBuilder b=new StringBuilder();for(byte v:i.getBytes())b.append(String.format("%02x",v&255));List<String> flows=new ArrayList<>();for(var f:i.getFlows())flows.add("0x"+f);pseudo.add(Map.of("address",String.format("0x%08x",a),"instruction",i.toString(),"bytes",b.toString(),"flows",flows));a+=i.getLength();}
  Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(Map.of("sha256",currentProgram.getExecutableSHA256(),"ranges",ranges,"pseudo_thumb_linear_not_cfg",pseudo))+"\n");
 }
}
