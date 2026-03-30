const int capacitivePin = 2;  
const int laserPin = 9;       

bool laserState = false;

void setup() {
  pinMode(capacitivePin, INPUT);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW); 
}

void loop() {
  int buttonState = digitalRead(capacitivePin);

  if (buttonState == HIGH) {
    laserState = !laserState;
    digitalWrite(laserPin, laserState ? HIGH : LOW);
    delay(300);
  }
}
