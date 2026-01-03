#include <LiquidCrystal.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Joystick
const int joyX = A0;           // Navegación horizontal del menú
const int joyY = A1;           // Ajuste de brillo/velocidad
const int joyButton = 8;

// Pines RGB (PWM)
const int ledR = 9;
const int ledG = 10;
const int ledB = 11;

// Menú de opciones
enum Opcion {
  APAGAR = 0,
  ROJO, VERDE, AZUL, AMARILLO, CIAN, MAGENTA, BLANCO, MORADO, NARANJA, AZULCOBALTO,
  FADE, PULSO, ARCOIRIS, PARPADEO
};

const char* opciones[] = {
  "Apagar", "Rojo", "Verde", "Azul", "Amarillo", "Cian", "Magenta",
  "Blanco", "Morado", "Naranja", "AzulCobalto",
  "Fade", "Pulso", "Arcoiris", "Parpadeo"
};
const int totalOpciones = sizeof(opciones) / sizeof(opciones[0]);

// Estado
int menuIndex = 0;
int lastButton = HIGH;
unsigned long buttonPressStart = 0;

// Brillo y velocidad
int brillo = 255;           // 0-255
int velocidad = 50;         // ms por paso (menor = más rápido)

// Color actual (antes de aplicar brillo)
int baseR = 0, baseG = 0, baseB = 0;

// Timers para efectos
unsigned long lastUpdate = 0;
int efectoStep = 0;

// Flags de efectos
bool efectoActivo = false;
Opcion efectoTipo = APAGAR;

// Umbrales joystick
const int deadZone = 40;    // zona muerta para evitar ruido
const int lowThreshold = 300;
const int highThreshold = 700;

// ------------------ Utilidades de color ------------------

void writePWM(int r, int g, int b) {
  // Aplica brillo global (escala lineal)
  int rScaled = (r * brillo) / 255;
  int gScaled = (g * brillo) / 255;
  int bScaled = (b * brillo) / 255;

  analogWrite(ledR, rScaled);
  analogWrite(ledG, gScaled);
  analogWrite(ledB, bScaled);
}

void setBaseColor(int r, int g, int b) {
  baseR = r; baseG = g; baseB = b;
  writePWM(r, g, b);
}

void apagar() {
  baseR = baseG = baseB = 0;
  writePWM(0, 0, 0);
}

// ------------------ Map de colores fijos ------------------

void aplicarColorFijo(Opcion opcion) {
  switch (opcion) {
    case ROJO:        setBaseColor(255, 0, 0); break;
    case VERDE:       setBaseColor(0, 255, 0); break;
    case AZUL:        setBaseColor(0, 0, 255); break;
    case AMARILLO:    setBaseColor(255, 255, 0); break;
    case CIAN:        setBaseColor(0, 255, 255); break;
    case MAGENTA:     setBaseColor(255, 0, 255); break;
    case BLANCO:      setBaseColor(255, 255, 255); break;
    case MORADO:      setBaseColor(128, 0, 128); break;
    case NARANJA:     setBaseColor(255, 45, 0); break;        // como tu primer sketch
    case AZULCOBALTO: setBaseColor(0, 71, 171); break;        // azul cobalto
    default:          apagar(); break;
  }
}

// ------------------ Efectos ------------------

// Fade in/out sobre el color base
void efectoFade() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad) {
    lastUpdate = now;

    // efectoStep oscila 0..255..0
    static int dir = 1;
    efectoStep += dir;
    if (efectoStep >= 255) { efectoStep = 255; dir = -1; }
    if (efectoStep <= 0)   { efectoStep = 0;   dir = 1; }

    int r = (baseR * efectoStep) / 255;
    int g = (baseG * efectoStep) / 255;
    int b = (baseB * efectoStep) / 255;
    writePWM(r, g, b);
  }
}

// Pulso tipo “respiración” (curva seno aproximada con tabla simple)
void efectoPulso() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad) {
    lastUpdate = now;

    // rampa triangular 0..255..0
    static int dir = 1;
    efectoStep += dir * 5; // pasos un poco más grandes
    if (efectoStep >= 255) { efectoStep = 255; dir = -1; }
    if (efectoStep <= 0)   { efectoStep = 0;   dir = 1; }

    // aplicar al brillo relativo del color base
    int r = (baseR * efectoStep) / 255;
    int g = (baseG * efectoStep) / 255;
    int b = (baseB * efectoStep) / 255;
    writePWM(r, g, b);
  }
}

// Arcoíris continuo (HSV a RGB aproximado)
void efectoArcoiris() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad) {
    lastUpdate = now;

    // hue 0..359
    efectoStep = (efectoStep + 1) % 360;
    float h = efectoStep;
    float s = 1.0f;
    float v = 1.0f;

    int r, g, b;
    // Conversión simple HSV->RGB
    int i = int(h / 60) % 6;
    float f = (h / 60) - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    float rf, gf, bf;
    switch (i) {
      case 0: rf = v; gf = t; bf = p; break;
      case 1: rf = q; gf = v; bf = p; break;
      case 2: rf = p; gf = v; bf = t; break;
      case 3: rf = p; gf = q; bf = v; break;
      case 4: rf = t; gf = p; bf = v; break;
      case 5: rf = v; gf = p; bf = q; break;
    }
    r = int(rf * 255);
    g = int(gf * 255);
    b = int(bf * 255);

    // actualiza base para que la LCD muestre RGB del arcoíris
    baseR = r; baseG = g; baseB = b;
    writePWM(r, g, b);
  }
}

// Parpadeo ON/OFF del color base
void efectoParpadeo() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad * 5) {  // más pausado
    lastUpdate = now;
    static bool on = false;
    on = !on;
    if (on) writePWM(baseR, baseG, baseB);
    else    writePWM(0, 0, 0);
  }
}

// Dispatcher de efectos
void actualizarEfectos() {
  if (!efectoActivo) return;
  switch (efectoTipo) {
    case FADE:     efectoFade(); break;
    case PULSO:    efectoPulso(); break;
    case ARCOIRIS: efectoArcoiris(); break;
    case PARPADEO: efectoParpadeo(); break;
    default: break;
  }
}

// ------------------ LCD ------------------

void mostrarMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu:");
  lcd.setCursor(0, 1);
  lcd.print(opciones[menuIndex]);
}

void mostrarEstado() {
  lcd.clear();
  // Línea 1: nombre + brillo
  lcd.setCursor(0, 0);
  lcd.print(opciones[menuIndex]);
  lcd.print(" B:");
  lcd.print(brillo);

  // Línea 2: RGB + efecto
  lcd.setCursor(0, 1);
  lcd.print(baseR); lcd.print(",");
  lcd.print(baseG); lcd.print(",");
  lcd.print(baseB);

  // muestra efecto si activo
  if (efectoActivo) {
    lcd.print(" ");
    switch (efectoTipo) {
      case FADE:     lcd.print("Fade"); break;
      case PULSO:    lcd.print("Pulso"); break;
      case ARCOIRIS: lcd.print("Arc"); break;
      case PARPADEO: lcd.print("Blink"); break;
      default: break;
    }
  }
}

// ------------------ Control ------------------

void ejecutarOpcion(int opcion) {
  // Apagar efectos cuando se selecciona color fijo
  efectoActivo = false;
  efectoTipo = APAGAR;
  efectoStep = 0;
  lastUpdate = millis();

  switch (opcion) {
    case APAGAR:      apagar(); break;
    case ROJO:
    case VERDE:
    case AZUL:
    case AMARILLO:
    case CIAN:
    case MAGENTA:
    case BLANCO:
    case MORADO:
    case NARANJA:
    case AZULCOBALTO:
      aplicarColorFijo((Opcion)opcion);
      break;

    case FADE:
    case PULSO:
    case ARCOIRIS:
    case PARPADEO:
      // Al activar un efecto: si es Arcoiris, la base se gestiona dentro del efecto
      if (opcion != ARCOIRIS && baseR==0 && baseG==0 && baseB==0) {
        // Si estaba apagado, coloca un blanco suave de base
        setBaseColor(255, 255, 255);
      }
      efectoActivo = true;
      efectoTipo = (Opcion)opcion;
      efectoStep = 0;
      lastUpdate = millis();
      break;
  }

  mostrarEstado();
}

// ------------------ Setup y Loop ------------------

void setup() {
  lcd.begin(16, 2);
  pinMode(joyButton, INPUT_PULLUP);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  // Estado inicial
  aplicarColorFijo(AZUL);       // color por defecto
  mostrarMenu();
}

void loop() {
  // Lectura de joystick
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int reading = digitalRead(joyButton);

  // Navegación con eje X
  if (xValue < lowThreshold) {
    menuIndex = (menuIndex - 1 + totalOpciones) % totalOpciones;
    mostrarMenu();
    delay(180); // pequeño debounce
  } else if (xValue > highThreshold) {
    menuIndex = (menuIndex + 1) % totalOpciones;
    mostrarMenu();
    delay(180);
  }

  // Ajuste de brillo con eje Y (arriba = más brillo, abajo = menos)
  // Solo si se sale de la zona muerta
  if (abs(yValue - 512) > deadZone) {
    if (yValue < lowThreshold) {
      brillo = min(255, brillo + 5);
      writePWM(baseR, baseG, baseB);
      mostrarEstado();
      delay(60);
    } else if (yValue > highThreshold) {
      brillo = max(0, brillo - 5);
      writePWM(baseR, baseG, baseB);
      mostrarEstado();
      delay(60);
    }
  }

  // Pulsación corta/larga del botón:
  // - Corta: ejecutar opción del menú.
  // - Larga (>700 ms): alternar efecto ON/OFF si la opción es un efecto.
  if (reading == LOW && lastButton == HIGH) {
    buttonPressStart = millis();
  }
  if (reading == LOW && lastButton == LOW) {
    // manteniendo presionado
    if (millis() - buttonPressStart > 700) {
      // larga: si estamos en un efecto, alternar
      if (menuIndex >= FADE) {
        if (efectoActivo) {
          efectoActivo = false;
          efectoTipo = APAGAR;
          writePWM(baseR, baseG, baseB);
        } else {
          efectoActivo = true;
          efectoTipo = (Opcion)menuIndex;
          efectoStep = 0;
          lastUpdate = millis();
        }
        mostrarEstado();
        // esperar hasta soltar para no seguir disparando
        while (digitalRead(joyButton) == LOW) { actualizarEfectos(); }
      }
    }
  }
  if (reading == HIGH && lastButton == LOW) {
    // soltó: si fue corta, ejecutar opción
    if (millis() - buttonPressStart <= 700) {
      ejecutarOpcion(menuIndex);
    }
  }
  lastButton = reading;

  // Ajuste de velocidad del efecto con pequeños giros del eje Y cuando un efecto está activo
  if (efectoActivo) {
    if (yValue < lowThreshold) {
      velocidad = max(10, velocidad - 2);   // más rápido
    } else if (yValue > highThreshold) {
      velocidad = min(200, velocidad + 2);  // más lento
    }
  }

  // Actualización no bloqueante de efectos
  actualizarEfectos();
}
