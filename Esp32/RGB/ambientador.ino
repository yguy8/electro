// Pines del LED RGB (cátodo común)
const int redPin   = 25;
const int greenPin = 26;
const int bluePin  = 27;

// Sensor capacitivo TTP223B
const int sensorCap = 33;

// Potenciómetro
const int potPin = 34;

// Variables de control
int modo = 0; // 0 = noche, 1 = meditación, 2 = arcoíris
bool estadoAnterior = false;

int hue = 0; // para arcoíris

void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(sensorCap, INPUT);
  Serial.println("Toca el sensor para cambiar de modo.");
}

void loop() {
  // Leer sensor capacitivo (flanco ascendente)
  bool estadoActual = (digitalRead(sensorCap) == HIGH);
  if (estadoActual && !estadoAnterior) {
    modo++;
    if (modo > 2) modo = 0;
    Serial.print("Modo cambiado a: ");
    if (modo == 0) Serial.println("Noche (cálidos)");
    else if (modo == 1) Serial.println("Meditación (fríos suaves)");
    else Serial.println("Arcoíris automático");
  }
  estadoAnterior = estadoActual;

  // Leer potenciómetro para brillo
  int potValue = analogRead(potPin); // 0–4095
  int brillo = map(potValue, 0, 4095, 50, 255); // brillo mínimo 50

  int r = 0, g = 0, b = 0;

  if (modo == 0) {
    // Modo noche: cálidos (rojo/naranja/amarillo)
    r = brillo;
    g = brillo / 2;
    b = 0;
  } else if (modo == 1) {
    // Modo meditación: fríos suaves (azul/verde/morado)
    r = brillo / 3;
    g = brillo / 2;
    b = brillo;
  } else if (modo == 2) {
    //  Modo arcoíris automático
    hsvToRgb(hue, 255, brillo, &r, &g, &b);
    hue++;
    if (hue > 360) hue = 0;
    delay(20); // velocidad arcoíris
  }

  // Aplicar color al LED RGB
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);

  delay(10);
}

// Conversión HSV → RGB
void hsvToRgb(int h, int s, int v, int* r, int* g, int* b) {
  float hf = h / 60.0;
  int i = (int)hf;
  float f = hf - i;
  int p = (int)(v * (1.0 - s / 255.0));
  int q = (int)(v * (1.0 - f * s / 255.0));
  int t = (int)(v * (1.0 - (1.0 - f) * s / 255.0));

  switch (i) {
    case 0: *r = v; *g = t; *b = p; break;
    case 1: *r = q; *g = v; *b = p; break;
    case 2: *r = p; *g = v; *b = t; break;
    case 3: *r = p; *g = q; *b = v; break;
    case 4: *r = t; *g = p; *b = v; break;
    case 5: *r = v; *g = p; *b = q; break;
  }
}
