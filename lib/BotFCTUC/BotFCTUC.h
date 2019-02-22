#ifndef _BOTFCTUC
#define _BOTFCTUC

#include "Arduino.h"
#include "Adafruit_TCS34725.h"

#define BUTTON_PIN            8
#define GREEN_LED_PIN         7
#define RED_LED_PIN           13
#define LED_ON                1

#define SONAR_NUMBER          3
//#define SONAR_TIMEOUT         3492 // 60cm x 58.2 cm/us
#define LEFT_SONAR_TRIGGER    11
#define LEFT_SONAR_ECHO       12
#define CENTER_SONAR_TRIGGER  2
#define CENTER_SONAR_ECHO     4
#define RIGHT_SONAR_TRIGGER   0
#define RIGHT_SONAR_ECHO      1

#define FLAME_SENSOR_PIN      A0
#define FLAME_SENSOR_SCALE_1  A1
#define FLAME_SENSOR_SCALE_2  A2
#define FLAME_SENSOR_SCALE_3  A3

#define FAN_PIN               10
#define FAN_ON                LOW

#define MOTOR_A_IN1           5
#define MOTOR_A_IN2           3
#define MOTOR_A_FORWARD       1 
#define MOTOR_B_IN1           9
#define MOTOR_B_IN2           6
#define MOTOR_B_FORWARD       -1 

typedef enum
{
  SCALE_1 = 0x00,
  SCALE_2 = 0x01,
  SCALE_3 = 0x02,
  SCALE_4 = 0x03,
  SCALE_5 = 0x04,
  SCALE_6 = 0x05,
  SCALE_7 = 0x06,
  SCALE_8 = 0x07
}
IRSensorScale_t;

class BotFCTUC{
  public:
  bool begin(void);
  void MotorEsqSpeed(int16_t Speed);
  void MotorDirSpeed(int16_t Speed);
  void Move(int16_t Vel_Esq, int16_t Vel_Dir);
  void FanOn(void);
  void FanOff(void);
  bool ButtonPressed(void);
  void GreenLEDOn(void);
  void GreenLEDOff(void);
  void RedLEDOn(void);
  void RedLEDOff(void);
  void SetIRScale(IRSensorScale_t scale);
  IRSensorScale_t GetIRScale(void);
  int16_t GetIR();
  void GetSonars(uint16_t Distance[]);
  int16_t GetSonar(uint16_t sonarTrigger, uint16_t sonarEcho);
  void GetColor(uint16_t RGBC[]);
  
  private:
  // Sonar pins {left, center, right}
  uint16_t _sonarEchoPins[SONAR_NUMBER] = {
    LEFT_SONAR_ECHO,
    CENTER_SONAR_ECHO,
    RIGHT_SONAR_ECHO
  };
  uint16_t _sonarTriggerPins[SONAR_NUMBER] = {
    LEFT_SONAR_TRIGGER,
    CENTER_SONAR_TRIGGER,
    RIGHT_SONAR_TRIGGER
  };
  IRSensorScale_t _irSensorScale;
  Adafruit_TCS34725 _colorSensor;

};

#endif
