#include<stdint.h>
uint32_t led=4;//definimos nuestro led con nuestro pin 2
uint32_t button=18;//definimos nuestro boton.
bool state_led=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLDOWN);//inicializamos como boton apagado
  digitalWrite(led, LOW);//estado inicial de nuestro led;
}

void loop() {
  if(digitalRead(button)==LOW)
  {
    
  delay(50);
state_led=!state_led;//intercambio el valor del estado del led
digitalWrite(led,state_led);
  }
}