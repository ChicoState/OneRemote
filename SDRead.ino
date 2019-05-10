
#include <SPI.h>                                                                                                                                                        
#include <SD.h>
#include<device.h>
File data;
void setup() {
  String mainName="";
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
  String x;
  String powerCode=""; 
  Serial.println("Print data from ArduinoTest:");
  while(data.available()){
     char loc;// = data.read();
   // x +=  data.read();
   //  loc = data.read(); 
   Serial.write(loc = data.read());
   //Serial.read();
   if(loc=='\n'){
   char t='\0'; 
    x=t;
    Serial.print(x);
    }
   if(loc!= '-1'){
   x+=loc;
   }
  //Serial.println(x);
  //delay(1000);
    if(x.equals("NAME:")){
      Serial.println("Found\n");
      char reader = ' ';
        while(reader!='#'){
           Serial.write(reader =data.read());
  //          Serial.println(reader);
      //     x+= reader; 
           mainName += reader; 
            }
        }
        if(x.equals("KEYPOWER:")){
         Serial.println("Power Found");
         char reading =' ';
         while(reading!='#'){ 
             Serial.write(reading =data.read());
            x+=reading; 
            powerCode+=reading;
            }
         }
              Serial.print(x);
     }
    
      Serial.print(mainName);
      Serial.println("is\n");
      Serial.print(powerCode); 
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
