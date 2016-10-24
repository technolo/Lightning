#ifndef LINK_H
#define LINK_H

#include "Defines.h"
#include "DriveSettings.h"
#include "Sensor.h"
#include "Odometr.h"
#include "Drive.h"

class Link : public Module
{ 
private:
    Actuators* actuators_ = NULL;
    Odometr* odometr_ = NULL;
    Drive* drive_ = NULL;
    Sensor* sensorFrontLeft_ = NULL;
    Sensor* sensorFrontRight_ = NULL;
    Sensor* sensorLeft_ = NULL;
    Sensor* sensorRight_ = NULL;
    Sensor* sensorLeftBig_ = NULL;
    Sensor* sensorRightBig_ = NULL;  

public:
    Link(int period, Actuators* actuators, Odometr* odometr, Drive* drive, Sensor* frontLeft, Sensor* frontRight, Sensor* left, Sensor* right, Sensor* leftBig, Sensor* rightBig) : Module(period)
    {
      actuators_ = actuators;
      odometr_ = odometr;
      drive_ = drive;
      sensorFrontLeft_ = frontLeft;
      sensorFrontRight_ = frontRight;
      sensorLeft_ = left;
      sensorRight_ = right;
      sensorLeftBig_ = leftBig;
      sensorRightBig_ = rightBig;        
    }

    void onUpdate()
    {
      const int packageSize = 60;
      int availableBytes = BTSerial.availableForWrite();
      if (availableBytes < packageSize)
        return;

      int l;
      int r;
      int fl;
      int fr;
      int fc;
      l = sensorLeft_->getCm();
      r = sensorRight_->getCm();
      fr = sensorRightBig_->getCm();      
      fl = sensorLeftBig_->getCm();
      
      //fl = sensorFrontLeft_->getCm();
      //fr = sensorFrontRight_->getCm();
            
      SerialPrintBT(l);
      SerialPrintBT("\t");
      SerialPrintBT(fl);
      SerialPrintBT("\t");
      SerialPrintBT(fr);
      SerialPrintBT("\t");
      SerialPrintBT(r);
      SerialPrintBT("\t");
      SerialPrintBT(odometr_->getDistance());      
      SerialPrintBT("\t");
      SerialPrintBT(odometr_->getAvgSpeed());

      
      //SerialPrintBT("\t");
      //SerialPrintBT(digitalRead(ENCODER_1));    
      //SerialPrintBT("\t");
      //SerialPrintBT(digitalRead(ENCODER_2));    
      SerialPrintlnBT();
      //   SerialPrintBT(sensorFrontLeft.value);
      //   SerialPrintBTln();        
    }
};

#endif // LINK_H
