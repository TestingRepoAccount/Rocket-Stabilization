/* Made By Jeremy Hall
 * Credit to Majenko Technologies
 * for some base code
 * 
 * 
 * 
  */
/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

/* Set these to your desired credentials. */
const char *ssid = "ComputerAP";
const char *password = "BobThePineapple";


WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back
char capturedData[255];
unsigned int ClientIP;
int ClientPort;
String Datain = "";
char Dataout[255];
ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
 

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
  Serial.print(myIP);
  Udp.begin(localUdpPort);
  
}

void loop() {
  
  while (Serial.available() > 0) {
  Datain = Serial.readString();
  strcpy(Dataout, Datain.c_str());
  Serial.println(Dataout);
  Udp.beginPacket(ClientIP, ClientPort);
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
    
    ClientIP = Udp.remoteIP();
    ClientPort = Udp.remotePort();
    std::copy(std::begin(incomingPacket), std::end(incomingPacket), std::begin(capturedData));
    Serial.println(capturedData);
  }
}
