#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h> //OTA Библиотека для OTA-прошивки
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define TERMINAL_RECEIVE 3

#define ONE_WIRE_BUS D1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//byte qty; // количество градусников на шине 
 byte led;
unsigned long previousMillis = 0;        // время последнего чтения
const long interval = 10000;              // интервал чтения с датчика


char auth[] = "cb54c98792304514b8ecbb9ebf056b5a";
char ssid[] = "TP-LINK_A5B116";
char pass[] = "0011223344";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  //************************
  ArduinoOTA.setHostname("ESP8266MQTT-01"); //OTA Задаем имя сетевого порта
  //ArduinoOTA.setPassword((const char *)"852456_!"); //OTA Задаем пароль доступа для удаленной прошивки
  ArduinoOTA.begin(); //OTA Инициализируем OTA
  ESP.wdtEnable(15000);  //***********************
  sensors.begin();
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
    pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
 WidgetTerminal terminal(V3);
}

void loop()
{
ArduinoOTA.handle(); // OTA Всегда готовы к прошивке

    temper();
}

void temper(){
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
  sensors.requestTemperatures(); // считываем температуру с датчиков
float temp1 = sensors.getTempCByIndex(0);
float temp2 = sensors.getTempCByIndex(1);

Serial.println(temp1);
Serial.println(temp2);
Blynk.virtualWrite(V0, temp1);
Blynk.virtualWrite(V2, temp2);
  }
  Blynk.run();

 }
