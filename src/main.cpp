#include <Arduino.h>
#include <BotFCTUC.h>
#include <PID_v1.h>
#include <PID_Autotune_V0.h>

//#define TEST
#define THRESHOLD 10
#define DEFAULTSPEED 85
#define MAXRANGE 100;
#define K 1.5

BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;
int16_t Motor[2];
/*double Setpoint, Input, Output, consKp=101, consKi=0.003, consKd=0.2;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
SetOutputLimits(0,THRESHOLD)*/


void navigate(){
  arlindo.GetSonars(Distance);
  for(int i = 0; i < 3;i++){
    if(Distance[i]==0){
      Distance[i] = THRESHOLD+1;
    }
  }

  if(Distance[1] < 11){
    arlindo.Move(85,-85);

    }
  else{
    int kp=(Distance[2]-THRESHOLD)*5;
    /*Serial.print("Left Motor Speed =");
    Serial.println(DEFAULTSPEED+kp);
    Serial.print("Right Motor Speed =");
    Serial.println(DEFAULTSPEED-kp);*/
  	arlindo.Move(DEFAULTSPEED-kp,DEFAULTSPEED+kp);

  }

  #ifdef TEST
  Serial.print("Esquerda =");
  Serial.println(Distance[0]);
  Serial.print("Center =");
  Serial.println(Distance[1]);
  Serial.print("Direita =");
  Serial.println(Distance[2]);
  //Input = (double)Distance[2];
  //myPID.Compute();
  //Serial.print("Output PID = ");
  //Serial.println(Output);
  Serial.print("Motor Esquerda = ");
  Serial.println(Motor[0]);
  Serial.print("Motor Direita = ");
  Serial.println(Motor[1]);

  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");
  #endif
  //arlindo.Move(Motor[0],Motor[1]);
}

void setup(){
  Serial.begin(57600);
  arlindo.begin();
  //Setpoint=(double)THRESHOLD;
  //myPID.SetMode(AUTOMATIC);
  //#ifdef !defined(TEST)
  while(!arlindo.ButtonPressed()){}
}

void loop() {
  navigate();
}
