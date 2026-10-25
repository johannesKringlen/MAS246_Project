/*Button
This class represents a button and manages its pressed and illuminated states.*/

#pragma once // to avoid double include when compiling
#include "HardwareSerial.h"


class Button
{
  protected:

  public:
  bool isPressed{0};
  bool isIlluminated{0};
  
  virtual void SetButtonLight(bool onOff) = 0;
};
