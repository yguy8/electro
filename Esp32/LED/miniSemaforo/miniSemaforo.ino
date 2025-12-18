const int ledRojo = 25;
const int ledAmarillo = 26;
const int ledVerde = 27;
const int ledPeaton = 14; // LED blanco peatón

unsigned long tiempoCambio = 0;
int estado = 0; // 0=Rojo, 1=Verde, 2=Amarillo, 3=Peaton
bool solicitudPeaton = false;
bool mensajeMostrado = false; // bandera para imprimir solo una vez

void setup() {
  Serial.begin(115200);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledPeaton, OUTPUT);

  estado = 0;
  tiempoCambio = millis();
}

void loop() {
  // Leer comando serial
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if (comando.equalsIgnoreCase("peaton")) {
      solicitudPeaton = true;
      Serial.println("Solicitud peatonal recibida");
    }
  }

  unsigned long ahora = millis();

  switch (estado) {
    case 0: // Rojo
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, LOW);
      digitalWrite(ledPeaton, LOW);
      if (ahora - tiempoCambio >= 5000) {
        estado = 1;
        tiempoCambio = ahora;
      }
      break;

    case 1: // Verde autos
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarillo, LOW);
      digitalWrite(ledPeaton, LOW);
      if (ahora - tiempoCambio >= 5000) {
        estado = 2;
        tiempoCambio = ahora;
      }
      break;

    case 2: // Amarillo
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, HIGH);
      digitalWrite(ledPeaton, LOW);
      if (ahora - tiempoCambio >= 2000) {
        if (solicitudPeaton) {
          estado = 3; // pasa a peaton
          solicitudPeaton = false;
          mensajeMostrado = false; // reset bandera
        } else {
          estado = 0;
        }
        tiempoCambio = ahora;
      }
      break;

    case 3: // Paso peatonal
      digitalWrite(ledRojo, HIGH);   // autos detenidos
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, LOW);
      digitalWrite(ledPeaton, HIGH); // peatón puede pasar

      // Mostrar mensaje solo una vez
      if (!mensajeMostrado) {
        Serial.println("Peatones ya pueden pasar");
        mensajeMostrado = true;
      }

      // Duración total del paso peatonal
      if (ahora - tiempoCambio >= 8000) {
        estado = 0;
        tiempoCambio = ahora;
      } else if (ahora - tiempoCambio >= 6000) {
        // últimos 2 segundos: rojo parpadea
        if ((ahora / 300) % 2 == 0) {
          digitalWrite(ledRojo, LOW);
        } else {
          digitalWrite(ledRojo, HIGH);
        }
      }
      break;
  }
}
