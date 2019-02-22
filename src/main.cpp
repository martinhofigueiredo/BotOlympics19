#include <Arduino.h>
#include <BotFCTUC.h>

int incomingByte;
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
      // read the oldest byte in the serial buffer:
      incomingByte = Serial.read();
      // if it's a capital H (ASCII 72), turn on the LED:
      if (incomingByte == 'W') {
        arlindo.Move(50,50);
        Serial.print("frente\n");
      }
      // if it's an L (ASCII 76) turn off the LED:
      if (incomingByte == 'A') {
        arlindo.Move(-50,50);
        Serial.print("esquerda\n");
      }
      if (incomingByte == 'S') {
        arlindo.Move(-50,-50);
        Serial.print("tras\n");
      }
      // if it's an L (ASCII 76) turn off the LED:
      if (incomingByte == 'D') {
        arlindo.Move(50,-50);
        Serial.print("direita\n");
      }
      if (incomingByte == 'P') {
        arlindo.Move(0,0);
        Serial.print("parado\n");
      }
}
}
