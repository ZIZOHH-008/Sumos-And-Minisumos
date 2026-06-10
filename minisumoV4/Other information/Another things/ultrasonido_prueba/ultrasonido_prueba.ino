const int trigger = 3;
const int echo = 2;

const int trigger2 = 5;
const int echo2 = 6;


void setup() {

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);


  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);


  Serial.begin(9600);
}

void loop() {

  // =========================
  // SENSOR 1
  // =========================

  long tiempo1;
  float distancia1;

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);

  tiempo1 = pulseIn(echo, HIGH);

  distancia1 = (tiempo1/2)*0.0343;

  // =========================
  // SENSOR 2
  // =========================


  long tiempo2;
  float distancia2;

  digitalWrite(trigger2, LOW);
  delayMicroseconds(50);

  digitalWrite(trigger2, HIGH);
  delayMicroseconds(20);

  digitalWrite(trigger2, LOW);

  tiempo2 = pulseIn(echo2, HIGH);

  distancia2 = tiempo2 / 58.0;



  // =========================
  // MOSTRAR DATOS
  // =========================

  Serial.print("Sensor 1: ");
  Serial.print(distancia1);
  Serial.println(" cm");


  Serial.print("Sensor 2: ");
  Serial.print(distancia2);
  Serial.println(" cm");

  Serial.println("----------------");


  delay(500);
}
