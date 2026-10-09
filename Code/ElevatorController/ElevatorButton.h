#include "HardwareSerial.h"
#include "Arduino.h"
/*ElevatorButton
This class represents a button used to select a destination floor inside the elevator.

History:

revision  date        description
0.0.2     09.10.2026  included class button
                      implemented inherited functions
0.0.1     01.10.2026  file created

*/
#include "Button.h"

class ElevatorButton : public Button
{
  private:
  bool _log;
  
  
  int _inputPin;
  int _outputPin;
  bool _lastState;

  public:

  void Begin(int inputPin, int outputPin,  bool log) override
  {
    _inputPin=inputPin;
     _outputPin=outputPin;
    _log = log;
    pinMode(_inputPin, INPUT);
    pinMode(_outputPin, OUTPUT);
    if(_log == 1)
    {
        Serial.print("Elevator button ");
        Serial.print(_inputPin-22);
        Serial.println(" initialized");
    }
  };

  bool GetStatus() override
  {
    bool actualState = digitalRead(_inputPin);
    if(_lastState != actualState)
    {
        Serial.print("Elevator button ");
        Serial.print(_inputPin-22);
        Serial.print(" = ");
        Serial.println(actualState);
    };

    _lastState = actualState;
    return actualState;
  };

  void SetButtonLight(bool onOff) override
  {
    digitalWrite(_outputPin, onOff);
    isIlluminated = onOff;
  }
};