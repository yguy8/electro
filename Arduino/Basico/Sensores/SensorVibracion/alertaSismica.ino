// Sensor de vibración con alarma modulada sincronizada
const int pinSensor = 2;   // Sensor de vibración
const int ledAzul = 8;     // LED azul
const int ledRojo = 9;     // LED rojo (PWM)
const int buzzer = 10;     // Buzzer

unsigned long tiempoAnterior = 0;

void setup() {
  pinMode(pinSensor, INPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int estadoSensor = digitalRead(pinSensor);

  if (estadoSensor == HIGH) {
    // ALERTA: vibración detectada
    digitalWrite(ledAzul, LOW); // LED azul apagado
    alarmaModulada();           // LED rojo + buzzer sincronizados
  } else {
    //ESTABLE: sin vibración
    digitalWrite(ledRojo, LOW);   // LED rojo apagado
    digitalWrite(ledAzul, HIGH);  // LED azul encendido fijo
    pipRadar();                   // Pip cada 6 segundos
  }
}

// Función: alarma modulada (LED rojo + buzzer sincronizados)
void alarmaModulada() {
  // Subida de tono y brillo
  for (int valor = 400; valor <= 1000; valor += 10) {
    tone(buzzer, valor);                 // tono sube
    int brillo = map(valor, 400, 1000, 0, 255);
    analogWrite(ledRojo, brillo);        // brillo sube
    delay(10);
  }
  // Bajada de tono y brillo
  for (int valor = 1000; valor >= 400; valor -= 10) {
    tone(buzzer, valor);                 // tono baja
    int brillo = map(valor, 400, 1000, 255, 0);
    analogWrite(ledRojo, brillo);        // brillo baja
    delay(10);
  }
  noTone(buzzer);
}

// Pip corto cada 6 segundos (modo radar)
void pipRadar() {
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= 6000) {
    tiempoAnterior = tiempoActual;
    tone(buzzer, 1200); // pip agudo
    delay(150);
    noTone(buzzer);
  }
}
