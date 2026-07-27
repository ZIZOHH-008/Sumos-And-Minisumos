#include <ESP8266WiFi.h> //El wifi pa la node
#include <WiFiClient.h>  //El wifi para conectarse a un servidor (el de la node)
#include <ESP8266WebServer.h> //Para crear el servidor en la node
#include <Servo.h> //Para manejar el servo

//El nombre y la clave de el robot
const char* ssid = "catamaran";
const char* password = "12345678";

String command;  //Esto es para almanecar el valor dado cuando se presione algo
int initPWM = 150;  //tener en cuenta que el maximo es 255  = HIGH

Servo timon;


ESP8266WebServer server(80);  //Creamos un objeto servidor WEB que escuchará en el puerto 80

void setup() {
  timon.attach(12); // D6 
  timon.write(90); 
  delay(1000);

  
// Wifi gratis :D
  WiFi.mode(WIFI_AP);           //Un solo punto de acceso
  WiFi.softAP(ssid, password);  //esto es para crear el wifi teniendo en cuenta lo valores que le di

  IPAddress myIP = WiFi.softAPIP(); //retorna la direccion IP que tiene la node
  Serial.print("AP IP address: "); //para imprimir esa string
  Serial.println(myIP); //para imprimir mi IP
 
 // Empezar a recibir información por medio de la web
     server.on ( "/", HTTP_handleRoot );  //Para manejar los INPUT
     server.onNotFound ( HTTP_handleRoot ); //por si alguien daña la IP en la app
     server.begin();   // Inicia el servidor para escuchar los INPUT
}


void HTTP_handleRoot(void) {
  if( server.hasArg("State") ){  //solo sucederá esto si es correcta la conexión
        Serial.println(server.arg("State"));
    }
    server.send ( 200, "text/html", "" );  //Enviar estado HTTP 200 (Ok) y enviar texto al navegador/cliente - Según StackOverfloow, es para decir QUE SÍ TA BIEN
    delay(100);
  }



void timon_izqui(){
  timon.write(180);
  delay(500);
}

void timon_derec(){
  timon.write(0);
  delay(500);
}


void loop() {
      server.handleClient();      //escucha las conexiones entrantes para tenerlas en cuenta
          
      command = server.arg("State"); //lee el input y hacer según el valor de ese input
      if (command == "L") timon_izqui;
      else if (command == "R") timon_derec();
}
