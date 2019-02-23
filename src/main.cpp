#include <Arduino.h>
#include <BotFCTUC.h>
#include <PID_v1.h>

#define DTHRESHOLD 5

BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;
double Setpoint, Input, Output, consKp=1, consKi=0.05, consKd=0.25;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);


void navigate(){
  if (Distance[1]>DTHRESHOLD) {
    Input = (double)Distance[2];
    myPID.Compute();
	  arlindo.Move(x*(int16_t)Output,x/(int16_t)Output);
  }
  else if (Distance[1]<DTHRESHOLD) { //demasiado perto de merdas
    arlindo.Move(0,50);				 //roda 90 graus
  }

}

void setup() {
  Serial.begin(9600);
  arlindo.begin();
  Setpoint=(double)Dthreshold;
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  navigate();
}
