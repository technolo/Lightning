#include "Sensor.h"
#include "DriveSettings.h"
#include "Defines.h"
#include "Actuators.h"
#include "Drive.h"
#include "Odometr.h"
#include "Link.h"

Sensor sensorFrontLeft(FRONT_LEFT, SENSOR_PERIOD, 120, 5126, 36, -1, 5);
Sensor sensorFrontRight(FRONT_RIGHT, SENSOR_PERIOD, 120, 5688, 59, -2, 5);

Sensor sensorLeft(LEFT, SENSOR_PERIOD, 120, 5344, 34, -1, 5);
Sensor sensorRight(RIGHT, SENSOR_PERIOD, 120, 5789, 39, -2, 5);

Sensor sensorLeftBig(LEFT_BIG, BIG_SENSOR_PERIOD, 150, 23101, -12, -10, 5);
Sensor sensorRightBig(RIGHT_BIG, BIG_SENSOR_PERIOD, 150, 27110, -46, -15, 5);

Odometr odometr(ODOMETR_PERIOD, false);
Actuators actuators(ACTUATORS_PERIOD, &odometr);
Drive drive(DRIVE_PERIOD, &actuators, &odometr, &sensorFrontLeft, &sensorFrontRight, &sensorLeft, &sensorRight, &sensorLeftBig, &sensorRightBig);
Link lnk(LINK_PERIOD, &actuators, &odometr, &drive, &sensorFrontLeft, &sensorFrontRight, &sensorLeft, &sensorRight, &sensorLeftBig, &sensorRightBig);

void isrEnc1Change()
{
  odometr.isrDirEncoder();
}

void isrEnc2Falling()
{
  odometr.isrCountEncoder();
}

void setup() 
{
  Serial.begin(57600);
  BTSerial.begin(57600);

  pinMode(ENCODER_1, INPUT_PULLUP);
  pinMode(ENCODER_2, INPUT_PULLUP); 
  noInterrupts();
  odometr.init(digitalRead(ENCODER_1));
  attachInterrupt(ENCODER_1, isrEnc1Change, CHANGE);
  attachInterrupt(ENCODER_2, isrEnc2Falling, FALLING); 
  interrupts();
  
  actuators.init();
  //drive.init(&actuators, &sensorFrontLeft, &sensorFrontRight, &sensorLeft, &sensorRight, &sensorLeftBig, &sensorRightBig);

}

void processStr(String str)
{
  int pos = str.indexOf("&");
  if (pos >= 0)
  {
    DriveSettings::SetValue(str.substring(0, pos), str.substring(pos + 1));
  }
}

void loop()
{
  bool mAuto = true;//false;

  while (1)
  {
    sensorFrontLeft.update();
    sensorFrontRight.update();
    sensorLeft.update();
    sensorRight.update();
    sensorLeftBig.update();
    sensorRightBig.update();
    
    odometr.update();
    drive.update();
    lnk.update();
    /*
      while (BTSerial.available())
      {
      char sym = (char)BTSerial.read();

      static bool strStarted = false;
      const int maxStrlen = 50;
      static char str[50];
      static int curPos = 0;
      if (strStarted)
      {
        if (sym == '\n')
        {
          str[curPos] = 0;
          strStarted = false;
          processStr(str);
        }
        else
        {
          str[curPos++] = sym;
          if (curPos >= maxStrlen)
          {
            strStarted = false;
          }
        }
      }
      else if (sym == '*')
      {
        strStarted = true;
        curPos = 0;
      }
      }
    */
  }
}


