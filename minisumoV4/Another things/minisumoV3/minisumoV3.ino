// D0 y D1
// D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12
// A0, A1, A2, A3, A4, A5, A6, A7


// ===== ULTRASONIDOS =====

// IZQUIERDA
const int triggerIzq = 8;
const int echoIzq = 2;

// CENTRO
const int triggerCentro = 9;
const int echoCentro = 10;

// DERECHA
const int triggerDer = A0;
const int echoDer = A1;



// ===== MOTOR A =====
const int PWMA = 6; //D6
const int AIN1 = 7; //D7
const int AIN2 = 12; //D12

// ===== MOTOR B =====
const int PWMB = 3; //D3
const int BIN1 = 5; //D5
const int BIN2 = 4;//D4

// ===== STANDBY =====
const int STBY = 11; //D11



// ===== SENSOR DE LINEA =====
const int sensorIzq = A2;
const int sensorCentro = A3;
const int sensorDer = A4;
const int IR = 13;
const int UMBRAL = 700;





void setup() {
  pinMode(triggerIzq, OUTPUT);
  pinMode(echoIzq, INPUT);

  pinMode(triggerCentro, OUTPUT);
  pinMode(echoCentro, INPUT);

  pinMode(triggerDer, OUTPUT);
  pinMode(echoDer, INPUT);

  // MOTOR A
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  // MOTOR B
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // STANDBY
  pinMode(STBY, OUTPUT);

  // Activar puente H
  digitalWrite(STBY, HIGH);

  detenerMotores();

  //  Iniciar el sensor de linea
  pinMode(IR, OUTPUT);
  digitalWrite(IR, HIGH);
  Serial.println("QTR listo");


  Serial.begin(9600);

  delay(4000);
}



//======== FUNCIONES DE DETECCIÓN =========
float medirDistancia(int trigger, int echo) {

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);

  long tiempo = pulseIn(echo, HIGH, 30000);

  if (tiempo == 0) {
    return 999;
  }

  return tiempo * 0.034 / 2.0;
}


void loop() {

  // Guardar valores del color
  int izq = analogRead(sensorIzq);
  int centro = analogRead(sensorCentro);
  int der = analogRead(sensorDer);

  bool lineaIzquierda = (izq < UMBRAL);
  bool lineaCentro    = (centro < UMBRAL);
  bool lineaDerecha   = (der < UMBRAL);


  //Guardar valores de distancia
  float distanciaAtras = medirDistancia(triggerIzq, echoIzq);
  delay(20);
  float distanciaDerecha = medirDistancia(triggerCentro, echoCentro);
  delay(20);
  float distanciaAdelante = medirDistancia(triggerDer, echoDer);

  const int DETECCION = 25;

  bool rivalAtras = (distanciaAtras > 0) && (distanciaAtras <= DETECCION);
  bool rivalDerecha = (distanciaDerecha > 0) && (distanciaDerecha <= DETECCION);
  bool rivalAdelante = (distanciaAdelante > 0) && (distanciaAdelante <= DETECCION);

  


  // ===== LÓGICA DEL MINISUMO =====

  // ===== ANALIZAR DONDE ESTÁ =====
  if (lineaCentro) {
      retroceder(255);
      delay(300);
  }

  else if (lineaDerecha) {
      girarIzquierda(170);
      delay(250);
  }

  else if (lineaIzquierda) {
      girarDerecha(170);
      delay(250);
  }
  

  // ===== BUSCAR Y ATACAR=====
  else if (rivalAdelante) {
      avanzar(255);
  }

  else if (rivalDerecha) {
      girarDerecha(170);
  }

  else if (rivalAtras) {
      retroceder(170);
  }

  else {
      girarIzquierda(170);
  }


  // ===== Imprimir valores de distancia =====
  Serial.print("Atr: ");
  Serial.print(distanciaAtras);

  Serial.print("  Der: ");
  Serial.print(distanciaDerecha);

  Serial.print("  Adel: ");
  Serial.println(distanciaAdelante);


  // ===== Imprimir valores de color =====
  Serial.print("Izq: ");
  Serial.print(izq);
  Serial.print(" (");
  Serial.print(lineaIzquierda ? "BLANCO" : "NEGRO");
  Serial.print(") | ");

  Serial.print("Centro: ");
  Serial.print(centro);
  Serial.print(" (");
  Serial.print(lineaCentro ? "BLANCO" : "NEGRO");
  Serial.print(") | ");

  Serial.print("Der: ");
  Serial.print(der);
  Serial.print(" (");
  Serial.print(lineaDerecha ? "BLANCO" : "NEGRO");
  Serial.println(")");

  delay(100);
}







// ========= FUNCIONES DE MOVIMIENTO =========
void activarDriver() {
  digitalWrite(STBY, HIGH);
}



void desactivarDriver() {
  digitalWrite(STBY, LOW);
}



void girarDerecha(int velocidad) {
  activarDriver();

  // Motor A
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, velocidad);

  // Motor B
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velocidad);
}



void girarIzquierda(int velocidad) {
  activarDriver();

  // Motor A
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, velocidad);

  // Motor B
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, velocidad);
}



void retroceder(int velocidad) {
  activarDriver();

  // Izquierdo atrás
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, velocidad);

  // Derecho adelante
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velocidad);
}



void avanzar(int velocidad) {
  activarDriver();

  // Izquierdo adelante
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, velocidad);

  // Derecho atrás
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, velocidad);
}



void detenerMotores() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}
