#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "smartHome";
const char* password = "12345678";
WebServer server(80);

enum AlarmState { DEACTIVATED, ACTIVATED, TRIGGERED };
AlarmState alarmState = DEACTIVATED;
AlarmState lastState = DEACTIVATED;

String getAlarmStateText() {
    if (alarmState == TRIGGERED) return "triggered";
    if (alarmState == ACTIVATED) return "activated";
    return "deactivated";
}

String generateWebpage() {
    String webpage = "<html><head>";
    webpage += "<style>";
    webpage += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f4; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
    webpage += "h1 { font-size: 2em; padding: 20px; border-radius: 10px; box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.1); transition: background-color 0.3s, transform 0.2s; }";
    webpage += ".alarm-deactivated { background-color: #777; color: white; }";
    webpage += ".alarm-activated { background-color: #4CAF50; color: white; }";
    webpage += ".alarm-triggered { background-color: #FF5733; color: white; animation: pulse 1s infinite alternate; }";
    webpage += "@keyframes pulse { from { transform: scale(1); } to { transform: scale(1.05); } }";
    webpage += "</style>";

    webpage += "<script>";
    webpage += "function checkStatus() {";
    webpage += "  var xhr = new XMLHttpRequest();";
    webpage += "  xhr.onreadystatechange = function() {";
    webpage += "    if (xhr.readyState == 4 && xhr.status == 200) {";
    webpage += "      var response = JSON.parse(xhr.responseText);";
    webpage += "      document.getElementById('status').className = 'alarm-' + response.state;";
    webpage += "      document.getElementById('status').innerHTML = 'Alarm ' + response.state.charAt(0).toUpperCase() + response.state.slice(1);";
    webpage += "    }";
    webpage += "  };";
    webpage += "  xhr.open('GET', '/status', true);";
    webpage += "  xhr.send();";
    webpage += "}";
    webpage += "setInterval(checkStatus, 2000);";
    webpage += "</script>";

    webpage += "</head><body>";
    webpage += "<h1 id='status' class='alarm-" + getAlarmStateText() + "'>Alarm " + getAlarmStateText() + "</h1>";
    webpage += "</body></html>";

    return webpage;
}

void handleRoot() {
    server.send(200, "text/html", generateWebpage());
}

void handleStatus() {
    if (alarmState != lastState) {
        lastState = alarmState;
        String jsonResponse = "{\"state\": \"" + getAlarmStateText() + "\"}";
        server.send(200, "application/json", jsonResponse);
    } else {
        server.send(204, "application/json", "");
    }
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, 16, 17);
    Serial.println("\nStarting...");
    Wire.begin();
    
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    
    server.on("/", handleRoot);
    server.on("/status", handleStatus);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();

    if (Serial2.available()) {
        char command = Serial2.read();
        if (command == '0') {
            alarmState = DEACTIVATED;
            Serial.println("Alarm Deactivated.");
        } else if (command == '1') {
            alarmState = ACTIVATED;
            Serial.println("Alarm Activated.");
        } else if (command == '2') {
            alarmState = TRIGGERED;
            Serial.println("Alarm Triggered!");
        }
    }

    delay(100);
}
