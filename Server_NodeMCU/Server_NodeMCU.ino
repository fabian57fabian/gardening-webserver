#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>
#define MAX_TIME_WATER 15000
#define MIN_TIME_WATER 2000
#define MIN_DELAY_TIME_BETWEEN_BACKETS 500

int pinRelay = D0;
int LEDPin = D2;
int pinWaterSensor = A0;

bool watering = false;
long last_time_watering;


//Local variable for received time to water
int received_time_water = 1000;
// Replace with your network credentials
const char* ssid_hotspot = "ssid";
const char* password_hotspot = "password";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";

bool print_for_debug = true;

void setup(void) {
  if (print_for_debug) {
    Serial.begin(115200);
  }

  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);

  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, HIGH);

  pinMode(pinWaterSensor, INPUT);

  WiFi.begin(ssid_hotspot, password_hotspot); //begin WiFi connection
  print_this("");

  Serial.println("Try with selected ssid ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    print_this(".");
  }
  server.on("/gardening", manage_gardening_request);
  server.begin();
  print_this("Web server started!");
  blink_led();
  last_time_watering = millis();
}

void loop(void) {
  server.handleClient();
}

void send_errorAnswer(String error) {
  print_this(error);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(400, "application/json", "{\"result\": \"ERROR\", \"status\": \"" + error + "\"}");
  return;
}

void printargs() {
  if (print_for_debug) {
    String message = "Number of args received: " + String(server.args());
    for (int i = 0; i < server.args(); i++) {
      message += "\nArg nº" + (String)i + " – > ";
      message += server.argName(i) + ": ";
      message += server.arg(i) + "";
    }
    print_this(message);
  }
}
void manage_gardening_request() {
  printargs();
  if (!server.hasArg("plain")) {
    send_errorAnswer("No plain received");
    return;
  }
  DynamicJsonBuffer JSONBuffer;
  JsonObject&  root = JSONBuffer.parseObject(server.arg("plain"));
  if (!root.success()) {
    send_errorAnswer("Malformed json received");
    return;
  }
  if (!root.containsKey("action")) {
    send_errorAnswer("No action received");
    return;
  }
  String action = root["action"];
  if (action == "annaffia") {
    if (watering) {
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "json", "{\"result\":\"WARNING\",\"status\":\"Already watering\"}");
      return;
    }
    if (millis() - last_time_watering < MIN_DELAY_TIME_BETWEEN_BACKETS) {
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "json", "{\"result\":\"WARNING\",\"status\":\"Slow down watering so fast :D\"}");
      return;
    }
    if (!root.containsKey("time")) {
      send_errorAnswer("No time received");
      return;
    } else {
      received_time_water = root["time"];
      if (received_time_water > MAX_TIME_WATER) {
        print_this(String(received_time_water) + " > " + String(MAX_TIME_WATER));
        received_time_water = MAX_TIME_WATER;
      }
      if (received_time_water < MIN_TIME_WATER) {
        print_this(String(received_time_water) + " < " + String(MIN_TIME_WATER));
        received_time_water = MIN_TIME_WATER;
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "json", "{\"result\":\"OK\",\"status\":\"watering for " + String(received_time_water) + " ms\"}");
      manager_annaffia(received_time_water + 3000);
    }
  } else if (action == "leggiacqua") {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    int livello = analogRead(pinWaterSensor);
    server.send(200, "json", "{\"result\":\"OK\",\"status\":\"Level of water readed\", \"value\": " + String(livello) + "}");
  } else {
    send_errorAnswer(String("Unknown action " + action));
  }
}

void manager_annaffia(int time_water) {
  watering = true;
  print_this(String("watering for " + time_water));
  blink_led();
  digitalWrite(pinRelay, LOW);
  delay(time_water);
  digitalWrite(pinRelay, HIGH);
  blink_led();
  watering = false;
  last_time_watering = millis();
}

void manage_access(JsonObject &  root) {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "json", "{\"result\":\"OK\",\"status\":\"online and ready\"}");
  print_this("access request sent");
}

void print_this(String s) {
  if (print_for_debug) {
    Serial.println(s);
  }
}

void blink_led() {
  digitalWrite(LEDPin, HIGH);
  delay(20);
  digitalWrite(LEDPin, LOW);
}

