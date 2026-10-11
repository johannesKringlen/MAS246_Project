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
  int currentFloor; // 1 to 4
  int actualDirection; // 1 = up,  2 = down
  int lastDirection; // 1 = up,  2 = down
  bool isMoving;

  void Begin(bool log)
  {
    /*Starting at floor 1 
      with door closed
      not moving */ 
    _log =log;
    currentFloor = 1; 
    actualDirection = 1; 
    lastDirection = 2;
    isMoving = false;

    encoder.Begin(_log);
    lcd.Begin(_log);
  };
};