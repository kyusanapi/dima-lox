#include <Arduino.h>
#include <SPI.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

const char *ssid = "WNP-RP-002";                           // SSID вашей Wi-Fi сети
const char *password = "12348765";                         // Пароль вашей Wi-Fi сети
const char *serverUrl = "http://210.10.41.246:3000/alarm"; // URL сервера для отправки данных
const int id = 0;
#define first 13
#define second 14
#define third 18
#define fourth 19
#define fifth 25
#define sixth 26
#define seventh 27
#define eighth 32
#define nineth 33
#define tenth 34

byte d1 = 0;
byte d2 = 0;
byte d3 = 0;
byte d4 = 0;
byte d5 = 0;
byte d6 = 0;
byte d7 = 0;
byte d8 = 0;
byte d9 = 0;
byte d10 = 0;

long lt;


void sendToServer(String data);

void setup()
{
  Serial.begin(115200);
  pinMode(first, INPUT);
  pinMode(second, INPUT);
  pinMode(third, INPUT);
  pinMode(fourth, INPUT);
  pinMode(fifth, INPUT);
  pinMode(sixth, INPUT);
  pinMode(seventh, INPUT);
  pinMode(eighth, INPUT);
  pinMode(nineth, INPUT);
  pinMode(tenth, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected!");
}

void loop()
{
  d1 = digitalRead(first);
  d2 = digitalRead(second);
  d3 = digitalRead(third);
  d4 = digitalRead(fourth);
  d5 = digitalRead(fifth);
  d6 = digitalRead(sixth);
  d7 = digitalRead(seventh);
  d8 = digitalRead(eighth);
  d9 = digitalRead(nineth);
  d10 = digitalRead(tenth);

  DynamicJsonDocument sendDataDoc(256);
  if (millis() -lt >= 1000 )
  {

    lt = millis();

    sendDataDoc["id"] = id;
    sendDataDoc["zone"]["d1"] = d1;
    sendDataDoc["zone"]["d2"] = d2;
    sendDataDoc["zone"]["d3"] = d3;
    sendDataDoc["zone"]["d4"] = d4;
    sendDataDoc["zone"]["d5"] = d5;
    sendDataDoc["zone"]["d6"] = d6;
    sendDataDoc["zone"]["d7"] = d7;
    sendDataDoc["zone"]["d8"] = d8;
    sendDataDoc["zone"]["d9"] = d9;
    sendDataDoc["zone"]["d10"] = d10;

    String sendData;
    serializeJson(sendDataDoc, sendData);

    // Отправка данных на сервер
    sendToServer(sendData);
  }
}

void sendToServer(String data)
{
  HTTPClient http;

  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0)
  {
  }
  else
  {
    Serial.println("HTTP POST request failed!");
  }

  http.end();
}
