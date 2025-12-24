// Sensor de vibración con estado de alerta
const int pinSensor = 2;   // Sensor de vibración
const int ledAzul = 6;     // LED azul (PWM)
const int ledRojo = 9;     // LED rojo (PWM)
const int buzzer = 10;     // Buzzer

// Temporización
unsigned long tiempoAnteriorPip = 0;
unsigned long ultimoEventoAlerta = 0;
const unsigned long retencionAlertaMs = 300; // mantiene alerta 300 ms después del último pulso

// Estado
bool alertaActiva = false;

// Variables para efectos
int tonoActual = 400;
int direccionTono = 10;
int brilloRojo = 0;
int direccionBrillo = 5;

void setup() {
  pinMode(pinSensor, INPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);

  analogWrite(ledAzul, 0);
  analogWrite(ledRojo, 0);
  noTone(buzzer);
}

void loop() {
  // Lectura del sensor y actualización de estado de alerta con retención
  int estadoSensor = digitalRead(pinSensor);
  unsigned long ahora = millis();

  if (estadoSensor == HIGH) {
    alertaActiva = true;
    ultimoEventoAlerta = ahora;
  } else {
    // pasa a estable solo si transcurrió el tiempo de retención sin nueva vibración
    if (alertaActiva && (ahora - ultimoEventoAlerta > retencionAlertaMs)) {
      alertaActiva = false;
    }
  }

  if (alertaActiva) {
    // ALERTA: vibración detectada
    analogWrite(ledAzul, 0);   // LED azul apagado SIEMPRE en alerta
    alarmaModuladaPasoAPaso(); // LED rojo + buzzer sincronizados
  } else {
    // ESTABLE: sin vibración
    noTone(buzzer);            // buzzer apagado (salvo pip)
    analogWrite(ledRojo, 0);   // LED rojo apagado
    efectoLedAzul();           // LED azul respirando
    pipRadar();                // Pip cada 6 s + LED azul al máximo en el pip
  }
}

// Alarma modulada paso a paso (sin bucles largos)
void alarmaModuladaPasoAPaso() {
  // tono sube y baja
  tone(buzzer, tonoActual);
  tonoActual += direccionTono;
  if (tonoActual >= 1000 || tonoActual <= 400) {
    direccionTono = -direccionTono;
  }

  // brillo rojo sube y baja sincronizado
  analogWrite(ledRojo, brilloRojo);
  brilloRojo += direccionBrillo;
  if (brilloRojo >= 255 || brilloRojo <= 0) {
    direccionBrillo = -direccionBrillo;
  }

  delay(10); // velocidad del ciclo de alerta
}

// LED azul respirando en modo estable
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

// Pip cada 6 segundos + LED azul al máximo en ese instante (modo radar)
void pipRadar() {
  unsigned long ahora = millis();
  if (ahora - tiempoAnteriorPip >= 6000) {
    tiempoAnteriorPip = ahora;

    // refuerzo visual: azul al máximo
    analogWrite(ledAzul, 255);

    // pip corto agudo
    tone(buzzer, 1200);
    delay(150);
    noTone(buzzer);
  }
}
