//ahora ambos leds emiten el mismo color cuando detectan sonido

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
    // Colores aleatorios para ambos LED
    int r = random(0, 256);
    int g = random(0, 256);
    int b = random(0, 256);
//primer led
    analogWrite(redPin1, r);
    analogWrite(greenPin1, g);
    analogWrite(bluePin1, b);

//segundo led
    analogWrite(redPin2, r);
    analogWrite(greenPin2, g);
    analogWrite(bluePin2, b);

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
