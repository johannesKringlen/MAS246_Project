/*FloorButton
This class represents a button used to request the elevator from a specific floor.

History:

revision  date        description
0.0.1     10.10.2026  file created

*/

#include "Button.h"

class FloorButton : public Button
{
private:
  bool _log;
  char _key;
  int _floor;
  const char* _direction;
  bool _lastStateLed;
  bool _isPressed;

public:
  FloorButton(char key, int floor, const char* direction)
    : _key(key), _floor(floor), _direction(direction) {}

  void Begin(bool log) 
  {
    _log =log;
    if(_log == 1)
    {
        Serial.print("Floor button ");
        Serial.print(_floor);
        Serial.print(" ");
        Serial.print(_direction);
        Serial.println(" initialized");
    }
  };

  bool GetStatus(char pressedKey) 
  {
    if (pressedKey == _key) 
    {
      if(_log)
      {
        Serial.print("Floor ");
        Serial.print(_floor);
        Serial.print(" ");
        Serial.print(_direction);
        Serial.println(" pressed");
      }
      isPressed = true;
      SetButtonLight(true); // to be added by queue, not here    
      return isPressed;
    }
    SetButtonLight(false); // to be removed from queue, not here
    return false;
  }

  void SetButtonLight(bool onOff) override
  {
    if(_lastStateLed != onOff)
    {
      Serial.print("Floor ");
      Serial.print(_floor);
      Serial.print(" button ");
      Serial.print(_direction);
      Serial.print(" light");
      if(onOff)
      {
        Serial.println(" on");    
      }
      else 
      {
        Serial.println(" off");
      }
    }
    isIlluminated = onOff;
    _lastStateLed = onOff;
  }
};