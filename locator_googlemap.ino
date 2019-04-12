#include <SPI.h>
#include <LoRa.h>
bool respond=false;
bool flag=false;
bool g=false;
bool f=true;
String beacons;
String beaconNo="";
String latitude="";
  String longitude="";
void setup() {
  Serial.begin(115200);
  SPI.begin();
  while (!Serial);
  Serial.println("LoRa Locator");
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
void sendpacket()
{ if(g==false && f==true)
    {Serial.println("Sending packet to beacon....");
    LoRa.beginPacket();
    LoRa.print("gps");
    LoRa.endPacket();
    
    
    }
    else if(g==true && f==false){
      Serial.println("sending packet to base station");
      String str="loc";
      str+=latitude;
      str+=",";
      str+=longitude;
      str+=",";
      LoRa.beginPacket();
    LoRa.print(str);
    
    LoRa.endPacket();
    g=false;
    
    }
    else{
      Serial.println("not sending any packet");
    }
    flag =true;
    LoRa.receive();
}
void onReceive(int packetSize) {
  
  delayMicroseconds(100);
  Serial.println("received message from beacon : ");
  
  String recPkt = "";
     while (LoRa.available()) {
      recPkt+=(char)LoRa.read();
    
    }
    
    if(recPkt=="Hii")
    {
      //Serial.println( recPkt);
      g==false;
      f=true;}
    else{
      //Serial.println( recPkt);
      beaconNo="";
      int i=0;
      latitude="";
      longitude="";
      
      for(i=0;recPkt.charAt(i)!=',';i++)
      {
        beaconNo+=recPkt.charAt(i);
      }
      i++;
      //Serial.println("line 76");
      for(;recPkt.charAt(i)!=',';i++)
      {
        latitude += recPkt.charAt(i);
      }
      i++;
      //Serial.println("line 82");
      for(;recPkt.charAt(i)!=',';i++)
      {
        longitude += recPkt.charAt(i);
      }
      //Serial.println("line 87");
      for(i=0;i<beacons.length();)
      {
        if(beaconNo.charAt(0)==beacons.charAt(i))
        {
         g=false;
         f=false;
         break;
        }
        //Serial.println("line 95");
        
      }
      if(i==beacons.length())
      {
        g=true;
      f=false;
      //sendpacket();
      beacons+=beaconNo;
      Serial.println("location of beacon :");
      Serial.print("latitude=");
      Serial.println(latitude);
      Serial.print("longitude = ");
      Serial.println(longitude);
      }
     Serial.print("beacons numbers found= ");
      Serial.println(beacons);
      //Serial.println("line 103");
      //String link="https://www.google.com/maps/search/?api=1&query="+latitude+","+longitude;
      //Serial.print(link);
      
      flag=false;
    }
  
  
  respond = true;
}
void loop() {
  //delayMicroseconds(100);
  if (respond) {
    
    sendpacket();
    respond = false;
  }
}
