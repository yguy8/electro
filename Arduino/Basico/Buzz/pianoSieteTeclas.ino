#include <CapacitiveSensor.h>

// Configuración de sensores (pin común = 2, pines de recepción = 3–9)
CapacitiveSensor cs1 = CapacitiveSensor(2,3);
CapacitiveSensor cs2 = CapacitiveSensor(2,4);
CapacitiveSensor cs3 = CapacitiveSensor(2,5);
CapacitiveSensor cs4 = CapacitiveSensor(2,6);
CapacitiveSensor cs5 = CapacitiveSensor(2,7);
CapacitiveSensor cs6 = CapacitiveSensor(2,8);
CapacitiveSensor cs7 = CapacitiveSensor(2,9);

int buzzer = 10;

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

  if(val1 > 300) tone(buzzer, 262);   // Do
  else if(val2 > 300) tone(buzzer, 294); // Re
  else if(val3 > 300) tone(buzzer, 330); // Mi
  else if(val4 > 300) tone(buzzer, 349); // Fa
  else if(val5 > 300) tone(buzzer, 392); // Sol
  else if(val6 > 300) tone(buzzer, 440); // La
  else if(val7 > 300) tone(buzzer, 494); // Si
  else noTone(buzzer);
}
