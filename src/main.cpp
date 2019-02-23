#include <Arduino.h>
#include <BotFCTUC.h>

#define TrashHole 67

int incomingByte;
BotFCTUC arlindo = BotFCTUC();

uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;

<<<<<<< HEAD
=======
void flame_test()
{
  arlindo.SetIRScale(SCALE_1);

  IRSensorScale_t scale = arlindo.GetIRScale();


  IR = arlindo.GetIR();
  Serial.print("IR = ");
  Serial.println(IR);

    if(IR > TrashHole)
      {
        Serial.println(" FLAME DETEC");
        arlindo.FanOn();
      }
    else
      {
        Serial.println(" FLAME NOT DETEC")
      }
}

>>>>>>> 992bd248a5e37f0e0605dc9ac428ed901bc73afd
void setup() {
  arlindo.begin();
  Serial.begin(9600);
}

void loop(){
    flame_test();
    Serial.print("test");
}
