/*FloorButton
This class represents a button used to request the elevator from a specific floor.
*/

#include "Button.h"
#include "Logger.h"

class FloorButton : public Button
{
private:
  char _key;
  const int _floor;
  const char* _direction;
  bool _lastStateLed;
  bool _isPressed;
  String _tempString;

public:
  int buttonLocation;
  int direction; // 1= up, 2 = down

  FloorButton(char key, int floor, const char* direction)
    : _key(key), 
    _floor(floor), 
    _direction(direction) 
    {}

  // Initializes the elevator button
  void Begin() 
  {    
    _tempString = "Floor button ";
    _tempString += String(_floor);
    _tempString += " ";
    _tempString += _direction;
    _tempString += " initialized";
    logMessage(_tempString);
    
    //Serial.print("Floor button ");
    //Serial.print(_floor);
    //Serial.print(" ");
    //Serial.print(_direction);
    //Serial.println(" initialized");
    
    buttonLocation = _floor;
    if (strcmp(_direction, "up") == 0) 
    {
      direction = 1;
    }
    else if (strcmp(_direction, "down") == 0) 
    {
      direction = 2;
    }
  };

  // Returns the current status of the floor button.
  bool GetStatus(char pressedKey) 
  {
    if (pressedKey == _key) 
    {
      _tempString = "Floor button ";
      _tempString += String(_floor);
      _tempString += " ";
      _tempString += _direction;
      _tempString += " pressed";
      logMessage(_tempString);

      //Serial.print("Floor ");
      //Serial.print(_floor);
      //Serial.print(" ");
      //Serial.print(_direction);
      //Serial.println(" pressed");
      isPressed = true;
      return isPressed;
    }
    isPressed = false;
    return false;
  }

  // Turns the button light on or off.
  void SetButtonLight(bool onOff) override
  {
    if(_lastStateLed != onOff)
    {
      _tempString = "Floor ";
      _tempString += String(_floor);
      _tempString += " button ";
      _tempString += _direction;
      _tempString += " light";
      
      
      //Serial.print("Floor ");
      //Serial.print(_floor);
      //Serial.print(" button ");
      //Serial.print(_direction);
      //Serial.print(" light");
      if(onOff)
      {
        //Serial.println(" on");    
        _tempString +=" on";
      }
      else 
      {
        //Serial.println(" off");
        _tempString +=" off";
      }
      logMessage(_tempString);
    }
    isIlluminated = onOff;
    _lastStateLed = onOff;
  }
};