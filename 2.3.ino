const int sensor = 4;  
const int bocina= 21; 
int led_verde=5;
int led_rojo=2;
 
void setup() {
  
  pinMode(sensor, INPUT);  
  pinMode(bocina, OUTPUT); 
  pinMode(led_verde, OUTPUT);
  pinMode(led_rojo, OUTPUT);
  digitalWrite(led_verde,LOW);
  digitalWrite(led_rojo,LOW);
  Serial.begin(115200);   
}

void loop() {
  // Leer el valor del sensor
  int estado= digitalRead(sensor);

  // Si el sensor detecta movimiento (sensorState = HIGH)
  if (estado == HIGH) {
    digitalWrite(bocina, HIGH);  // Activar el buzzer
    digitalWrite(led_verde,HIGH);
    digitalWrite(led_rojo,LOW);
      
  } else {
    digitalWrite(bocina, LOW);   // Apagar el buzzer
    digitalWrite(led_verde,LOW);
    digitalWrite(led_rojo,HIGH);
      
  }

  delay(100);  // Un pequeño retraso para evitar lecturas repetidas innecesarias
}
