#include "Module.h"


Module::Module(int updatePeriod)
{
  updatePeriod_ = updatePeriod;
}

// getUpdateTime()
unsigned long Module::getUpdateTime()
{
  return updateTime_;
}

// getUpdateTime()
int Module::getUpdatePeriod()
{
  return updatePeriod_;
}

// update
void Module::update()
{
  if (isEnabled)
  {
    if (updatePeriod_ > 0)
    {
      unsigned long curTime = millis();
      if ((curTime - updateTime_) >= updatePeriod_)
      {
        onUpdate();

        updateTime_ = millis();
      }
    }
    else
    {
      onUpdate();
    }
  }
}


