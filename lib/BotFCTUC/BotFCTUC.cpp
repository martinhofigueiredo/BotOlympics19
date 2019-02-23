#include "BotFCTUC.h"

#define PHYSICALCORRECTIONLW 0.95
#define PHYSICALCORRECTIONRW 1.05
bool BotFCTUC::begin(void) {

  pinMode(BUTTON_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  for (int i = 0; i < SONAR_NUMBER; i++) {
    pinMode(_sonarEchoPins[i], INPUT);
    pinMode(_sonarTriggerPins[i], OUTPUT);
  }

  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(FLAME_SENSOR_SCALE_1, OUTPUT);
  pinMode(FLAME_SENSOR_SCALE_2, OUTPUT);
  pinMode(FLAME_SENSOR_SCALE_3, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);

  SetIRScale(SCALE_1);
  FanOff();
  Move(0, 0);

  _colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);

  //return 1;
  return _colorSensor.begin();
}

void BotFCTUC::MotorEsqSpeed(int16_t Speed) {
  if (Speed == 0) {
    digitalWrite(MOTOR_B_IN1, HIGH);
    digitalWrite(MOTOR_B_IN2, HIGH);
  }
  bool forwards = 1;

  if (Speed < 0) {
    Speed = Speed * (-1);
    forwards = 0;
  }
  if (Speed > 255)
    Speed = 255;

  Speed = 255 - Speed;

  if (forwards) {
    digitalWrite(MOTOR_B_IN1, HIGH);
    analogWrite(MOTOR_B_IN2, Speed);
  }
  else {
    analogWrite(MOTOR_B_IN1, Speed);
    digitalWrite(MOTOR_B_IN2, HIGH);
  }
}

void BotFCTUC::MotorDirSpeed(int16_t Speed) {
  if (Speed == 0) {
    digitalWrite(MOTOR_A_IN1, HIGH);
    digitalWrite(MOTOR_A_IN2, HIGH);
  }
  bool forwards = 1;

  if (Speed < 0) {
    Speed = Speed * (-1);
    forwards = 0;
  }
  if (Speed > 255)
    Speed = 255;

  Speed = 255 - Speed;

  if (forwards) {
    digitalWrite(MOTOR_A_IN1, HIGH);
    analogWrite(MOTOR_A_IN2, Speed);
  }
  else {
    analogWrite(MOTOR_A_IN1, Speed);
    digitalWrite(MOTOR_A_IN2, HIGH);
  }
}

void BotFCTUC::Move(int16_t Vel_Esq, int16_t Vel_Dir) {
  MotorEsqSpeed(MOTOR_B_FORWARD * Vel_Esq * PHYSICALCORRECTIONLW);
  MotorDirSpeed(MOTOR_A_FORWARD * Vel_Dir * PHYSICALCORRECTIONRW);

}

void BotFCTUC::FanOn(void) {
  digitalWrite(FAN_PIN, FAN_ON);
}

void BotFCTUC::FanOff(void) {
  digitalWrite(FAN_PIN, !FAN_ON);
}

bool BotFCTUC::ButtonPressed(void) {
  return digitalRead(BUTTON_PIN);
}

void BotFCTUC::GreenLEDOn(void) {
  digitalWrite(GREEN_LED_PIN, LED_ON);
}

void BotFCTUC::GreenLEDOff(void) {
  digitalWrite(GREEN_LED_PIN, !LED_ON);
}

void BotFCTUC::RedLEDOn(void) {
  digitalWrite(RED_LED_PIN, LED_ON);
}

void BotFCTUC::RedLEDOff(void) {
  digitalWrite(RED_LED_PIN, !LED_ON);
}

void BotFCTUC::SetIRScale(IRSensorScale_t scale) {
  _irSensorScale = scale;

  switch (_irSensorScale) {
    default:
    case SCALE_1:             //SCALE 1 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, INPUT);
      pinMode(FLAME_SENSOR_SCALE_2, INPUT);
      pinMode(FLAME_SENSOR_SCALE_3, INPUT);
      break;


    case SCALE_2:             //SCALE 2 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, OUTPUT); //4.7 K
      pinMode(FLAME_SENSOR_SCALE_2, INPUT); //2.3 K
      pinMode(FLAME_SENSOR_SCALE_3, INPUT); //1   K
      digitalWrite(FLAME_SENSOR_SCALE_1, LOW);
      //digitalWrite(FLAME_SENSOR_SCALE_2, LOW);
      //digitalWrite(FLAME_SENSOR_SCALE_3, LOW);
      break;

    case SCALE_3:             //SCALE 3 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, INPUT);
      pinMode(FLAME_SENSOR_SCALE_2, OUTPUT);
      pinMode(FLAME_SENSOR_SCALE_3, INPUT);
      //digitalWrite(FLAME_SENSOR_SCALE_1, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_2, LOW);
      //digitalWrite(FLAME_SENSOR_SCALE_3, LOW);
      break;

    case SCALE_4:             //SCALE 4 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, OUTPUT);
      pinMode(FLAME_SENSOR_SCALE_2, OUTPUT);
      pinMode(FLAME_SENSOR_SCALE_3, INPUT);
      digitalWrite(FLAME_SENSOR_SCALE_1, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_2, LOW);
      //digitalWrite(FLAME_SENSOR_SCALE_3, LOW);
      break;

    case SCALE_5:             //SCALE 5 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, INPUT);
      pinMode(FLAME_SENSOR_SCALE_2, INPUT);
      pinMode(FLAME_SENSOR_SCALE_3, OUTPUT);
      //digitalWrite(FLAME_SENSOR_SCALE_1, LOW);
      //digitalWrite(FLAME_SENSOR_SCALE_2, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_3, LOW);
      break;

    case SCALE_6:             //SCALE 6 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, OUTPUT);
      pinMode(FLAME_SENSOR_SCALE_2, INPUT);
      pinMode(FLAME_SENSOR_SCALE_3, OUTPUT);
      digitalWrite(FLAME_SENSOR_SCALE_1, LOW);
      //digitalWrite(FLAME_SENSOR_SCALE_2, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_3, LOW);
      break;

    case SCALE_7:             //SCALE 7 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, INPUT);
      pinMode(FLAME_SENSOR_SCALE_2, OUTPUT);
      pinMode(FLAME_SENSOR_SCALE_3, OUTPUT);
      //digitalWrite(FLAME_SENSOR_SCALE_1, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_2, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_3, LOW);
      break;

      case SCALE_8:             //SCALE 8 ----------------------------------------------------------
      pinMode(FLAME_SENSOR_SCALE_1, OUTPUT);
      pinMode(FLAME_SENSOR_SCALE_2, OUTPUT);
      pinMode(FLAME_SENSOR_SCALE_3, OUTPUT);
      digitalWrite(FLAME_SENSOR_SCALE_1, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_2, LOW);
      digitalWrite(FLAME_SENSOR_SCALE_3, LOW);
      break;
  }
}

IRSensorScale_t BotFCTUC::GetIRScale(void) {
  return _irSensorScale;
}

int16_t BotFCTUC::GetIR() {
  return analogRead(FLAME_SENSOR_PIN);
}

void BotFCTUC::GetSonars(uint16_t Distance[]) {
  for (int i = 0; i < SONAR_NUMBER; i++) {
    Distance[i] = GetSonar(_sonarTriggerPins[i], _sonarEchoPins[i]);
  }
}

int16_t BotFCTUC::GetSonar(uint16_t sonarTrigger, uint16_t sonarEcho) {
  digitalWrite(sonarTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonarTrigger, LOW);

#ifdef SONAR_TIMEOUT
  uint16_t distance = pulseIn(sonarEcho, HIGH, SONAR_TIMEOUT);
#else
  uint16_t distance = pulseIn(sonarEcho, HIGH);
#endif
  delay(50);

  return (distance / 58.2);
}

void BotFCTUC::GetColor(uint16_t RGBC[]) {
  _colorSensor.getRawData(&RGBC[0], &RGBC[1], &RGBC[2], &RGBC[3]);
}
