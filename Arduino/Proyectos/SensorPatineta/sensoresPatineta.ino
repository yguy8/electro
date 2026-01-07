#define TRIG 9
#define ECHO 10
#define RED 3
#define GREEN 5
#define BLUE 6
#define BUZZER 8

#define JOY_X A0
#define JOY_SW 7
#define LED1 11
#define LED2 12

bool ledsEncendidos = false;

// Frecuencias definidas
const int FREQ_CRITICA = 2500;   // rojo
const int FREQ_PRECAUCION = 1500; // naranja
const int FREQ_SWITCH = 700;     // confirmación

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(JOY_SW, INPUT_PULLUP);

  Serial.begin(9600);
}

long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duracion = pulseIn(ECHO, HIGH);
  long distancia = duracion * 0.034 / 2; // cm
  return distancia;
}

void loop() {
  long d = medirDistancia();
  Serial.print("Distancia: ");
  Serial.println(d);

  // --- Colores + buzzer ---
  if (d <= 8) {
    // Rojo + alarma rápida
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    tone(BUZZER, FREQ_CRITICA, 120); // tono agudo
    delay(120);
  } else if (d <= 15) {
    // Naranja + alarma lenta
    analogWrite(RED, 255);
    analogWrite(GREEN, 150);
    analogWrite(BLUE, 0);
    tone(BUZZER, FREQ_PRECAUCION, 250); // tono medio
    delay(600);
  } else {
    // Apagado
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    noTone(BUZZER);
  }

  // --- Joystick + LEDs blancos ---
  int xVal = analogRead(JOY_X); // 0–1023
  int swVal = digitalRead(JOY_SW);

  int brillo = map(xVal, 0, 1023, 0, 255);

  if (swVal == LOW) {
    ledsEncendidos = !ledsEncendidos;
    // Pequeño beep de confirmación
    tone(BUZZER, FREQ_SWITCH, 100);
    delay(300); // debounce
  }

  if (ledsEncendidos) {
    analogWrite(LED1, brillo);
    analogWrite(LED2, brillo);
  } else {
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
  }
}
