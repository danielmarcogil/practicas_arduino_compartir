#include <WiFi.h>
#include <time.h>
#include <stdint.h>
#include <PubSubClient.h> // Incluimos la biblioteca PubSubClient
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define ANCHO_PANTALLA 128 
#define ALTO_PANTALLA 64 
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

// WIFI
char* ssid = "Redmi Note 11 Pro 5G";
char* password = "yd96261885";

// servidor para fecha y hora
char* ntpServer = "es.pool.ntp.org";
// zona horaria
int32_t gmtOffset_sec = 3600;
// horario de verano
int32_t daylightOffset_sec = 0;

// Estructura para trabajar con ntp
struct tm timeinfo;

// MQTT Broker
char* mqtt_username="yaya";
char* mqtt_password="yd12" ;
char* mqtt_server = "broker.emqx.io"; // Ejemplo de broker público
int mqtt_port = 1883;

uint64_t bultin_buzzer = 4 ;
uint64_t sensor = 18; 
uint64_t oledAddress = 0x3C; // Dirección I2C común para OLED de 128x64



WiFiClient espClient;
PubSubClient mqtt_client(espClient);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en el tópico: ");
  Serial.println(topic);

 String message ;
 for(unsigned int i= 0; i < length; i++){
  message += (char)payload[i];
 }

  Serial.print("Mensaje:");
  Serial.println(message);

  if ( message == "1"){
    Serial.println("ON");
    digitalWrite(4,HIGH);
  } 
  else if ( message == "0"){
    Serial.println("OFF");
    digitalWrite(4,LOW);
  }
}
 // Función para conectar a MQTT
void reconnect(){
  while (! mqtt_client.connected()) {
    Serial.print("Conectando a MQTT...");
    String client_Id = "ESP32-Client-" + String(WiFi.macAddress()); // Genera un ID de cliente único
    if (mqtt_client.connect(client_Id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Conectado !");
      mqtt_client.subscribe("sensor/boton"); // Suscribirse al topic del LED
    } else {
      Serial.print("Error , código: ");
      Serial.println(mqtt_client.state());
      delay(5000);
    }
  }
}


void setup(){
  Serial.begin(115200);
  pinMode(bultin_buzzer,OUTPUT);
  pinMode(sensor,INPUT);
  Serial.println("Iniciando pantalla OLED");
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 // conectarWiFi();
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status()!= WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  mqtt_client.setServer(mqtt_server, mqtt_port);
  mqtt_client.setCallback(callback);

}


void loop() {

  // Asegurar conexión a MQTT
  if (!mqtt_client.connected()) {
    reconnect();
  }
 mqtt_client.loop();//procesa mensajes mqtt
 getLocalTime(&timeinfo);
 Serial.println(&timeinfo, "%d-%m-%Y %H:%M:%S");
 String currentTime = String(timeinfo.tm_mday) +"/" +String(timeinfo.tm_mon + 1) + "/" + String(timeinfo.tm_year + 1900);
  if (mqtt_client.connected()) {  
    mqtt_client.publish("sensor/hora","hola");
  }
delay(1000);
 // Comprobar el mensaje recibido
 uint64_t portvalue = digitalRead(sensor);
  if (portvalue == HIGH) {
    Serial.println("Alarma armada");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 32);
    display.printf("sin movimiento");
    display.display();
    mqtt_client.publish("sensor/movimiento", "Sin movimiento");
  } 
  else if (portvalue == LOW) {
   Serial.println("Alarma desarmada");
   display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(10, 32);
   display.println("alerta");
   display.display();
   mqtt_client.publish("sensor/movimiento", "Movimiento detectado");
    
  }
delay(1000);
}