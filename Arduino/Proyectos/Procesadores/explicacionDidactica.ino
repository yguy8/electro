//es para explicar como funciona una cpu, tpu y gpu 
//explicando los procesos con leds y esta el menu escribiendo en la lcd el modo que se quiere

#include <LiquidCrystal.h>

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Filas y columnas de la matriz
int filas[3] = {8, 9, 10};
int columnas[3] = {11, 12, 13};

// Joystick
int joyX = A0;   // navegación izquierda/derecha
int joySW = A2;  // selección con botón

// Buzzer activo
int buzz = A3;

// LED indicador de fin de ciclo
int ledFin = A4;

int menuOption = 0;     // 0=CPU, 1=GPU, 2=TPU
int currentOption = -1; // opción actualmente ejecutándose

void setup() {
  lcd.begin(16, 2);
  lcd.print("Menu Procesador");

  for (int i=0; i<3; i++) {
    pinMode(filas[i], OUTPUT);
    pinMode(columnas[i], OUTPUT);
    digitalWrite(filas[i], LOW);
    digitalWrite(columnas[i], HIGH);
  }

  pinMode(joySW, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);

  pinMode(ledFin, OUTPUT);
  digitalWrite(ledFin, LOW);
}

void loop() {
  int xVal = analogRead(joyX);
  int swVal = digitalRead(joySW);

  // Navegación con joystick (izquierda/derecha)
  if (xVal < 300) { // izquierda
    menuOption--;
    if (menuOption < 0) menuOption = 2;
    delay(200);
  } else if (xVal > 700) { // derecha
    menuOption++;
    if (menuOption > 2) menuOption = 0;
    delay(200);
  }

  // Mostrar opción actual en LCD SIEMPRE
  lcd.clear();
  if (menuOption == 0) lcd.print("CPU: secuencial");
  else if (menuOption == 1) lcd.print("GPU: paralelo");
  else if (menuOption == 2) lcd.print("TPU: IA");

  // Confirmación con botón → activa ejecución indefinida
  if (swVal == LOW) {
    currentOption = menuOption; // guarda la opción seleccionada
    delay(300);
  }

  // Si hay una opción activa, ejecutarla en bucle
  if (currentOption == 0) cpuMode();
  else if (currentOption == 1) gpuMode();
  else if (currentOption == 2) tpuMode();
}

// --- Funciones de control LEDs ---
void apagarMatriz() {
  for (int f=0; f<3; f++) digitalWrite(filas[f], LOW);
  for (int c=0; c<3; c++) digitalWrite(columnas[c], HIGH);
}

void encenderLED(int fila, int columna) {
  apagarMatriz();
  digitalWrite(filas[fila], HIGH);
  digitalWrite(columnas[columna], LOW);
}

// --- MODO CPU ---
void cpuMode() {
  for (int f=0; f<3; f++) {
    for (int c=0; c<3; c++) {
      encenderLED(f, c);
      digitalWrite(buzz, HIGH);
      delay(200);
      digitalWrite(buzz, LOW);
      delay(300);
    }
  }
  cicloCompletado();
}

// --- MODO GPU ---
void gpuMode() {
  for (int f=0; f<3; f++) digitalWrite(filas[f], HIGH);
  for (int c=0; c<3; c++) digitalWrite(columnas[c], LOW);

  digitalWrite(buzz, HIGH);
  delay(100);
  digitalWrite(buzz, LOW);

  delay(400);
  apagarMatriz();

  cicloCompletado();
}

// --- MODO TPU ---
void tpuMode() {
  for (int i=0; i<3; i++) {
    encenderLED(i, i);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(100);
  }
  delay(300);
  apagarMatriz();

  cicloCompletado();
}

// --- LED indicador de fin de ciclo ---
void cicloCompletado() {
  digitalWrite(ledFin, HIGH);
  delay(300);
  digitalWrite(ledFin, LOW);
  delay(300);
}
