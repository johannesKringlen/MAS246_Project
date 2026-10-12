#include "HardwareSerial.h"
#include "Arduino.h"
/*ElevatorButton
This class represents a button used to select a destination floor inside the elevator.

History:

revision  date        description
0.0.3     10.10.2026  Updated Get Status and SetButtonLight
0.0.2     09.10.2026  Included class button
                      implemented inherited functions
0.0.1     01.10.2026  File created

*/
#include "Button.h"

class ElevatorButton : public Button
{
  private:
  bool _log;
  
  int _inputPin;
  int _outputPin;
  bool _lastStateBtn;
  bool _lastStateLed;
  bool _isPressed;


  public:
  int floorNum;

  void Begin(int inputPin, int outputPin,  bool log)
  {
    _inputPin=inputPin;
    floorNum = _inputPin-22;
    _outputPin=outputPin;
    _log = log;
    pinMode(_inputPin, INPUT);
    pinMode(_outputPin, OUTPUT);
    if(_log == 1)
    {
        Serial.print("Elevator button ");
        Serial.print(floorNum);
        Serial.println(" initialized");
    }
  };

  bool GetStatus()
  {
    _isPressed = digitalRead(_inputPin);
    if(_lastStateBtn != _isPressed)
    {
        Serial.print("Elevator button ");
        Serial.print(_inputPin-22);
        if(_isPressed == 1)
        {
          Serial.println(" has been pressed");
          SetButtonLight(true); // to be added by queue, not here
        }
        else
        {
          //Serial.println(" is released");          
          SetButtonLight(false); // to be removed from queue, not here
        }
        isPressed = _isPressed;
    };

    _lastStateBtn = _isPressed;
    return _isPressed;
  };

  void SetButtonLight(bool onOff) override
  {
    if(_lastStateLed != onOff)
    {
      digitalWrite(_outputPin, onOff);
      Serial.print("Elevator button ");
      Serial.print(_inputPin-22);
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

  void UpdateStatus()
  {
    _isPressed = digitalRead(_inputPin);
    isPressed = _isPressed;
  }
};