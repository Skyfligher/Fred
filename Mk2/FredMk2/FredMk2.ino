#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

const char* ssid_controller = "Controller";
const char* ssid_home = "Jared's Network";
cosnt char* ssid_main;

WiFiUDP UDP;
IPAddress control(192, 168, 4, 1);
IPAddress local(192, 168, 0, 1);
IPAddress gateway(192, 168, 1, 9);
IPAddress subnet(255, 255, 255, 0);
const unsigned int port = 150;

void setup() {
  int networks_number = WiFi.scanNetworks();

  for(int i = 0; i < networks_number; i++){
    if(WiFi.SSID(i) == ssid_controller){
      ssid_main = ssid_controller;
      i = networks_number;
      return;
    }
    else if(WiFi.SSID(i) == ssid_home){
      ssid_main = ssid_home;
      i = networks_number;
      return;
    }
    else{
      return;
    }
  }

  Serial.begin(115200);
  WiFi.config(local, gateway, subnet);
  WiFi.begin(ssid_main);
  UDP.begin(port);

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
