
#include <SPI.h>
#include <SD.h>

File data;
void setup() {
  Serial.begin(57600);
//  if(!SD.begin(4)){
  //  Serial.println("No SD card found");
   // }
  // put your setup code here, to run once:

}

void loop() {
   if(!SD.begin(5)){
    Serial.println("No SD card found");
    }
  data = SD.open("/");
  data.rewindDirectory();
 // data.open("/");
  // put your main code here, to run repeatedly:

}
