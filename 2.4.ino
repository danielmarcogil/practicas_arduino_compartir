#include <DHT.h>
#define DHTPIN 14     
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);

int  azul= 2;
int verde =21;
int rojo= 5;
void setup() {
  Serial.begin(115200);
  // Iniciar el sensor DHT
  dht.begin();
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(rojo, OUTPUT);
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(rojo, LOW);
}
void loop() {
  
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error ");
    delay(2000);
    return;
  }
  
  // Evaluar condiciones
  bool temperatura_Baja = temperatura < 20;
  bool temperatura_Alta = temperatura > 15;
  bool humedad_Baja = humedad < 50;

  if (temperatura_Baja && temperatura_Alta && humedad_Baja) {
    digitalWrite(rojo, HIGH);
  }
  else {digitalWrite(rojo,LOW);}

  if (temperatura_Alta) {
    digitalWrite(azul, HIGH);
  }

  else {digitalWrite(azul,LOW);}

  if (temperatura_Baja) {
    digitalWrite(verde, HIGH);
  }
  else {digitalWrite(verde,LOW);}

  delay(2000); 
}
