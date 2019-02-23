#include <Arduino.h>
#include <BotFCTUC.h>

//#define COLOR_TEST


int incomingByte;
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

void linetest(){
  arlindo.GetColor(RGBC);
  #ifdef COLOR_TEST
    Serial.print("R = ");
    Serial.println(RGBC[0]);
    Serial.print("G = ");
    Serial.println(RGBC[1]);
    Serial.print("B = ");
    Serial.println(RGBC[2]);
    Serial.print("C = ");
    Serial.println(RGBC[3]);
  #else
  if(RGBC[0] < 100 && RGBC[1] < 100 && RGBC[2] < 100){
    Serial.print("Preto");
  }
  else{Serial.print("Branco");}
  #endif


}

void setup() {
  Serial.begin(9600);
  arlindo.begin();
}

void loop() {
  linetest();
}
