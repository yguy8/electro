// Pines del LED RGB (cátodo común)
const int redPin   = 25;
const int greenPin = 26;
const int bluePin  = 27;

int hue = 0; // tono inicial (0 = rojo)

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Convertir Hue (0–360) a RGB
  int r, g, b;
  hsvToRgb(hue, 255, 255, &r, &g, &b);

  // Aplicar al LED
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);

  // Avanzar el tono
  hue++;
  if (hue > 360) hue = 0;

  delay(20); // velocidad del cambio
}

// Función para convertir HSV a RGB
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
