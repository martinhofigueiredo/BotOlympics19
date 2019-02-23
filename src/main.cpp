#include <Arduino.h>
#include <BotFCTUC.h>


int incomingByte;
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

void linetest(){
  arlindo.GetColor(RGBC);
  Serial.print("R = ");
  Serial.println(RGBC[0]);
  Serial.print("G = ");
  Serial.println(RGBC[1]);
  Serial.print("B = ");
  Serial.println(RGBC[2]);
}

void setup() {
  Serial.begin(9600);
  arlindo.begin();
}

void loop() {
  linetest();
}
