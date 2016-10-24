#ifndef MODULE_H
#define MODULE_H

#include "Arduino.h"


// Module
class Module
{
  public:
    bool isEnabled = true;

    unsigned long getUpdateTime();
    int getUpdatePeriod();
    void update();
  protected:
    Module(int updatePeriod);

  private:
    int updatePeriod_ = 0;
    unsigned long updateTime_ = 0;

    virtual void onUpdate() = 0;
};

#endif // MODULE_H
