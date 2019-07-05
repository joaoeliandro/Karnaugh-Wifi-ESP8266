#include "lwip/tcp_impl.h"
#include <ESP8266WiFi.h>

const char *ssid = "Robot_", *password = "asdhjklm";
const byte m1h = 5, m1a = 4, m2h = 14, m2a = 12, enA = 15, enB = 13; //var sentidos dos motores 1 e 2
boolean A = 0, B = 0, C = 0, D = 0; //var dos botoes
unsigned int Speed = 0;

WiFiServer server(80);
WiFiClient client;

void setup() {
  IPAddress staticIP(192, 168, 4, 2); // IP set to Static
  IPAddress gateway(192, 168, 4, 1);// gateway set to Static
  IPAddress subnet(255, 255, 255, 0);// subnet set to Static
  WiFi.mode(WIFI_AP);// Working mode only as Acess Point
  WiFi.softAP(ssid, password, 11, 0); //rede, senha, canal (1 a 11), visivel
  WiFi.config(staticIP, gateway, subnet);
  server.begin();
  pinMode(m1h, OUTPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m2h, OUTPUT);
  pinMode(m2a, OUTPUT);
}

void loop() {
  tcpCleanup();
  wifidados();
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);

  if (!A && !C && D || !A && B && !C) 
    digitalWrite(m1h, HIGH); 
  else 
    digitalWrite(m1h, LOW);//motor 1 sentido horario
  
  if (B && !C && !D || A && !C && !D) 
    digitalWrite(m2h, HIGH); 
  else 
    digitalWrite(m2h, LOW);//motor 2 sentido horario
  if (!A && !B && C || A && B && !C && !D) 
    digitalWrite(m1a, HIGH); 
  else 
    digitalWrite(m1a, LOW);//motor 1 sentido anti-horario
  if (!B && C && !D || !A && B && !C && D) 
    digitalWrite(m2a, HIGH); 
  else 
    digitalWrite(m2a, LOW);//motor 2 sentido anti-horario

  client.flush();
  tcpCleanup();
}
