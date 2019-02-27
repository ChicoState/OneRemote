#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <aREST.h>

#define LISTEN_PORT           80
WiFiServer server(LISTEN_PORT);
void handlePOST();
int ledControl(String command);

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

aREST rest = aREST();

String WiFiSSD = "";
String WiFiPW = "";
String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>OneRemote Setup</title></head><body>"\
                      "<FORM action=\"/\" method=\"post\">"
                      "SSID:<INPUT type=\"text\" name=\"ssidvalue\"><BR>"
                      "Password: <INPUT type=\"password\" name=\"pwvalue\"><BR>"
                      "<INPUT type=\"submit\" value=\"Connect\"></FORM>";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("OneRemote-Setup");

  dnsServer.start(DNS_PORT, "*", apIP);
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
  webServer.on("/", HTTP_POST, handlePOST);
  
}

void handlePOST() {
  if (webServer.args() > 0 ) {
    WiFiSSD = webServer.arg("ssidvalue");
    WiFiPW = webServer.arg("pwvalue");
     WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.begin(WiFiSSD, WiFiPW);
    Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    RESTServer();
  }
}
void RESTServer()
{
}
void loop() {

  dnsServer.processNextRequest();
  webServer.handleClient();
}
