/*Elevator
This class represents the elevator’s current state, including its floor, direction, and movement status.

History:

revision  date        description
0.0.1     01.10.2026  file created

*/

#include "Encoder.h"
#include "LCD.h"

Encoder encoder;
LCD lcd;

class Elevator
{
  private:
  bool _log;

  public:
  void Begin(bool log)
  {
    _log =log;
    encoder.Begin(_log);
    lcd.Begin(_log);
  };
};