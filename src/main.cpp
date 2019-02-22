#include <Arduino.h>
#include <BotFCTUC.h>

int incomingByte;
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

void linetest(){
  int i = 0;
  int r, g, b;
}

void setup() {
  Serial.begin(9600);
  arlindo.begin();
}

void loop() {
  linetest();
}
