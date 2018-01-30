#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <stdlib.h>

#define ssid_controller "Controller"
#define port 150

WiFiUDP UDP;

void setup() {
 pinMode(2, OUTPUT);
  
 Serial.begin(115200); 
 WiFi.begin(ssid_controller);           //Starts searching for the controller

 while(WiFi.status() != WL_CONNECTED){  //Waits for a connection blinking the blue light
   delay(500);
   digitalWrite(2,HIGH);
   delay(500);
   digitalWrite(2,LOW);
 }
 UDP.begin(port);                       //Connecting to the port
 }



void loop() {
  valueset(16777215);
  delay(2000);



}



unsigned long int readpack(){           //Reads packets and converts them to long int
  char incPack[255];
  if(UDP.parsePacket()){
    int packLength = UDP.read(incPack,255);
    if(packLength > 0){
      incPack[packLength] = 0;
    }
    UDP.flush();
    char test[255] = {1,2,3,4,5};
    unsigned long int temp = atoi(test);   
    return temp;
  }
  else{ 
    return 0;
  }
}

void valueset(unsigned long int temp){    //Bitwise operations to seperate out the button clicks
  unsigned long int x = temp & 0x0003ff;
  unsigned long int y = (temp >> 10) & 0x0003ff;
  unsigned long int left = (temp >> 20) & 0x000001;
  unsigned long int right = (temp >> 21) & 0x000001;
  unsigned long int up = (temp >> 22) & 0x000001;
  unsigned long int down = (temp >> 23) & 0x000001;


}


