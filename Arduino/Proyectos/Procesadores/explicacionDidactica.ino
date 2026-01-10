//es para explicar como funciona una cpu, tpu y gpu 
//explicando los procesos con leds y esta el menu escribiendo en la lcd el modo que se quiere

#include <LiquidCrystal.h>

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Filas y columnas de la matriz
int filas[3] = {8, 9, 10};
int columnas[3] = {11, 12, 13};

// Buzzer activo
int buzz = A3;

// LED indicador de fin de ciclo
int ledFin = A4;

String inputOption = "";   // texto recibido por Serial
int currentOption = -1;    // opción actualmente ejecutándose

void setup() {
  lcd.begin(16, 2);
  lcd.print("Menu Procesador");

  for (int i=0; i<3; i++) {
    pinMode(filas[i], OUTPUT);
    pinMode(columnas[i], OUTPUT);
    digitalWrite(filas[i], LOW);
    digitalWrite(columnas[i], HIGH);
  }

  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);

  pinMode(ledFin, OUTPUT);
  digitalWrite(ledFin, LOW);

  Serial.begin(9600);
  Serial.println("Escribe CPU, GPU o TPU:");
}

void loop() {
  // Leer entrada del Serial
  if (Serial.available() > 0) {
    inputOption = Serial.readStringUntil('\n');
    inputOption.trim(); // elimina espacios y saltos

    if (inputOption.equalsIgnoreCase("CPU")) {
      currentOption = 0;
      lcd.clear();
      lcd.print("Ejecutandose CPU");
    } else if (inputOption.equalsIgnoreCase("GPU")) {
      currentOption = 1;
      lcd.clear();
      lcd.print("Ejecutandose GPU");
    } else if (inputOption.equalsIgnoreCase("TPU")) {
      currentOption = 2;
      lcd.clear();
      lcd.print("Ejecutandose TPU");
    } else {
      lcd.clear();
      lcd.print("Opcion invalida");
      currentOption = -1;
    }
  }

  // Ejecutar la opción activa
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
