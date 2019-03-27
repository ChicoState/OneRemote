
/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

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

Dlist connector;

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const uint16_t recvButtonPin = 13;
const uint16_t sendButtonPin = 16;
const uint16_t redPin = 12;

IRrecv recv(14);
decode_results results;
uint64_t stored_sig;
int recvButtonState = 0;
int sendButtonState = 0;
int rune = 0;
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
void send_sig();
void recv_sig();

void setup() {
  pinMode(recvButtonPin, INPUT);
  pinMode(sendButtonPin,INPUT);
  pinMode(redPin,OUTPUT);
  irsend.begin();
  recv.enableIRIn();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  while(!Serial) {
    delay(50);
  }
}

void loop() {
  recvButtonState = digitalRead(recvButtonPin);
  sendButtonState = digitalRead(sendButtonPin);
  if(recvButtonState == LOW) 
  {
    //connector.addDevice("Fan");
    recv_sig();
   
  }
  if(sendButtonState == LOW)
  {
    send_sig("Fan","Power");
    //send_sig();
  }

}

void recv_sig()
{
  digitalWrite(redPin,HIGH);
  while(!(recv.decode(&results))) {
    delay(100);
  }
  connector.addDevice("Fan",&results);
  connector.findDevice("Fan")->add_button("Power",results);
  digitalWrite(redPin,LOW);
  serialPrintUint64(results.value,HEX);
  Serial.println("");
  recv.resume();
}


void send_sig(char* dname,char* bname)
{
  Device* temp = connector.findDevice(dname);
  //decode_results res = *(temp->findButton(bname));
  decode_results res = temp->findButton(bname);
  uint64_t data = res.value;
  uint64_t nbits = res.bits;
  Serial.println(temp->get_name());
  /*
void send_sig()
{
  uint64_t data = results.value;
  uint64_t nbits = results.bits;
  */
  switch(res.decode_type) {
    case NEC:
    case NEC_LIKE:
    {
      Serial.println("NEC");
      irsend.sendNEC(data,nbits);
      break;
    }
    case SONY:
    {
      Serial.println("SONY");
      irsend.sendSony(data,nbits,2);
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
      irsend.sendDISH(data, nbits,3);
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
      irsend.sendSharpRaw(irsend.encodeSharp(results.address,results.command), nbits);
      break;
    case SHERWOOD:
      Serial.println("SHERWOOD");
      irsend.sendSherwood(data, nbits,1);
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
  delay(650);


}
