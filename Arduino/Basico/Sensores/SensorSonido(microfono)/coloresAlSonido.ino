// Pin del micrófono
int micPin = A0;

// Pines de los LEDs RGB (dos LEDs)
int redPins[]   = {9, 6};   // Rojo en pin 6
int greenPins[] = {10, 5};   // Verde en pin 5
int bluePins[]  = {11, 3};  // Azul en 11 y 3 (ejemplo)

int numLEDs = 2; // Número de LEDs RGB

//Paleta de colores (8 colores definidos)
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
  int valorSonido = analogRead(micPin);
  int umbral = 100;

  if (valorSonido > umbral) {
    // Tomar el color actual de la paleta
    int r = colores[indiceColor][0];
    int g = colores[indiceColor][1];
    int b = colores[indiceColor][2];

    // Aplicar el color a todos los LEDs
    for (int i = 0; i < numLEDs; i++) {
      analogWrite(redPins[i], r);
      analogWrite(greenPins[i], g);
      analogWrite(bluePins[i], b);
    }

    // Avanzar al siguiente color
    indiceColor++;
    if (indiceColor >= 8) indiceColor = 0; // Reiniciar ciclo

    delay(150); // Retardo para ver el cambio
  } else {
    // Apagar LEDs si no hay sonido
    for (int i = 0; i < numLEDs; i++) {
      analogWrite(redPins[i], 0);
      analogWrite(greenPins[i], 0);
      analogWrite(bluePins[i], 0);
    }
  }
}
