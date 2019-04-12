 #include <SPI.h>
#include <LoRa.h>
int i=0;
String latitude="";
String longitude="";
void setup() {
  Serial.begin(115200);
  SPI.begin();
  while (!Serial);
  Serial.println("LoRa base station");
  LoRa.setPins(D8, D0, D1);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // register the receive callback
  LoRa.onReceive(onReceive);
  // put the radio into receive mode
  LoRa.receive();
}
void onReceive(int packetSize) {
  
  delayMicroseconds(100);
  String s="";
  String recPkt = "";
     while (LoRa.available()) {
      recPkt+=(char)LoRa.read();
     }
     for(i=0;i<3;i++)
     {
      s+=recPkt[i];
     }
     if(s=="loc")
     {
      latitude="";
      longitude="";
      //Serial.println("received");
      for(i=3;recPkt.charAt(i)!=',';i++)
      {
        latitude+=recPkt[i];
      }
      i++;
      for(;recPkt.charAt(i)!=',';i++)
      {
        longitude+=recPkt[i];
      }
      String link="start https://www.google.com/maps/search/?api=1^&query="+latitude+","+longitude;
     Serial.println(link);
     }
     else{
      return;
     }
}
void loop()
{
  delay(5000);
}
