#include <Wire.h>
#include "SparkFunHTU21D.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

HTU21D myHumidity;
WiFiClient wifiClient;
const char* WIFI_SSID = "YOUR_NETWORK_SSID";
const char* WIFI_PASSWORD = "YOUR_NETWORK_PASSWORD";
const char* POST_REQUEST_ENDPOINT = "http://192.168.1.117:3100/weather"; // e.g. http://192.168.1.117:3100/weather

void setup() {
  Serial.begin(115200);
  myHumidity.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to " + String(WIFI_SSID));
  }
}

// the loop function runs over and over again forever
void loop() {
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    float humd = myHumidity.readHumidity();
    float temp = myHumidity.readTemperature();
    http.begin(wifiClient, POST_REQUEST_ENDPOINT );
    http.addHeader("Content-Type", "application/json");
    http.POST("{\"temperature\":" + String(temp, 3) + ",\"humidity\":" + String(humd, 3) + "}");
    http.writeToStream(&Serial);
    Serial.println();
    http.end();
  }
  delay(3000);  // wait for 3 seconds
}
