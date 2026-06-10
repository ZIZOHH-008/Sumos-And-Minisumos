
// ===== MOTOR A =====
const int PWMA = 6; //D3
const int AIN1 = 7; //D7
const int AIN2 = 12; //D12

// ===== MOTOR B =====
const int PWMB = 3; //D3
const int BIN1 = 5; //D5
const int BIN2 = 4;//D4

// ===== STANDBY =====
const int STBY = 11; //D11

void setup() {

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
}

void loop() {

  avanzar(200);
  delay(2000);

  detenerMotores();
  delay(1000);

  retroceder(200);
  delay(2000);

  detenerMotores();
  delay(1000);

  girarIzquierda(200);
  delay(1500);

  detenerMotores();
  delay(1000);

  girarDerecha(200);
  delay(1500);

  detenerMotores();
  delay(1000);
  
}

//
// ========= FUNCIONES =========
//

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