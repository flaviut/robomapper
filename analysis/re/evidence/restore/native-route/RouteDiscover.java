// Read-only discovery on a private baseline copy; never creates instructions/functions.
//@category RE
import ghidra.app.util.headless.HeadlessScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.util.*;
import com.google.gson.*;
public class RouteDiscover extends HeadlessScript {
 public void run() throws Exception {
  List<Object> hits=new ArrayList<>();
  var it=currentProgram.getListing().getInstructions(true);
  while(it.hasNext()) { Instruction i=it.next(); boolean hit=false;
   for(int n=0;n<i.getNumOperands();n++) for(Object o:i.getOpObjects(n)) if(o instanceof Scalar) {
    long v=((Scalar)o).getUnsignedValue();
    if(v==0x3203 || v==0x3204 || v==0x3212 || v==0x2033203 || v==0x2033204 || v==0x2033212) hit=true;
   }
   if(hit) {Function f=getFunctionContaining(i.getAddress()); hits.add(Map.of("address","0x"+i.getAddress(),"instruction",i.toString(),"entry",f==null?"none":"0x"+f.getEntryPoint()));}
  }
  List<Object> names=new ArrayList<>(); var fs=currentProgram.getFunctionManager().getFunctions(true);
  while(fs.hasNext()){Function f=fs.next();String n=f.getName(true); if(n.toLowerCase().matches(".*(ipc|packet|register|dispatch|loadmap|savemap|maphandle).*"))names.add(Map.of("address","0x"+f.getEntryPoint(),"name",n));}
  List<Object> refs=new ArrayList<>();
  for(String a: new String[]{"683e0","304b78","68c24","68e40","6905c","6a180","3c068","3c0e0","3c320","3c444"}) {
   var ri=currentProgram.getReferenceManager().getReferencesTo(toAddr(a));
   while(ri.hasNext()){Reference r=ri.next();Function f=getFunctionContaining(r.getFromAddress());refs.add(Map.of("to",a,"from","0x"+r.getFromAddress(),"type",r.getReferenceType().toString(),"entry",f==null?"none":"0x"+f.getEntryPoint()));}
  }
  List<Object> strings=new ArrayList<>(); var ds=currentProgram.getListing().getDefinedData(true);
  while(ds.hasNext()){Data d=ds.next();Object v=d.getValue();if(!(v instanceof String))continue;String s=(String)v;if(!s.matches("(?is).*(ipc|packet|register.*msg|recv.*msg|dispatch.*msg).*"))continue;
   List<Object> sr=new ArrayList<>();var ri=currentProgram.getReferenceManager().getReferencesTo(d.getAddress());while(ri.hasNext()){Reference r=ri.next();Function f=getFunctionContaining(r.getFromAddress());sr.add(Map.of("from","0x"+r.getFromAddress(),"entry",f==null?"none":"0x"+f.getEntryPoint()));}
   strings.add(Map.of("address","0x"+d.getAddress(),"string",s,"references",sr));}
  Files.writeString(Path.of(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(Map.of("program",currentProgram.getName(),"sha256",currentProgram.getExecutableSHA256(),"constants",hits,"names",names,"references",refs,"strings",strings))+"\n");
 }
}
