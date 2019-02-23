#include <Arduino.h>
#include <BotFCTUC.h>

int incomingByte;
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

void linetest(){
  
}

void setup() {
  Serial.begin(9600);
  arlindo.begin();
}

void loop() {
  linetest();
}
