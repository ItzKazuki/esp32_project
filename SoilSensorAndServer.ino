/* Copyright (C) 2024 Chaeza Ibnu Akbar - All Rights Reserved
 * You may use, distribute and modify this code please be careful
 * what are you doing.
 *
 * Please following documentation to start this project.
 * If your ESP32 break we already warn to you 
 * and you make responbility to your device.
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "configESP32.h"

void connectWifi() {
  // Menghubungkan ke Wi-Fi
  WiFi.begin(SSID, PASSWORD);

  Serial.println("========== WiFi ===========");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Wi-Fi terhubung
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("========== End WiFi ===========\n");
}

void sendPostData(String httpRequestData) {
    HTTPClient http;

    // initial connection
    http.begin(BACKEND_URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(httpRequestData); // Mengirim data POST

    // Mengecek hasil dari permintaan
    if (httpResponseCode > 0) {
      String response = http.getString(); // Mendapatkan respons dari server
      Serial.print("Status Code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response Server: ");   // Menampilkan kode respons
      Serial.println(response);           // Menampilkan respons dari server
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode); // Menampilkan kode error
    }

    http.end(); // Menutup koneksi
}

void setup() {
  // add log to see process
  Serial.begin(115200);

  // set pinmode
  pinMode(SENSOR_INPUT, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  connectWifi();
}

void loop() {
  int sensorValue = analogRead(SENSOR_INPUT);
  int soilMoisturePercent = getSensorPercent(sensorValue);

  Serial.println("========= ESP32 Connection ========== \n");

  // Menampilkan nilai persentase kelembapan di Serial Monitor
  Serial.print("Soil Moisture Percentage: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");

  if(WiFi.status() == WL_CONNECTED) {
    char httpRequestData[100];
    sprintf(httpRequestData, "indikator_kelembapan=%d&key=%s&kelembapan=%d&SSID=%s&SSID_Stregth=%s", sensorValue, BACKEND_KEY, soilMoisturePercent, WiFi.SSID(), WiFi.RSSI());

    sendPostData(httpRequestData);
    Serial.print("Soil Moisture Value: ");
    Serial.println(sensorValue);

    // do led switch in here ;)
    if(soilMoisturePercent >= 0 && soilMoisturePercent <= 39) {
      switchLED("RED");
    } else if(soilMoisturePercent >= 40 && soilMoisturePercent <= 69) {
      switchLED("GREEN");
    } else {
      switchLED("YELLOW");
    }

    Serial.println("\n========= ESP32 Connection ==========\n");
  } else {
    Serial.println("Wifi Disconnected.. no connection to reach backend!");
  }

  delay(3000);
}
