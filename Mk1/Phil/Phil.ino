#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

const char* ssid = "Controller";
IPAddress control(192, 168, 4, 1);
IPAddress local(192, 168, 0, 1);
IPAddress gateway(192, 168, 1, 9);
IPAddress subnet(255, 255, 255, 0);
unsigned int port = 100;
unsigned int port2 = 150;

const int Stop = 0;
const int Forward = 1;
const int Backward = 2;
const int Left = 3;
const int Right = 4;
const int leftForward = 5;
const int leftBackward = 6;
const int rightForward = 7;
const int rightBackward = 8;

WiFiUDP udp;
char incomingPacket[255];
char testPacket[] = "testing 123";

void setup() {
  Serial.begin(115200);
  WiFi.config(local, gateway, subnet);
  WiFi.begin(ssid);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);
  udp.begin(port2);

  pinMode(4, OUTPUT);
}

void loop() {
///////////Switch case based on what button is pressed, string to int///////////
  delay(10);
  switch (checkPacket().toInt()) {
    case 12:
      Serial.println(" Left Button");
      digitalWrite(2, LOW);
      moveDirection(Left);
      break;
    case 13:
      Serial.println(" Right Button");
      digitalWrite(2, LOW);
      moveDirection(Right);
      break;
    case 4:
      Serial.println(" Up Button");
      digitalWrite(2, LOW);
      moveDirection(Forward);
      break;
    case 5:
      Serial.println(" Down Button");
      digitalWrite(2, LOW);
      moveDirection(Backward);
      break;
   /* case 6:
      Serial.println(" Left Forward");
      digitalWrite(2, LOW);
      moveDirection(leftForward);
      break;
    case 7:
      Serial.println(" Left Backward");
      digitalWrite(2, LOW);
      moveDirection(leftBackward);
      break;      
    case 8:
      Serial.println(" Right Forward");
      digitalWrite(2, LOW);
      moveDirection(rightForward);
      break;
    case 9:
      Serial.println(" Right Backward");
      digitalWrite(2, LOW);
      moveDirection(rightBackward);
      break;
    */        
    case 0:
      Serial.println(checkPacket());
      digitalWrite(2,HIGH);
      moveDirection(Stop);
      break;
  }

  delay(20);

}

String checkPacket() {
  if (udp.parsePacket() != 0) {
    int len = udp.read(incomingPacket, 255);
    incomingPacket[len] = 0;
    Serial.print(" Packet Recieved ");
    Serial.print(incomingPacket);
    Serial.print(" ");
    Serial.print(WiFi.localIP());
    udp.flush();
    return incomingPacket;
  }
  else {
    return "0";
  }
}

void moveDirection(int direct){
  switch(direct){
    case 1://Forward    
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(14,HIGH);
    digitalWrite(16,LOW);
    break;

    case 2://Backward
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(14,LOW);
    digitalWrite(16,HIGH); 
    break;

    case 3://Left
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(14,LOW);
    digitalWrite(16,HIGH);
    break;

    case 4://Right
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(14,HIGH);
    digitalWrite(16,LOW);
    break;

    case 5://leftForward
    digitalWrite(13,LOW);
    analogWrite(12,120);
    digitalWrite(14,HIGH);
    digitalWrite(16,LOW);
    break;

    case 6://leftBackward
    analogWrite(13,120);
    digitalWrite(12,LOW);
    digitalWrite(14,LOW);
    digitalWrite(16,HIGH);
    break;

    case 7://rightForward
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    analogWrite(14,120);
    digitalWrite(16,LOW);
    break;

    case 8://rightBackward
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(14,LOW);
    analogWrite(16,120);
    break;
    
    case 0://Stop
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(14,LOW);
    digitalWrite(16,LOW);
    break;

  }
}

