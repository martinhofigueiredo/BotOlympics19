#include <Arduino.h>
#include <BotFCTUC.h>
#include <PID_v1.h>

#define TEST
#define DTHRESHOLD 6
#define DEFAULTSPEED 60
#define MAXRANGE 100;

BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;
double Setpoint, Input, Output, consKp=10, consKi=5, consKd=5;
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
  Input = (double)Distance[2];
  myPID.Compute();
  Serial.print("Output PID = ");
  Serial.println(Output);
  Serial.print("Motor Direira = ");
  Serial.println(DEFAULTSPEED/(Output/255));
  Serial.print("Motor Esquerda= ");
  Serial.println(DEFAULTSPEED);

  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");

  #else/*
  for(int i = 0; i < 3;i++){
    if(Distance[i]==0){
      Distance[i] = MAXRANGE;
    }
  }

  if (Distance[2]>DTHRESHOLD) {
	  arlindo.Move(DEFAULTSPEED,DEFAULTSPEED);
  }
  else if (Distance[1]<DTHRESHOLD) { //demasiado perto de merdas
    Input = (double)Distance[2];
    myPID.Compute();
    Serial.println(Output);
    Serial.println(Distance[1]);
    Serial.println(Distance[2]);
    arlindo.Move(DEFAULTSPEED,DEFAULTSPEED*(Output/255));				 //roda 90 graus
  }*/
  #endif
}

void setup() {

  Serial.begin(57600);
  arlindo.begin();
  Setpoint=(double)DTHRESHOLD;
  myPID.SetMode(AUTOMATIC);
  while(!arlindo.ButtonPressed()){}

}

void loop() {
  navigate();
}
