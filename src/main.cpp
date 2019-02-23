#include <Arduino.h>
#include <BotFCTUC.h>


int incomingByte;
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

void linetest(){
<<<<<<< HEAD
  arlindo.GetColor(RGBC);
  Serial.print("R = ");
  Serial.println(RGBC[0]);
<<<<<<< HEAD
  Serial.print("G = ");
  Serial.println(RGBC[1]);
  Serial.print("B = ");
  Serial.println(RGBC[2]);
=======
  Serial.print("R = ");
  Serial.println(RGBC[0]);
  Serial.print("R = ");
  Serial.println(RGBC[0]);
=======
  
>>>>>>> 91061a2f947361719b16fb71f98a0c8ff13f8147
>>>>>>> cc0a986435c6f3a286c7c2f061d287272c4e0255
}

void setup() {
  Serial.begin(9600);
  arlindo.begin();
}

void loop() {
  linetest();
}
