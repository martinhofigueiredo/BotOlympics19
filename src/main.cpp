#include <Arduino.h>
#include <BotFCTUC.h>
#include <PID_v1.h>

//#define TEST
#define DTHRESHOLD 6
#define DEFAULTSPEED 60

BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;
double Setpoint, Input, Output, consKp=0.8, consKi=0.05, consKd=0.25;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);


void navigate(){
  arlindo.GetSonars(Distance);
  #ifdef TEST
  Serial.print("Esquerda =");
  Serial.println(Distance[0]);
  Serial.print("Center =");
  Serial.println(Distance[1]);
  Serial.print("Direita =");
  Serial.println(Distance[2]);
  arlindo.Move(255*0.6,255*0.6);
  #else
  if (Distance[1]==0) Distance[1]=DTHRESHOLD+2;
  if (Distance[1]>DTHRESHOLD) {
    Input = (double)Distance[2];
    myPID.Compute();
    Serial.println(Output);
    Serial.println(Distance[1]);
    Serial.println(Distance[2]);
	  arlindo.Move(DEFAULTSPEED*(int16_t)Output,DEFAULTSPEED/(int16_t)Output);
  }
  else if (Distance[1]<DTHRESHOLD) { //demasiado perto de merdas
    arlindo.Move(0,DEFAULTSPEED);				 //roda 90 graus
  }
  #endif
}

void setup() {

  Serial.begin(9600);
  arlindo.begin();
  Setpoint=(double)DTHRESHOLD;
  myPID.SetMode(AUTOMATIC);
  while(!arlindo.ButtonPressed()){}

}

void loop() {
  navigate();
}
