#include <Arduino.h>
#include <BotFCTUC.h>

// variaveis
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

void setup(){
  Serial.begin(9600);
  arlindo.begin();
  arlindo.SetIRScale(SCALE_8);
}

void loop()
{
IR = arlindo.GetIR();
Serial.print("IR = ");
Serial.println(IR);
}
