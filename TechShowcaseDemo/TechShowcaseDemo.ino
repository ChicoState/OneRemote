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
#include <aREST.h>

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

uint16_t power[167] = {1316, 346,  1256, 404,  486, 1188,  1262, 400,  1264, 406,  484, 1196,  488, 1222,  464, 1194,  492, 1192,  494, 1190,  496, 1184,  1318, 6874,  1318, 344,  1258, 402,  486, 1188,  1264, 400,  1254, 414,  486, 1196,  490, 1220,  466, 1192,  494, 1190,  496, 1188,  488, 1194,  1310, 6866,  1314, 348,  1264, 396,  492, 1182,  1258, 404,  1260, 408,  440, 1242,  494, 1188,  486, 1196,  490, 1194,  490, 1192,  492, 1188,  1314, 6878,  1312, 350,  1262, 398,  430, 1244,  1258, 406,  1260, 410,  438, 1244,  494, 1188,  496, 1188,  488, 1196,  490, 1194,  492, 1190,  1260, 6916,  1266, 396,  1258, 402,  436, 1238,  1264, 400,  1256, 414,  432, 1250,  488, 1194,  490, 1194,  492, 1192,  494, 1190,  496, 1186,  1264, 6922,  1258, 402,  1262, 398,  438, 1236,  1256, 406,  1258, 412,  436, 1246,  492, 1190,  494, 1188,  486, 1198,  488, 1196,  490, 1192,  1258, 6970,  1262, 402,  1262, 396,  430, 1244,  1258, 406,  1258, 410,  438, 1244,  492, 1190,  494, 1188,  486, 1196,  488, 1194,  490, 1192,  1258};  // UNKNOWN DD68A539
uint16_t chSpeed[167] = {1312, 348,  1264, 396,  492, 1182,  1310, 352,  1260, 410,  488, 1194,  440, 1242,  434, 1250,  434, 1248,  436, 1244,  1310, 360,  488, 7728,  1312, 348,  1264, 398,  490, 1184,  1318, 346,  1256, 412,  486, 1194,  492, 1192,  442, 1242,  434, 1250,  436, 1246,  1316, 354,  494, 7710,  1320, 342,  1260, 402,  436, 1238,  1316, 346,  1256, 414,  484, 1196,  488, 1194,  440, 1244,  440, 1242,  434, 1248,  1316, 354,  494, 7722,  1318, 342,  1260, 402,  434, 1240,  1314, 348,  1264, 406,  484, 1198,  488, 1196,  490, 1194,  440, 1244,  442, 1240,  1314, 356,  490, 7714,  1314, 346,  1256, 406,  430, 1244,  1310, 352,  1262, 410,  438, 1244,  494, 1188,  496, 1188,  488, 1196,  490, 1192,  1310, 360,  488, 7722,  1318, 344,  1258, 404,  434, 1240,  1314, 348,  1264, 406,  432, 1250,  486, 1196,  490, 1194,  492, 1192,  492, 1188,  1314, 356,  492, 7744,  1318, 342,  1260, 402,  434, 1240,  1314, 348,  1254, 416,  432, 1250,  488, 1194,  492, 1192,  492, 1190,  494, 1188,  1316, 354,  494};  // UNKNOWN F47F7D3
uint16_t osc[143] = {1318, 340,  1262, 400,  490, 1184,  1316, 346,  1258, 412,  488, 1194,  490, 1190,  1312, 356,  490, 1192,  492, 1190,  434, 1250,  436, 7800,  1310, 348,  1316, 344,  492, 1182,  1310, 352,  1262, 408,  492, 1190,  496, 1186,  1316, 352,  494, 1188,  488, 1196,  438, 1246,  440, 7792,  1310, 350,  1314, 346,  492, 1184,  1308, 354,  1260, 410,  490, 1192,  494, 1188,  1314, 354,  492, 1190,  494, 1188,  486, 1196,  438, 7798,  1312, 348,  1308, 352,  484, 1192,  1310, 352,  1262, 408,  492, 1190,  496, 1186,  1316, 354,  494, 1188,  486, 1198,  488, 1194,  490, 7740,  1310, 352,  1262, 400,  490, 1186,  1316, 344,  1258, 410,  436, 1246,  492, 1190,  1312, 356,  490, 1192,  492, 1190,  494, 1188,  486, 7754,  1316, 344,  1258, 404,  486, 1188,  1312, 350,  1264, 406,  430, 1250,  486, 1196,  1316, 352,  486, 1198,  488, 1196,  490, 1194,  490};  // UNKNOWN 4F7BE2FB
uint16_t ionizer[167] = {1318, 342,  1260, 398,  490, 1184,  1308, 352,  1260, 410,  490, 1190,  1314, 354,  494, 1188,  486, 1196,  436, 1246,  440, 1242,  432, 7770,  1310, 348,  1254, 406,  482, 1190,  1312, 350,  1264, 406,  482, 1196,  1318, 350,  486, 1196,  490, 1192,  440, 1242,  434, 1250,  436, 7762,  1320, 340,  1262, 398,  438, 1236,  1308, 352,  1262, 408,  440, 1238,  1316, 352,  484, 1198,  488, 1194,  438, 1244,  440, 1242,  432, 7770,  1312, 346,  1256, 404,  434, 1240,  1312, 348,  1254, 414,  432, 1246,  1308, 360,  488, 1194,  490, 1192,  494, 1188,  434, 1250,  436, 7762,  1310, 350,  1262, 398,  440, 1234,  1310, 352,  1262, 408,  430, 1248,  1316, 352,  484, 1198,  486, 1196,  490, 1194,  492, 1190,  494, 7714,  1316, 344,  1258, 402,  434, 1238,  1316, 346,  1256, 412,  436, 1244,  1310, 358,  490, 1190,  494, 1188,  486, 1196,  488, 1194,  492, 7748,  1310, 350,  1264, 398,  438, 1236,  1318, 344,  1258, 412,  436, 1244,  1310, 360,  488, 1194,  490, 1192,  494, 1190,  494, 1188,  486};  // UNKNOWN 6EA44F22

// Connor's Fan Buttons
uint64_t power_button_fan = 0xC03FD926;
uint64_t dir_change_fan = 0xC03F1BE4;
uint64_t timer_set_fan = 0xC03F09F6;
uint64_t top_left_fan = 0xC03F8976;



// Create aREST instance
aREST rest = aREST();
decode_results results;

// WiFi parameters
const char* ssid = "testRouter";
const char* password = "OneRemote!";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int temperature;
int humidity;

// Declare functions to be exposed to the API
int deviceControl(String command);

void setup(void)
{

	recv.enableIRIn();

	// Start Serial
	irsend.begin();
	Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
	while (!Serial) {
		delay(50);
	}
	// Init variables and expose them to REST API
	temperature = 24;
	humidity = 40;
	rest.variable("temperature", &temperature);
	rest.variable("humidity", &humidity);

	// Function to be exposed
	rest.function("device", deviceControl);

	// Give name & ID to the device (ID should be 6 characters long)
	rest.set_id("1");
	rest.set_name("OneRemote");

	// Connect to WiFi
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");

	// Start the server
	server.begin();
	Serial.println("Server started");

	// Print the IP address
	Serial.println(WiFi.localIP());
}

void loop() {

	// Handle REST calls
	WiFiClient client = server.available();
	if (!client) {
		return;
	}
	while (!client.available()) {
		delay(1);
	}
	rest.handle(client);

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
// Custom function accessible by the API
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
			//Case 1 handles "SEND" to send learned signal
		case 1:
			Serial.println("But Send");
			send_sig();
			delay(400);
		case 2:
			irsend.sendNEC(power_button_fan,32); //Connor's Fan Power
			break;
		case 3:
			irsend.sendNEC(dir_change_fan,32); //Connor's Fan direction change
			break;
		case 4:
			irsend.sendNEC(timer_set_fan,32); //Connor's Fan timer set
			break;
		case 5:
			irsend.sendNEC(top_left_fan,32); //Connor's Fan top left button
			break;
			//Fan Remote section
		case 6:
			irsend.sendRaw(power, 167, 38);  // Send a raw data capture at 38kHz.
			delay(2000);
			break;
		case 7:
			irsend.sendRaw(chSpeed, 167, 38);  // Send a raw data capture at 38kHz.
			break;
		case 8:
			irsend.sendRaw(osc, 143, 38);  // Send a raw data capture at 38kHz.
			break;
		case 9:
			irsend.sendRaw(ionizer, 167, 38);  // Send a raw data capture at 38kHz.
			break;
		default:
			break;
	}
	return 1;
}
