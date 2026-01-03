#include <LiquidCrystal.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Joystick
int joyX = A0;
int joyButton = 8;

// Pines RGB
int ledR = 9;
int ledG = 10;
int ledB = 11;

// Menú
int menuIndex = 0;
const char* opciones[] = {"Apagar", "Rojo", "Verde", "Azul", "Amarillo", "Magenta", "Cian", "Blanco"};
int totalOpciones = 8;

// Estado botón
int lastButton = HIGH;

void setup() {
  lcd.begin(16, 2);
  pinMode(joyButton, INPUT_PULLUP);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  mostrarMenu();
}

void loop() {
  int xValue = analogRead(joyX);
  int reading = digitalRead(joyButton);

  // Movimiento con joystick
  if (xValue < 250) {
    menuIndex = (menuIndex - 1 + totalOpciones) % totalOpciones;
    mostrarMenu();
    delay(250);
  } else if (xValue > 750) {
    menuIndex = (menuIndex + 1) % totalOpciones;
    mostrarMenu();
    delay(250);
  }

  // Selección con botón
  if (reading == LOW && lastButton == HIGH) {
    ejecutarOpcion(menuIndex);
    delay(200);
  }
  lastButton = reading;
}

void mostrarMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu:");
  lcd.setCursor(0, 1);
  lcd.print(opciones[menuIndex]);
}

void ejecutarOpcion(int opcion) {
  // Apagar todos primero
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);

  switch (opcion) {
    case 1: digitalWrite(ledR, HIGH); break;                  // Rojo
    case 2: digitalWrite(ledG, HIGH); break;                  // Verde
    case 3: digitalWrite(ledB, HIGH); break;                  // Azul
    case 4: digitalWrite(ledR, HIGH); digitalWrite(ledG, HIGH); break; // Amarillo
    case 5: digitalWrite(ledR, HIGH); digitalWrite(ledB, HIGH); break; // Magenta
    case 6: digitalWrite(ledG, HIGH); digitalWrite(ledB, HIGH); break; // Cian
    case 7: digitalWrite(ledR, HIGH); digitalWrite(ledG, HIGH); digitalWrite(ledB, HIGH); break; // Blanco
    case 0: default: break; // Apagar
  }
}
