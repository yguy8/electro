#define TRIG 9
#define ECHO 10
#define RED 3
#define GREEN 5
#define BLUE 6
#define BUZZER 8   // único buzzer pasivo

#define JOY_X A0
#define JOY_Y A1
#define JOY_SW 7
#define LED1 11
#define LED2 12

bool ledsEncendidos = false;
bool modoParpadeo = false;

// Frecuencias
const int FREQ_CRITICA = 2500;   // rojo (alarma aguda)
const int FREQ_PRECAUCION = 1500; // naranja (alarma media)
const int FREQ_SWITCH = 700;     // beep confirmación
const int FREQ_RELE = 800;      // clic tipo relé

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
  return duracion * 0.034 / 2; // cm
}

void loop() {
  long d = medirDistancia();

  // --- RGB + buzzer según distancia ---
  if (d <= 8) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    tone(BUZZER, FREQ_CRITICA, 120);
    delay(120);
    noTone(BUZZER);
    delay(120);
  } else if (d <= 15) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    tone(BUZZER, FREQ_PRECAUCION, 250);
    delay(250);
    noTone(BUZZER);
    delay(600);
  } else {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    noTone(BUZZER);
  }

  // --- Joystick + LEDs blancos ---
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  int swVal = digitalRead(JOY_SW);

  if (swVal == LOW) {
    ledsEncendidos = !ledsEncendidos;
    modoParpadeo = false; // cancela parpadeo
    tone(BUZZER, FREQ_SWITCH, 100); // beep confirmación
    delay(300);
    noTone(BUZZER);
  }

  if (ledsEncendidos) {
    // X = 0 → parpadeo tipo direccional
    if (xVal < 50) {
      modoParpadeo = true;
    } else if (xVal > 970) {
      modoParpadeo = false;
    }

    int brillo = 128;
    if (yVal > 970) brillo = 255;
    else if (yVal < 50) brillo = 50;

    if (modoParpadeo) {
      // Ambas luces parpadean juntas + clic relé
      analogWrite(LED1, brillo);
      analogWrite(LED2, brillo);
      tone(BUZZER, FREQ_RELE, 100); // clic relé
      delay(300);
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      noTone(BUZZER);
      delay(300);
    } else {
      // LEDs fijos
      analogWrite(LED1, brillo);
      analogWrite(LED2, brillo);
    }
  } else {
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    noTone(BUZZER);
  }
}
