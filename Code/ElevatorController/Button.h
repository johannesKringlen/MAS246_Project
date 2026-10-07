#include "HardwareSerial.h"
/*Button
This class represents a button and manages its pressed and illuminated states.

History:

revision  date        description
0.0.1     01.10.2026  file created

*/

#include "FloorButton.h"
#include "ElevatorButton.h"

FloorButton fBtn1Up;
FloorButton fBtn2Up;
FloorButton fBtn2Down;
FloorButton fBtn3Up;
FloorButton fBtn3Down;
FloorButton fBtn4Down;

ElevatorButton eBtn1;
ElevatorButton eBtn2;
ElevatorButton eBtn3;
ElevatorButton eBtn4;

class Button
{
  public:
  void Begin()
  {
    fBtn1Up.Begin();
    Serial.println();
    eBtn1.Begin(23,0);
    eBtn2.Begin(24,0);
    eBtn3.Begin(25,0);
    eBtn4.Begin(26,0);
    
  };
};