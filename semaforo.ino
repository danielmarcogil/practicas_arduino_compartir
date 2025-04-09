// Definimos los pines para los LEDs
const int LED_ROJO = 18;
const int LED_AMARILLO = 19;
const int LED_VERDE = 21;

// Definimos las duraciones de cada fase en milisegundos
const unsigned long TIEMPO_ROJO = 5000;
const unsigned long TIEMPO_AMARILLO = 2000;
const unsigned long TIEMPO_VERDE = 5000;

// Variables para el control del tiempo
unsigned long tiempoAnterior = 0;  // Almacena el último tiempo cuando se cambió de fase
unsigned long faseActual = 0;  // Fase actual del semáforo (0: rojo, 1: rojo+amarillo, 2: verde, 3: amarillo)

// Función que cambia la fase del semáforo
void cambiarFase() {
  // Apagar todos los LEDs
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);

  // Cambiar la fase según el valor de faseActual
  switch (faseActual) {
    case 0:  // Fase roja
      digitalWrite(LED_ROJO, HIGH);
      faseActual = 1;
      tiempoAnterior = millis();  // Actualiza el tiempo de la fase actual
      break;
    case 1:  // Fase roja + amarilla
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, HIGH);
      faseActual = 2;
      tiempoAnterior = millis();
      break;
    case 2:  // Fase verde
      digitalWrite(LED_VERDE, HIGH);
      faseActual = 3;
      tiempoAnterior = millis();
      break;
    case 3:  // Fase amarilla
      digitalWrite(LED_AMARILLO, HIGH);
      faseActual = 0;
      tiempoAnterior = millis();
      break;
  }
}

void setup() {
  // Inicializamos los pines de los LEDs como salida
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  // Comenzamos en la fase 0 (rojo)
  cambiarFase();
}

void loop() {
  // Comprobamos si ha pasado el tiempo correspondiente para cambiar de fase
  unsigned long tiempoActual = millis();
  
  // Dependiendo de la fase, verificamos el tiempo transcurrido
  switch (faseActual) {
    case 0:  // Fase roja
      if (tiempoActual - tiempoAnterior >= TIEMPO_ROJO) {
        cambiarFase();
      }
      break;
    case 1:  // Fase roja + amarilla
      if (tiempoActual - tiempoAnterior >= TIEMPO_AMARILLO) {
        cambiarFase();
      }
      break;
    case 2:  // Fase verde
      if (tiempoActual - tiempoAnterior >= TIEMPO_VERDE) {
        cambiarFase();
      }
      break;
    case 3:  // Fase amarilla
      if (tiempoActual - tiempoAnterior >= TIEMPO_AMARILLO) {
        cambiarFase();
      }
      break;
  }
}


