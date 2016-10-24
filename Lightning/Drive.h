#ifndef DRIVE_H
#define DRIVE_H

#include "Defines.h"
#include "DriveSettings.h"
#include "Sensor.h"
#include "Odometr.h"

class Drive : public Module
{ 
  public:
    unsigned long moveTime = 0;
    unsigned long turnTime = 0;
    float curSpeed = 0;
    int curAngle = DriveSettings::angCenter;
    unsigned long logicTime = 0;

    unsigned long stopTime = 0;
    long stopCnt = 0;
    unsigned long reverseTime = 0;

private:
    Actuators* actuators_ = NULL;
    Odometr* odometr_ = NULL;
    Sensor* sensorFrontLeft_ = NULL;
    Sensor* sensorFrontRight_ = NULL;
    Sensor* sensorLeft_ = NULL;
    Sensor* sensorRight_ = NULL;
    Sensor* sensorLeftBig_ = NULL;
    Sensor* sensorRightBig_ = NULL;    
    
public:
    Drive(int period, Actuators* actuators, Odometr* odometr, Sensor* frontLeft, Sensor* frontRight, Sensor* left, Sensor* right, Sensor* leftBig, Sensor* rightBig) : Module(period)
    {
      actuators_ = actuators;
      odometr_ = odometr;
      sensorFrontLeft_ = frontLeft;
      sensorFrontRight_ = frontRight;
      sensorLeft_ = left;
      sensorRight_ = right;
      sensorLeftBig_ = leftBig;
      sensorRightBig_ = rightBig;        
    }

   /* void init(Actuators* actuators, Sensor* frontLeft, Sensor* frontRight, Sensor* left, Sensor* right, Sensor* leftBig, Sensor* rightBig)
    {
      actuators_ = actuators;
      sensorFrontLeft_ = frontLeft;
      sensorFrontRight_ = frontRight;
      sensorLeft_ = left;
      sensorRight_ = right;
      sensorLeftBig_ = leftBig;
      sensorRightBig_ = rightBig;        
    }*/

    void onUpdate()
    {
      int l;
      int r;
      int fl;
      int fr;
      int fc;

/*
      l = sensorRightBig_->getCm();      
      r = sensorLeftBig_->getCm();
      fl = sensorLeft_->getCm();
      fr = sensorRight_->getCm();
*/
      l = sensorRightBig_->getCm();      
      r = sensorLeftBig_->getCm();
      fl = sensorLeft_->getCm();
      fr = sensorRight_->getCm();


//      l = sensorLeft_->getCm();
//      r = sensorRight_->getCm();
//      fr = sensorRightBig_->getCm();      
//      fl = sensorLeftBig_->getCm();
      
      //fl = sensorFrontLeft_->getCm();
      //fr = sensorFrontRight_->getCm();
      //fc = sensorRightBig_->getCm();
/*
      SerialPrint(l);
      SerialPrint("\t");
      SerialPrint(fl);
      SerialPrint("\t");
      SerialPrint(fr);
      SerialPrint("\t");
      SerialPrint(r);
      SerialPrint("\t");
      SerialPrint(odometr_->getDistance());      
      //SerialPrint("\t");
      //SerialPrint(digitalRead(ENCODER_1));    
      //SerialPrint("\t");
      //SerialPrint(digitalRead(ENCODER_2));    
      SerialPrintln();
      //   SerialPrint(sensorFrontLeft.value);
      //   SerialPrintln();
*/

      int frontDistance = (fl + fr) >> 1;

      if ((millis() - reverseTime) >= 400)
      {
        if (curSpeed >= 0 )
        {
          if (frontDistance <= DriveSettings::dstFwBack)
          {
            curSpeed = -1;
          }
          else if (frontDistance >= DriveSettings::dstTurbo)
          {
            curSpeed = 1.5;
          }
          else
          {
            curSpeed = 1;
          }
        }
        else
        {
          if (frontDistance > DriveSettings::dstBkForward)
          {
            curSpeed = 1;
          }
        }

         
        if ((millis() - stopTime) >= 600)
        {
          int distanceCnt = odometr_->getDistance();
          if (abs(distanceCnt - stopCnt) <= 1)
          {
            curSpeed = (curSpeed >= 0 ) ? -1 : 1;
            reverseTime = millis();
            //SerialPrint("Reverse");
            //SerialPrintln();
          }
          stopTime = millis();
          stopCnt = distanceCnt;
        }
      }

      if (curSpeed < 0)
      {
        if ((millis() - reverseTime) >= 400)
        {
          curAngle = (r > l) ? DriveSettings::angLeft : DriveSettings::angRight;
        }
        else
        {
          curAngle = DriveSettings::angCenter;
        }
      }
      else
      {
        curAngle = (r > l) ? DriveSettings::angRight : DriveSettings::angLeft;
      }   
      
      /*
      // Right Side
      else if (r >= 40)
      {
        curAngle = DriveSettings::angRight;
      }
      else if (r <= 30 || frontDistance <= 50)
      {
        curAngle = DriveSettings::angLeft;
      }      
      else
      {
        curAngle = DriveSettings::angCenter;
      }
      */

      
      // Left Side
  /*    else if (l >= 40)
      {
        curAngle = DriveSettings::angLeft;
      }
      else if (l <= 30 || frontDistance <= 100)
      {
        curAngle = DriveSettings::angRight;
      }      
      else
      {
        curAngle = DriveSettings::angCenter;
      }*/
            

/*
      // Default
      else if (min(fl, fr) > 120) //&& l < 100 && r < 100)
      {
        curAngle = DriveSettings::angCenter;
      }
      else if (min(fl, fr) > 100) //&& l < 100 && r < 100)
      {
        curAngle = (r > l) ? DriveSettings::angHalfRight : DriveSettings::angHalfLeft;
      }
      else
      {
        curAngle = (r > l) ? DriveSettings::angRight : DriveSettings::angLeft;
      }      
*/

      /* else
        if (min(fl, fr) <= DriveSettings::dstTurn && min(fl, fr) > DriveSettings::dstTurn2)
        {
         curAngle = (r > l) ? DriveSettings::angHalfRight : DriveSettings::angHalfLeft;
        }*/

      /* else if (min(fl, fr) <= DriveSettings::dstTurn2 )
        {
         curAngle = (r > l) ? DriveSettings::angRight : DriveSettings::angLeft;
        }
        else
        {
         curAngle = DriveSettings::angCenter;
        }*/

      actuators_->setSpeed(curSpeed);
      actuators_->setAngle(curAngle);
    }
};

#endif // DRIVE_H
