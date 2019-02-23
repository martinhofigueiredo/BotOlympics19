#include <Arduino.h>
#include <BotFCTUC.h>
#include <PID_v1.h>

#define TEST
#define THRESHOLD 10
#define DEFAULTSPEED 60
#define MAXRANGE 100;
#define K 1.5

BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;
int16_t Motor[2];
double Setpoint, Input, Output, consKp=10, consKi=5, consKd=5;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);


void navigate(){
  arlindo.GetSonars(Distance);
  for(int i = 0; i < 3;i++){
    if(Distance[i]==0){
      Distance[i] = MAXRANGE;
    }
  }

  if(Distance[1] < THRESHOLD){
    if(Distance[0]>Distance[2]){
      Motor[0] = DEFAULTSPEED*-1*K;
      Motor[1] = DEFAULTSPEED*K;
      Motor[0] = DEFAULTSPEED;
      Motor[1] = DEFAULTSPEED;
      delay(500);
    }
    else{
      Motor[0] = DEFAULTSPEED*K;
      Motor[1] = DEFAULTSPEED*-1*K;
      Motor[0] = DEFAULTSPEED;
      Motor[1] = DEFAULTSPEED;
      delay(500);
    }
  }
  else{
      Motor[0] = DEFAULTSPEED;
      Motor[1] = DEFAULTSPEED;
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
  arlindo.Move(Motor[0],Motor[1]);
}

void setup(){
  Serial.begin(57600);
  arlindo.begin();
  Setpoint=(double)THRESHOLD;
  myPID.SetMode(AUTOMATIC);
  //#ifdef !defined(TEST)
  while(!arlindo.ButtonPressed()){}
}

void loop() {
  navigate();
}
