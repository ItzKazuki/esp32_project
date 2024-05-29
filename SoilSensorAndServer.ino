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

void setup() {
  // add log to see process
  Serial.begin(115200);

  // set pinmode
  pinMode(SENSOR_INPUT, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

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

void loop() {
  int sensorValue = analogRead(SENSOR_INPUT);

  int soilMoisturePercent = getSensorPercent(sensorValue);

  Serial.println("========= ESP32 Connection ========== \n");

  // Menampilkan nilai persentase kelembapan di Serial Monitor
  Serial.print("Soil Moisture Percentage: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");

  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // initial connection
    http.begin(BACKEND_URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // String httpRequestData = "indikator_kelembapan=" + sensorValue + "&key=koneksiESP32&kelembapan=" + soilMoisturePercent;
    char httpRequestData[100];
    sprintf(httpRequestData, "indikator_kelembapan=%d&key=%s&kelembapan=%d", sensorValue, BACKEND_KEY, soilMoisturePercent);

    int httpResponseCode = http.POST(httpRequestData); // Mengirim data POST
    Serial.print("Soil Moisture Value: ");
    Serial.println(sensorValue);

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

    // do led switch in here ;)
    if(soilMoisturePercent >= 70 && soilMoisturePercent <= 100) {
      // set conditional led
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, LOW);

      //set led
      digitalWrite(LED_RED, HIGH);
    } else if(soilMoisturePercent >= 40 && soilMoisturePercent <= 69) {
      // set conditional led
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);
      
      //set led
      digitalWrite(LED_GREEN, HIGH);
    } else {
      // set conditional led
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, LOW);

      // set led
      digitalWrite(LED_YELLOW, HIGH);
    }

    http.end(); // Menutup koneksi
    Serial.println("\n========= ESP32 Connection ==========\n");
  } else {
    Serial.println("Wifi Disconnected.. try to reconnect");
  }

  delay(3000);
}
