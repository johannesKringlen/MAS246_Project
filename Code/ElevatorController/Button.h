#pragma once // to avoid double include when compiling
#include "HardwareSerial.h"
/*Button
This class represents a button and manages its pressed and illuminated states.

History:

revision  date        description
0.0.2     09.10.2026  created virtual functions
0.0.1     01.10.2026  file created

*/

class Button
{
  protected:

  public:
  bool isPressed{0};
  bool isIlluminated{0};
  
  //virtual bool GetStatus() = 0;

  //virtual void Begin(int inputPin, int outputPin,  bool log);

  virtual void SetButtonLight(bool onOff) = 0;
};
