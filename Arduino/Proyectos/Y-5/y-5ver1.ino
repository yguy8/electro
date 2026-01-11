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
String comando = "";
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
  Serial.println("Modo: Felicidad ");
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
    setEyes(random(0,255), random(0,255), random(0,255)); // colores aleatorios
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

void reaccionConversacion() {
  Serial.println("Modo: Conversación 🗣️");
  for (int i=0; i<4; i++) {
    setEyes(0,255,255); // cian
    tone(buzzer_pin, 600+i*100, 150);
    delay(200);
    setEyes(255,255,255); // blanco
    delay(200);
  }
  noTone(buzzer_pin);
}

void reaccionExploracion() {
  Serial.println("Modo: Exploración");
  setEyes(0,0,255); // azul
  for (int i=0; i<3; i++) {
    tone(buzzer_pin, 400+i*50, 200);
    delay(500);
  }
  noTone(buzzer_pin);
  ojosNaturales();
}

void reaccionAlerta() {
  Serial.println("Modo: ALERTA");
  for (int i=0; i<6; i++) {
    setEyes(255,0,0); // rojo
    tone(buzzer_pin, 1000, 200);
    delay(300);
    setEyes(0,0,0); // apagado
    noTone(buzzer_pin);
    delay(300);
  }
  // transición a amarillo
  for (int c=0; c<=255; c+=5) {
    setEyes(c,c,0);
    delay(20);
  }
  ojosNaturales();
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

  // --- Micrófono ---
  if (sonido > 600) { // ruido fuerte → curiosidad
    reaccionCuriosidad();
    ultimaActividadSonido = millis();
  } else {
    // si hay silencio prolongado → sueño
    if (millis() - ultimaActividadSonido > T_SILENCIO) {
      reaccionSueno();
      ultimaActividadSonido = millis();
    }
  }

  // --- Tilt ---
  if (tilt == HIGH) {
    reaccionSorpresa();
  }

  // --- Vibración ---
  if (vib > 500) {
    reaccionCelebracion();
  }

  // --- Control por Serial ---
  if (Serial.available() > 0) {
    comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando == "natural") ojosNaturales();
    else if (comando == "pensar") reaccionPensando();
    else if (comando == "feliz") reaccionFelicidad();
    else if (comando == "sueno") reaccionSueno();
    else if (comando == "curioso") reaccionCuriosidad();
    else if (comando == "celebrar") reaccionCelebracion();
    else if (comando == "sorpresa") reaccionSorpresa();
    else if (comando == "conversar") reaccionConversacion();
    else if (comando == "explorar") reaccionExploracion();
    else if (comando == "alerta") reaccionAlerta();
    else Serial.println("Comando no reconocido.");
  }

  delay(200); // pequeña pausa para estabilidad
}
