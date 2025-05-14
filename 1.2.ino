uint32_t red_led=19;
uint32_t green_led=4;
uint64_t previous_millis_red=0;
uint64_t previous_millis_green=0;
uint64_t red_interval=1000;
uint64_t green_interval=2000;
void setup() {
 
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
}

void loop() {
  uint64_t actual_millis=millis();
  if(actual_millis-previous_millis_red>red_interval){
    previous_millis_red=millis();
    if(digitalRead(red_led)){
      digitalWrite(red_led, LOW);
    }
    else {digitalWrite(red_led,HIGH);}
  }
  if(actual_millis-previous_millis_green>green_interval){
    previous_millis_green=millis();
    if(digitalRead(green_led)){
      digitalWrite(green_led, LOW);
    }
    else {digitalWrite(green_led,HIGH);}
  }
}