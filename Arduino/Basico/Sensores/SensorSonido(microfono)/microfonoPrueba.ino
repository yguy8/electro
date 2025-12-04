int micPin = A0;
int ledPins[4] = {3, 5, 6, 9};
int umbral = 200; // Ajusta según el ambiente

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int valorSonido = analogRead(micPin); // 0 - 1023
  int nivel = map(valorSonido, 0, 1023, 0, 4); // Escala a 4 niveles

  // Enciende LEDs según el nivel de sonido
  for (int i = 0; i < 4; i++) {
    if (i < nivel) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
