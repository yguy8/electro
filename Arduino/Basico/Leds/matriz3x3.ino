int fila1=5;
int fila2=6;
int fila3=7;
int columna1=8;
int columna2=9;
int columna3=10;
int tiempo = 2;
void setup(){
  pinMode(fila1,OUTPUT);
  pinMode(fila2,OUTPUT);
  pinMode(fila3,OUTPUT);
  pinMode(columna1,OUTPUT);
  pinMode(columna2,OUTPUT);
  pinMode(columna3,OUTPUT);

}

void loop(){
for(int i = 0; i<300;i++){ 
  // cuadrado
  digitalWrite(fila2,LOW);
   digitalWrite(fila1,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna1,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila2,LOW);
   digitalWrite(fila3,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);
    digitalWrite(fila3,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna2,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);
  digitalWrite(fila1,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna2,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);

    digitalWrite(fila1,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna1,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila1,LOW);
   digitalWrite(fila3,HIGH);
    digitalWrite(fila2,HIGH);
  digitalWrite(columna3,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);
    digitalWrite(fila3,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna1,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna2,LOW);
  delay(tiempo);
  digitalWrite(fila3,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);
}
  digitalWrite(fila3,HIGH);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
delay(1000);

for(int i = 0; i<300;i++){ 
 // X
 digitalWrite(fila1,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna1,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila2,LOW);
   digitalWrite(fila1,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna2,HIGH);
  digitalWrite(columna1,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila3,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);
    digitalWrite(fila3,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna1,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna2,LOW);
  delay(tiempo);
  digitalWrite(fila1,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna3,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);

}
digitalWrite(fila3,HIGH);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
delay(1000);
for(int i = 0; i<300;i++){ 
// DIAGONAL 

 digitalWrite(fila1,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna1,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila2,LOW);
   digitalWrite(fila1,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna2,HIGH);
  digitalWrite(columna1,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila3,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);



}
digitalWrite(fila3,HIGH);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
delay(1000);
for(int i = 0; i<300;i++){ 
// +
  digitalWrite(fila2,LOW);
   digitalWrite(fila1,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna1,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila2,LOW);
   digitalWrite(fila1,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna2,HIGH);
  digitalWrite(columna1,LOW);
  digitalWrite(columna3,LOW);
  delay(tiempo);
  digitalWrite(fila2,LOW);
   digitalWrite(fila3,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,HIGH);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);
    digitalWrite(fila3,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna2,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);
  digitalWrite(fila1,LOW);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila3,HIGH);
  digitalWrite(columna2,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna1,LOW);
  delay(tiempo);


}
digitalWrite(fila3,HIGH);
   digitalWrite(fila2,HIGH);
    digitalWrite(fila1,HIGH);
  digitalWrite(columna3,LOW);
  digitalWrite(columna2,LOW);
  digitalWrite(columna1,LOW);
delay(1000);


}
