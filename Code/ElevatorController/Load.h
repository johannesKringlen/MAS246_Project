#include "HardwareSerial.h"
/*Load
This class handle the load sensor.
*/
#include "Logger.h"

class Load
{
  private:
  int _potValue = 0;
  static const int _pinPot = A0; // Analog input 0
  int _lastWeight = 0;
  String _tempString;

  public:
  int weight;
  bool overload;

  // Initialiazes the load sensor
  void Begin()
  {
    overload = false;
    logMessage("Load sensor initialized"); 
  };

  // Returns the elevator weight
  int GetStatus()
  {
    _potValue = analogRead(_pinPot);
    weight = _potValue;  
    bool newOverload = (weight > 500);

    if (newOverload != overload) 
    {
      overload = newOverload;
      if(overload)
      {
        logMessage("Elevator too heavy"); 
        overload = true;
      }
      else 
      {
        logMessage("Weight ok, it is below allowed limit"); 
        overload = false;
      }     
    }

    if (overload && _lastWeight!=weight) 
    {
      _tempString = "Passengers total weight ";
      _tempString += String(weight);
      _tempString += " kg";
      logMessage(_tempString); 
    }
    _lastWeight = weight;
    delay(200);
    return weight;
  }
};