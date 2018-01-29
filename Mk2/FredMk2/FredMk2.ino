#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#define ssid_controller "Controller"
#define ssid_home "Jared's Network"
#define port 150

WiFiUDP UDP;
IPAddress 
control(192, 168, 4, 1),
local(192, 168, 0, 1),
gateway(192, 168, 1, 9),
subnet(255, 255, 255, 0);

void setup() {
  char* priority[2];
  int networks_number = WiFi.scanNetworks();
  
  scan:
  for(int i = 0; i < networks_number; i++){   //Loop to go through the current wireless networks
    if(WiFi.SSID(i) == ssid_controller){      //looking for specific networks. Puts them in 
      i = networks_number;                    //specific places in the priority array that 
      priority[0] = ssid_controller;          //informs the next step.
      return;
    }
    else if(WiFi.SSID(i) == ssid_home){
      i = networks_number;
      priority[1] = ssid_home;
      return;
    }
    else{
      return;
    }
  }

  if(priority[0] == ssid_controller){         //Checks the priority array connecting to the
    Serial.begin(115200);                     //first available in the priority array.
    WiFi.config(local, gateway, subnet);
    WiFi.begin(ssid_controller);
    UDP.begin(port);
    return;
  }
  else if(priority[1] == ssid_home){
    Serial.begin(115200);
    WiFi.config(local, gateway, subnet);
    WiFi.begin(ssid_home);
    UDP.begin(port);
    return;
  }
  else{
    goto scan;                                //Jumps back to rescan the networks, repeats until
    return;                                   //turned off or connected to a specified network.
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
