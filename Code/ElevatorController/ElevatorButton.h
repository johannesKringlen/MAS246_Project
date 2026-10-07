/*ElevatorButton
This class represents a button used to select a destination floor inside the elevator.

History:

revision  date        description
0.0.1     01.10.2026  file created

*/

class ElevatorButton
{
  private:
  bool _debugMode;
  
  
  int _pinNumber;

  public:
  
  void Begin(int pinNumber, bool debugMode)
  {
    _pinNumber=pinNumber;
    _debugMode = debugMode;
    pinMode(_pinNumber, INPUT);
    if(_debugMode == 1)
    {
        Serial.print("Elevator button ");
        Serial.print(_pinNumber-22);
        Serial.println(" initialized");
    }
  };

  bool GetStatus()
  {
    if(_debugMode == 1)
    {
      Serial.print("Getting status for button ");
      Serial.println(_pinNumber);
    }
    return digitalRead(_pinNumber);
  };
};