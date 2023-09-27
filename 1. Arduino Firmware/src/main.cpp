#include <Arduino.h>

#include <Valve.hpp>
#include <Regulator.hpp>

int incomingByte = 0;

Valve valve;
Regulator regulator;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println("-");
  Serial.println("[System Information] Initialization Starting...");
  delay(1000);
  valve.Initialization();
  regulator.Initialization();
}

// void loop() {
//   // put your main code here, to run repeatedly:
//   if (Serial.available() > 0)
//   {
//     incomingByte = Serial.read();

//     Serial.print("I received: ");
//     Serial.println(incomingByte, DEC);
//   }
// }

void loop() {
  Serial.println("[User Information] Enter data:");
  while (Serial.available() == 0) {}     //wait for data available
  String teststr = Serial.readString();  //read until timeout
  teststr.trim();                        // remove any \r \n whitespace at the end of the String
  if (teststr == "Release") {
    valve.Release();
    Serial.println("[System Information]: Transfer to Release Mode.");
    delay(1000);
  } else if (teststr == "Shrink")
  {
    valve.Shrink();
    Serial.println("[System Information]: Transfer to Shrink Mode.");
    delay(1000);
  }
  else
  {
    int Pressure = teststr.toInt();
    regulator.Start(Pressure);
    Serial.print("[System Information]: Set Pressure: ");
    Serial.print(teststr);
    Serial.println(" to the Regulator.");
    delay(1000);
  }
}



// char myData[30] = {0};
// void loop()
// {
//   byte n = Serial.available();
//   if (n != 0)
//   {
//     byte m = Serial.readBytesUntil('\n', myData, 30);
//     myData[m] = '\0'; //null-byte
 
//     float y1 = atof(strtok(myData, ","));
//     Serial.print("float y1 = "); Serial.println(y1, 2);

//     float y2 = atof(strtok(NULL, ","));
//     Serial.print("float y2 = "); Serial.println(y2, 2);

//     float y3 = atof(strtok(NULL, ","));
//     Serial.print("float y3 = "); Serial.println(y1, 2);
//   }
// }


// void loop() {
//   // digitalWrite(23, HIGH); // sets the digital pin 13 on
//   // digitalWrite(22, LOW); // sets the digital pin 13 on
//   // digitalWrite(21, HIGH); // sets the digital pin 13 on
//   // digitalWrite(19, HIGH); // sets the digital pin 13 on
//   // digitalWrite(18, HIGH); // sets the digital pin 13 on
//   // delay(3000);            // waits for a second
//   digitalWrite(23, LOW);  // sets the digital pin 13 off
//   digitalWrite(22, HIGH);
//   digitalWrite(21, HIGH); // sets the digital pin 13 on
//   digitalWrite(19, HIGH); // sets the digital pin 13 on
//   digitalWrite(18, HIGH); // sets the digital pin 13 on
//   delay(3000);            // waits for a second
// }