#include "HardwareSerial.h"
/*Load
This class handle the load sensor.
*/

int _potValue = 0;
static const int _pinPot = A0; // Analog input 0
bool _log;
int _lastWeight = 0;

class Load
{
  public:
  int weight;
  bool overload;

  void Begin(bool log)
  {
    _log = log;
    overload = false;
    if(_log == 1)
    {
      Serial.println("Load sensor initialized");
    }
  };

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
        Serial.println("Elevator too heavy");
        overload = true;
      }
      else 
      {
        Serial.println("Weight ok, it is below allowed limit");
        overload = false;
      }     
    }

    if (overload && _lastWeight!=weight) 
    {
      String tmpString = "Passengers total weight ";
      tmpString += String(weight);
      tmpString += " kg";
      Serial.println(tmpString);
    }
    _lastWeight = weight;
    delay(200);
    return weight;
  }
};