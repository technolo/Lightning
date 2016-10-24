#ifndef ODOMETR_H
#define ODOMETR_H

//#include <Filter.h>
#include "defines.h"

class Odometr : public Module
{
  private:
    volatile long distance_ = 0;
    volatile unsigned long distanceTime_ = 0;
    volatile bool dirState_ = false;
    volatile int speed_ = 0;
    volatile double x_ = 0;
    volatile double y_ = 0;
    float angX_ = 0;
    float angY_ = 0;
    float angZ_ = 0;
    bool useImu_ = false;

    Filter* filter_;
    
  public:
    Odometr(int period, bool useImu) : Module(period)
    {
      useImu_ = useImu;
      filter_ = new Filter(30);
    }  

    void init(bool dirState)
    {
      dirState_ = dirState;
    }

    void isrDirEncoder()
    {
      dirState_ = !dirState_;
    }
    
    void isrCountEncoder()
    {
      unsigned long curTime = micros();
      int dir = (dirState_) ? -1 : 1;
      
      speed_ = dir * 1000000.0 / (curTime - distanceTime_); 
      distance_ += dir;

      if (useImu_)
      {
        // TODO: расчет нового местоположения, используя текущий угол по оси Z
      }

      distanceTime_ = curTime;
    } 

    long getDistance()
    {
      return distance_;
    }

    long getDistanceTime()
    {
      return distanceTime_;
    }  

    double getX()
    {
      return x_;
    }  

    double getY()
    {
      return y_;
    } 

    float getAngX()
    {
      return angX_;
    }  

    float getAngY()
    {
      return angY_;
    }                  

    float getAngZ()
    {
      return angZ_;
    }  

    int getSpeed()
    {
      int result = speed_;
      
      int dir = (speed_ >= 0) ? 1 : -1;
      int curSpeed = dir * 1000000.0 / (micros() - distanceTime_); 

      if (abs(curSpeed) < abs(speed_))
      {
        result = curSpeed;
      }
      
      return result; 
    }

    int getAvgSpeed()
    {
      return filter_->mean();
    }

    void onUpdate()
    {
      // TODO: обработка данных с IMU, расчет текущих углов эйлера   
      filter_->write(getSpeed());
    }
};

#endif // ODOMETR_H
