#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "ComputerAP";
const char *password = "BobThePineapple";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back
String ActualServerIP = "192.168.4.1";
int ServerPort = 4211;
char serialIn[255];  // buffer for incoming packets
String Datain = "";
char Dataout[255];
void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.println("Connecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println(" connected");
  Udp.begin(4210);
  //ActualServerIP = WiFi.softAPIP();
  Serial.println("192.168.4.1");
  delay(2000);
  Udp.beginPacket("192.168.4.1", 4211);
  Udp.write("Startup");
  Udp.endPacket();
  Serial.print("sent");
}



void loop()
{
    // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
  Datain = Serial.readString();
  strcpy(Dataout, Datain.c_str());
  Serial.println(Dataout);
  Udp.beginPacket("192.168.4.1", 4211);
  Udp.write(Dataout);
  Udp.endPacket();
}
  
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.println(incomingPacket);
    
    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket("192.168.4.1", 4211);
    Udp.write(incomingPacket);
    Udp.endPacket();
  }
}
