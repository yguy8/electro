int micPin = A0;                 // Pin analógico del micrófono KY-037
int ledPins[4] = {3, 5, 6, 9};   // Pines de los LEDs
int umbral = 200;                // Umbral mínimo de sonido

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600); // Para ver valores en el monitor serial
}

void loop() {
  int valorSonido = analogRead(micPin);          // Lectura del micrófono (0-1023)
  Serial.println(valorSonido);                   // Mostrar en monitor serial

  if (valorSonido > umbral) {
    // Escalar el valor de sonido a rango PWM (0-255)
    int brillo = map(valorSonido, umbral, 1023, 0, 255);

    // Aplicar el mismo brillo a todos los LEDs
    for (int i = 0; i < 4; i++) {
      analogWrite(ledPins[i], brillo);
    }
  } else {
    // Si el sonido es bajo, apagar LEDs
    for (int i = 0; i < 4; i++) {
      analogWrite(ledPins[i], 0);
    }
  }
}
