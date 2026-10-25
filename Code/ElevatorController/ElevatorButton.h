/*ElevatorButton
This class represents a button used to select a destination floor inside the elevator.
*/
#include "HardwareSerial.h"
#include "Arduino.h"
#include "Button.h"

class ElevatorButton : public Button
{
  private: 
  int _inputPin;
  int _outputPin;
  bool _lastStateBtn;
  bool _lastStateLed;
  bool _isPressed;


  public:
  int floorNum;

  // Initializes the elevator button
  void Begin(int inputPin, int outputPin)
  {
    _inputPin=inputPin;
    floorNum = _inputPin-22;
    _outputPin=outputPin;
    pinMode(_inputPin, INPUT);
    pinMode(_outputPin, OUTPUT);
    Serial.print("Elevator button ");
    Serial.print(floorNum);
    Serial.println(" initialized");
  };

  // Returns the current status of the elevator button.
  bool GetStatus()
  {
    _isPressed = digitalRead(_inputPin);
    if(_lastStateBtn != _isPressed)
    {

        if(_isPressed == 1)
        {
          Serial.print("Elevator button ");
          Serial.print(_inputPin-22);
          Serial.println(" has been pressed");
          isPressed = true;
          _lastStateBtn = _isPressed;
          return true;         
        }
        
        else
        {
          isPressed = false;
          _lastStateBtn = _isPressed;
          return false;
        }
    }
    else
    {
      return false;
    }
  }

  // Turns the button light on or off.
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