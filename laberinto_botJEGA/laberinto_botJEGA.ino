


int trigPin = 9;
int echoPin = 10;
int trigPinCENTRO = 11;
int echoPinCENTRO = 12;
int trigPinIZQ = 7;
int echoPinIZQ = 8;


//int led = 7;
#define E1  3    
#define E2  5   
#define M1  2            
#define M2  4 
#define PWM 190
#define PWM2 240
#define PWM3 70

#define BUTTON_START 13
#define MEDIDAC 12
#define MEDIDA 10
int statusStart = 1;


void setup() {
  pinMode(BUTTON_START,OUTPUT);
  Serial.begin(9600); 
  // pinMode(led, OUTPUT);
  
 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinCENTRO, OUTPUT);
  pinMode(echoPinCENTRO, INPUT);
  pinMode(trigPinIZQ, OUTPUT);
  pinMode(echoPinIZQ, INPUT);

  // put your setup code here, to run once:
  pinMode(M1,OUTPUT); 
  pinMode(M2,OUTPUT); 
  pinMode(E1,OUTPUT); 
  pinMode(E2,OUTPUT); 
  statusStart = 1;
   while(statusStart){

    
  if(digitalRead(BUTTON_START)){
    statusStart = 0;
  }

}
}
void advance(void)     // move forward
{
    digitalWrite(M1,HIGH);    // right wheel moves forward
    digitalWrite(M2, HIGH);  // left wheel moves forward
    analogWrite(E1,PWM);   
    analogWrite(E2,PWM);
}

void advance2(void)     // move forward
{
    digitalWrite(M1,HIGH);    // right wheel moves forward
    digitalWrite(M2, HIGH);  // left wheel moves forward
    analogWrite(E1,340);   
    analogWrite(E2,340);
}

void turnR(void)        // turn right 
{
   digitalWrite(M1,LOW);  // left wheel moves forward
   digitalWrite(M2, HIGH); // right wheel moves backward der
   analogWrite(E1,290);   //der
   analogWrite(E2, 190);  //izq
}
void turnL(void)        // turn left 
{
   digitalWrite(M1,HIGH);   // left wheel moves backwards
   digitalWrite(M2,LOW);   // right wheel moves forward
   analogWrite(E1,190);   //der
   analogWrite(E2, 290);  //izq

   
}    
void stopp(void)              // stop 
{
    digitalWrite(M1,LOW);    
    digitalWrite(M2, LOW);  
    analogWrite(E1, 0);   
    analogWrite(E2, 0);  // both left and right wheels stop
}
void back(void)            // move backward
{
   digitalWrite(M1,HIGH);   // both left and right wheels move forward
   digitalWrite(M2, HIGH);  
   analogWrite(E1,PWM2);   
   analogWrite(E2, PWM2);
}
void loop() {

  
  long duration, distance, distanceCENTRO, durationCENTRO, distanceIZQ, durationIZQ;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  //Serial.println("distance");
  //Serial.print(distance);
  //Serial.println("CM");
  digitalWrite(trigPinCENTRO,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPinCENTRO, LOW);
  durationCENTRO=pulseIn(echoPinCENTRO, HIGH);
  distanceCENTRO =(durationCENTRO/2)/29.1;
  /*Serial.println("centro");
  Serial.print(distanceCENTRO);
  Serial.println("CM");*/

  digitalWrite(trigPinIZQ,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPinIZQ, LOW);
  durationIZQ=pulseIn(echoPinIZQ, HIGH);
  distanceIZQ =(durationIZQ/2)/29.1;
  //delay(10);

  /*
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);*/

 
 /*if(distanceCENTRO>=MEDIDA&&distance>=MEDIDA)back();*/
 
if(((distanceCENTRO>MEDIDAC&&distanceIZQ<=MEDIDA&&distance>MEDIDA)||distance<=MEDIDA)||(distanceCENTRO>MEDIDAC&&distance<=MEDIDA&&distanceIZQ<=MEDIDA)||(distanceCENTRO>MEDIDAC&&distance<=MEDIDA&&distanceIZQ>MEDIDA))
advance();


if(distanceCENTRO<=MEDIDAC&&distance<=MEDIDA&&distanceIZQ>MEDIDA)
turnL();

/*if(distance>MEDIDA)
advance2();*/

if((distanceCENTRO<=MEDIDAC&&distanceIZQ<=MEDIDA&&distance>MEDIDA)||(distanceCENTRO<=MEDIDAC&&distanceIZQ>MEDIDA&&distance>MEDIDA)||(distanceCENTRO>MEDIDAC&&distanceIZQ>MEDIDA&&distance>MEDIDA))
turnR();

}
