#include <Arduino.h>


#include <Valve.hpp>
#include <Regulator.hpp>
#include <Wifi_Module.hpp>



int incomingByte = 0;

Wifi_Module wifi_module;
Valve valve;
Regulator regulator;

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   delay(1000);
//   WiFi.mode(WIFI_STA); //Optional
//   WiFi.begin(ssid, password);
//   Serial.println("\nConnecting");

//   while(WiFi.status() != WL_CONNECTED){
//       Serial.print(".");
//       delay(100);
//   }

//   Serial.println("\nConnected to the WiFi network");
//   Serial.print("Local ESP32 IP: ");
//   Serial.println(WiFi.localIP());
//   Serial.println("-");
  
//   Serial.println("[System Information] Initialization Starting...");
//   delay(1000);
//   valve.Initialization();
//   regulator.Initialization();


// }
void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("[System Information] Initialization Starting...");

  wifi_module.Initialization();

  valve.Initialization();

  regulator.Initialization();
}

int value = 0;

void loop(){
  wifi_module.Loop();
}


// void loop() {
//   Serial.println("[User Information] Enter data:");
//   while (Serial.available() == 0) {}     //wait for data available
//   String teststr = Serial.readString();  //read until timeout
//   teststr.trim();                        // remove any \r \n whitespace at the end of the String
//   if (teststr == "Release") {
//     valve.Release();
//     Serial.println("[System Information]: Transfer to Release Mode.");
//     delay(1000);
//   } else if (teststr == "Shrink")
//   {
//     valve.Shrink();
//     Serial.println("[System Information]: Transfer to Shrink Mode.");
//     delay(1000);
//   }
//   else
//   {
//     int Pressure = teststr.toInt();
//     regulator.Start(Pressure);
//     Serial.print("[System Information]: Set Pressure: ");
//     Serial.print(teststr);
//     Serial.println(" to the Regulator.");
//     delay(1000);
//   }
// }