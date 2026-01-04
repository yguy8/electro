#include <LiquidCrystal.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Joystick
const int joyX = A0;
const int joyY = A1;
const int joyButton = 8;

// Pines RGB (PWM)
const int ledR = 9;
const int ledG = 10;
const int ledB = 11;

// Zumbador (buzzer)
const int buzzerPin = 12;

// ------------------ Menú ------------------
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

int menuIndex = 0;
int lastButton = HIGH;
unsigned long buttonPressStart = 0;

// Brillo y velocidad
int brillo = 255;
int velocidad = 50;

// Color base
int baseR = 0, baseG = 0, baseB = 0;

// Timers
unsigned long lastUpdate = 0;
int efectoStep = 0;

// Flags de efectos
bool efectoActivo = false;
Opcion efectoTipo = APAGAR;

// Joystick thresholds
const int deadZone = 40;
const int lowThreshold = 300;
const int highThreshold = 700;

// ------------------ Ahorro de energía ------------------
const unsigned long idleTimeout = 30000; // 30 s sin interacción
unsigned long lastInteraction = 0;
bool ahorroActivo = false;

// ------------------ Sonido buzz ------------------
void beep() {
  tone(buzzerPin, 1200, 100); // pitido corto
}

// ------------------ Utilidades ------------------
void writePWM(int r, int g, int b) {
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

// ------------------ Colores fijos ------------------
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
    case NARANJA:     setBaseColor(255, 45, 0); break;
    case AZULCOBALTO: setBaseColor(0, 71, 171); break;
    default:          apagar(); break;
  }
}

// ------------------ Efectos ------------------
void efectoFade() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad) {
    lastUpdate = now;
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

void efectoPulso() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad) {
    lastUpdate = now;
    static int dir = 1;
    efectoStep += dir * 5;
    if (efectoStep >= 255) { efectoStep = 255; dir = -1; }
    if (efectoStep <= 0)   { efectoStep = 0;   dir = 1; }
    int r = (baseR * efectoStep) / 255;
    int g = (baseG * efectoStep) / 255;
    int b = (baseB * efectoStep) / 255;
    writePWM(r, g, b);
  }
}

// -------- Nuevo Arcoiris por fases --------
int r = 0, g = 0, b = 0;
int fase = 0;
int paso = 1;

void efectoArcoiris() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad) {
    lastUpdate = now;
    switch (fase) {
      case 0: r += paso; if (r >= 255) { r = 255; fase = 1; } break;
      case 1: g += paso; if (g >= 255) { g = 255; fase = 2; } break;
      case 2: r -= paso; if (r <= 0)   { r = 0;   fase = 3; } break;
      case 3: b += paso; if (b >= 255) { b = 255; fase = 4; } break;
      case 4: g -= paso; if (g <= 0)   { g = 0;   fase = 5; } break;
      case 5: r += paso; if (r >= 255) { r = 255; fase = 6; } break;
      case 6: b -= paso; if (b <= 0)   { b = 0;   fase = 0; } break;
    }
    baseR = r; baseG = g; baseB = b;
    writePWM(r, g, b);
  }
}

void efectoParpadeo() {
  unsigned long now = millis();
  if (now - lastUpdate >= velocidad * 5) {
    lastUpdate = now;
    static bool on = false;
    on = !on;
    if (on) writePWM(baseR, baseG, baseB);
    else    writePWM(0, 0, 0);
  }
}

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

// ------------------ Ahorro: activar / desactivar ------------------
void activarAhorro() {
  ahorroActivo = true;
  lcd.noDisplay(); // apaga la LCD
  beep();          // pitido al entrar en modo ahorro
}

void desactivarAhorro() {
  ahorroActivo = false;
  lcd.display();   // enciende la LCD
  mostrarMenu();   // refresca menú
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
  lcd.setCursor(0, 0);
  lcd.print(opciones[menuIndex]);
  lcd.print(" B:");
  lcd.print(brillo);
  lcd.setCursor(0, 1);
  lcd.print(baseR); lcd.print(",");
  lcd.print(baseG); lcd.print(",");
  lcd.print(baseB);
  if (efectoActivo) {
    lcd.print(" ");
    switch (efectoTipo) {
      case FADE:     lcd.print("Fade"); break;
      case PULSO:    lcd.print("Pulso"); break;
      case ARCOIRIS: lcd.print("Arc");  break;
      case PARPADEO: lcd.print("Blink"); break;
      default: break;
    }
  }
}

// ------------------ Control ------------------
void ejecutarOpcion(int opcion) {
  efectoActivo = false;
  efectoTipo = APAGAR;
  efectoStep = 0;
  lastUpdate = millis();

  switch (opcion) {
    case APAGAR: apagar(); break;

    case ROJO: case VERDE: case AZUL: case AMARILLO:
    case CIAN: case MAGENTA: case BLANCO: case MORADO:
    case NARANJA: case AZULCOBALTO:
      aplicarColorFijo((Opcion)opcion);
      break;

    case FADE: case PULSO: case ARCOIRIS: case PARPADEO:
      if (opcion != ARCOIRIS && baseR==0 && baseG==0 && baseB==0) {
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

// ------------------ Setup ------------------
void setup() {
  lcd.begin(16, 2);
  pinMode(joyButton, INPUT_PULLUP);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  aplicarColorFijo(AZUL);   // color inicial
  mostrarMenu();

  lastInteraction = millis(); // inicia temporizador de ahorro
}

// ------------------ Loop ------------------
void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int reading = digitalRead(joyButton);

  // Detecta interacción → reinicia temporizador y sale de ahorro si estaba activo
  bool hayInteraccion = (xValue < lowThreshold) || (xValue > highThreshold) ||
                        (yValue < lowThreshold) || (yValue > highThreshold) ||
                        (reading == LOW);
  if (hayInteraccion) {
    lastInteraction = millis();
    if (ahorroActivo) desactivarAhorro();
  }

  // Navegación con eje X
  if (xValue < lowThreshold) {
    menuIndex = (menuIndex - 1 + totalOpciones) % totalOpciones;
    mostrarMenu();
    delay(180);
  } else if (xValue > highThreshold) {
    menuIndex = (menuIndex + 1) % totalOpciones;
    mostrarMenu();
    delay(180);
  }

  // Ajuste de brillo con eje Y
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

  // Pulsación corta/larga del botón
  if (reading == LOW && lastButton == HIGH) {
    buttonPressStart = millis();
  }
  if (reading == LOW && lastButton == LOW) {
    if (millis() - buttonPressStart > 700) {
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
        while (digitalRead(joyButton) == LOW) { actualizarEfectos(); }
      }
    }
  }
  if (reading == HIGH && lastButton == LOW) {
    if (millis() - buttonPressStart <= 700) {
      beep(); // pitido leve al confirmar selección
      ejecutarOpcion(menuIndex);
    }
  }
  lastButton = reading;

  // Ajuste de velocidad del efecto con eje Y
  if (efectoActivo) {
    if (yValue < lowThreshold) {
      velocidad = max(10, velocidad - 2);
    } else if (yValue > highThreshold) {
      velocidad = min(200, velocidad + 2);
    }
  }

  // Si pasa el tiempo → entra en ahorro
  if (!ahorroActivo && (millis() - lastInteraction > idleTimeout)) {
    activarAhorro();
  }

  // Actualización de efectos
  actualizarEfectos();
}
