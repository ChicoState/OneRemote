#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <aREST.h>

#define LISTEN_PORT           80
WiFiServer server(LISTEN_PORT);
void handlePOST();
int ledControl(String command);
aREST rest = aREST();

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);


String WiFiSSD = "";
String WiFiPW = "";
String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>OneRemote Setup</title></head><body>"\
                      "<FORM action=\"/\" method=\"post\">"
                      "SSID:<INPUT type=\"text\" name=\"ssidvalue\"><BR>"
                      "Password: <INPUT type=\"password\" name=\"pwvalue\"><BR>"
                      "<INPUT type=\"submit\" value=\"Connect\"></FORM>";
int settingUp = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  rest.function("led",ledControl);
  rest.set_id("1");
  rest.set_name("esp8266");
  
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
    webServer.close();
    webServer.stop();
    RESTServer();
  }
}
void RESTServer()
{
  settingUp = 1;
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}
void loop() {

  if(settingUp == 0)
  {
    dnsServer.processNextRequest();
    webServer.handleClient();
  }
  else
  {
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
    while(!client.available()){
      delay(1);
    }
    rest.handle(client);
  }

}
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(LED_BUILTIN,state);
  return 1;
}
