#include <SoftwareSerial.h>
#include <Servo.h>                      // Controle do servo

SoftwareSerial BT(2, 3); // RX, TX
Servo myservo;                   // Declara o controle do servo
#define enA 10
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define enB 9
#define inclinacaoPin 13 //sensor de inclinação
#define MIN_DISTANCIA 15 // Distância mínima em centímetros para parar
#define echopin A0     // Echo pin do sensor ultrassônico
#define trigpin A1    // Trigger pin do sensor ultrassônico

int xAxis=140, yAxis=140;

int motorSpeedA = 0;
int motorSpeedB = 0;
int angulo = 0;               // Ângulo inicial
int direcao = 1;              // 1 para aumentar o ângulo, -1 para diminuir
long distancia;               // Valor do tempo do pulso = distância medida

void setup() {
myservo.attach(8);      // Conecta o servo ao pino 8
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(inclinacaoPin, INPUT);
Serial.begin(9600);
BT.begin(9600); // comunicação sereal
delay(500);
}

// Função para verificar se há um obstáculo à frente
bool checando_obstaculo() {
  long duracao;
  
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duracao = pulseIn(echopin, HIGH);
  long distancia = duracao * 0.034 / 2; // Converte o tempo para distância em cm

  if (distancia < MIN_DISTANCIA) {
    Serial.println("Obstáculo detectado");
    return true; // Obstáculo detectado
  }
  return false; // Nenhum obstáculo detectado
}
void loop() {
  //  Joystick no centro
  //xAxis = 140;
  //yAxis = 140;

  // Leitura do app
  while (BT.available() >= 2) {
    xAxis = BT.read();
    delay(10);
    yAxis = BT.read();
   Serial.print(xAxis);
   Serial.print(",");
   Serial.println(yAxis);
  }
  delay(10);
   // sensor de inclinação
  int estadoInclinacao = digitalRead(inclinacaoPin);

  if (estadoInclinacao == HIGH) {
    Serial.println("Sensor na posição estável");
  } else {
    Serial.println("Sensor inclinado");
  }

  delay(500);
  
  // valores corretos

if (xAxis > 130 && xAxis <150 && yAxis > 130 && yAxis <150){parar();}


if (yAxis > 130 && yAxis <150){    

if (xAxis < 130){virardireita();
motorSpeedA = map(xAxis, 130, 60, 0, 255);
motorSpeedB = map(xAxis, 130, 60, 0, 255);    
}

if (xAxis > 150) {viraresquerda();
motorSpeedA = map(xAxis, 150, 220, 0, 255);
motorSpeedB = map(xAxis, 150, 220, 0, 255); 
}

}else{

if (xAxis > 130 && xAxis <150){   

if (yAxis < 130){frente();}
if (yAxis > 150){re();}

if (yAxis < 130){
motorSpeedA = map(yAxis, 130, 60, 0, 255);
motorSpeedB = map(yAxis, 130, 60, 0, 255); 
}

if (yAxis > 150){
motorSpeedA = map(yAxis, 150, 220, 0, 255);
motorSpeedB = map(yAxis, 150, 220, 0, 255);
 }
 
}else{

if (yAxis < 130){frente();}
if (yAxis > 150){re();}

if (xAxis < 130){
motorSpeedA = map(xAxis, 130, 60, 255, 50);
motorSpeedB = 255; 
 }
 
if (xAxis > 150){
motorSpeedA = 255;
motorSpeedB = map(xAxis, 150, 220, 255, 50); 
  }
  
 } 
}

   //Serial.print(motorSpeedA);
   //Serial.print(",");
   //Serial.println(motorSpeedA);

analogWrite(enA, motorSpeedA); // motor A
analogWrite(enB, motorSpeedB); // motor B
}


void frente(){Serial.println("avançar");
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW); 
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void re(){Serial.println("ré");
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH); 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void virardireita(){Serial.println("virar direita");
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void viraresquerda(){Serial.println("virar esquerda");
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH); 
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void parar(){
digitalWrite(in1, LOW);
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
Serial.println("parou");
}
