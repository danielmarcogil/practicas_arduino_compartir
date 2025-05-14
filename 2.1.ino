int bocina = 19; 
int potenciometro = 32; 
int led_verde=2;
int led_rojo=4;
int led_azul=5;
float vpot; 
int Fmin= 100; int Fmax = 5000;
void setup() {
  pinMode(led_verde, OUTPUT);
  pinMode(led_rojo, OUTPUT);
  pinMode(led_azul, OUTPUT);
pinMode(bocina, OUTPUT); 
pinMode(potenciometro, INPUT); 
}
void loop() {
vpot = analogRead(potenciometro);
float intensidad=map(vpot,0,1023,0,255);
float frecuencia = map(vpot, 0, 1023, Fmin, Fmax);
analogWrite(bocina,frecuencia);
 if (intensidad<100){analogWrite(led_verde,intensidad);}
 if (intensidad<200 && intensidad>100  ){analogWrite(led_rojo,intensidad);} 
 else {analogWrite(led_azul,intensidad);}
delay(1000);
}
