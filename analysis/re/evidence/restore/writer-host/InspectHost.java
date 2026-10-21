// Read-only bounded instruction decoding. Does not create instructions or functions.
import ghidra.app.script.GhidraScript;
import ghidra.app.util.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import java.math.BigInteger;
import java.nio.file.*;
import java.util.*;
import com.google.gson.*;

public class InspectHost extends GhidraScript {
 public void run() throws Exception {
  if (!currentProgram.getExecutableSHA256().equals("020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125")) throw new Exception("HASH_MISMATCH");
  List<Object> rows = new ArrayList<>();
  PseudoDisassembler pd = new PseudoDisassembler(currentProgram);
  PseudoDisassemblerContext ctx = new PseudoDisassemblerContext(currentProgram.getProgramContext());
  for (Address a=toAddr(0x18314); a.compareTo(toAddr(0x18446))<=0;) {
   ctx.setValue(currentProgram.getRegister("TMode"),a,BigInteger.ONE);
   PseudoInstruction i=pd.disassemble(a,ctx,false);
   if(i==null) throw new Exception("DECODE_FAILED "+a);
   List<String> flows=new ArrayList<>(); for(Address f:i.getFlows()) flows.add("0x"+f);
   rows.add(Map.of("address","0x"+a,"instruction",i.toString(),"bytes",HexFormat.of().formatHex(i.getBytes()),"flows",flows));
   a=a.add(i.getLength());
  }
  Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(Map.of(
   "program",currentProgram.getName(),"sha256",currentProgram.getExecutableSHA256(),
   "scope","Pseudo Thumb decoding of original-ELF EHABI start 0x18314 through next start 0x18448; linear bytes may include literal data; NOT a recovered function or CFG proof",
   "instructions",rows))+"\n");
 }
}
