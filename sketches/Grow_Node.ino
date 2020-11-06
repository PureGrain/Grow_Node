/*
  Grow Node v1.0
  Created 11/02/2020
  By: Challon Holt a.k.a. "PureGrain"
  
http://github.com/PureGrain/Grow_Node

*/
#define BLYNK_PRINT Serial

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#ifndef STASSID
#define STASSID "Your Wifi Router"
#define STAPSK  "Your Wifi Password"
#endif

//added for soil moisture
int sensorpin=A0;
int sensorvalue=0;
int outputvalue=0;
// *********************

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "E4sgIWlKRHc-Z3buTyDiTsOUfPNeQBBS"; // prototype
char auth[] = "oTbjLId3M83i31hBEPUE8Pa_SoVwKomz"; //  this is the Grow Project

const char* ssid = STASSID;
const char* password = STAPSK;

//DHT22 Sensor
#define DHTPIN D5 // What digital pin we're connected to for the DHT22 sensor

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(true); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  Blynk.begin(auth, ssid, password, IPAddress(10,10,4,4), 8080); // change this to match your IP of your docker container

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  
  Serial.begin(115200);
  Serial.println("Booting OTA Setup");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
   ArduinoOTA.setHostname("grow01"); // you can change this or not use it at all. I prefer to name them so i can easily find them when doing OTA updates.

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
}

void loop() {
  // I added this code to notify me if the temperature was getting to high in a certain grow tent.
  // The code used for this section uses the DHT22 terminals on the Grow Node Shield.
  float t = dht.readTemperature(true); // or dht.readTemperature(true) for Fahrenhei
  if(t>85)
  {
       Serial.println("It's getting hot in here");
       Serial.print(t);
       Blynk.notify("Temp is over 85  ");
       delay(1000); 
  }
  else if(t<60)
  {
       Serial.println("It's getting cold in here");
       Serial.print(t);
       Blynk.notify("Temp is under 60");
       delay(1000); 
  }
// this is the section of code that will notify you if your plants need watering.
//This code is only for 1 (one) soil sensor connected in "soil0" terminals.
  
  sensorvalue=analogRead(sensorpin);
  outputvalue=map(sensorvalue,0,1023,0,100); //100,0 pottupaaru
  delay(1000);
  if(outputvalue>88)
  {
       Serial.println("water your plant");
       Serial.print(outputvalue);
       Blynk.notify("Water Plants");
       delay(1000); 
  }
  else if(outputvalue<45)
  {
       Serial.println("soil is wet enough");
       Serial.print(outputvalue);
       //Blynk.notify("Soil Is Wet Enough");
       delay(1000);
  }
 
  
  Blynk.virtualWrite(V1,outputvalue);
  Blynk.run();
  timer.run();
  
  //end the OTA code
  ArduinoOTA.handle();
}
