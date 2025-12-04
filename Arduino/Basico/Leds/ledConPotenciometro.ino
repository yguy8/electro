int potPin = A0;
int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int valor = analogRead(potPin);          // Lee el potenciómetro (0-1023)
  int brillo = map(valor, 0, 1023, 0, 255); // Escala a rango PWM
  analogWrite(ledPin, brillo);             // Ajusta brillo del LED
}
