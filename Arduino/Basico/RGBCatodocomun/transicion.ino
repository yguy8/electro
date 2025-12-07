// Pines de los LEDs RGB
int redPins[]   = {9, 6};
int greenPins[] = {10, 5};
int bluePins[]  = {11, 3};

int numLEDs = 2;

// Variables para el ciclo
int r = 0, g = 0, b = 0;
int fase = 0; // fase del ciclo
int paso = 1; // incremento de brillo

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLEDs; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
  }
}

void loop() {
  // Ciclo fluido de colores
  switch (fase) {
    case 0: // subir rojo
      r += paso;
      if (r >= 255) { r = 255; fase = 1; }
      break;
    case 1: // subir verde
      g += paso;
      if (g >= 255) { g = 255; fase = 2; }
      break;
    case 2: // bajar rojo
      r -= paso;
      if (r <= 0) { r = 0; fase = 3; }
      break;
    case 3: // subir azul
      b += paso;
      if (b >= 255) { b = 255; fase = 4; }
      break;
    case 4: // bajar verde
      g -= paso;
      if (g <= 0) { g = 0; fase = 5; }
      break;
    case 5: // subir rojo
      r += paso;
      if (r >= 255) { r = 255; fase = 6; }
      break;
    case 6: // bajar azul
      b -= paso;
      if (b <= 0) { b = 0; fase = 0; } // reinicia ciclo
      break;
  }

  // Aplicar el color actual a todos los LEDs
  for (int i = 0; i < numLEDs; i++) {
    analogWrite(redPins[i], r);
    analogWrite(greenPins[i], g);
    analogWrite(bluePins[i], b);
  }

  delay(5); // velocidad del cambio (más pequeño = más fluido)
}
