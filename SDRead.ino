
#include <SPI.h>                                                                                                                                                        
#include <SD.h>

File data;
void setup() {
  Serial.begin(57600);
  if(!SD.begin(D11)){
    Serial.println("No SD card found");
    }
  // put your setup code here, to run once:

}

void loop() {
  //need to find the correct port
//   if(!SD.begin(D11)){
  //  Serial.println("No SD card found");
   // }
    //else{
     // Serial.println("I found it");
//      }
  data = SD.open("ArduinoTest.txt" );
  Serial.write(data.read());
  //data.rewindDirectory();
 // data.open("/");
  // put your main code here, to run repeatedly:

}
