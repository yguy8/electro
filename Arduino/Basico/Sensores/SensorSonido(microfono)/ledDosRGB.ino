// Pin del micrófono
int micPin = A0;

// Pines del primer LED RGB
int redPin1   = 9;
int greenPin1 = 10;
int bluePin1  = 11;

// Pines del segundo LED RGB
int redPin2   = 6;
int greenPin2 = 5;
int bluePin2  = 3;

void setup() {
  Serial.begin(9600);

  // Configurar pines del primer LED
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);

  // Configurar pines del segundo LED
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);
}

void loop() {
  // Leer el valor del micrófono
  int valorSonido = analogRead(micPin);

  // Umbral para detectar sonido
  int umbral = 100;

  if (valorSonido > umbral) {
    // Colores aleatorios para el primer LED
    int r1 = random(0, 256);
    int g1 = random(0, 256);
    int b1 = random(0, 256);

    analogWrite(redPin1, r1);
    analogWrite(greenPin1, g1);
    analogWrite(bluePin1, b1);

    // Colores aleatorios para el segundo LED
    int r2 = random(0, 256);
    int g2 = random(0, 256);
    int b2 = random(0, 256);

    analogWrite(redPin2, r2);
    analogWrite(greenPin2, g2);
    analogWrite(bluePin2, b2);

    delay(200); // pequeño retardo para ver el cambio
  } else {
    // Apagar ambos LEDs
    analogWrite(redPin1, 0);
    analogWrite(greenPin1, 0);
    analogWrite(bluePin1, 0);

    analogWrite(redPin2, 0);
    analogWrite(greenPin2, 0);
    analogWrite(bluePin2, 0);
  }
}
