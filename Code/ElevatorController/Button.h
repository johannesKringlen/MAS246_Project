#include "HardwareSerial.h"
/*Button
This file will take care of elevator floor request

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
  void begin()
  {
    fBtn1Up.begin();
    Serial.println();
    eBtn1.begin(23);
    eBtn2.begin(24);
    eBtn3.begin(25);
    eBtn4.begin(26);
    
  };
};