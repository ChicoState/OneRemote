
#include <SPI.h>                                                                                                                                                        
#include <SD.h>

File data;
void setup() {
  Serial.begin(57600,SERIAL_8N1, SERIAL_TX_ONLY);
  if(!SD.begin(D11)){
    Serial.println("No SD card found");
    }
    delay(150);
    if(!SD.exists("Newfile.txt")){
      Serial.println("NO print");
      }
      else{
        Serial.println("File found");
        }
    data = SD.open("Newfile.txt" );
  //  File newFile = SD.open("NewFile.txt",FILE_WRITE);
    delay(150);
    /*if(newFile){
      Serial.println("exists");
      }
      else{
       Serial.println("doesn't exist");
        }*/
if(data){
  Serial.println("Print data from ArduinoTest:");
  while(data.available()){
    Serial.write(data.read());
    }
}
else{
  Serial.println("File not Found");
  }
data.close();
  // put your setup code here, to run once:

}

void loop() {
  //need to find the correct port, (Found is D11). 

  

}
