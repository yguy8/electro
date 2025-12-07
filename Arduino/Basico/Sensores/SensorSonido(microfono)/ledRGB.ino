// Pin del micrófono
int micPin = A0;

// Pines del LED RGB
int redPin   = 9;
int greenPin = 10;
int bluePin  = 11;

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Leer el valor del micrófono
  int valorSonido = analogRead(micPin);
  //Serial.println(valorSonido); //lecturas del micro
  //delay(2000);

  // Umbral para detectar sonido (ajustar segun la lectura deseada)
  int umbral = 100;

  if (valorSonido > umbral) {
    // Si hay sonido, cambiar color aleatorio en el RGB
    int r = random(0, 256);
    int g = random(0, 256);
    int b = random(0, 256);

    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);

    delay(200); // pequeño retardo para ver el cambio
  } else {
    // Si no hay sonido, apagar el LED
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
}
