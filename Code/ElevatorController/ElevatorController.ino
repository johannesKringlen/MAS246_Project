#include "ElevatorButton.h"
#include "FloorButtons.h"
#include "LiftMotor.h"
#include "DoorMotor.h"
#include "Brake.h"
#include "Elevator.h" 

Elevator elevator;

ElevatorButton eBtn1;
ElevatorButton eBtn2;
ElevatorButton eBtn3;
ElevatorButton eBtn4;


FloorButtons floorButtons;
/*
FloorButton fBtn2Up;
FloorButton fBtn2Down;
FloorButton fBtn3Up;
FloorButton fBtn3Down;
FloorButton fBtn4Down;
*/

void setup()
{
//general

Serial.begin(9600);
delay(1500);

elevator.Begin();

eBtn1.Begin(23,48,1);
eBtn2.Begin(24,47,1);
eBtn3.Begin(25,46,1);
eBtn4.Begin(26,45,1);

floorButtons.Begin(0);

}

void loop()
{
  floorButtons.GetStatus();


}
