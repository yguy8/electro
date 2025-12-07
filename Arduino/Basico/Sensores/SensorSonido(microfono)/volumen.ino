// entre más ruido cambia va de cyan, verde, amarillo hasta el rojo que volumen ruido máximo
// Pin del micrófono
int micPin = A0;

// Pines de los LEDs RGB (dos LEDs)
int redPins[]   = {9, 6};   // Rojo
int greenPins[] = {10, 5};  // Verde
int bluePins[]  = {11, 3};  // Azul

int numLEDs = 2; // Número de LEDs RGB

// Paleta de colores (4 colores definidos)
int colores[4][3] = {
  {0, 255, 255},   // Cian
  {0, 255, 0},     // Verde
  {255, 255, 0},   // Amarillo
  {224, 17, 95}    // Rojo rubí (RGB aproximado)
};

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

  // Escalar el sonido a un índice de color (0-3)
  // Umbral bajo = cian, medio = verde, más alto = amarillo, máximo = rojo rubí
  int indiceColor = map(valorSonido, 100, 1023, 0, 3);

  // Limitar el índice para que no se salga del rango
  if (indiceColor < 0) indiceColor = 0;
  if (indiceColor > 3) indiceColor = 3;

  // Tomar el color correspondiente
  int r = colores[indiceColor][0];
  int g = colores[indiceColor][1];
  int b = colores[indiceColor][2];

  // Aplicar el color a todos los LEDs
  for (int i = 0; i < numLEDs; i++) {
    analogWrite(redPins[i], r);
    analogWrite(greenPins[i], g);
    analogWrite(bluePins[i], b);
  }

  delay(50); // pequeño retardo para estabilidad
}
