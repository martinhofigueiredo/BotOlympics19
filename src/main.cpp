#include <Arduino.h>
#include <BotFCTUC.h>

//#define TEST
#define COLORTHRESHOLD = 100;

BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

void setup() {
  Serial.begin(9600);
  arlindo.begin();
}

void loop() {

}
