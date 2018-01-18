#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

const char* ssid = "Controller";
IPAddress remote(192, 168, 0, 1);
unsigned int port = 100;
unsigned int port2 = 150;

WiFiUDP udp;
char incomingPacket[255];
char leftButton[] = "12";
char rightButton[] = "13";
char upButton[] = "4";
char downButton[] = "5";
char leftForward[] = "6";
char leftBackward[] = "7";
char rightForward[] = "8";
char rightBackward[] = "9";

void setup() {
  Serial.begin(115200);
  udp.begin(port);
  WiFi.softAP(ssid);
  pinMode(2, OUTPUT);
  ////////Button Pins///////
  pinMode(12, INPUT_PULLUP); //Left
  pinMode(13, INPUT_PULLUP); //Right
  pinMode(4, INPUT_PULLUP);  //Up
  pinMode(5, INPUT_PULLUP);  //Down

}
////////Finding and sending button press///////
void loop() {
  switch (buttoncheck()) {
    case 12:
      sendPress(12);
      break;
    case 13:
      sendPress(13);
      break;
    case 4:
      sendPress(4);
      break;
    case 5:
      sendPress(5);
      break;
    case 6:
      sendPress(6);
      break;
    case 7:
      sendPress(7);
      break;
    case 8:
      sendPress(8);
      break;
     case 9:
      sendPress(9);
      break;
    case 0:
      break;
  }
}



//////Function to send information to the reciever///////
void sendPress(int pressed) {
  switch (pressed) {
    case 12:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(leftButton);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }

      switch (udp.endPacket()) {
        case 0:
          Serial.print(" Packet NOT sent!!! ");
          break;                                   ////Ending packet
        case 1:
          Serial.print(" Packet Sent! ");
          Serial.println(remote);
          break;
      }
      break;
    case 13:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(rightButton);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }

      switch (udp.endPacket()) {
        case 0:
          Serial.print(" Packet NOT sent!!! ");
          break;                                   ////Ending packet
        case 1:
          Serial.print(" Packet Sent! ");
          Serial.println(remote);
          break;
      }
      break;
    case 4:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(upButton);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }

      switch (udp.endPacket()) {
        case 0:
          Serial.print(" Packet NOT sent!!! ");
          break;                                   ////Ending packet
        case 1:
          Serial.print(" Packet Sent! ");
          Serial.println(remote);
          break;
      }
      break;
    case 5:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(downButton);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }
    case 6:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(leftForward);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }
    case 7:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(leftBackward);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }
    case 8:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(rightForward);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }
    case 9:
      if (udp.beginPacket(remote, port2) == 1) {
        udp.write(rightBackward);
        delay(10);
      }                                             ////Start packet and write if it starts
      else {
        Serial.print(" Packet not started. ");
        return;
      }


      
      switch (udp.endPacket()) {
        case 0:
          Serial.print(" Packet NOT sent!!! ");
          break;                                   ////Ending packet
        case 1:
          Serial.print(" Packet Sent! ");
          Serial.println(remote);
          break;
      }
      break;
      switch (udp.endPacket()) {
        case 0:
          Serial.print(" Packet NOT sent!!! ");
          break;                                   ////Ending packet
        case 1:
          Serial.print(" Packet Sent! ");
          Serial.println(remote);
          break;
      }
      break;
  }
  delay(10);
  digitalWrite(2, LOW);
  delay(10);                                ////Blinking blue LED to indicate working
  digitalWrite(2, HIGH);
}


///////Checks for button press, only one is registered///////
int buttoncheck() {
 /* if (digitalRead(12) == LOW and digitalRead(4) == LOW) {
    Serial.print("Left Forward");
    return 6;
  }
  else if (digitalRead(12) == LOW and digitalRead(5) == LOW) {
    Serial.print("Left Backward");
    return 7;
  }
  else if (digitalRead(13) == LOW and digitalRead(4) == LOW) {
    Serial.print("Right Forward");
    return 8;
  }
  else if (digitalRead(13) == LOW and digitalRead(5) == LOW) {
    Serial.print("Right Backward");
    return 9;
  }
  */
  if (digitalRead(12) == LOW) {
    Serial.print("Left");
    return 12;
  }
  else if (digitalRead(13) == LOW) {
    Serial.print("Right");
    return 13;
  }
  else if (digitalRead(4) == LOW) {
    Serial.print("Up");
    return 4;
  }
  else if (digitalRead(5) == LOW) {
    Serial.print("Down");
    return 5;
  }
  else {
    return 0;
  }
}

