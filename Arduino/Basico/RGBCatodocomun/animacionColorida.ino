// Pines de los LEDs RGB
int redPins[]   = {9, 6};
int greenPins[] = {10, 5};
int bluePins[]  = {11, 3};

int numLEDs = 2;

// Variable para elegir el modo (0 = fuego, 1 = agua)
int modo = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLEDs; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
  }
  Serial.println("Escribe 'fuego' o 'agua' en el monitor serial para cambiar el efecto.");
}

void loop() {
  // Cambiar modo desde el monitor serial
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if (comando.equalsIgnoreCase("fuego")) {
      modo = 0;
      Serial.println("Modo fuego activado");
    } else if (comando.equalsIgnoreCase("agua")) {
      modo = 1;
      Serial.println("Modo agua activado");
    }
  }

  if (modo == 0) {
    efectoFuego();
  } else {
    efectoAgua();
  }
}

//Efecto fuego: parpadeo aleatorio en tonos cálidos
void efectoFuego() {
  int r = random(180, 255);   // Rojo fuerte
  int g = random(50, 180);    // Verde medio (para naranja/amarillo)
  int b = random(0, 50);      // Azul bajo (casi apagado)

  aplicarColor(r, g, b);
  delay(random(50, 150)); // parpadeo irregular
}

// Efecto agua: transición suave en tonos fríos
void efectoAgua() {
  static int r = 0, g = 0, b = 255;
  static int paso = 1;

  // Oscilar entre azul y cian
  g += paso;
  if (g >= 255 || g <= 0) paso = -paso;

  aplicarColor(r, g, b);
  delay(20); // transición suave
}

// Función para aplicar color a todos los LEDs
void aplicarColor(int r, int g, int b) {
  for (int i = 0; i < numLEDs; i++) {
    analogWrite(redPins[i], r);
    analogWrite(greenPins[i], g);
    analogWrite(bluePins[i], b);
  }
}
