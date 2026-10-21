// Read-only evidence for the three authorized candidates; never disassembles into the database.
import ghidra.app.script.GhidraScript;
import ghidra.app.util.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.math.BigInteger;
public class InspectCandidates extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();
  Address lo=toAddr(args[1]), hi=toAddr(args[2]);
  try(PrintWriter o=new PrintWriter(args[0])) {
   o.println("program="+currentProgram.getName()+" language="+currentProgram.getLanguageID());
   o.println("block="+currentProgram.getMemory().getBlock(lo));
   o.println("base_context="+currentProgram.getProgramContext().getRegisterValue(currentProgram.getProgramContext().getBaseContextRegister(),toAddr(currentProgram.getName().equals("AppProxy")?0x3c5b4:currentProgram.getName().equals("WatchDoge")?0x1af18:0x20bac0)));
   FunctionIterator bi=currentProgram.getFunctionManager().getFunctions(lo,false), ai=currentProgram.getFunctionManager().getFunctions(hi,true);
   Function before=bi.hasNext()?bi.next():null, after=ai.hasNext()?ai.next():null;
   o.println("before="+before+" body="+(before==null?null:before.getBody()));
   o.println("after="+after+" body="+(after==null?null:after.getBody()));
   for(Address a=lo; a.compareTo(hi)<=0; a=a.add(2)) {
    byte[] b=new byte[2];currentProgram.getMemory().getBytes(a,b);
    o.println(a+" bytes="+java.util.HexFormat.of().formatHex(b)+" context="+currentProgram.getProgramContext().getValue(currentProgram.getRegister("TMode"),a,false)+" ins="+getInstructionAt(a)+" data="+getDataAt(a)+" function="+getFunctionContaining(a));
    for(int k=0;k<2;k++) {
     Address q=a.add(k); var refs=currentProgram.getReferenceManager().getReferencesTo(q);
     while(refs.hasNext())o.println(" IN "+refs.next());
     for(Symbol s:currentProgram.getSymbolTable().getSymbols(q))o.println(" SYMBOL "+s+" source="+s.getSource());
    }
   }
   o.println("PSEUDO THUMB (not database instructions):");
   PseudoDisassembler pd=new PseudoDisassembler(currentProgram);
   PseudoDisassemblerContext ctx=new PseudoDisassemblerContext(currentProgram.getProgramContext());
   Address start=toAddr(currentProgram.getName().equals("AppProxy")?0x3c5b4:currentProgram.getName().equals("WatchDoge")?0x1af18:0x20babc);
   for(Address a=start;a.compareTo(hi)<=0;) {
    try { ctx.setValue(currentProgram.getRegister("TMode"),a,BigInteger.ONE); PseudoInstruction i=pd.disassemble(a,ctx,false); if(i==null)throw new Exception("null decode");
     o.println(a+" "+i+" bytes="+java.util.HexFormat.of().formatHex(i.getBytes())+" flow="+i.getFlowType()+" targets="+java.util.Arrays.toString(i.getFlows())+" fall="+i.getFallThrough());a=a.add(i.getLength());
    }catch(Exception e){o.println(a+" decode error "+e);break;}
   }
  }
 }
}
