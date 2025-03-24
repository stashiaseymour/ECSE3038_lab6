#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  delay(1000);

  Serial.print("Connecting to WiFi");
  if (is_wokwi)
    WiFi.begin(ssid, password, 6); 
  else
    WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  // GET request to check light state
  HTTPClient http;
  http.begin(String(endpoint) + "/api/light");
  http.addHeader("api-key", api_key);

  int httpCode = http.GET();
  if (httpCode == 200) {
    String response = http.getString();
    Serial.println("GET response: " + response);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);
    bool light = doc["light"];
    digitalWrite(led_pin, light ? HIGH : LOW);
  } else {
    Serial.println("GET failed with code: " + String(httpCode));
  }
  http.end();

  // Read temperature from sensor 
  int raw = analogRead(temp_sensor);
  float voltage = raw * 3.3 / 4095.0;
  float tempC = (voltage - 0.5) * 100.0;

  // PUT request to send temperature
  http.begin(String(endpoint) + "/api/temp");
  http.addHeader("api-key", api_key);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument data(256);
  data["temp"] = tempC;

  String body;
  serializeJson(data, body);
  httpCode = http.PUT(body);
  if (httpCode == 200) {
    String response = http.getString();
    Serial.println("PUT response: " + response);
  } else {
    Serial.println("PUT failed with code: " + String(httpCode));
  }
  http.end();

 
}
