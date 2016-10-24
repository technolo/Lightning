#ifndef SENSOR_H
#define SENSOR_H

#include "Module.h"
#include "MedianFilter.h"
#include "Filter.h"

// SensorClass
class Sensor : public Module
{
  public:
    int value;

  private:
    int _pin;
    int _k, _p, _m;
    int _maxRange;
    MedianFilter _mFilter;
    Filter* _filter = NULL;

  public:
    Sensor(int pin, unsigned period, int maxRange, int k, int p, int m, int filterSize) : Module(period)
    {
      _pin = pin;
      _maxRange = maxRange;
      _k = k;
      _p = p;
      _m = m;
      _filter = new Filter(filterSize);
    }

    void onUpdate()
    {
        _filter->write(_mFilter.run(analogRead(_pin)));
        value = _filter->mean();
        // value = analogRead(_pin);
    }

    int getCm()
    {
      int val = _k / (constrain(value, _p + 1, 1023) - _p) + _m;
      val = constrain(val, 0, _maxRange);
      return val;
    }
};

#endif // SENSOR_H
