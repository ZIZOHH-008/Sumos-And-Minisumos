      //Explicacion: Primero, definimos los pines de donde se conectó


// ===== ULTRASONIDOS =====

// IZQUIERDA
const int triggerIzq = 9;
const int echoIzq = 8;

// CENTRO
const int triggerDerecha = 10;
const int echoDerecha = 11;

// DERECHA
const int triggerAdelante = A1;
const int echoAdelante = A0;





// ===== MOTOR A =====
const int IN1 = 7;  
const int IN2 = 6;  
const int ENA = 5;  


// ===== MOTOR B =====
const int IN3 = 4;  
const int IN4 = 2;  
const int ENB = 3;  




// ===== SENSOR DE LINEA =====
const int sensorIzq = A2;
const int sensorCentro = A3;
const int sensorDer = A4;
const int IR = 13;
const int UMBRAL = 700;




      /*Explicacion: El void setup define que componentes emiten informacion y cuales reciben
      Echo por ejemplo, recibe la señal que dispara trigger
      Los motores no reciben info, pero sí envían "movimiento"*/

void setup() {
  pinMode(triggerIzq, OUTPUT);
  pinMode(echoIzq, INPUT);

  pinMode(triggerDerecha, OUTPUT);
  pinMode(echoDerecha, INPUT);

  pinMode(triggerAdelante, OUTPUT);
  pinMode(echoAdelante, INPUT);

  // MOTOR A
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // MOTOR B
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  detenerMotores();

  //  Iniciar el sensor de linea
  pinMode(IR, OUTPUT);
  digitalWrite(IR, HIGH);
  Serial.println("QTR listo");


        //Inicia el monitor serial donde se ven los datos
  Serial.begin(9600);

  delay(4000);
}



      // Explicación: Esta funcion tiene dos parámetros, los pines del sensor ultrasonido

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
  // Explicación: Guardar valores del color
  int izq = analogRead(sensorIzq);
  int centro = analogRead(sensorCentro);
  int der = analogRead(sensorDer);

  // Explicación: Son los posibles casos que suceden con el detector de linea
  bool lineaIzquierda = (izq < UMBRAL);
  bool lineaCentro    = (centro < UMBRAL);
  bool lineaDerecha   = (der < UMBRAL);
  bool lineaIzqCentro = lineaIzquierda && lineaCentro;
  bool lineaCentroDer = lineaCentro && lineaDerecha;
  bool lineaIzqDer = lineaIzquierda && lineaDerecha;
  bool lineaTodos = lineaIzquierda && lineaCentro && lineaDerecha;


  //Guardar valores de distancia
  float distanciaIzquierda = medirDistancia(triggerIzq, echoIzq);
  delay(20);
  float distanciaDerecha = medirDistancia(triggerDerecha, echoDerecha);
  delay(20);
  float distanciaAdelante = medirDistancia(triggerAdelante, echoAdelante);

  const int DETECCION = 25;

  // Explicación: Son los posibles casos que suceden con el detector del enemigos
  bool rivalIzquierda = (distanciaIzquierda > 0) && (distanciaIzquierda <= DETECCION);
  bool rivalDerecha = (distanciaDerecha > 0) && (distanciaDerecha <= DETECCION);
  bool rivalAdelante = (distanciaAdelante > 0) && (distanciaAdelante <= DETECCION);


  //Casos raros (Es raro que el sensor de adelante y el de atrás detecten al mismo tiempo.
  // No debería suceder, pero igual se define)
  bool rivalIzquierdaDerecha = rivalIzquierda && rivalDerecha;
  bool rivalIzquierdaAdelante = rivalIzquierda && rivalAdelante;
  bool rivalDerechaAdelante = rivalDerecha && rivalAdelante;
  bool rivalTodos = rivalIzquierda && rivalDerecha && rivalAdelante;



  // ============================== LÓGICA DEL MINISUMO =========================

  // ===== ANALIZAR DONDE ESTÁ =====
  if (lineaTodos) {
      retroceder(255);
  }

  else if (lineaIzqCentro) {
      retroceder(200);
      delay(200);
      girarDerecha(200);
  }

  else if (lineaCentroDer) {
      retroceder(200);
      delay(200);
      girarIzquierda(200);
  }

  else if (lineaIzqDer) {
      retroceder(200);
  }

  else if (lineaCentro) {
      retroceder(180);
  }

  else if (lineaIzquierda) {
      girarDerecha(180);
  }

  else if (lineaDerecha) {
      girarIzquierda(180);
  }



  // ===== ATACAR =====
  else if (rivalTodos) {
      avanzar(255);
  }

  else if (rivalDerechaAdelante) {
      girarDerecha(180);
  }

  else if (rivalIzquierdaAdelante) {
      girarIzquierda(180); 
  }

  else if (rivalIzquierdaDerecha) {
      girarDerecha(180);
  }

  else if (rivalAdelante) {
      avanzar(255);
  }

  else if (rivalDerecha) {
      girarDerecha(180);
  }

  else if (rivalIzquierda) {
      girarDerecha(180);
  }


  else {
      girarIzquierda(150);
  }



  // ===== Imprimir valores de distancia =====
  Serial.print("Izq: ");
  Serial.print(distanciaIzquierda);

  Serial.print("  Der: ");
  Serial.print(distanciaDerecha);

  Serial.print("  Adel: ");
  Serial.println(distanciaAdelante);


  Serial.print("\n");


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

  delay(200);
}







// ========= FUNCIONES DE MOVIMIENTO =========
void girarIzquierda(int velocidad) {
  // Motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad);

  // Motor B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, velocidad);
}



void girarDerecha(int velocidad) {
  // Motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidad);

  // Motor B
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, velocidad);
}



void retroceder(int velocidad) {
  // Izquierdo atrás
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidad);

  // Derecho adelante
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, velocidad);
}



void avanzar(int velocidad) {
  // Izquierdo adelante
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad);

  // Derecho atrás
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, velocidad);
}



void detenerMotores() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}