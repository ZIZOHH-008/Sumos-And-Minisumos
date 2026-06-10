// IZQUIERDA
const int triggerIzq = 8;
const int echoIzq = 2;

// CENTRO
const int triggerCentro = 9;
const int echoCentro = 10;

// DERECHA
const int triggerDer = A0;
const int echoDer = A1;




void setup() {
  Serial.begin(9600);

  pinMode(triggerIzq, OUTPUT);
  pinMode(echoIzq, INPUT);

  pinMode(triggerCentro, OUTPUT);
  pinMode(echoCentro, INPUT);

  pinMode(triggerDer, OUTPUT);
  pinMode(echoDer, INPUT);
}



float medirDistancia(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000); // timeout 30 ms

  if (duracion == 0) {
    return 999; // fuera de alcance
  }

  return duracion * 0.034 / 2.0;
}

void loop() {
  float distanciaIzq = medirDistancia(triggerIzq, echoIzq);
  float distanciaCentro = medirDistancia(triggerCentro, echoCentro);
  float distanciaDer = medirDistancia(triggerDer, echoDer);

  Serial.print("Izq: ");
  Serial.print(distanciaIzq);
  Serial.print(" cm\t");

  Serial.print("Centro: ");
  Serial.print(distanciaCentro);
  Serial.print(" cm\t");

  Serial.print("Der: ");
  Serial.print(distanciaDer);
  Serial.println(" cm");

  delay(200);
}