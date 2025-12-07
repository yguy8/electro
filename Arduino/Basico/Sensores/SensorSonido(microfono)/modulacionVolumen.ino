// Pin del micrófono
int micPin = A0;

// Pines de los LEDs RGB (dos LEDs)
int redPins[]   = {9, 6};   // Rojo
int greenPins[] = {10, 5};  // Verde
int bluePins[]  = {11, 3};  // Azul

int numLEDs = 2; // Número de LEDs RGB

// Paleta de colores (8 colores definidos)
int colores[8][3] = {
  {255, 0, 0},     // Rojo
  {0, 255, 0},     // Verde
  {0, 0, 255},     // Azul
  {255, 255, 0},   // Amarillo
  {0, 255, 255},   // Cian
  {255, 0, 255},   // Magenta
  {255, 255, 255}, // Blanco
  {128, 0, 128}    // Morado
};

int indiceColor = 0; // Índice del color actual

void setup() {
  Serial.begin(9600);

  // Configurar todos los pines como salida
  for (int i = 0; i < numLEDs; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
  }
}

void loop() {
  int valorSonido = analogRead(micPin);   // Lectura del micrófono (0-1023)
  int umbral = 100;

  if (valorSonido > umbral) {
    // Escalar el valor del sonido a rango de brillo (0-255)
    int brillo = map(valorSonido, umbral, 1023, 0, 255);
    if (brillo < 0) brillo = 0;
    if (brillo > 255) brillo = 255;

    // Tomar el color actual de la paleta
    int r = colores[indiceColor][0];
    int g = colores[indiceColor][1];
    int b = colores[indiceColor][2];

    // Ajustar el color según el brillo
    int rMod = (r * brillo) / 255;
    int gMod = (g * brillo) / 255;
    int bMod = (b * brillo) / 255;

    // Aplicar el color modulado a todos los LEDs
    for (int i = 0; i < numLEDs; i++) {
      analogWrite(redPins[i], rMod);
      analogWrite(greenPins[i], gMod);
      analogWrite(bluePins[i], bMod);
    }

    // Avanzar al siguiente color cada cierto tiempo
    static unsigned long lastChange = 0;
    if (millis() - lastChange > 500) { // cada medio segundo cambia color
      indiceColor++;
      if (indiceColor >= 8) indiceColor = 0;
      lastChange = millis();
    }

  } else {
    // Apagar LEDs si no hay sonido
    for (int i = 0; i < numLEDs; i++) {
      analogWrite(redPins[i], 0);
      analogWrite(greenPins[i], 0);
      analogWrite(bluePins[i], 0);
    }
  }
}
