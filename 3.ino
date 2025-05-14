#include <WiFi.h>
#include "time.h"
#include <stdint.h>

const char* ssid = "MiFibra-3366";
const char* password = "4JX5dynX";
const char* ntpServer = "es.pool.ntp.org";
const int32_t gmtOffset_sec = 3600;
const int32_t daylightOffset_sec = 3600;

struct tm timeinfo;

void setup() {
  Serial.begin(115200);

  // Conexión WiFi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConexión WiFi establecida");
  Serial.println("Dirección IP:");
  Serial.println(WiFi.localIP());

  // Configuración de hora
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  if (getLocalTime(&timeinfo)) {
    Serial.println(&timeinfo, "%d/%m/%Y %H:%M:%S");
  } else {
    Serial.println("No se pudo obtener la hora");
  }
  delay(1000);
}
