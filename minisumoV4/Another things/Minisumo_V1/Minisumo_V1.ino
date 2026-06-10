const int trigger = 8; //D8
const int echo = 2; //D2

const int trigger2 = 9;  //D9
const int echo2 = 10; //D10


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


void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);

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

  Serial.begin(9600);

  delay(4000);
}



void loop() {

  // SENSOR 1
  long tiempo1;
  float distancia1;

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);

  tiempo1 = pulseIn(echo, HIGH);

  distancia1 = (tiempo1/2)*0.0343;


  // SENSOR 2
  long tiempo2;
  float distancia2;

  digitalWrite(trigger2, LOW);
  delayMicroseconds(50);

  digitalWrite(trigger2, HIGH);
  delayMicroseconds(20);

  digitalWrite(trigger2, LOW);

  tiempo2 = pulseIn(echo2, HIGH);

  distancia2 = tiempo2 / 58.0;



  // LÓGICA DEL ROBOT
  bool rivalAdelante = (distancia1 > 0) && (distancia1 <= 25);
  bool rivalAtras    = (distancia2 > 0) && (distancia2 <= 25);

  if (rivalAdelante) {
    avanzar(255);
  }

  else if (rivalAtras) {
    retroceder(255);
  }

  else {
    girarDerecha(180);
  }



  // MOSTRAR DATOS
  Serial.print("Sensor 1: ");
  Serial.print(distancia1);
  Serial.println(" cm");


  Serial.print("Sensor 2: ");
  Serial.print(distancia2);
  Serial.println(" cm");

  Serial.println("----------------");

  delay(500);
}








// ========= FUNCIONES =========

void activarDriver() {
  digitalWrite(STBY, HIGH);
}



void desactivarDriver() {
  digitalWrite(STBY, LOW);
}



void avanzar(int velocidad) {
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



void retroceder(int velocidad) {
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



void girarIzquierda(int velocidad) {
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



void girarDerecha(int velocidad) {
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
