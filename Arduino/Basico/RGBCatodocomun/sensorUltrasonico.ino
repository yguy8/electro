//simular que algo como mágia tipo cine y el sensor si esta cerca la mano carga energía (el led RGB sube su brillo en 5 seg y es morado el color del led) como recargando poderes
int TRIGGER = 6;
int ECHO = 5;
int ROJO = 11;
int VERDE = 10;
int AZUL = 9;

long tiempo;
float distancia;

unsigned long inicioFade = 0;   // Marca de tiempo para el fade
bool enFade = false;            // Estado del fade

void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(AZUL, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Medición con el sensor ultrasónico
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  tiempo = pulseIn(ECHO, HIGH);
  distancia = 0.03432 * tiempo / 2;

  // Lógica de brillo
  if (distancia > 10 && distancia < 20) {
    // Brillo máximo inmediato
    analogWrite(ROJO, 255);
    analogWrite(VERDE, 0);
    analogWrite(AZUL, 255);
    enFade = false; // Cancelar fade
  } else if (distancia < 10) {
    if (!enFade) {
      inicioFade = millis(); // Inicia el conteo
      enFade = true;
    }
    // Calcular cuánto tiempo ha pasado desde el inicio
    unsigned long tiempoTranscurrido = millis() - inicioFade;
    // Mapear de 0 a 5000 ms → brillo de 0 a 255
    int brillo = map(tiempoTranscurrido, 0, 5000, 0, 255);
    if (brillo > 255) brillo = 255; // Limitar al máximo

    analogWrite(ROJO, brillo);
    analogWrite(VERDE, 0);
    analogWrite(AZUL, brillo);
  } else {
    // Apagar LEDs si está fuera del rango
    analogWrite(ROJO, 0);
    analogWrite(VERDE, 0);
    analogWrite(AZUL, 0);
    enFade = false;
  }

  // Debug opcional
  // Serial.print("Distancia: ");
  // Serial.print(distancia);
  // Serial.println(" cm");
}
