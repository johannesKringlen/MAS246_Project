/* ElevatorController
This is the main file

History:

revision  date        description
0.0.2     13.10.2026  Implemented sequences
0.0.1     01.10.2026  File created
*/

#include "Brake.h"
#include "DoorMotor.h"
#include "Elevator.h" 
#include "ElevatorButton.h"
#include "Encoder.h"
#include "FloorButton.h"
#include "LiftMotor.h"
#include "Load.h"
#include "Queue.h"


DoorMotor doorMotor;
Elevator elevator;
ElevatorButton eBtn1;
ElevatorButton eBtn2;
ElevatorButton eBtn3;
ElevatorButton eBtn4;
Encoder encoder;
FloorButton fBtn1Up('1', 1, "up");
FloorButton fBtn2Up('2', 2, "up");
FloorButton fBtn2Down('w', 2, "down");
FloorButton fBtn3Up('3', 3, "up");
FloorButton fBtn3Down('e', 3, "down");
FloorButton fBtn4Down('4', 4, "down");
LiftMotor liftMotor;
Load load;
Queue queue;

int nextFloor;
int elevatorStatus; // 1 = Stop, 2 = Going up, 3 = Going down
int doorStatus; // 1 = Closed, 2 = Opening, 3 Open, 4 = Closing
long targetPos;
bool firstTimeEl;
bool firstTimeDoor;
bool startupDoorMessage;

void setup()
{
  bool log = true;
  nextFloor = 1;
  elevatorStatus = 1;
  doorStatus = 1;
  firstTimeEl = true;
  firstTimeDoor = false;
  startupDoorMessage = true;
  Serial.begin(9600);
  delay(1500);
  Serial.println();

  doorMotor.Begin(log);
  elevator.Begin(log);
  eBtn1.Begin(23,48,log);
  eBtn2.Begin(24,47,log);
  eBtn3.Begin(25,46,log); 
  eBtn4.Begin(26,45,log);
  encoder.Begin(log);
  fBtn1Up.Begin(log);
  fBtn2Up.Begin(log);
  fBtn2Down.Begin(log);
  fBtn3Up.Begin(log);
  fBtn3Down.Begin(log);
  fBtn4Down.Begin(log);
  liftMotor.Begin();
  load.Begin(log);
  queue.Begin(log);
}

void loop()
{
  LCDOnOff(); // to be removed when done with the program
  switch (elevatorStatus) //1 = Stop, 2 = Going up, 3 = Going down
  {
    case 1:
    {
      elevator.lastDirection = elevator.actualDirection;
      if (firstTimeEl) 
      {
        elevator.currentFloor = nextFloor;
        String tempString = "Elevator stopped at floor ";
        tempString += String(elevator.currentFloor);
        Serial.println(tempString);
        String tempRow = "Stop at floor ";
        tempRow += String(elevator.currentFloor);
        lcd.WriteToRow(0, tempRow);
        elevator.isMoving = false;
      };      
      DoorSequence(firstTimeEl);
      firstTimeEl = false;   
      DecideNextFloor();     
      if (nextFloor > elevator.currentFloor) 
      {
        elevatorStatus = 2;
        firstTimeEl = true;
      }
      if (nextFloor < elevator.currentFloor) 
      {
        elevatorStatus = 3;
        firstTimeEl = true;
      }
      break;
    }
    case 2:
    { 
      if (firstTimeEl) 
      {
        Serial.println("Elevator going up");
        String row = "Moving up       ";  
        lcd.WriteToRow(0, row);
        firstTimeEl = false;
        elevator.isMoving = true;
        elevator.actualDirection = 1;
      }
      
      liftMotor.Move(50, encoder, targetPos);

      elevator.currentFloor = 2;
      elevatorStatus = 1;      
      firstTimeEl = true;
      firstTimeDoor = true;
      break;
    }
    case 3:
    { 
      if (firstTimeEl) 
      {
        Serial.println("Elevator going down");
        String row = "Moving down     ";
        lcd.WriteToRow(0, row);
        firstTimeEl = false;
        elevator.isMoving = true;
        elevator.actualDirection = 2;
      }
    
      liftMotor.Move(-50, encoder, targetPos);
      elevator.currentFloor = 1;
      elevatorStatus = 1;
      firstTimeEl = true;
      firstTimeDoor = true;
      break; 
    }
    default:
    break;
  }
}

void DecideNextFloor()
{
  if (queue.isEmpty) 
  {
    GetStatusFloorBtn();
    GetStatusElevatorBtn();
    
    switch (nextFloor)
    {
      case 1:
      {
        targetPos = 0;
        break;
      }
      case 2:
      {
        targetPos = 4096;
        break;
      }
      case 3:
      {
        targetPos = 8192;
        break;
      }
      case 4:
      {
        targetPos = 12288;
        break;
      }
      default:
      break;
    }
  }
  else
  {
    // add some code to decide floor based on queue
  }
}

void DoorSequence(bool firstTimeEl)
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
      doorMotor.OpenDoor(12, 10000);
      doorStatus = 3;
      break;
    }  
    case 3:
    {
      lcd.WriteToRow(1, "Door open       ");
      Serial.println("Door open");
      CheckLoad();
      doorStatus = 4;
      break;
    }  
    case 4:
    {
      lcd.WriteToRow(1, "Closing door    ");
      Serial.println("Closing door");
      doorMotor.CloseDoor(12, 10000);
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
      nextFloor = 1;  // just to tets up and down.
    }
    if (fBtn2Up.GetStatus(key)) 
    {
      nextFloor = 2;  // just to tets up and down.
    }
    if (fBtn3Up.GetStatus(key)) 
    {
      nextFloor = 3;  // just to tets up and down.
    }
    if (fBtn2Down.GetStatus(key)) 
    {
      nextFloor = 1;  // just to tets up and down.
    }
    if (fBtn3Down.GetStatus(key)) 
    {
      nextFloor = 3;  // just to tets up and down.
    }
    if (fBtn4Down.GetStatus(key)) 
    {
      nextFloor = 4;  // just to tets up and down.
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

void CheckLoad()
{
  int tmpLoad = 0;
  unsigned long startTime = millis();
  const unsigned long duration = 4000; // 10 seconds
  while (millis() - startTime < duration || load.overload) 
  {
    tmpLoad = load.GetStatus();
    if (load.overload) 
    {
      lcd.WriteToRow(0, "Too Heavy       ");
      String tmpString = "Weight ";
      tmpString += String(tmpLoad);
      tmpString += " kg     ";
      lcd.WriteToRow(1, tmpString);
    }
    else 
    {
      String tempRow = "Stop at floor ";
      tempRow += String(elevator.currentFloor);
      lcd.WriteToRow(0, tempRow);
      lcd.WriteToRow(1, "Door open       "); 
    }
  }
  delay(2000);
}
