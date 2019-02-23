#include <Arduino.h>
#include <BotFCTUC.h>

#define TrashHole 60

int incomingByte;
BotFCTUC arlindo = BotFCTUC();

uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;


void flame_test()
{
  arlindo.SetIRScale(SCALE_7);
  arlindo.GetSonars(Distance);
  IRSensorScale_t scale = arlindo.GetIRScale();


  IR = arlindo.GetIR();
  Serial.print("IR = ");
  Serial.println(IR);
  Serial.print("dist = ");
  Serial.println(Distance[1]);
    if(IR > TrashHole && Distance[1] > 14)
      {
        Serial.println(" FLAME DETEC FAR");
        //arlindo.FanOn();
      }
      if(IR > TrashHole && Distance[1] < 13){
        Serial.println("flame deetect near");
        arlindo.FanOn();
    }
    else
      {
        Serial.println(" FLAME NOT DETEC");
        arlindo.FanOff();
      }
}

void setup() {
  arlindo.begin();
  Serial.begin(9600);
}

void loop(){
    flame_test();
}
