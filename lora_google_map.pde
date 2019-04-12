import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;
String str;// Data received from the serial port
void setup()
{
  
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);
}
void draw()
{
  if ( myPort.available() > 0) 
  {  // If data is available,
  val = myPort.readStringUntil('\n');
 
  } 
   println(val); //print it out in the console
if(val!=null && str!=val)
{
 launch(val);
  str=val;
}// read it and store it in val


}
