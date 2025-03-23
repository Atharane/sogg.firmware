#include <WiFi.h>
#include <HTTPClient.h>

const char *SSID = SSID_SECRET;
const char *PASSWORD = PASSWORD_SECRET;

const int SENSOR_PIN = 34;

void setup()
{
  Serial.begin(921600);
  delay(1000);

  Serial.println("[*] initiating wifi connection sequence...");
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(":");
  }

  Serial.println("\n[+] access granted!");
  Serial.print("[*] assigned IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  int reading = analogRead(SENSOR_PIN);
  Serial.print("[+] moisture: ");
  Serial.println(reading);

  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin("https://soggweb.vercel.app/api/logs");
    // http.begin("http://192.168.29.184:3000/api/logs");

    http.addHeader("Content-Type", "application/json");
    // http.addHeader("Authorization", "Bearer testing...");

    String payload = "{\"type\":\"upsert\",\"data\":{\"value\":" + String(reading) + "}}";

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0)
    {
      Serial.print("[+] POST success: ");
      Serial.println(httpResponseCode);
    }
    else
    {
      Serial.print("[!] POST failed: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else
  {
    Serial.println("[!] WiFi not connected!");
  }

  delay(60 * 1000); // a minute
}