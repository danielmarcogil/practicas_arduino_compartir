#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

// WiFi
const char* ssid = "MiFibra-3366";//wifi personal, clase :"ALUMNOS_CICLOS";
const char* password = "4JX5dynX";//wifi personal,clase :"Ciclos2025sz?";

// NTP
const char* ntpServer = "es.pool.ntp.org";
const int32_t gmtOffset_sec = 3600;
const int32_t daylightOffset_sec = 3600;//horario de verano , si fuera de invierno seria un 0.

// MQTT
const char* mqtt_server = "broker.emqx.io";
const char* mqtt_username = "Dani";
const char* mqtt_password = "1234";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

struct tm timeinfo;

// LED conectado al pin GPIO 2
const int ledPin = 2;

// Callback MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en el tópico: ");
  Serial.println(topic);

  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Mensaje: ");
  Serial.println(message);

  if (message == "1") {
    Serial.println("Encendiendo LED");
    digitalWrite(ledPin, HIGH); // Encender LED
  } else if (message == "0") {
    Serial.println("Apagando LED");
    digitalWrite(ledPin, LOW); // Apagar LED
  }
}

void reconnect() {
  Serial.print("Conectando a MQTT...");
  String client_id = "esp32-client-" + String(WiFi.macAddress());
  if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
    Serial.println("Conectado a MQTT");
    mqtt_client.subscribe("sensor/boton");
  } else {
    Serial.print("Error, código: ");
    Serial.println(mqtt_client.state());
    delay(5000);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);        // Inicializar pin del LED
  digitalWrite(ledPin, LOW);      // Asegurarse que el LED inicia apagado

  WiFi.begin(ssid, password);
  Serial.println("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP:");
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  mqtt_client.setServer(mqtt_server, mqtt_port);
  mqtt_client.setCallback(callback);
}

void loop() {
  if (!mqtt_client.connected()) {
    reconnect();
  }

  mqtt_client.loop();

  if (getLocalTime(&timeinfo)) {
    char formattedTime[64];
    strftime(formattedTime, sizeof(formattedTime), "%d/%m/%Y %H:%M:%S", &timeinfo);
    Serial.println(formattedTime);
    mqtt_client.publish("sensor/hora", formattedTime);
  }

  delay(1000);
}