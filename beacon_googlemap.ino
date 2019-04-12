#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
boolean flag=false;
String beaconNo="1";
String str="";
static const int RXPin = D4, TXPin = D3; //RX TX of nodemcu
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
void sendpacket()
{ 
  Serial.println("Sending packet to locator");
  if(flag == false)
  {
    
    LoRa.beginPacket();
    LoRa.print("Hii");
    LoRa.endPacket();
    
  }
  else{
    
    Serial.println("Sending location to locator....");
   /* bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  if(newData)
  { str=beaconNo;
    str+=",";
    str+=String(gps.location.lat(),6);
    str+=",";
    str+=String(gps.location.lng(),6);
    str+=",";
    LoRa.beginPacket();
    LoRa.print(str);
    LoRa.endPacket();
  }
    */
    flag=false;
  
 String str=beaconNo;
 str+=",";
  str+="28.6653";
  str+=",";
  str+="77.2324";
  str+=",";
  //Serial.println(str);
  LoRa.beginPacket();
  LoRa.print(str);
  LoRa.endPacket();
 
  }
  LoRa.receive();
  
}
void onReceive(int packetSize){
  delayMicroseconds(100);
   String str1 = "";
   while (LoRa.available()) {
      str1+=(char)LoRa.read();
    
    }
    Serial.println("received message from locator : ");
    //Serial.println(str1);
    if(str1=="gps")
    {flag=true;}
    else{
      flag=false;
    }
}
void setup() {
  Serial.begin(115200);
  SPI.begin();
  ss.begin(GPSBaud);
  while (!Serial);

  Serial.println("LoRa Beacon");
  LoRa.setPins(D8,D2,D1);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.onReceive(onReceive);
   LoRa.receive();
   
}
void loop() {
  sendpacket();
  delay(5000);
  
 
}
