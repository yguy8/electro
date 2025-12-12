#include <CapacitiveSensor.h>

// Configuración de sensores (pin común = 3, pines de recepción = 4–10)
CapacitiveSensor cs1 = CapacitiveSensor(3,4);
CapacitiveSensor cs2 = CapacitiveSensor(3,5);
CapacitiveSensor cs3 = CapacitiveSensor(3,6);
CapacitiveSensor cs4 = CapacitiveSensor(3,7);
CapacitiveSensor cs5 = CapacitiveSensor(3,8);
CapacitiveSensor cs6 = CapacitiveSensor(3,9);
CapacitiveSensor cs7 = CapacitiveSensor(3,10);

int buzzer = 2;

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long val1 = cs1.capacitiveSensor(30);
  long val2 = cs2.capacitiveSensor(30);
  long val3 = cs3.capacitiveSensor(30);
  long val4 = cs4.capacitiveSensor(30);
  long val5 = cs5.capacitiveSensor(30);
  long val6 = cs6.capacitiveSensor(30);
  long val7 = cs7.capacitiveSensor(30);

  if(val1 > 100) tone(buzzer, 262);   // Do
  else if(val2 > 100) tone(buzzer, 294); // Re
  else if(val3 > 100) tone(buzzer, 330); // Mi
  else if(val4 > 100) tone(buzzer, 349); // Fa
  else if(val5 > 100) tone(buzzer, 392); // Sol
  else if(val6 > 100) tone(buzzer, 440); // La
  else if(val7 > 100) tone(buzzer, 494); // Si
  else noTone(buzzer);
}
