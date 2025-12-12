#include <CapacitiveSensor.h>

// Configuración de sensores (pin común = 2, pines de recepción = 3,4,5,6)
CapacitiveSensor cs1 = CapacitiveSensor(2,3);
CapacitiveSensor cs2 = CapacitiveSensor(2,4);
CapacitiveSensor cs3 = CapacitiveSensor(2,5);
CapacitiveSensor cs4 = CapacitiveSensor(2,6);

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

  if(val1 > 300) tone(buzzer, 262);   // Do
  else if(val2 > 300) tone(buzzer, 349); // Fa (cuarta de Do)
  else if(val3 > 300) tone(buzzer, 466); // Si♭ (cuarta de Fa)
  else if(val4 > 300) tone(buzzer, 622); // Mi♭ (cuarta de Si♭)
  else noTone(buzzer);
}
