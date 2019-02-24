#include <Arduino.h>
#include <BotFCTUC.h>

#define K 1.5

//NAVIGATION
#define DEFAULTSPEED 80
#define SLOWSPEED DEFAULTSPEED/2
#define MAXRANGE 100
#define HARDTURN 97
#define FRONTLIMIT 14
#define RIGHTLIMIT 20
#define LEFTLIMIT 20
#define COMPENSATER 37
//#define TEST
#define RIGHT true
#define LEFT false

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


int n_linhas = 0;
int state = 0;
unsigned long currentmillis;
bool oldline=0, currentline=0, entroudivisao=0;


//Wallfollowing algorithm
void navigate(bool dir){
  for(int i = 0; i < 3;i++){
    if(Distance[i]==0){
      Distance[i] = 50;
    }
  }
  if(dir){
  if(Distance[1] < FRONTLIMIT){
    arlindo.Move(HARDTURN,-(HARDTURN));
  }
  else {
    float ke = (Distance[2]-RIGHTLIMIT)*(COMPENSATER/10);
  	arlindo.Move(DEFAULTSPEED,DEFAULTSPEED+ke);
  }
  }
  else{

  if(Distance[1] < FRONTLIMIT){
    arlindo.Move(-(HARDTURN),HARDTURN);
  }
  else {
    float ke = (Distance[0]-LEFTLIMIT)*(COMPENSATER/10);
  	arlindo.Move(DEFAULTSPEED+ke,DEFAULTSPEED);
  }
  }
}

//Returns 2 if flame far, 1 if close, 0 if no flame
bool flametest(){
  if(IR > IRLIMIT)
  {
    Serial.println(" FLAME DETEC");
    arlindo.RedLEDOn();
    return 1;
  }
  else
  {
    Serial.println(" FLAME NOT DETEC");
    arlindo.RedLEDOff();
    return 0;
  }
}

//true if passes white line
bool linetest(){
  if(RGBC[0] < COLORLIMIT && RGBC[1] < COLORLIMIT && RGBC[2] < COLORLIMIT && RGBC[3]){
    arlindo.GreenLEDOff();
    return 0;
  }
  else{
    n_linhas++;
    arlindo.GreenLEDOn();
    return 1;
  }
}

bool FE_line(){
  oldline=currentline;
  currentline=linetest();
  if (oldline==1 && currentline==0){
    return 1;
  }
  else{
    return 0;
  }
}

void setup(){
  #ifdef TEST
  Serial.begin(57600);
  #endif
  arlindo.begin();
  arlindo.SetIRScale(SCALE_8);
  while(!arlindo.ButtonPressed()){}

}

void loop()
{
  arlindo.GetColor(RGBC);
  IR = arlindo.GetIR();
  arlindo.GetSonars(Distance);
  entroudivisao=FE_line();

  switch(state){
    case 0: //A mexer
    {
      navigate(RIGHT);
      if(entroudivisao && !(n_linhas%2) && (n_linhas > 1))
      {
        state = 1;
      }
      break;
    }
    case 1: //Dentro de Quarto
    {
      currentmillis = millis();
      while(millis()- currentmillis < 1000 || Distance[1] < 15){
        arlindo.Move(SLOWSPEED,SLOWSPEED);
      }
      state = 2;
      break;
    }
    case 2: //RODA A PROCURA DA CHAMA
    {
      while(((millis()- currentmillis) < 3500) && ((millis() - currentmillis) > 1000) && (n_linhas > 1))
      {
          arlindo.Move(DEFAULTSPEED*0.7,-DEFAULTSPEED*0.7);
          if(flametest() == 1){
            state = 3;
            break;
          }
      }
      break;
    }
    case 3:
    {

      while(Distance[1] > 13)
      {
      arlindo.Move(SLOWSPEED,SLOWSPEED);
      }
      arlindo.Move(0,0);
      state = 4;
      break;
    }
    case 4:
    {
      currentmillis = millis();
      while((millis()- currentmillis) < 1000 ){
      arlindo.FanOn();
    }
    case 5:
    {
      while(n_linhas != 0){
        navigate(LEFT);
      }
    }
  }
}
  #ifdef TEST
  //Serial.print("Esquerda =");
  //Serial.println(Distance[0]);
  Serial.print("Center =");
  Serial.println(Distance[1]);
  Serial.print("Direita =");
  Serial.println(Distance[2]);
  Serial.print("IR = ");
  Serial.println(IR);
  Serial.print("n_linhas = ");
  Serial.println(n_linhas);
  Serial.print("!n_linhas%12 = ");
  Serial.println(!(n_linhas%2));
  Serial.print("State = ");
  Serial.println(state);
  Serial.println();
  /*Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");*/
  #endif
}
