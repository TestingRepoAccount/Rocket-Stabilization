#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "ComputerAP";
const char *password = "BobThePineapple";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back
unsigned int ActualServerIP;
int ServerPort = 55420;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  Udp.begin(localUdpPort);  ActualServerIP = WiFi.softAPIP();
  Serial.println(ActualServerIP);
  delay(2000);
  Udp.beginPacket("192.168.1.3", 55420);
  Udp.write("Start");
  Udp.endPacket();

}



void loop()
{
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
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(incomingPacket);
    Udp.endPacket();
  }
}
