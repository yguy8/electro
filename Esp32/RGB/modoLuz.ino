// Pines del LED RGB (cátodo común)
const int redPin   = 25;
const int greenPin = 26;
const int bluePin  = 27;

String comando = "";
bool modoNoche = true; // por defecto

void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.println("Escribe 'modoNoche' o 'modoMedi' en el monitor serial");
}

void loop() {
  // Leer comando serial
  if (Serial.available() > 0) {
    comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando.equalsIgnoreCase("modoNoche")) {
      modoNoche = true;
      Serial.println("Modo noche activado (colores cálidos)");
    } else if (comando.equalsIgnoreCase("modoMedi")) {
      modoNoche = false;
      Serial.println("Modo meditación activado (colores fríos suaves)");
    }
  }

  if (modoNoche) {
    // Colores cálidos: rojo → naranja → amarillo
    for (int i = 0; i <= 255; i++) {
      analogWrite(redPin, 250);   // rojo dominante
      analogWrite(greenPin, i/3);   // verde sube para formar naranja/amarillo
      analogWrite(bluePin, 0);    // sin azul
      delay(30);
    }
    for (int i = 255; i >= 0; i--) {
      analogWrite(redPin, 250);
      analogWrite(greenPin, i/3);
      analogWrite(bluePin, 0);
      delay(30);
    }
  } else {
    // Colores fríos suaves: azul → verde
    for (int i = 0; i <= 255; i++) {
      analogWrite(redPin, 0);     // sin rojo
      analogWrite(greenPin, i/2); // verde suave
      analogWrite(bluePin, i);    // azul dominante
      delay(30);
    }
    for (int i = 255; i >= 0; i--) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, i/2);
      analogWrite(bluePin, i);
      delay(30);
    }
  }
}
