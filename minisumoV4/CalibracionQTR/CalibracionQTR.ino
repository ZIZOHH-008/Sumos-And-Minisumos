const int sensorIzq = A2;
const int sensorCentro = A3;
const int sensorDer = A4;
const int IR = 13;
const int UMBRAL = 700;

void setup() {
  Serial.begin(9600);
  pinMode(IR, OUTPUT);
  digitalWrite(IR, HIGH);

  Serial.println("QTR listo");
  
}

void loop() {

  int izq = analogRead(sensorIzq);
  int centro = analogRead(sensorCentro);
  int der = analogRead(sensorDer);

  Serial.print("LEFT: ");
  Serial.print(izq);
  Serial.print(" (");
  Serial.print(izq < UMBRAL ? "Blanco" : "Negro");
  Serial.print(")");

  Serial.print(" | CENTER: ");
  Serial.print(centro);
  Serial.print(" (");
  Serial.print(centro < UMBRAL ? "Blanco" : "Negro");
  Serial.print(")");

  Serial.print(" | RIGHT: ");
  Serial.print(der);
  Serial.print(" (");
  Serial.print(der < UMBRAL ? "Blanco" : "Negro");
  Serial.println(")");

  delay(500);
}