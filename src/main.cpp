#include <Arduino.h>
#include <BotFCTUC.h>


//#define TEST
#define THRESHOLD 20
#define DEFAULTSPEED 120
#define MAXRANGE 100;
#define K 1.5

#define TrashHole 60

int incomingByte;

BotFCTUC arlindo = BotFCTUC();

uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;
int16_t Motor[2];

//Wallfollowing algorithm
void navigate(){
  arlindo.GetSonars(Distance);
  for(int i = 0; i < 3;i++){
    if(Distance[i]==0){
      Distance[i] = 50;
    }
  }
//Serial.println(Distance[2]);
  if(Distance[1] < 14){
    arlindo.Move(97,-(97));

    }
 else {
    float ke = (Distance[2]-THRESHOLD)*3.7;
    /*Serial.print("Left Motor Speed =");
    Serial.println(DEFAULTSPEED+kp);
    Serial.print("Right Motor Speed =");
    Serial.println(DEFAULTSPEED-kp);*/
  	arlindo.Move(DEFAULTSPEED,DEFAULTSPEED+ke);
    //Serial.println(DEFAULTSPEED-kp);
  	//arlindo.Move(DEFAULTSPEED-kp,DEFAULTSPEED+kp);
}}

//Returns 2 if flame far, 1 if close, 0 if no flame
int flametest(){
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
        return 1;
      }
      if(IR > TrashHole && Distance[1] < 13){
        Serial.println("flame deetect near");
        arlindo.FanOn();
        return 2;
    }
    else
      {
        Serial.println(" FLAME NOT DETEC");
        arlindo.FanOff();
        return 0;
      }
}

//true if passes white line
bool linetest(){
  arlindo.GetColor(RGBC);
  #ifdef TEST
    Serial.print("R = ");
    Serial.println(RGBC[0]);
    Serial.print("G = ");
    Serial.println(RGBC[1]);
    Serial.print("B = ");
    Serial.println(RGBC[2]);
    Serial.print("C = ");
    Serial.println(RGBC[3]);
  #else
  if(RGBC[0] < 100 && RGBC[1] < 100 && RGBC[2] < 100){
    return false;
  }
  else{
    return true;
  }
  #endif
}


void setup(){
  Serial.begin(9600);
  arlindo.begin();
  while(!arlindo.ButtonPressed()){}
}


void loop() {

  if(linetest()){
    while(flametest() == 0){
      arlindo.Move(-20,20);
    }}
  else{
    navigate();
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
}
