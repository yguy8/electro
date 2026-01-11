// --- Pines RGB (dos ojos, cátodo común) ---
// ojo izquierdo
int R1_pin = 3;
int G1_pin = 5;
int B1_pin = 6;

// ojo derecho
int R2_pin = 9;
int G2_pin = 10;
int B2_pin = 11;

// --- Buzzer activo ---
int buzzer_pin = 8;

// --- Sensores ---
int micPin = A0;   // micrófono analógico
int tiltPin = 2;   // sensor tilt digital
int vibPin = A1;   // sensor vibración analógico
int capPin = 4;    // botón capacitivo

// --- Variables ---
unsigned long ultimaActividadSonido = 0;
const unsigned long T_SILENCIO = 120000UL; // 2 minutos
const unsigned long T_PENSANDO = 120000UL; // 2 minutos de sonido continuo

// --- Umbrales calibrados ---
const int TH_SONIDO = 130;       // sonido
const int TH_VIB_MIN = 200;      // vibración mínima para felicidad
const int TH_VIB_MAX = 700;      // vibración máxima para felicidad
const int TH_VIB_PELIGRO = 800;  // vibración peligrosa

// --- Función para color en ambos ojos ---
void setEyes(int r, int g, int b) {
  analogWrite(R1_pin, r); analogWrite(G1_pin, g); analogWrite(B1_pin, b);
  analogWrite(R2_pin, r); analogWrite(G2_pin, g); analogWrite(B2_pin, b);
}

// --- Función auxiliar para buzzer activo ---
void beepActivo(int repeticiones, int duracion, int pausa) {
  for (int i=0; i<repeticiones; i++) {
    digitalWrite(buzzer_pin, HIGH);
    delay(duracion);
    digitalWrite(buzzer_pin, LOW);
    delay(pausa);
  }
}

// --- Funciones de reacciones ---
void ojosNaturales() {
  // ojo izquierdo amarillo
  analogWrite(R1_pin,255); analogWrite(G1_pin,255); analogWrite(B1_pin,0);
  // ojo derecho azul
  analogWrite(R2_pin,0);   analogWrite(G2_pin,0);   analogWrite(B2_pin,255);
}

void reaccionPensando() {
  setEyes(0,0,180); // azul suave
  beepActivo(1, 500, 200);
  ojosNaturales();
}

void reaccionFelicidad() {
  setEyes(0,255,0); // verde
  beepActivo(3, 200, 150);
  ojosNaturales();
}

void reaccionSueno() {
  for (int b = 255; b >= 0; b -= 5) {
    setEyes(0,0,b); // azul descendente
    delay(50);
  }
  beepActivo(2, 400, 300);
  delay(300000); // 5 minutos
  ojosNaturales();
}

void reaccionCuriosidad() {
  // transición rosa ↔ naranja
  for (int i=0; i<3; i++) {
    setEyes(255,0,255); // rosa
    delay(300);
    setEyes(255,165,0); // naranja
    delay(300);
  }
  beepActivo(2, 200, 200);
  ojosNaturales();
}

void reaccionCelebracion() {
  // transición amarillo → verde → azul
  setEyes(255,255,0); delay(300); // amarillo
  setEyes(0,255,0);   delay(300); // verde
  setEyes(0,0,255);   delay(300); // azul
  beepActivo(3, 150, 100);
  ojosNaturales();
}

void reaccionSorpresa() {
  setEyes(255,0,255); // magenta
  beepActivo(2, 300, 200);
  ojosNaturales();
}

void reaccionAlertaMaxima() {
  for (int i=0; i<6; i++) {
    setEyes(255,0,0); // rojo
    digitalWrite(buzzer_pin, HIGH);
    delay(300);
    setEyes(255,255,255); // blanco
    digitalWrite(buzzer_pin, LOW);
    delay(300);
  }
  ojosNaturales();
}

// --- Setup ---
void setup() {
  pinMode(R1_pin,OUTPUT); pinMode(G1_pin,OUTPUT); pinMode(B1_pin,OUTPUT);
  pinMode(R2_pin,OUTPUT); pinMode(G2_pin,OUTPUT); pinMode(B2_pin,OUTPUT);
  pinMode(buzzer_pin,OUTPUT);
  pinMode(tiltPin,INPUT);
  pinMode(capPin,INPUT);
  ojosNaturales();
  ultimaActividadSonido = millis();
}

// --- Loop principal ---
void loop() {
  // --- Lectura de sensores ---
  int sonido = analogRead(micPin);
  int tilt = digitalRead(tiltPin);
  int vib = analogRead(vibPin);
  int cap = digitalRead(capPin);

  // --- Priorización de estados ---
  if (tilt == HIGH && vib > TH_VIB_PELIGRO && sonido > TH_SONIDO) {
    reaccionAlertaMaxima();
    ultimaActividadSonido = millis();
  }
  else if (sonido > TH_SONIDO && (millis() - ultimaActividadSonido > T_PENSANDO)) {
    reaccionPensando();
    ultimaActividadSonido = millis();
  }
  else if (sonido > TH_SONIDO) {
    reaccionCuriosidad();
    ultimaActividadSonido = millis();
  }
  else if (tilt == HIGH) {
    reaccionSorpresa();
  }
  else if (vib >= TH_VIB_MIN && vib <= TH_VIB_MAX) {
    reaccionFelicidad();
  }
  else if (cap == HIGH) {
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
