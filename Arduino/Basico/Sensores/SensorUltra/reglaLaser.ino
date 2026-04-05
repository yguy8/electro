//configuración y pines de la pantalla
#include <LiquidCrystal.h>
int rs = 7;
int e = 6;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
//pines del sensor ultrasonico
int trigPin = 11; 
int echoPin = 10;
//pin del laser
int laserPin = 8;

long duration;
int distance;
int safetyDistance;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(laserPin, OUTPUT);
}

void loop() {
  digitalWrite(laserPin, HIGH);

  //limpia el trigPin 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //selecciona el trigPin por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // lee el echoPin
  duration = pulseIn(echoPin, HIGH);
  //calcula la distancia
  distance = duration*0.034/2;


  //mostrar en pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print(distance);
  lcd.print("cm   ");
  delay(250);

  //prueba de que funciona bien el sensor ultrasonico
  // Serial.print(distance);
  // Serial.println(" cm");
  // delay(5000);
}
