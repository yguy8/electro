// Pines de los LEDs RGB (dos LEDs)
int redPins[]   = {9, 6};   // Rojo
int greenPins[] = {10, 5};  // Verde
int bluePins[]  = {11, 3};  // Azul

int numLEDs = 2; // Número de LEDs RGB

// Color por defecto (Azul)
int r = 0;
int g = 0;
int b = 255;

void setup() {
  Serial.begin(9600);

  // Configurar todos los pines como salida
  for (int i = 0; i < numLEDs; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
  }

  // Aplicar el color inicial
  setColor(r, g, b);
  Serial.println("Color por defecto: Azul");
  Serial.println("Escribe un color en el monitor serial (rojo, verde, azul, amarillo, cian, magenta, blanco, morado)");
}

void loop() {
  // Si hay datos en el monitor serial
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim(); // quitar espacios y saltos de línea

    if (comando.equalsIgnoreCase("rojo")) {
      r = 255; g = 0; b = 0;
    } else if (comando.equalsIgnoreCase("verde")) {
      r = 0; g = 255; b = 0;
    } else if (comando.equalsIgnoreCase("azul")) {
      r = 0; g = 0; b = 255;
    } else if (comando.equalsIgnoreCase("amarillo")) {
      r = 255; g = 255; b = 0;
    } else if (comando.equalsIgnoreCase("cian")) {
      r = 0; g = 255; b = 255;
    } else if (comando.equalsIgnoreCase("magenta")) {
      r = 255; g = 0; b = 255;
    } else if (comando.equalsIgnoreCase("blanco")) {
      r = 255; g = 255; b = 255;
    } else if (comando.equalsIgnoreCase("morado")) {
      r = 128; g = 0; b = 128;
    } else {
      Serial.println("Comando no reconocido. Intenta con: rojo, verde, azul, amarillo, cian, magenta, blanco, morado.");
    }

    // Aplicar el nuevo color
    setColor(r, g, b);
    Serial.print("Color cambiado a: ");
    Serial.println(comando);
  }
}

// Función para aplicar el color a todos los LEDs
void setColor(int r, int g, int b) {
  for (int i = 0; i < numLEDs; i++) {
    analogWrite(redPins[i], r);
    analogWrite(greenPins[i], g);
    analogWrite(bluePins[i], b);
  }
}
