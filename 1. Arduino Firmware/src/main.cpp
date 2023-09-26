#include <Arduino.h>

int incomingByte = 0;
// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);

  // pinMode(led, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);

  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);

  pinMode(26, OUTPUT);
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

// void loop() {
//   Serial.println("Enter data:");
//   while (Serial.available() == 0) {}     //wait for data available
//   String teststr = Serial.readString();  //read until timeout
//   teststr.trim();                        // remove any \r \n whitespace at the end of the String
//   if (teststr == "red") {
//     Serial.println("A primary color");
//   } else {
//     Serial.println("Something else");
//   }
// }



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


void loop() {
  // digitalWrite(23, HIGH); // sets the digital pin 13 on
  // digitalWrite(22, LOW); // sets the digital pin 13 on
  // digitalWrite(21, HIGH); // sets the digital pin 13 on
  // digitalWrite(19, HIGH); // sets the digital pin 13 on
  // digitalWrite(18, HIGH); // sets the digital pin 13 on
  // delay(3000);            // waits for a second
  digitalWrite(23, LOW);  // sets the digital pin 13 off
  digitalWrite(22, HIGH);
  digitalWrite(21, HIGH); // sets the digital pin 13 on
  digitalWrite(19, HIGH); // sets the digital pin 13 on
  digitalWrite(18, HIGH); // sets the digital pin 13 on
  delay(3000);            // waits for a second
}

// void loop() {
//   analogWrite(26, 100);
//   delay(1000);
// }

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}