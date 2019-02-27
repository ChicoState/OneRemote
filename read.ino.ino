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
//#include <ir_Vestel.h>
#include <ir_Whirlpool.h>

/**
 *@The reading portion for the arduino . 
 * 
 */
// #include <boarddefs.h>
//#include <IRremote.h>
//#include <IRremoteInt.h>
///#include <ir_Lego_PF_BitStreamEncoder.h>


//#include <IRremote.h>
IRrecv receiver1(11);
IRrecv receiver2(2);
IRrecv receiver3(3);
decode_results res;
int vals[10];
int totSize=0; 
void setup() {
  Serial.begin(57600);
  delay(2000);
  receiver1.enableIRIn();
  Serial.println("Begin reading IR signals");
}

void loop() {
  // runs the current loop to ensure proper ar
  if (receiver1.decode(&res)) {
    int val = res.value;
    if(totSize==10){
        totSize=0;
        }
    vals[totSize]=val;
    totSize++;
    Serial.println(totSize);
    Serial.println(val);

  }
}
