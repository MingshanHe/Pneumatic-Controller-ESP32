#ifndef WIFI_MODULE_HPP
#define WIFI_MODULE_HPP


#include <Arduino.h>
#include <Configuration.hpp>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
    <h2>Pressure Controller Web Server</h2>
    <h4>Designed by BioRobotics Laboratory, Seoul National University</h4>
    


    <form action="/update">
        Pressure Input(0~100): <input type="text" name="input1">
        <input type="submit" value="Submit">
    </form><br>

   %BUTTONPLACEHOLDER1%
    <script>function toggleCheckbox1(element) {
    var xhr = new XMLHttpRequest();
    if(element.checked){ xhr.open("GET", "/update?state1=1", true); }
    else { xhr.open("GET", "/update?state1=0", true); }
    xhr.send();
    }
    setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        var inputChecked;
        var outputStateM;
        if( this.responseText == 1){ 
            inputChecked = false;
            outputStateM = "Off";
        }
        else { 
            inputChecked = true;
            outputStateM = "On";
        }
        document.getElementById("output1").checked = inputChecked;
        document.getElementById("outputState1").innerHTML = outputStateM;
        }
    };
    xhttp.open("GET", "/state1", true);
    xhttp.send();
    }, 1000 ) ;
    </script>



    %BUTTONPLACEHOLDER2%
    <script>function toggleCheckbox2(element) {
    var xhr = new XMLHttpRequest();
    if(element.checked){ xhr.open("GET", "/update?state2=1", true); }
    else { xhr.open("GET", "/update?state2=0", true); }
    xhr.send();
    }
    setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        var inputChecked;
        var outputStateM;
        if( this.responseText == 1){ 
            inputChecked = false;
            outputStateM = "Off";
        }
        else { 
            inputChecked = true;
            outputStateM = "On";
        }
        document.getElementById("output2").checked = inputChecked;
        document.getElementById("outputState2").innerHTML = outputStateM;
        }
    };
    xhttp.open("GET", "/state2", true);
    xhttp.send();
    }, 1000 ) ;
    </script>

    %BUTTONPLACEHOLDER3%
    <script>function toggleCheckbox3(element) {
    var xhr = new XMLHttpRequest();
    if(element.checked){ xhr.open("GET", "/update?state3=1", true); }
    else { xhr.open("GET", "/update?state3=0", true); }
    xhr.send();
    }
    setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        var inputChecked;
        var outputStateM;
        if( this.responseText == 1){ 
            inputChecked = false;
            outputStateM = "Off";
        }
        else { 
            inputChecked = true;
            outputStateM = "On";
        }
        document.getElementById("output3").checked = inputChecked;
        document.getElementById("outputState3").innerHTML = outputStateM;
        }
    };
    xhttp.open("GET", "/state3", true);
    xhttp.send();
    }, 1000 ) ;
    </script>

    %BUTTONPLACEHOLDER4%
    <script>function toggleCheckbox4(element) {
    var xhr = new XMLHttpRequest();
    if(element.checked){ xhr.open("GET", "/update?state4=1", true); }
    else { xhr.open("GET", "/update?state4=0", true); }
    xhr.send();
    }
    setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        var inputChecked;
        var outputStateM;
        if( this.responseText == 1){ 
            inputChecked = false;
            outputStateM = "Off";
        }
        else { 
            inputChecked = true;
            outputStateM = "On";
        }
        document.getElementById("output4").checked = inputChecked;
        document.getElementById("outputState4").innerHTML = outputStateM;
        }
    };
    xhttp.open("GET", "/state4", true);
    xhttp.send();
    }, 1000 ) ;
    </script>




    

    <h2><b> SETTING </b></h2>

    <br>
    <form action="/update" target="hidden-form">
        Delay01 (value: %inputFloat1%): <input type="number " name="inputFloat1">
        <input type="submit" value="Submit" onclick="submitMessage()">
    </form>
    <br>
    <form action="/update" target="hidden-form">
        Delay12 (value: %inputFloat2%): <input type="number " name="inputFloat2">
        <input type="submit" value="Submit" onclick="submitMessage()">
    </form>
    <br>
    <form action="/update" target="hidden-form">
        Delay23 (value: %inputFloat3%): <input type="number " name="inputFloat3">
        <input type="submit" value="Submit" onclick="submitMessage()">
    </form>
    <br>
    
    <img src="brlsnu" width="250">
</body>
</html>
)rawliteral";







class Wifi_Module
{
private:
    /* data */
    const char* ssid;
    const char* password;
public:
    Wifi_Module(/* args */);
    ~Wifi_Module();
    void Initialization();
    void Loop();
};
#endif

    // %BUTTONPLACEHOLDER5%
    // <script>function toggleCheckbox5(element) {
    // var xhr = new XMLHttpRequest();
    // if(element.checked){ xhr.open("GET", "/update?state5=1", true); }
    // else { xhr.open("GET", "/update?state5=0", true); }
    // xhr.send();
    // }
    // setInterval(function ( ) {
    // var xhttp = new XMLHttpRequest();
    // xhttp.onreadystatechange = function() {
    //     if (this.readyState == 4 && this.status == 200) {
    //     var inputChecked;
    //     var outputStateM;
    //     if( this.responseText == 1){ 
    //         inputChecked = false;
    //         outputStateM = "Off";
    //     }
    //     else { 
    //         inputChecked = true;
    //         outputStateM = "On";
    //     }
    //     document.getElementById("output5").checked = inputChecked;
    //     document.getElementById("outputState5").innerHTML = outputStateM;
    //     }
    // };
    // xhttp.open("GET", "/state5", true);
    // xhttp.send();
    // }, 1000 ) ;
    // </script>