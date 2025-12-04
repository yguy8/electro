int potPin = A0;
int ledPins[4] = {3, 5, 6, 9}; // Pines de los 4 LEDs

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int valor = analogRead(potPin);          // 0 - 1023
  int nivel = map(valor, 0, 1023, 0, 4);   // Escala a 4 niveles (0,1,2,3,4)

  // Enciende LEDs según el nivel
  for (int i = 0; i < 4; i++) {
    if (i < nivel) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
