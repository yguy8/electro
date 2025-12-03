#include <Servo.h>

const int pinServo = 3;
const int pinLdrIzq = A0;
const int pinLdrDer = A1;

// Configuración de ángulos del servo
int anguloCentro = 90;      // posición neutral
int anguloMin = 30;         // límite mínimo (ajusta según tu mecánica)
int anguloMax = 150;        // límite máximo

// Parámetros de control
int zonaMuerta = 20;        // diferencia mínima para actuar (reduce vibración)
float ganancia = 0.25;      // sensibilidad del movimiento (0.1–0.5 recomendable)

// Filtro simple
const int N = 10;           // muestras para promedio
int sumaIzq = 0, sumaDer = 0;
int idx = 0;
int bufferIzq[N], bufferDer[N];

Servo servo;
int anguloActual = anguloCentro;

void setup() {
  servo.attach(pinServo);
  servo.write(anguloActual);

  for (int i = 0; i < N; i++) {
    bufferIzq[i] = analogRead(pinLdrIzq);
    bufferDer[i] = analogRead(pinLdrDer);
    sumaIzq += bufferIzq[i];
    sumaDer += bufferDer[i];
    delay(5);
  }
}

void loop() {
  // Actualiza promedios móviles
  sumaIzq -= bufferIzq[idx];
  sumaDer -= bufferDer[idx];
  bufferIzq[idx] = analogRead(pinLdrIzq);
  bufferDer[idx] = analogRead(pinLdrDer);
  sumaIzq += bufferIzq[idx];
  sumaDer += bufferDer[idx];
  idx = (idx + 1) % N;

  int ldrIzq = sumaIzq / N;
  int ldrDer = sumaDer / N;

  // Calcula diferencia (positivo: más luz a la derecha)
  int dif = ldrDer - ldrIzq;

  // Aplica zona muerta
  if (abs(dif) < zonaMuerta) {
    // Mantén posición
  } else {
    // Ajuste proporcional
    int delta = (int)(ganancia * dif);

    anguloActual = constrain(anguloActual + delta, anguloMin, anguloMax);
    servo.write(anguloActual);
  }

  // Opcional: imprimir para depurar
  // Serial.print("Izq: "); Serial.print(ldrIzq);
  // Serial.print(" Der: "); Serial.print(ldrDer);
  // Serial.print(" Dif: "); Serial.print(dif);
  // Serial.print(" Ang: "); Serial.println(anguloActual);

  delay(20);
}
