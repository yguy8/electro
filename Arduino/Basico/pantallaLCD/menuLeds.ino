#include <LiquidCrystal.h>

// Configuración LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Pines del joystick
int joyX = A0;
//int joyY = A1;
int joyButton = 8;

// Pines de LEDs
int ledWhite = 9;
int ledYellow = 10;
int ledBlue = 11;

// Variables de menú
int menuIndex = 0;
String opciones[] = {"LED Blanco", "LED Amarillo", "LED Azul"};
int totalOpciones = 3;

void setup() {
  lcd.begin(16, 2);

  pinMode(joyButton, INPUT_PULLUP);
  pinMode(ledWhite, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  mostrarMenu();
}

void loop() {
  int yValue = analogRead(joyX);
  int buttonState = digitalRead(joyButton);

  // Movimiento hacia arriba
  if (yValue < 400) {
    menuIndex--;
    if (menuIndex < 0) menuIndex = totalOpciones - 1;
    mostrarMenu();
    delay(300);
  }

  // Movimiento hacia abajo
  if (yValue > 600) {
    menuIndex++;
    if (menuIndex >= totalOpciones) menuIndex = 0;
    mostrarMenu();
    delay(300);
  }

  // Selección con botón
  if (buttonState == LOW) {
    ejecutarOpcion(menuIndex);
    delay(300);
  }
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
  digitalWrite(ledWhite, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledBlue, LOW);

  switch (opcion) {
    case 0:
      digitalWrite(ledWhite, HIGH);
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledYellow, LOW);
      break;
    case 1:
      digitalWrite(ledYellow, HIGH);
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledWhite, LOW);
      break;
    case 2:
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledWhite, LOW);
      break;
    default:
      digitalWrite(ledWhite, HIGH);
      digitalWrite(ledYellow, HIGH);
      digitalWrite(ledBlue, HIGH);
      break;
  }
}
