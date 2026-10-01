/*ElevatorButton
This file will take care of elevator floor request

History:

revision  date        description
0.0.1     01.10.2026  file created

*/

class ElevatorButton
{
  private:

  int _pinNumber;

  public:

  void begin(int pinNumber)
  {
    _pinNumber=pinNumber;
    pinMode(_pinNumber, INPUT);
    Serial.print("Elevator button ");
    Serial.print(_pinNumber);
    Serial.println(" initialized");

  };

  bool GetStatus()
  {
    Serial.print("Getting status for button ");
    Serial.println(_pinNumber);
    return digitalRead(_pinNumber);
  };
};