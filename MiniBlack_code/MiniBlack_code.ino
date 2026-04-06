/*Codigo de MiniBlack MiniSumo
  BY:Roger Andres Alvarez Diaz: rogeralvarez22082007@gmail.com
  Institucion Educatica Jorge Eliecer Gaitan-Palmira
  star code in 31/10/2022
  Last update 10/11/2022
  Configuracion en "Herramientas"
  placa: "Atmega328/328p"
  procesador: "Atmega328p"
  clock: "External: 20 MHz"
  pogramador: "Atmel STK500 devolopment board"
  Link para el gestor de tarjetas: https://raw.githubusercontent.com/carlosefr/atmega/master/package_carlosefr_atmega_index.json
  Paginas que recomiendo para investigacion y entender mejor el codigo
  https://create.arduino.cc/projecthub/muhammad-aqib/arduino-pwm-tutorial-ae9d71
  https://www.monografias.com/trabajos104/algebra-boole-i/algebra-boole-i
  https://www.thomsonlinear.com/es/soporte/consejos/que-es-pwm
  https://ja-bots.com/producto/minisumo-miniblack/
  https://www.youtube.com/watch?v=BtLSaxRnIhc
  https://ja-bots.com/wp-content/uploads/2017/08/Manual-Modulo-de-Inicio.pdf
  Buena Suerte mejorando el codigo
*/
//         Declaracion de pines
const int led1 = 13;     //Led Amarillo
const int led2 = 12;     //Led Azul
const int led3 = 11;     //Led Rojo
const int sensor1 = 14;  // conexion sensor 1
const int sensor2 = 15;  // conexion sensor 2
const int sensor3 = 16;  // conexion sensor 3
const int sensor4 = 17;  // conexion sensor 4
const int sensor5 = 18;  // conexion sensor 5
const int sw1 = 8;       //pulsador 1
const int in1a = 19;     //Direccion de motor 1 derecha
const int in2a = 4;      //Direccion de motor 2 derecha
const int in1b = 3;      //direccion motor 1 izquierda
const int in2b = 2;      //direccion motor 2 izquierda
const int pwm1 = 5;      //PWM motor 1 Derecho
const int pwm2 = 6;      //PWM motor 2 Izquierdo
const int Star = 9;      // Pin del modulo de inicio Star
const int Stop = 10;     //Pin del modulo de inicio Stop
//   Variables que se van a usar
int StatusStar = 0;
int adcd = 0;            //Variable de lectura Sensor de piso derecha
int adci = 0;            //Variable de lectura Sensor de piso derecha
int s1 = 0;              //Sensor Derecha
int s2 = 0;              //Sensor Lateral Derecha
int s3 = 0;              //Sensor delantero
int s4 = 0;              //Sensor Lateral Izquierda
int s5 = 0;              //Sensor Izquierda
int pushSw1 = 0;         //Variable para guardar el estado del boton
int estadoAnterior = 0;  // Guarda el estado anterior del boton "sw1"
int estadoNuevo = 0;     // Estado actual en el que esta el boton "sw1"
int tiempoI = 5000;      // En esta variable define el tiempo que nesesitas para que inicie el robot. Tiempo en Milisegundos
//   Define los estados HIGH.LOW de cada led
#define led1on digitalWrite(led1, HIGH);
#define led2on digitalWrite(led2, HIGH);
#define led3on digitalWrite(led3, HIGH);
#define led1off digitalWrite(led1, LOW);
#define led2off digitalWrite(led2, LOW);
#define led3off digitalWrite(led3, LOW);
void setup() {
  //Configuracion de pines
  //Leds
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  //Sensores
  pinMode(Star, INPUT);
  pinMode(Stop, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT_PULLUP);
  pinMode(sensor5, INPUT_PULLUP);
  // Motores
  pinMode(in1a, OUTPUT);
  pinMode(in2a, OUTPUT);
  pinMode(in1b, OUTPUT);
  pinMode(in2b, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
}

void loop() {
  inicio();
  switch (StatusStar) {
    case 1:
      led1on;
      MedirSensores();
      tiempoI = 1;
      atacar();
      break;
    case 0:
      tiempoI = 5000;
      led1off;
      motors(0, 0);
      led2on;
      delay(120);
      led2off;
      led3on;
      delay(100);
      led3off;
      break;
  }
  if ((adci >= 40 && adci <= 300) || (adcd >= 40 && adcd <= 300)) {
    motors(-220, -220);
    delay(300);
    motors(-220, 220);
    delay(200);
    led2on;

  } else {
    led2off;
  }
}

/*Funcion para manejar los motores con PWM y la señales del driver
  Con esta funcion se puede manejar la velocidad de cada motor Izquierda Y Derecha
  con el comando: motors(Velocidad del motor izquierda,Velociad del motor derecha); :D
*/
int motors(int speedL, int speedR) {
  if (speedL > 0) {
    digitalWrite(in2b, LOW);
    digitalWrite(in1b, HIGH);
  } else {
    digitalWrite(in2b, HIGH);
    digitalWrite(in1b, LOW);
    speedL = speedL * -1;
  }

  if (speedR > 0) {
    digitalWrite(in2a, LOW);
    digitalWrite(in1a, HIGH);
  } else {
    digitalWrite(in2a, HIGH);
    digitalWrite(in1a, LOW);
    speedR = speedR * -1;
  }
  analogWrite(pwm1, speedR);
  analogWrite(pwm2, speedL);
}
//Lee el estado de los sensores 1 o 0 o El valor analogico de los sensores de piso
void MedirSensores() {
  adci = analogRead(6);
  adcd = analogRead(7);
  s1 = digitalRead(sensor1);
  s2 = digitalRead(sensor2);
  s3 = digitalRead(sensor3);
  s4 = digitalRead(sensor4);
  s5 = digitalRead(sensor5);
}
/*
  Esto sirve para Activar y desactivar el minisumo con el Boton incluido en la placa miniblack
  se lee el estado del pin si es 1 o 0 y en base a eso se guarda en una variable de tipo entero y otra variable con el estado antiguo del
  Pin logrando hacer un interuptor de prendido y apagado :D
  Tambien podemos usar el modulo de inicio con el control para minisumo o seguidor de linea con un tiempo de seguridad de 5
  segundos :D Lo unico que tienes que hacer es comentar una y descomentar otra
*/
void inicio() {
  pushSw1 = digitalRead(sw1);  //Almacenamos en la variable la lectura del pulsador.
  if ((pushSw1 == 1) && (estadoAnterior == 0)) {
    estadoNuevo = 1 - estadoNuevo;
    delay(1);
  }
  estadoAnterior = pushSw1;

  if (estadoNuevo == 1)  //Condición que si tenemos el valor de 1 entra en el.
  {
    led3on;
    StatusStar = 1;
    delay(tiempoI);
  } else  //Condición que se cumple si no se cumple el if.
  {
    StatusStar = 0;
  }
}
/*
  Esta funcion esta diseñada para leer cada uno de los sensores y atacar dependiendo de que sensor detecta
  el enemigo :D
  Tambien Su if principal esta diseñado para ver si esta o no fuera del raund utilizando el perimetro blanco que
  rodea el round
  Buena suerte :D
  Simbolos logicos
  || == OR
  && == AND
  ! == NOT
  < == Menor
  > == Mayor
*/
void atacar(void) {

  //Si uno de los 2 sensores de piso tiene un valor entre 50 y 40 ir en dirrecion trasera
  if ((adci >= 40 && adci <= 300) || (adcd >= 40 && adcd <= 300)) {
    motors(-220, -220);
    delay(300);
    motors(-220, 220);
    delay(200);
  }
  /*else if ((adci >= 40 && adci <= 150)) {
    motors(120, -120);
    delay(200);
  } 
else if ((adcd >= 40 && adcd >= 150)){
  motors(-120,120);
  delay(200);
  }  
  */
  else {
    //Posibilidades para buscar                                          //Numero de combinacion
    if (((s5 == 0) && (s4 == 0) && (s3 == 0) && (s2 == 0) && (s1 == 0)) ||  //2
        ((s5 == 1) && (s4 == 0) && (s3 == 0) && (s2 == 0) && (s1 == 1)) ||  //15
        ((s5 == 1) && (s4 == 0) && (s3 == 0) && (s2 == 1) && (s1 == 1)) ||  //17
        ((s5 == 1) && (s4 == 0) && (s3 == 0) && (s2 == 1) && (s1 == 1)) ||  //18
        ((s5 == 1) && (s4 == 1) && (s3 == 0) && (s2 == 0) && (s1 == 1))) {  //20
      motors(70, -80);
      delay(1);
    }
    //Posibilidades para ir para adelante
    if (((s5 == 0) && (s4 == 1) && (s3 == 1) && (s2 == 1) && (s1 == 0)) ||  //11
        ((s5 == 0) && (s4 == 0) && (s3 == 1) && (s2 == 1) && (s1 == 0)) ||  //12
        ((s5 == 0) && (s4 == 1) && (s3 == 1) && (s2 == 0) && (s1 == 0)) ||  //13
        ((s5 == 0) && (s4 == 0) && (s3 == 1) && (s2 == 0) && (s1 == 0)) ||  //14
        ((s5 == 1) && (s4 == 1) && (s3 == 1) && (s2 == 1) && (s1 == 1)) ||  //1
        ((s5 == 1) && (s4 == 0) && (s3 == 1) && (s2 == 1) && (s1 == 1)) ||  //19
        ((s5 == 1) && (s4 == 0) && (s3 == 1) && (s2 == 1) && (s1 == 1))) {  //21
      motors(255, 255);
      delay(1);
    }
    //Posibilidades para ir para la derecha
    if (((s5 == 0) && (s4 == 0) && (s3 == 0) && (s2 == 1) && (s1 == 1)) ||  //7
        ((s5 == 0) && (s4 == 0) && (s3 == 0) && (s2 == 0) && (s1 == 1)) ||  //6
        ((s5 == 0) && (s4 == 1) && (s3 == 1) && (s2 == 1) && (s1 == 1)) ||  //9
        ((s5 == 0) && (s4 == 0) && (s3 == 1) && (s2 == 1) && (s1 == 1))) {  //11
      motors(120, -120);
      delay(1);
    }
    //Posibilidades para ir a la izquierda
    if (((s5 == 1) && (s4 == 0) && (s3 == 0) && (s2 == 0) && (s1 == 0)) ||  //3
        ((s5 == 1) && (s4 == 1) && (s3 == 1) && (s2 == 0) && (s1 == 0)) ||  //5
        ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0)) ||  //4
        ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))) {  //16
      motors(-120, 120);
      delay(1);
    }
  }
}