// Sensor de vibración con LED azul respirando y pip sincronizado
const int pinSensor = 2;   // Sensor de vibración
const int ledAzul = 6;     // LED azul (PWM)
const int ledRojo = 9;     // LED rojo (PWM)
const int buzzer = 10;     // Buzzer

unsigned long tiempoAnterior = 0;

// Variables para efecto rojo modulando
int tonoActual = 400;
int direccionTono = 10;
int brilloRojo = 0;
int direccionBrillo = 5;

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
    alarmaModuladaPasoAPaso();  // LED rojo + buzzer sincronizados
  } else {
    // ESTABLE: sin vibración
    noTone(buzzer);             // buzzer apagado
    analogWrite(ledRojo, 0);    // LED rojo apagado
    efectoLedAzul();            // LED azul respirando
    pipRadar();                 // Pip cada 6 segundos + LED azul máximo
  }
}

// Función: alarma modulada paso a paso (sin bucles largos)
void alarmaModuladaPasoAPaso() {
  // actualizar tono
  tone(buzzer, tonoActual);
  tonoActual += direccionTono;
  if (tonoActual >= 1000 || tonoActual <= 400) {
    direccionTono = -direccionTono;
  }

  // actualizar brillo rojo
  analogWrite(ledRojo, brilloRojo);
  brilloRojo += direccionBrillo;
  if (brilloRojo >= 255 || brilloRojo <= 0) {
    direccionBrillo = -direccionBrillo;
  }

  delay(10); // velocidad de cambio
}

// Función: LED azul respirando
void efectoLedAzul() {
  static int brillo = 0;
  static int direccion = 5;

  brillo += direccion;
  if (brillo >= 255) {
    brillo = 255;
    direccion = -5;
  } else if (brillo <= 0) {
    brillo = 0;
    direccion = 5;
  }

  analogWrite(ledAzul, brillo);
  delay(30); // velocidad de respiración
}

// Función: pip cada 6 segundos + LED azul máximo
void pipRadar() {
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= 6000) {
    tiempoAnterior = tiempoActual;

    // LED azul al máximo brillo
    analogWrite(ledAzul, 255);

    // Pip corto
    tone(buzzer, 1200);
    delay(150);
    noTone(buzzer);
  }
}
