/* ElevatorController
This is the main file
*/

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

int nextFloor;
int elevatorStatus; // 1 = Stop, 2 = Going up, 3 = Going down
int doorStatus; // 1 = Closed, 2 = Opening, 3 Open, 4 = Closing
bool firstTime;
bool firstTimeDoor;
bool startupDoorMessage;

void setup()
{
  bool log = true;
  nextFloor = 1;
  elevatorStatus = 1;
  doorStatus = 1;
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
  firstTime = true;
  firstTimeDoor = false;
  startupDoorMessage = true;
}

void loop()
{
  LCDOnOff(); // to be removed when done with th program
  switch (elevatorStatus) 
  {
    case 1:
    {
      if (firstTime) 
      {
        elevator.currentFloor = nextFloor;
        String tempString = "Elevator stopped at ";
        tempString += String(elevator.currentFloor);
        tempString += " floor";
        Serial.println(tempString);
        String tempRow = "Stopped";
        tempRow += "       F";  
        tempRow += String(elevator.currentFloor);
        lcd.WriteToRow(0, tempRow);
        elevator.isMoving = false;
      };      
      DoorSequence(firstTime);
      firstTime = false;        
      GetStatusFloorBtn();
      GetStatusElevatorBtn();
      if (nextFloor > elevator.currentFloor) 
      {
        elevatorStatus = 2;
        firstTime = true;
      }
      if (nextFloor < elevator.currentFloor) 
      {
        elevatorStatus = 3;
        firstTime = true;
      }
      break;
    }
    case 2:
    { 
      if (firstTime) 
      {
        Serial.println("Elevator going up");
        String row = "Moving ";
        row += "       Up";  
        lcd.WriteToRow(0, row);
        firstTime = false;
        elevator.isMoving = true;
        elevator.actualDirection = 1;
      }
      // below to be replaced with real motor control
      delay(3000);
      elevator.currentFloor = 2;
      elevatorStatus = 1;      
      firstTime = true;
      firstTimeDoor = true;
      break;
    }
    case 3:
    { 
      if (firstTime) 
      {
        Serial.println("Elevator going down");
        String row = "Moving ";
        row += "     Down";  
        lcd.WriteToRow(0, row);
        firstTime = false;
        elevator.isMoving = true;
        elevator.actualDirection = 2;
      }
      // below to be replaced with real motor control
      delay(3000);
      elevator.currentFloor = 1;
      elevatorStatus = 1;
      firstTime = true;
      firstTimeDoor = true;
      break; 
    }
    default:
    break;
  }
}

void DoorSequence(bool firstTime)
{
  // 1 = Closed, 2 = Opening, 3 Open, 4 = Closing
  switch (doorStatus) 
  {
    case 1:
    {
      // First message at start up
      if (startupDoorMessage)
      {
        lcd.WriteToRow(1, "Door closed     ");
        Serial.println("Door closed");
        startupDoorMessage = false;
      }

      // The elevator has just arrived at the floor
      if (firstTimeDoor) 
      {
        lcd.WriteToRow(1, "Door closed     ");
        Serial.println("Door closed");
        doorStatus = 2;
        firstTimeDoor = false;
      }      
      break;
    }
    case 2:
    {
      lcd.WriteToRow(1, "Opening door    ");
      Serial.println("Opening door");    
      delay(2000); // to be replace with transiction
      doorStatus = 3;
      break;
    }  
    case 3:
    {
      lcd.WriteToRow(1, "Door open       ");
      Serial.println("Door open");
      delay(2000);
      doorStatus = 4;
      break;
    }  
    case 4:
    {
      lcd.WriteToRow(1, "Closing door    ");
      Serial.println("Closing door");
      delay(2000); // to be replace with transiction
      doorStatus = 1;   
      lcd.WriteToRow(1, "Door closed     ");
      Serial.println("Door closed");
      break;
    }  
    default:
    break;
  }
}

void GetStatusFloorBtn()
{
  if (Serial.available() > 0) 
  {
    char key = Serial.read();
    if (fBtn1Up.GetStatus(key)) 
    {
      nextFloor = 2;  // just to tets up and down.
    }
    if (fBtn2Up.GetStatus(key)) 
    {
      nextFloor = 3;  // just to tets up and down.
    }
    if (fBtn3Up.GetStatus(key)) 
    {
      nextFloor = 4;  // just to tets up and down.
    }
    if (fBtn2Down.GetStatus(key)) 
    {
      nextFloor = 1;  // just to tets up and down.
    }
    if (fBtn3Down.GetStatus(key)) 
    {
      nextFloor = 2;  // just to tets up and down.
    }
    if (fBtn4Down.GetStatus(key)) 
    {
      nextFloor = 3;  // just to tets up and down.
    }
  }
}

void GetStatusElevatorBtn()
{
  if (eBtn1.GetStatus()) 
  {
    nextFloor = 1;  // just to tets up and down.
  }
  if (eBtn2.GetStatus()) 
  {
    nextFloor = 2;  // just to tets up and down.
  }
  if (eBtn3.GetStatus()) 
  {
    nextFloor = 3;  // just to tets up and down.
  }
  if (eBtn4.GetStatus()) 
  {
    nextFloor = 4;  // just to tets up and down.
  }  
}

