#include <Wifi_Module.hpp>

// WiFiServer server(80);
AsyncWebServer server(80);

Wifi_Module::Wifi_Module(/* args */)
{
    ssid = "ESP32_Pro_Network";
    password = "12342234";
}

Wifi_Module::~Wifi_Module()
{
}
const char* PARAM_INPUT_1 = "state1";
const char* PARAM_INPUT_2 = "state2";
const char* PARAM_INPUT_3 = "state3";
const char* PARAM_INPUT_4 = "state4";
const char* PARAM_INPUT_5 = "state5";
const char* PARAM_INPUT_6 = "input1";
const char* PARAM_FLOAT1 = "inputFloat1";
const char* PARAM_FLOAT2 = "inputFloat2";
const char* PARAM_FLOAT3 = "inputFloat3";

const int output1 = 5;
const int output2 = 33;
const int output3 = 27;
const int output4 = 13;


const int Valve1 = 23;
const int Valve2 = 21;
const int Valve3 = 18;
const int Valve4 = 17;

const int output6 = 2;

// Variables will change:
int State1 = LOW;          // the current state of the output pin
int State2 = LOW;          // the current state of the output pin
int State3 = LOW;   
int State4 = LOW;   
int State5 = LOW;   

String inputMessage;
String inputDelay1;
String inputDelay2;
String inputDelay3;

String outputState1(){ if(digitalRead(output1)){return "checked";} else { return ""; } return ""; }
String outputState2(){ if(digitalRead(output2)){return "checked";} else { return ""; } return ""; }
String outputState3(){ if(digitalRead(output3)){return "checked";} else { return ""; } return ""; }
String outputState4(){ if(digitalRead(output4)){return "checked";} else { return ""; } return ""; }
// String outputState5(){ if(digitalRead(output5)){return "checked";} else { return ""; } return ""; }

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
    if(var == "BUTTONPLACEHOLDER1"){
        String buttons ="";
        String outputStateValue = outputState1();
        buttons+= "<h4>LED: State <span id=\"outputState1\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox1(this)\" id=\"output1\" " + outputStateValue + "><span class=\"slider\"></span></label>";
        return buttons;
    }
    else if(var == "BUTTONPLACEHOLDER2"){
        String buttons ="";
        String outputStateValue = outputState2();
        buttons+= "<h4>Positive(On)/Negative(Off) SWITCH <span id=\"outputState2\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox2(this)\" id=\"output2\" " + outputStateValue + "><span class=\"slider\"></span></label>";
        return buttons;
    }
    else if(var == "BUTTONPLACEHOLDER3"){
        String buttons ="";
        String outputStateValue = outputState3();
        buttons+= "<h4>Release(On) and Shrink(On) SWITCH <span id=\"outputState3\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox3(this)\" id=\"output3\" " + outputStateValue + "><span class=\"slider\"></span></label>";
        return buttons;
    }
    else if(var == "inputFloat1"){
        return readFile(SPIFFS, "/inputFloat1.txt");
    }    
    else if(var == "inputFloat2"){
        return readFile(SPIFFS, "/inputFloat2.txt");
    }
    else if(var == "inputFloat3"){
        return readFile(SPIFFS, "/inputFloat3.txt");
    }
    // else if(var == "BUTTONPLACEHOLDER4"){
    //     String buttons ="";
    //     String outputStateValue = outputState4();
    //     buttons+= "<h4>Output - VALVE3: GPIO 17 - State <span id=\"outputState4\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox4(this)\" id=\"output4\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    //     return buttons;
    // }
    // else if(var == "BUTTONPLACEHOLDER5"){
    //     String buttons ="";
    //     String outputStateValue = outputState3();
    //     buttons+= "<h4>Output - VALVE4: GPIO 4 - State <span id=\"outputState5\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox5(this)\" id=\"output5\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    //     return buttons;
    // }
    return String();
}



void Wifi_Module::Initialization()
{
    pinMode(output1, OUTPUT);
    pinMode(output2, OUTPUT);
    pinMode(output3, OUTPUT);
    pinMode(output4, OUTPUT);
    pinMode(output6, OUTPUT);
    pinMode(Valve1, OUTPUT);
    pinMode(Valve2, OUTPUT);
    pinMode(Valve3, OUTPUT);
    pinMode(Valve4, OUTPUT);

    // pinMode(output5, OUTPUT);

    digitalWrite(output1, State1);
    digitalWrite(output2, State2);
    digitalWrite(output3, State3);
    digitalWrite(output4, State4);



    // digitalWrite(output5, State5);

    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html, processor);
    });
    server.on("/brlsnu", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/1.png", "image/png");
    });
    server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
        
        String inputParam;
        // GET input1 value on <ESP_IP>/update?state=<inputMessage>
        if (request->hasParam(PARAM_INPUT_1)) {
            inputMessage = request->getParam(PARAM_INPUT_1)->value();
            inputParam = PARAM_INPUT_1;
            digitalWrite(output1, inputMessage.toInt());
            State1 = !State1;
            request->send(200, "text/plain", "OK");
        }
        else if (request->hasParam(PARAM_INPUT_2)) {
            inputMessage = request->getParam(PARAM_INPUT_2)->value();
            inputParam = PARAM_INPUT_2;
            digitalWrite(output2, inputMessage.toInt());
            State2 = !State2;
            request->send(200, "text/plain", "OK");
        }
        else if (request->hasParam(PARAM_INPUT_3)) {
            inputMessage = request->getParam(PARAM_INPUT_3)->value();
            inputParam = PARAM_INPUT_3;
            digitalWrite(output3, inputMessage.toInt());
            State3 = !State3;
            request->send(200, "text/plain", "OK");
        }
        else if (request->hasParam(PARAM_INPUT_4)) {
            inputMessage = request->getParam(PARAM_INPUT_4)->value();
            inputParam = PARAM_INPUT_4;
            digitalWrite(output4, inputMessage.toInt());
            State4 = !State4;
            request->send(200, "text/plain", "OK");
        }
        // else if (request->hasParam(PARAM_INPUT_5)) {
        //     inputMessage = request->getParam(PARAM_INPUT_5)->value();
        //     inputParam = PARAM_INPUT_5;
        //     digitalWrite(output5, inputMessage.toInt());
        //     State5 = !State5;
        // }
        else if (request->hasParam(PARAM_INPUT_6)) {
            inputMessage = request->getParam(PARAM_INPUT_6)->value();
            inputParam = PARAM_INPUT_6;
            request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                        + inputParam + ") with value: " + inputMessage +
                                        "<br><a href=\"/\">Return to Home Page</a>");
        }
        else if (request->hasParam(PARAM_FLOAT1)) {
            inputDelay1 = request->getParam(PARAM_FLOAT1)->value();
            inputParam = PARAM_FLOAT1;
            writeFile(SPIFFS, "/inputFloat1.txt", inputDelay1.c_str());
            request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputDelay1 +
                                     "<br><a href=\"/\">Return to Home Page</a>");
        }
        else if (request->hasParam(PARAM_FLOAT2)) {
            inputDelay2 = request->getParam(PARAM_FLOAT2)->value();
            inputParam = PARAM_FLOAT2;
            writeFile(SPIFFS, "/inputFloat2.txt", inputDelay2.c_str());
            request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputDelay2 +
                                     "<br><a href=\"/\">Return to Home Page</a>");
        }
        else if (request->hasParam(PARAM_FLOAT3)) {
            inputDelay3 = request->getParam(PARAM_FLOAT3)->value();
            inputParam = PARAM_FLOAT3;
            writeFile(SPIFFS, "/inputFloat3.txt", inputDelay3.c_str());
            request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputDelay3 +
                                     "<br><a href=\"/\">Return to Home Page</a>");
        }
        else {
        inputMessage = "No message sent";
        inputParam = "none";
        }
        // Serial.println(inputMessage);

        // request->send(200, "text/plain", "OK");


    });

    // Send a GET request to <ESP_IP>/state

    server.on("/state1", HTTP_GET, [] (AsyncWebServerRequest *request) { request->send(200, "text/plain", String(!digitalRead(output1)).c_str());});
    server.on("/state2", HTTP_GET, [] (AsyncWebServerRequest *request) { request->send(200, "text/plain", String(!digitalRead(output2)).c_str()); });
    server.on("/state3", HTTP_GET, [] (AsyncWebServerRequest *request) { request->send(200, "text/plain", String(!digitalRead(output3)).c_str()); });
    server.on("/state4", HTTP_GET, [] (AsyncWebServerRequest *request) { request->send(200, "text/plain", String(!digitalRead(output4)).c_str()); });
    // server.on("/state5", HTTP_GET, [] (AsyncWebServerRequest *request) { request->send(200, "text/plain", String(!digitalRead(output5)).c_str()); });
  
  // Start server
  server.begin();
}

void Wifi_Module::Loop()
{
    // set the LED:
    digitalWrite(output1, State1);
    digitalWrite(output2, State2);
    digitalWrite(output3, State3);
    digitalWrite(output4, State4);
//   digitalWrite(output5, State5);

    if(State2)
    {
        digitalWrite(Valve1, HIGH);
    }
    else
    {
        digitalWrite(Valve1, LOW);
    }
    if(State3)
    {
        inputDelay1 =  readFile(SPIFFS, "/inputFloat1.txt");
        inputDelay2 =  readFile(SPIFFS, "/inputFloat2.txt");
        inputDelay3 =  readFile(SPIFFS, "/inputFloat3.txt");
        delay(1000*inputDelay1.toInt());
        digitalWrite(Valve2, HIGH);
        delay(1000*inputDelay2.toInt());
        digitalWrite(Valve3, HIGH);
        delay(1000*inputDelay3.toInt());
        digitalWrite(Valve4, HIGH);
    }
    else
    {
        digitalWrite(Valve2, LOW);
        digitalWrite(Valve3, LOW);
        digitalWrite(Valve4, LOW);
    }

    int pressure = (100 - inputMessage.toInt())*255/100;
    analogWrite(output6, pressure);
    delay(100);
}