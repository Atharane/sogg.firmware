#include <WiFi.h>

const char* SSID = SSID_SECRET;
const char* PASSWORD = PASSWORD_SECRET;

const int SENSOR_PIN = 34;

void setup() {
  Serial.begin(921600);
  delay(1000);
  
  Serial.println("[*] initiating wifi connection sequence...");
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(":");
  }

  Serial.println("\n[+] access granted!");
  Serial.print("[*] assigned IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int reading = analogRead(SENSOR_PIN);
  Serial.print("[+] moisture: ");
  Serial.println(reading);
  delay(1000);
}