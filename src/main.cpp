#include <Arduino.h>
#include <BotFCTUC.h>

int incomingByte;
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
uint16_t Distance[3];
int16_t IR;


void setup() {
  Serial.begin(57600);
  arlindo.begin();
  Serial.print("EstouVivo");
}

void loop() {
  arlindo.GetSonars(Distance);
  Serial.print("Esquerda = ");
  Serial.println(Distance[0]);
  Serial.print("Centro = ");
  Serial.println(Distance[1]);
  Serial.print("Direita = ");
  Serial.println(Distance[2]);
}
