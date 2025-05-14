#define sensor_luz 13
#define  led_azul 21
#define  led_verde 18
#define  led_rojo 19

int valor =0;
void setup() {
  Serial.begin(115200);
pinMode(sensor_luz, INPUT);
  pinMode(led_rojo, OUTPUT);
  pinMode(led_azul, OUTPUT);
  pinMode(led_verde, OUTPUT);
}
void loop() {
  valor = analogRead(sensor_luz);
 Serial.println(valor);
  if(valor>=1365){digitalWrite(led_verde, HIGH);
  }else if (valor<1365) {digitalWrite(led_verde, LOW);}
  if(valor>=2730){digitalWrite(led_rojo, HIGH);
  }else if (valor<2730) {digitalWrite(led_rojo, LOW);}
  if(valor>=4095){digitalWrite(led_azul, HIGH);
  }else if (valor<4095) {digitalWrite(led_azul, LOW);}
  delay(1000);
}

