// --- Pines RGB (dos ojos, cátodo común) ---
// ojo izquierdo
int R1_pin = 3;
int G1_pin = 5;
int B1_pin = 6;

// ojo derecho
int R2_pin = 9;
int G2_pin = 10;
int B2_pin = 11;

// --- Buzzer ---
int buzzer_pin = 8;

// --- Sensores ---
int micPin = A0;   // micrófono analógico
int tiltPin = 2;   // sensor tilt digital
int vibPin = A1;   // sensor vibración analógico

// --- Variables ---
unsigned long ultimaActividadSonido = 0;
const unsigned long T_SILENCIO = 120000UL; // 2 minutos

// --- Función para color en ambos ojos ---
void setEyes(int r, int g, int b) {
  analogWrite(R1_pin, r); analogWrite(G1_pin, g); analogWrite(B1_pin, b);
  analogWrite(R2_pin, r); analogWrite(G2_pin, g); analogWrite(B2_pin, b);
}

// --- Funciones de reacciones ---
void ojosNaturales() {
  Serial.println("Modo: Natural");
  setEyes(255,255,255); // blanco
}

void reaccionPensando() {
  Serial.println("Modo: Pensando");
  setEyes(0,0,180); // azul suave
  tone(buzzer_pin, 600, 200); delay(500);
  noTone(buzzer_pin);
  ojosNaturales();
}

void reaccionFelicidad() {
  Serial.println("Modo: Felicidad");
  setEyes(0,255,0); // verde
  tone(buzzer_pin, 800, 150); delay(300);
  tone(buzzer_pin, 1000, 150); delay(300);
  noTone(buzzer_pin);
  ojosNaturales();
}

void reaccionSueno() {
  Serial.println("Modo: Sueño");
  for (int b = 255; b >= 0; b -= 5) {
    setEyes(0,0,b); // azul descendente
    delay(50);
  }
  tone(buzzer_pin, 400, 300); delay(400);
  tone(buzzer_pin, 200, 500); delay(600);
  noTone(buzzer_pin);
  Serial.println("Durmiendo...");
  delay(300000); // 5 minutos
  Serial.println("Sistema activado");
  ojosNaturales();
}

void reaccionCuriosidad() {
  Serial.println("Modo: Curiosidad");
  // ojo izquierdo amarillo
  analogWrite(R1_pin,255); analogWrite(G1_pin,255); analogWrite(B1_pin,0);
  // ojo derecho azul
  analogWrite(R2_pin,0);   analogWrite(G2_pin,0);   analogWrite(B2_pin,255);
  tone(buzzer_pin, 700, 150); delay(300);
  noTone(buzzer_pin);
  ojosNaturales();
}

void reaccionCelebracion() {
  Serial.println("Modo: Celebración");
  for (int i=0; i<6; i++) {
    setEyes(255,255,0); // amarillo fijo
    tone(buzzer_pin, 600+i*100, 150);
    delay(200);
  }
  noTone(buzzer_pin);
  ojosNaturales();
}

void reaccionSorpresa() {
  Serial.println("Modo: Sorpresa (Magenta)");
  setEyes(255,0,255); // magenta
  tone(buzzer_pin, 1500, 300); delay(500);
  noTone(buzzer_pin);
  ojosNaturales();
}

void reaccionAlertaMaxima() {
  Serial.println("ALERTA MÁXIMA: Y-5 en peligro");
  
  // Sirena con parpadeo rojo
  for (int i=0; i<10; i++) {
    setEyes(255,0,0); // rojo intenso
    tone(buzzer_pin, 1200, 300); // tono alto
    delay(300);
    setEyes(0,0,0); // apagado
    tone(buzzer_pin, 800, 300); // tono bajo
    delay(300);
  }
  
  noTone(buzzer_pin);
  ojosNaturales(); // volver a estado natural después
}

// --- Setup ---
void setup() {
  pinMode(R1_pin,OUTPUT); pinMode(G1_pin,OUTPUT); pinMode(B1_pin,OUTPUT);
  pinMode(R2_pin,OUTPUT); pinMode(G2_pin,OUTPUT); pinMode(B2_pin,OUTPUT);
  pinMode(buzzer_pin,OUTPUT);
  pinMode(tiltPin,INPUT);
  Serial.begin(9600);
  ojosNaturales();
  ultimaActividadSonido = millis();
}

// --- Loop principal ---
void loop() {
  // --- Lectura de sensores ---
  int sonido = analogRead(micPin);
  int tilt = digitalRead(tiltPin);
  int vib = analogRead(vibPin);

  // --- Priorización de estados ---
  if (tilt == HIGH && vib > 500 && sonido > 600) {
    reaccionAlertaMaxima();
    ultimaActividadSonido = millis();
  }
  else if (sonido > 600) {
    reaccionCuriosidad();
    ultimaActividadSonido = millis();
  }
  else if (tilt == HIGH) {
    reaccionSorpresa();
  }
  else if (vib > 500) {
    reaccionCelebracion();
  }
  else if (millis() - ultimaActividadSonido > T_SILENCIO) {
    reaccionSueno();
    ultimaActividadSonido = millis();
  }
  else {
    ojosNaturales();
  }

  delay(200); // pequeña pausa para estabilidad
}
