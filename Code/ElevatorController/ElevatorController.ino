#include "ElevatorButton.h"
#include "FloorButton.h"
#include "LiftMotor.h"
#include "DoorMotor.h"
#include "Brake.h"
#include "Elevator.h" 

DoorMotor doorMotor;

Elevator elevator;

ElevatorButton eBtn1;
ElevatorButton eBtn2;
ElevatorButton eBtn3;
ElevatorButton eBtn4;

FloorButton fBtn1Up('1', 1, "up");
FloorButton fBtn2Up('2', 2, "up");
FloorButton fBtn2Down('w', 2, "down");
FloorButton fBtn3Up('3', 3, "up");
FloorButton fBtn3Down('e', 3, "down");
FloorButton fBtn4Down('4', 4, "down");


void setup()
{
  bool log = true;
  Serial.begin(9600);
  delay(1500);
  Serial.println();

  doorMotor.Begin(log);
  elevator.Begin(log);

  eBtn1.Begin(23,48,log);
  eBtn2.Begin(24,47,log);
  eBtn3.Begin(25,46,log); 
  eBtn4.Begin(26,45,log);

  fBtn1Up.Begin(log);
  fBtn2Up.Begin(log);
  fBtn2Down.Begin(log);
  fBtn3Up.Begin(log);
  fBtn3Down.Begin(log);
  fBtn4Down.Begin(log);
}

void loop()
{
  GetStatusFloorBtn();
  GetStatusElevatorBtn();
  //testLCD();
  //testDoor(true);
}

void GetStatusFloorBtn()
{
  if (Serial.available() > 0) 
  {
    char key = Serial.read();
    fBtn1Up.GetStatus(key);
    fBtn2Up.GetStatus(key);
    fBtn2Down.GetStatus(key);
    fBtn3Up.GetStatus(key);
    fBtn3Down.GetStatus(key);
    fBtn4Down.GetStatus(key);
  }
}

void GetStatusElevatorBtn()
{
  eBtn1.GetStatus();
  eBtn2.GetStatus();
  eBtn3.GetStatus();
  eBtn4.GetStatus();
}

