void setup() {

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}


void loop() {
Automatico(); 

  /*if (Serial.available()) {
    int data = Serial.read();

    switch (data) {
      case 1:
        adelante();
        break;
      case 2:
        atras();
        break;
      case 3:
        derecha();
        break;
      case 4:
        izquierda();
        break;
      case 20:
        Automatico();
        break;
      case 10:
        alto();
        break;
    }*/
  }


void alto() {

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}
void adelante() {
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
}
void atras() {
  digitalWrite(2, !1);
  digitalWrite(3, !0);
  digitalWrite(4, !1);
  digitalWrite(5, !0);
}
void izquierda() {
  digitalWrite(2, !1);
  digitalWrite(3, !0);
  digitalWrite(4, !0);
  digitalWrite(5, !1);
}
void derecha() {
  digitalWrite(2, !0);
  digitalWrite(3, !1);
  digitalWrite(4, !1);
  digitalWrite(5, !0);
}



void Automatico() {
  long tiempo = millis(); //tiempo antes de iniciar la lectura
  int D_cm = distancia(1); //lectura de distancia
  tiempo = millis() - tiempo; //milisegundos que duró la lectura
  Serial.print("Tiempo de lectura: ");
  Serial.print(tiempo);
  Serial.print("ms  Distancia: ");
  Serial.print(D_cm);
  Serial.println("  cm");
  if (D_cm <= 0 && D_cm >= 130) {
    adelante();
  }
  else {
    derecha();
  }
}
float distancia(int n)
{
  long suma = 0;
  for (int i = 0; i < n; i++)
  {
    suma = suma + analogRead(A0);
  }
  float adc = suma / n;
  float distancia_cm = 17569.7 * pow(adc, -1.2062);
  return (distancia_cm);
}
