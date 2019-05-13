#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRtimer.h>
#include <IRutils.h>
#include <ir_Argo.h>
#include <ir_Coolix.h>
#include <ir_Daikin.h>
#include <ir_Fujitsu.h>
#include <ir_Gree.h>
#include <ir_Haier.h>
#include <ir_Hitachi.h>
#include <ir_Kelvinator.h>
#include <ir_LG.h>
#include <ir_Magiquest.h>
#include <ir_Midea.h>
#include <ir_Mitsubishi.h>
#include <ir_NEC.h>
#include <ir_Panasonic.h>
#include <ir_Samsung.h>
#include <ir_Toshiba.h>
#include <ir_Trotec.h>
#include <ir_Vestel.h>
#include <ir_Whirlpool.h>
#include <device.h>
#include <rooms.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <aREST.h>

#define LISTEN_PORT           80
WiFiServer server(LISTEN_PORT);
void handlePOST();
int deviceControl(String command);

Dlist connector;

const uint16_t ButtonPin1 = 13; //white
const uint16_t ButtonPin2 = 12; //red
const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
IRrecv recv(14);

int ButtonState1 = 0;
int ButtonState2 = 0;
void send_sig();
void recv_sig();


uint16_t power[135] = {4562, 4502,  578, 1680,  574, 1684,  572, 1686,  578, 578,  550, 580,  546, 582,  544, 584,  554, 576,  550, 1680,  574, 1682,  572, 1684,  580, 576,  552, 578,  550, 580,  546, 584,  544, 584,  552, 576,  552, 1678,  574, 582,  546, 584,  544, 584,  552, 576,  550, 578,  548, 580,  546, 1686,  570, 586,  552, 1678,  576, 1682,  572, 1684,  572, 1686,  578, 1678,  576, 1682,  572, 47172,  4566, 4496,  572, 1686,  578, 1678,  576, 1682,  574, 582,  546, 584,  542, 586,  550, 578,  550, 580,  548, 1684,  570, 1686,  580, 1678,  576, 580,  548, 582,  546, 584,  554, 576,  550, 578,  548, 580,  546, 1684,  580, 576,  550, 578,  548, 580,  546, 582,  544, 584,  552, 576,  550, 1682,  574, 582,  544, 1686,  580, 1678,  576, 1680,  574, 1684,  570, 1688,  578, 1680,  576};  // SAMSUNG E0E040BF
uint16_t source[135] = {4566, 4496,  572, 1684,  580, 1676,  578, 1680,  574, 580,  546, 582,  544, 584,  552, 576,  550, 578,  548, 1682,  572, 1684,  580, 1678,  578, 578,  548, 580,  546, 584,  544, 584,  552, 576,  550, 1680,  574, 582,  546, 584,  544, 586,  550, 578,  548, 580,  546, 582,  544, 584,  552, 576,  550, 1680,  574, 1682,  572, 1686,  580, 1678,  576, 1680,  574, 1682,  572, 1684,  570, 47168,  4566, 4496,  572, 1684,  570, 1686,  578, 1678,  576, 580,  546, 580,  546, 584,  542, 586,  552, 576,  550, 1678,  576, 1680,  574, 1682,  572, 584,  544, 586,  552, 576,  550, 578,  548, 580,  546, 1682,  572, 584,  552, 576,  552, 578,  550, 578,  548, 580,  546, 582,  544, 586,  552, 576,  552, 1678,  576, 1682,  572, 1684,  572, 1686,  580, 1678,  576, 1680,  574, 1682,  574};  // SAMSUNG E0E0807F
uint16_t volUp[135] = {4568, 4494,  576, 1680,  574, 1684,  572, 1686,  578, 550,  578, 552,  574, 554,  574, 554,  572, 558,  580, 1678,  578, 1680,  574, 1682,  572, 556,  570, 558,  578, 550,  578, 552,  574, 554,  574, 1682,  572, 1686,  578, 1678,  576, 554,  574, 554,  572, 556,  570, 558,  580, 550,  576, 552,  576, 554,  574, 556,  570, 1686,  578, 1678,  576, 1682,  574, 1682,  572, 1684,  580, 47160,  4564, 4498,  570, 1686,  580, 1678,  576, 1680,  574, 554,  572, 556,  570, 558,  580, 550,  578, 550,  576, 1680,  574, 1682,  572, 1686,  580, 548,  578, 550,  576, 552,  574, 554,  574, 556,  572, 1686,  578, 1678,  576, 1680,  574, 554,  574, 556,  570, 558,  580, 550,  578, 550,  576, 552,  574, 554,  572, 556,  570, 1686,  580, 1678,  576, 1680,  574, 1682,  572, 1684,  570};  // SAMSUNG E0E0E01F
uint16_t volDown[67] = {4570, 4492,  576, 1680,  574, 1682,  572, 1686,  578, 550,  578, 552,  576, 552,  574, 554,  572, 558,  570, 1686,  578, 1678,  576, 1682,  574, 554,  572, 558,  580, 548,  578, 550,  576, 552,  574, 1682,  572, 1684,  570, 558,  578, 1678,  576, 552,  576, 552,  572, 556,  570, 558,  578, 550,  578, 552,  578, 1680,  572, 556,  572, 1686,  578, 1678,  576, 1680,  574, 1682,  572};  // SAMSUNG E0E0D02F
uint16_t chUp[135] = {4490, 4496,  572, 1686,  578, 1680,  574, 1686,  580, 550,  578, 552,  574, 556,  570, 560,  578, 552,  574, 1684,  580, 1680,  576, 1684,  570, 558,  578, 552,  574, 554,  574, 556,  580, 552,  576, 554,  572, 1688,  578, 552,  574, 554,  572, 1686,  578, 552,  574, 556,  572, 558,  578, 1680,  574, 556,  572, 1688,  578, 1680,  574, 556,  570, 1688,  576, 1682,  574, 1686,  578, 47168,  4504, 4500,  578, 1680,  574, 1684,  570, 1688,  576, 552,  574, 556,  572, 558,  578, 552,  576, 554,  572, 1686,  578, 1682,  572, 1686,  580, 552,  576, 552,  574, 556,  570, 558,  578, 552,  576, 554,  572, 1688,  578, 552,  574, 556,  572, 1688,  576, 554,  572, 556,  570, 558,  578, 1680,  574, 556,  572, 1688,  576, 1682,  574, 556,  570, 1688,  576, 1682,  572, 1686,  580};  // SAMSUNG E0E048B7
uint16_t chDown[67] = {4496, 4506,  572, 1686,  580, 1678,  576, 1682,  572, 558,  580, 550,  578, 552,  574, 556,  580, 550,  576, 1682,  572, 1686,  578, 1680,  574, 556,  572, 558,  578, 552,  576, 554,  572, 558,  578, 550,  576, 554,  572, 558,  580, 550,  578, 1682,  572, 558,  580, 552,  576, 554,  574, 1686,  578, 1680,  574, 1684,  580, 1678,  576, 554,  572, 1686,  578, 1680,  574, 1684,  580};  // SAMSUNG E0E008F7
uint16_t returnButton[67] = {4490, 4504,  574, 1684,  570, 1688,  576, 1682,  574, 556,  570, 560,  578, 552,  574, 554,  572, 558,  580, 1680,  574, 1684,  580, 1678,  576, 552,  574, 556,  570, 560,  576, 552,  574, 556,  570, 558,  580, 550,  576, 554,  572, 1686,  578, 1680,  574, 556,  570, 1688,  576, 552,  574, 1684,  580, 1678,  576, 1682,  572, 558,  580, 550,  576, 1684,  572, 556,  580, 1678,  576};  // SAMSUNG E0E01AE5
uint16_t mute[135] = {4486, 4498,  580, 1678,  578, 1682,  572, 1686,  578, 550,  576, 554,  572, 558,  580, 550,  576, 554,  572, 1688,  578, 1680,  574, 1686,  580, 550,  576, 554,  572, 558,  580, 550,  576, 554,  572, 558,  580, 1680,  576, 554,  572, 1690,  576, 1682,  572, 556,  572, 558,  578, 552,  574, 1686,  580, 550,  578, 1682,  572, 558,  580, 550,  576, 1682,  572, 1688,  576, 1682,  572, 47180,  4480, 4504,  576, 1682,  572, 1688,  576, 1682,  572, 558,  580, 548,  578, 552,  574, 556,  586, 544,  578, 1682,  572, 1686,  578, 1680,  574, 556,  570, 560,  578, 552,  576, 554,  572, 558,  578, 550,  576, 1684,  572, 558,  578, 1680,  574, 1684,  580, 550,  578, 552,  574, 556,  570, 1690,  576, 552,  574, 1686,  578, 550,  576, 554,  572, 1686,  580, 1680,  574, 1684,  570};  // SAMSUNG E0E058A7
uint16_t homeButton[135] = {4490, 4496,  572, 1686,  578, 1680,  574, 1684,  570, 558,  578, 552,  576, 554,  572, 558,  578, 552,  576, 1684,  570, 1688,  578, 1682,  572, 556,  570, 560,  578, 552,  574, 556,  572, 558,  578, 1680,  574, 1686,  580, 1678,  576, 1684,  570, 558,  578, 550,  576, 554,  572, 558,  580, 550,  576, 552,  574, 556,  570, 560,  578, 1682,  574, 1684,  580, 1680,  576, 1684,  570, 47172,  4478, 4500,  578, 1680,  574, 1684,  572, 1686,  578, 552,  576, 554,  572, 558,  580, 552,  574, 554,  572, 1686,  578, 1680,  574, 1684,  570, 558,  578, 552,  576, 554,  572, 558,  578, 550,  576, 1682,  572, 1686,  578, 1680,  574, 1684,  580, 550,  578, 552,  574, 554,  572, 558,  578, 552,  576, 554,  574, 556,  580, 550,  576, 1682,  574, 1686,  580, 1678,  574, 1684,  572};  // SAMSUNG E0E0F00F
uint16_t up[135] = {4566, 4498,  570, 1686,  578, 1678,  576, 1680,  574, 554,  574, 556,  572, 558,  580, 548,  578, 550,  576, 1680,  574, 1682,  572, 1684,  570, 558,  578, 550,  576, 552,  574, 556,  570, 556,  572, 558,  580, 550,  578, 550,  576, 552,  574, 554,  572, 1684,  570, 1686,  580, 550,  576, 1680,  574, 1682,  574, 1684,  570, 1686,  578, 1678,  578, 552,  574, 554,  574, 1684,  572, 47172,  4568, 4494,  574, 1682,  572, 1684,  570, 1686,  578, 550,  578, 552,  574, 554,  574, 554,  572, 558,  580, 1678,  576, 1682,  572, 1682,  574, 556,  572, 556,  580, 548,  578, 550,  576, 552,  574, 554,  572, 556,  570, 558,  580, 550,  578, 552,  574, 1682,  572, 1686,  580, 550,  578, 1678,  576, 1680,  574, 1684,  572, 1684,  580, 1678,  578, 552,  576, 552,  574, 1684,  572};  // SAMSUNG E0E006F9
uint16_t left[135] = {4564, 4498,  572, 1684,  580, 1676,  578, 1678,  576, 552,  574, 554,  574, 554,  572, 558,  580, 548,  578, 1678,  576, 1680,  576, 1682,  572, 556,  570, 558,  580, 548,  578, 552,  576, 552,  574, 1684,  570, 558,  570, 1686,  578, 550,  576, 552,  574, 1682,  572, 1684,  570, 558,  578, 550,  578, 1680,  576, 554,  572, 1684,  572, 1686,  580, 548,  578, 550,  576, 1680,  574, 47164,  4564, 4496,  572, 1684,  580, 1676,  578, 1678,  576, 552,  574, 554,  574, 556,  572, 558,  580, 548,  578, 1680,  576, 1680,  574, 1684,  572, 558,  568, 560,  578, 550,  576, 552,  576, 554,  574, 1682,  572, 556,  570, 1686,  578, 550,  576, 552,  574, 1682,  572, 1684,  580, 548,  578, 550,  576, 1682,  574, 556,  572, 1684,  570, 1686,  578, 550,  576, 552,  574, 1682,  572};  // SAMSUNG E0E0A659
uint16_t right[135] = {4560, 4500,  578, 1678,  578, 1680,  574, 1684,  572, 558,  570, 558,  578, 550,  576, 552,  574, 556,  572, 1684,  580, 1676,  578, 1680,  576, 552,  574, 554,  572, 558,  570, 560,  578, 550,  576, 552,  576, 1680,  572, 556,  570, 558,  578, 550,  576, 1680,  574, 1684,  572, 556,  582, 1676,  578, 552,  576, 1682,  572, 1684,  572, 1686,  578, 550,  576, 552,  574, 1682,  574, 47170,  4570, 4492,  576, 1680,  574, 1682,  572, 1686,  570, 558,  578, 550,  578, 552,  576, 554,  572, 556,  572, 1686,  580, 1678,  576, 1680,  576, 554,  574, 556,  570, 558,  580, 550,  576, 552,  574, 556,  572, 1684,  580, 550,  576, 552,  574, 554,  572, 1684,  570, 1686,  578, 550,  576, 1680,  576, 554,  574, 1682,  572, 1684,  580, 1676,  578, 550,  576, 552,  574, 1682,  574};  // SAMSUNG E0E046B9
uint16_t down[67] = {4568, 4492,  576, 1680,  574, 1682,  572, 1684,  570, 558,  578, 572,  556, 552,  574, 554,  572, 556,  570, 1684,  580, 1676,  578, 1678,  576, 554,  572, 556,  572, 558,  570, 558,  578, 550,  576, 1680,  574, 554,  572, 556,  570, 558,  580, 550,  578, 1680,  576, 1680,  574, 554,  572, 558,  570, 1686,  578, 1678,  576, 1680,  574, 1682,  572, 556,  570, 558,  578, 1678,  578};  // SAMSUNG E0E08679
uint16_t fanPower[167] = {1316, 346,  1256, 404,  486, 1188,  1262, 400,  1264, 406,  484, 1196,  488, 1222,  464, 1194,  492, 1192,  494, 1190,  496, 1184,  1318, 6874,  1318, 344,  1258, 402,  486, 1188,  1264, 400,  1254, 414,  486, 1196,  490, 1220,  466, 1192,  494, 1190,  496, 1188,  488, 1194,  1310, 6866,  1314, 348,  1264, 396,  492, 1182,  1258, 404,  1260, 408,  440, 1242,  494, 1188,  486, 1196,  490, 1194,  490, 1192,  492, 1188,  1314, 6878,  1312, 350,  1262, 398,  430, 1244,  1258, 406,  1260, 410,  438, 1244,  494, 1188,  496, 1188,  488, 1196,  490, 1194,  492, 1190,  1260, 6916,  1266, 396,  1258, 402,  436, 1238,  1264, 400,  1256, 414,  432, 1250,  488, 1194,  490, 1194,  492, 1192,  494, 1190,  496, 1186,  1264, 6922,  1258, 402,  1262, 398,  438, 1236,  1256, 406,  1258, 412,  436, 1246,  492, 1190,  494, 1188,  486, 1198,  488, 1196,  490, 1192,  1258, 6970,  1262, 402,  1262, 396,  430, 1244,  1258, 406,  1258, 410,  438, 1244,  492, 1190,  494, 1188,  486, 1196,  488, 1194,  490, 1192,  1258};  // UNKNOWN DD68A539
uint16_t chSpeed[167] = {1312, 348,  1264, 396,  492, 1182,  1310, 352,  1260, 410,  488, 1194,  440, 1242,  434, 1250,  434, 1248,  436, 1244,  1310, 360,  488, 7728,  1312, 348,  1264, 398,  490, 1184,  1318, 346,  1256, 412,  486, 1194,  492, 1192,  442, 1242,  434, 1250,  436, 1246,  1316, 354,  494, 7710,  1320, 342,  1260, 402,  436, 1238,  1316, 346,  1256, 414,  484, 1196,  488, 1194,  440, 1244,  440, 1242,  434, 1248,  1316, 354,  494, 7722,  1318, 342,  1260, 402,  434, 1240,  1314, 348,  1264, 406,  484, 1198,  488, 1196,  490, 1194,  440, 1244,  442, 1240,  1314, 356,  490, 7714,  1314, 346,  1256, 406,  430, 1244,  1310, 352,  1262, 410,  438, 1244,  494, 1188,  496, 1188,  488, 1196,  490, 1192,  1310, 360,  488, 7722,  1318, 344,  1258, 404,  434, 1240,  1314, 348,  1264, 406,  432, 1250,  486, 1196,  490, 1194,  492, 1192,  492, 1188,  1314, 356,  492, 7744,  1318, 342,  1260, 402,  434, 1240,  1314, 348,  1254, 416,  432, 1250,  488, 1194,  492, 1192,  492, 1190,  494, 1188,  1316, 354,  494};  // UNKNOWN F47F7D3
uint16_t osc[143] = {1318, 340,  1262, 400,  490, 1184,  1316, 346,  1258, 412,  488, 1194,  490, 1190,  1312, 356,  490, 1192,  492, 1190,  434, 1250,  436, 7800,  1310, 348,  1316, 344,  492, 1182,  1310, 352,  1262, 408,  492, 1190,  496, 1186,  1316, 352,  494, 1188,  488, 1196,  438, 1246,  440, 7792,  1310, 350,  1314, 346,  492, 1184,  1308, 354,  1260, 410,  490, 1192,  494, 1188,  1314, 354,  492, 1190,  494, 1188,  486, 1196,  438, 7798,  1312, 348,  1308, 352,  484, 1192,  1310, 352,  1262, 408,  492, 1190,  496, 1186,  1316, 354,  494, 1188,  486, 1198,  488, 1194,  490, 7740,  1310, 352,  1262, 400,  490, 1186,  1316, 344,  1258, 410,  436, 1246,  492, 1190,  1312, 356,  490, 1192,  492, 1190,  494, 1188,  486, 7754,  1316, 344,  1258, 404,  486, 1188,  1312, 350,  1264, 406,  430, 1250,  486, 1196,  1316, 352,  486, 1198,  488, 1196,  490, 1194,  490};  // UNKNOWN 4F7BE2FB
uint16_t ionizer[167] = {1318, 342,  1260, 398,  490, 1184,  1308, 352,  1260, 410,  490, 1190,  1314, 354,  494, 1188,  486, 1196,  436, 1246,  440, 1242,  432, 7770,  1310, 348,  1254, 406,  482, 1190,  1312, 350,  1264, 406,  482, 1196,  1318, 350,  486, 1196,  490, 1192,  440, 1242,  434, 1250,  436, 7762,  1320, 340,  1262, 398,  438, 1236,  1308, 352,  1262, 408,  440, 1238,  1316, 352,  484, 1198,  488, 1194,  438, 1244,  440, 1242,  432, 7770,  1312, 346,  1256, 404,  434, 1240,  1312, 348,  1254, 414,  432, 1246,  1308, 360,  488, 1194,  490, 1192,  494, 1188,  434, 1250,  436, 7762,  1310, 350,  1262, 398,  440, 1234,  1310, 352,  1262, 408,  430, 1248,  1316, 352,  484, 1198,  486, 1196,  490, 1194,  492, 1190,  494, 7714,  1316, 344,  1258, 402,  434, 1238,  1316, 346,  1256, 412,  436, 1244,  1310, 358,  490, 1190,  494, 1188,  486, 1196,  488, 1194,  492, 7748,  1310, 350,  1264, 398,  438, 1236,  1318, 344,  1258, 412,  436, 1244,  1310, 360,  488, 1194,  490, 1192,  494, 1190,  494, 1188,  486};  // UNKNOWN 6EA44F22



aREST rest = aREST();
decode_results results;

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
  recv.enableIRIn();

  // Start Serial
  irsend.begin();
  Serial.begin(115200);
  rest.function("device",deviceControl);
  rest.set_id("1");
  rest.set_name("OneRemote");
  
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
void send_sig()
{
  uint64_t data = results.value;
  uint64_t nbits = results.bits;
  serialPrintUint64(results.value, HEX);
  Serial.println("");
  switch (results.decode_type) {
    case NEC:
    case NEC_LIKE:
      {
        Serial.println("NEC");
        irsend.sendNEC(data, nbits);
        break;
      }
    case SONY:
      {
        Serial.println("SONY");
        irsend.sendSony(data, nbits, 2);
        break;
      }
    case AIWA_RC_T501:
      {
        Serial.println("AIWA_RC_T501");
        irsend.sendAiwaRCT501(data, nbits);
        break;
      }
    case CARRIER_AC:
      {
        Serial.println("CARRIER_AC");
        irsend.sendCarrierAC(data, nbits);
        break;
      }
    case COOLIX:
      Serial.println("COOLIX");
      irsend.sendCOOLIX(data, nbits);
      break;
    case DENON:
      Serial.println("DENON");
      irsend.sendDenon(data, nbits);
      break;
    case DISH:
      Serial.println("DISH");
      irsend.sendDISH(data, nbits, 3);
      break;
    case GICABLE:
      Serial.println("GICABLE");
      irsend.sendGICable(data, nbits);
      break;
    case GREE:
      Serial.println("GREE");
      irsend.sendGree(data, nbits);
      break;
    case JVC:
      Serial.println("JVC");
      irsend.sendJVC(data, nbits);
      break;
    case LASERTAG:
      Serial.println("LASERTAG");
      irsend.sendLasertag(data, nbits);
      break;
    case LG:
      Serial.println("LG");
      irsend.sendLG(data, nbits);
      break;
    case LG2:
      Serial.println("LG2");
      irsend.sendLG2(data, nbits);
      break;
    case LUTRON:
      Serial.println("LUTRON");
      irsend.sendLutron(data, nbits);
      break;
    case MAGIQUEST:
      Serial.println("MAGIQUEST");
      irsend.sendMagiQuest(data, nbits);
      break;
    case MIDEA:
      Serial.println("MIDEA");
      irsend.sendMidea(data, nbits);
      break;
    case MITSUBISHI:
      Serial.println("MITSUBISHI");
      irsend.sendMitsubishi(data, nbits);
      break;
    case MITSUBISHI2:
      Serial.println("MITSUBISHI2");
      irsend.sendMitsubishi2(data, nbits);
      delay(650);
      irsend.sendMitsubishi2(data, nbits);
      break;
    case NIKAI:
      Serial.println("NIKAI");
      irsend.sendNikai(data, nbits);
      break;
    case PANASONIC:
      Serial.println("PANASONIC");
      irsend.sendPanasonic64(data, nbits);
      break;
    case PIONEER:
      Serial.println("PIONEER");
      irsend.sendPioneer(data, nbits);
      break;
    case RC5:
      Serial.println("RC5");
      irsend.sendRC5(data, nbits);
      break;
    case RC6:
      Serial.println("RC6");
      irsend.sendRC6(data, nbits);
      break;
    case RCMM:
      Serial.println("RCMM");
      irsend.sendRCMM(data, nbits);
      break;
    case SAMSUNG:
      Serial.println("SAMSUNG");
      irsend.sendSAMSUNG(data, nbits);
      break;
      /*
         case SAMSUNG36:
         Serial.println("SAMSUNG36");
         irsend.sendSamsung36(data, nbits);
         break;
       */
    case SANYO_LC7461:
      Serial.println("SANYO_LC7461");
      irsend.sendSanyoLC7461(data, nbits);
      break;
    case SHARP:
      Serial.println("SHARP");
      irsend.sendSharpRaw(irsend.encodeSharp(results.address, results.command), nbits);
      break;
    case SHERWOOD:
      Serial.println("SHERWOOD");
      irsend.sendSherwood(data, nbits, 1);
      break;
      /*
         case TECO:
         Serial.println("TECO");
         irsend.sendTeco(data, nbits);
         break;
       */
    case VESTEL_AC:
      Serial.println("VESTEL_AC");
      irsend.sendVestelAC(data, nbits);
      break;
    case WHYNTER:
      Serial.println("WHYNTER");
      irsend.sendWhynter(data, nbits);
      break;
    default:
      Serial.println("Unknown signal");
      break;

  }
}
int deviceControl(String command) {
  switch (command.toInt()) {
    //Case 0 handles "LEARN" from IR
    case 0:
      Serial.println("But Read");
      recv.resume();
      while (!(recv.decode(&results))) {
        delay(100);
      }
      serialPrintUint64(results.value, HEX);
      Serial.println("");
      delay(400);
      break;
      
    case 1:
      Serial.println("But Send");
      send_sig();
      delay(400);
      break;
      
    case 2:
      irsend.sendRaw(power, 135, 38);  // Send a raw data capture at 38kHz.
      break;
      
    case 3:
      irsend.sendRaw(source, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 4:
      irsend.sendRaw(volUp, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 5:
      irsend.sendRaw(volDown, 67, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 6:
      irsend.sendRaw(chUp, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 7:
      irsend.sendRaw(chDown, 67, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 8:
      irsend.sendRaw(returnButton, 67, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 9:
      irsend.sendRaw(mute, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 10:
      irsend.sendRaw(homeButton, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 11: //up
      irsend.sendRaw(up, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 12: //left
      irsend.sendRaw(left, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 13: //right
      irsend.sendRaw(right, 135, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 14: //down
      irsend.sendRaw(down, 67, 38);  // Send a raw data capture at 38kHz.
     break;
     
    case 15:
      irsend.sendRaw(fanPower, 167, 38);  // Send a raw data capture at 38kHz.
      delay(2000);
      break;
      
    case 16:
      irsend.sendRaw(chSpeed, 167, 38);  // Send a raw data capture at 38kHz.
      break;

    case 17:
      irsend.sendRaw(osc, 143, 38);  // Send a raw data capture at 38kHz.
      break;
      
    case 18:
      irsend.sendRaw(ionizer, 167, 38);  // Send a raw data capture at 38kHz.
      break;
      
    default:
      break;
  }
  return 1;
}
