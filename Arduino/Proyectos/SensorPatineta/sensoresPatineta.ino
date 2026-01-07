#define TRIG 9
#define ECHO 10
#define RED 3
#define GREEN 5
#define BLUE 6
#define BUZZER 8

#define JOY_X A0
#define JOY_Y A1
#define JOY_SW 7
#define LED1 11
#define LED2 12

bool ledsEncendidos = false;
bool modoParpadeo = false;

// Frecuencias buzzer
const int FREQ_CRITICA = 2500;   // rojo
const int FREQ_PRECAUCION = 1500; // naranja
const int FREQ_SWITCH = 700;     // confirmación
const int FREQ_RELE = 1000;      // clic tipo relé

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

  // --- RGB + buzzer según distancia ---
  if (d <= 8) {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    tone(BUZZER, FREQ_CRITICA, 120);
    delay(120);
  } else if (d <= 15) {
    analogWrite(RED, 255);
    analogWrite(GREEN, 150);
    analogWrite(BLUE, 0);
    tone(BUZZER, FREQ_PRECAUCION, 250);
    delay(600);
  } else {
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    noTone(BUZZER);
  }

  // --- Joystick + LEDs blancos ---
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  int swVal = digitalRead(JOY_SW);

  // Switch: enciende/apaga LEDs en modo fijo
  if (swVal == LOW) {
    ledsEncendidos = !ledsEncendidos;
    modoParpadeo = false; // al presionar switch cancela parpadeo
    tone(BUZZER, FREQ_SWITCH, 100);
    delay(300); // debounce
  }

  if (ledsEncendidos) {
    // X = 0 → parpadeo tipo direccional
    if (xVal < 50) {
      modoParpadeo = true;
    } else if (xVal > 970) {
      modoParpadeo = false; // LEDs fijos
    }

    if (modoParpadeo) {
      // Parpadeo con clic de relé
      analogWrite(LED1, 255);
      analogWrite(LED2, 255);
      tone(BUZZER, FREQ_RELE, 100);
      delay(300);
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      noTone(BUZZER);
      delay(300);
    } else {
      // LEDs fijos, brillo controlado por Y
      int brillo = 128; // valor base

      if (yVal > 970) {
        brillo = 255; // máximo brillo
      } else if (yVal < 50) {
        brillo = 50; // brillo bajo
      }

      analogWrite(LED1, brillo);
      analogWrite(LED2, brillo);
    }
  } else {
    // LEDs apagados
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    noTone(BUZZER);
  }
}
