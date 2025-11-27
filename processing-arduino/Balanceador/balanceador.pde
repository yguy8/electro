import processing.serial.*;

Serial myPort;
String estado = "ESTABLE";
float angulo = 0;

void setup() {
  size(600, 400);
  
  // Abrir el puerto COM6 a 9600 baudios
  myPort = new Serial(this, "COM6", 9600);
}

void draw() {
  background(135, 206, 235); // cielo azul
  translate(width/2, height/2);

  // Ajustar ángulo según estado
  if (estado.equals("INCLINADO")) {
    angulo = radians(20); // inclinado
  } else {
    angulo = 0; // estable
  }

  rotate(angulo);

  // Dibujar avión simple
  fill(255);
  rectMode(CENTER);
  rect(0, 0, 150, 20); // cuerpo
  rect(-50, -20, 40, 10); // ala izquierda
  rect(50, -20, 40, 10);  // ala derecha
}

void serialEvent(Serial myPort) {
  estado = myPort.readStringUntil('\n');
  if (estado != null) {
    estado = estado.trim();
  }
}
