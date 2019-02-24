#include <Arduino.h>
#include <BotFCTUC.h>

#define K 1.5

//NAVIGATION
#define DEFAULTSPEED 100
#define MAXRANGE 100
#define HARDTURN 97
#define FRONTLIMIT 14
#define RIGHTLIMIT 20
#define COMPENSATER 37
#define TEST

//FLAME
#define IRLIMIT 60

//RGBC
#define COLORLIMIT 100


// variaveis
BotFCTUC arlindo = BotFCTUC();
uint16_t RGBC[3];
int16_t Distance[3];
int16_t IR;
int16_t Motor[2];

int incomingByte;

bool oldline = false;
int REline = 0;
int n_linhas = 0;

unsigned long currentmillis;



//Wallfollowing algorithm
void navigate(){
  arlindo.GetSonars(Distance);
  for(int i = 0; i < 3;i++){
    if(Distance[i]==0){
      Distance[i] = 50;
    }
  }
//Serial.println(Distance[2]);
  if(Distance[1] < FRONTLIMIT){
    arlindo.Move(HARDTURN,-(HARDTURN));
    }
 else {
    float ke = (Distance[2]-RIGHTLIMIT)*(COMPENSATER/10);
    /*Serial.print("Left Motor Speed =");
    Serial.println(DEFAULTSPEED+kp);
    Serial.print("Right Motor Speed =");
    Serial.println(DEFAULTSPEED-kp);*/
  	arlindo.Move(DEFAULTSPEED,DEFAULTSPEED+ke);
    //Serial.println(DEFAULTSPEED-kp);
  	//arlindo.Move(DEFAULTSPEED-kp,DEFAULTSPEED+kp);
}
}

//Returns 2 if flame far, 1 if close, 0 if no flame
int flametest(){
  arlindo.SetIRScale(SCALE_8);
  arlindo.GetSonars(Distance);
  arlindo.Move(0,0);

  IR = arlindo.GetIR();
  Serial.print("IR = ");
  Serial.println(IR);
  Serial.print("dist = ");
  Serial.println(Distance[1]);


    if(IR > IRLIMIT && Distance[1] > 13)
      {
        Serial.println(" FLAME DETEC FAR");
        arlindo.RedLEDOn();
        return 2;
      }
      if(IR > IRLIMIT && Distance[1] <= 13){
        Serial.println("FLAME DETEC CLOSE");
        arlindo.RedLEDOn();
        return 1;
    }
      else
      {
        Serial.println(" FLAME NOT DETEC");
        return 0;
      }
}

//true if passes white line
int linetest(){
  arlindo.GetColor(RGBC);
  if(RGBC[0] < COLORLIMIT && RGBC[1] < COLORLIMIT && RGBC[2] < COLORLIMIT){
    arlindo.GreenLEDOff();
    return 0;
  }
  else{
    arlindo.GreenLEDOn();
    return 1;
  }
}

void setup(){
  Serial.begin(9600);
  arlindo.begin();
  while(!arlindo.ButtonPressed()){}
}

void loop()
{
  //flametest();
  //navigate();

  if(oldline == false && linetest() == true)
  {
    REline = 1;
    n_linhas++;
  }
  else{
    REline = 0;
  }

  // Dentro Quarto
  if ((REline == 1) && !(n_linhas%2))
  {
    currentmillis = millis();
    // primeiro 1 seg

  while(millis()- currentmillis < 1000){
    navigate();

  }
// segundo 2 seg //
  while(millis()- currentmillis < 3500 && millis() - currentmillis > 1000 && n_linhas > 1)
  {
      Serial.print("dar a volta ");
      Serial.println(flametest());
      arlindo.Move(DEFAULTSPEED*0.8,-DEFAULTSPEED*0.8);
      if(flametest() == 2 || flametest() == 1){
        Serial.println("break");
        break;
      }
  }
  switch(flametest()){
    case 1:
    {
      while(1){
      arlindo.Move(0,0);}
      break;
    }
    case 2:
    {
      while(1){arlindo.Move(0,0);}
      break;
    }
  }
  arlindo.Move(0,0);
  }
  else{navigate();}


  oldline = linetest();

  #ifdef TEST
  //Serial.print("Esquerda =");
  //Serial.println(Distance[0]);
  //Serial.print("Center =");
  //Serial.println(Distance[1]);
  //Serial.print("Direita =");
  //Serial.println(Distance[2]);
  //Input = (double)Distance[2];
  //myPID.Compute();
  //Serial.print("Output PID = ");
  //Serial.println(Output);
  /*Serial.print("Motor Esquerda = ");
  Serial.println(Motor[0]);
  Serial.print("Motor Direita = ");
  Serial.println(Motor[1]);*/


  Serial.print("LineDetect = ");
  Serial.println(linetest());
  Serial.print("n_linhas = ");
  Serial.println(n_linhas);
  Serial.print(" ! n_linhas % 2 = ");
  Serial.println(!(n_linhas%2));
  Serial.print("REline = ");
  Serial.println(REline);
  Serial.println();


  /*Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");*/
  #endif
}
