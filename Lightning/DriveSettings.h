#ifndef DRIVE_SETTINGS_H
#define DRIVE_SETTINGS_H 

#include "Defines.h"

namespace DriveSettings
{
  
  // Angles
  int angCenter = SRV_CENTER - 0;
  int angLeft = SRV_CENTER + SRV_MAX_ANGLE;
  int angRight = SRV_CENTER - SRV_MAX_ANGLE;
  int angHalfLeft = SRV_CENTER + SRV_MAX_ANGLE / 3;
  int angHalfRight = SRV_CENTER - SRV_MAX_ANGLE / 3;
  
  // Distances
  int dstFwBack = 20;
  int dstBkForward = 40;
  int dstTurbo = 160;
  int dstTurn = 110;
  int dstTurn2 = 80;
  
  const int size = 10;
  int* values = &angCenter;
  String uids[size] = {"angCenter", "angLeft", "angRight", "angHalfLeft", "angHalfRight",
                       "dstFwBack", "dstBkForward", "dstTurbo", "dstTurn", "dstTurn2"
                      };
  
  void SetValue(String uid, String value)
  {
    for (int i = 0; i < size; i++)
    {
      if (uid.equals(uids[i]))
      {
        values[i] = value.toInt();
      }
    }
  }
  
  String GetDescription(char split)
  {
    String result = "";
    for (int i = 0; i < size; i++)
    {
      result += uids[i] + split + values[i];
    }
  
    return result;
  }
} 

#endif // DRIVE_SETTINGS_H 
