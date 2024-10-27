#include <WiFi.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h> 

const char* ssid = "Nothing";       
const char* password = "124dgsls";  

AsyncWebServer server(80);

const int pinA = 2;
const int pinB = 33;
const int pinC = 34;
const int pinD = 35;
const int pinE = 25;
const int pinF = 21;
const int pinG = 22;
const int pinH = 23;
const int pinI = 25;

int location = 0;

void handleCommand(String command) {
    if (command == "A"){
      digitalWrite(pinA, HIGH);

    }
    else if (command == "B") digitalWrite(pinA, LOW);
    else if (command == "C") digitalWrite(pinC, HIGH);
    else if (command == "D") digitalWrite(pinD, HIGH);
    else if (command == "E") digitalWrite(pinE, HIGH);
    else if (command == "F") digitalWrite(pinF, HIGH);
    else if (command == "G") digitalWrite(pinG, HIGH);
    else if (command == "H") digitalWrite(pinH, HIGH);
    else if (command == "I") digitalWrite(pinI, HIGH);

}


void setup() {
    Serial.begin(115200);
    pinMode(13,INPUT);

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(pinE, OUTPUT);
    pinMode(pinF, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinH, OUTPUT);
    pinMode(pinI, OUTPUT);

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html"); 
    });

    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/styles.css", "text/css"); 
    });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/script.js", "application/javascript");
    });

    server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("command")) {
            String command = request->getParam("command")->value();
            handleCommand(command);
            request->send(200, "text/plain", "Command received: " + command);
        } else {
            request->send(400, "text/plain", "Missing command parameter");
        }
    });

    server.on("/set-value", HTTP_POST, [](AsyncWebServerRequest *request){
        int params = request->params();
        for(int i = 0; i < params; i++){
            AsyncWebParameter* p = request->getParam(i);
            if (p->name() == "value") {
                int value = p->value().toInt();
                Serial.printf("Value received: %d\n", value);
                request->send(200, "text/plain", "Value set: " + String(value));
            }
        }
    });

    server.on("/toggle-mode", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("mode")) {
            String mode = request->getParam("mode")->value();
            Serial.printf("Mode changed to: %s\n", mode.c_str());
            request->send(200, "text/plain", "Mode changed to: " + mode);
        } else {
            request->send(400, "text/plain", "Missing mode parameter");
        }
    });



    server.on("/get-location", HTTP_GET, [](AsyncWebServerRequest *request){
        String response = String(location);
        request->send(200, "text/plain", response);
    });

    server.begin();
    Serial.println("Server started");
}

void loop() {
  if(digitalRead(13)== 1){
    location = location + 1;
  }
  
}
