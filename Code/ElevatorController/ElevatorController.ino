/* ElevatorController
This is the main file

*/

#include "Brake.h"
#include "Door.h"
#include "Elevator.h" 
#include "ElevatorButton.h"
#include "Encoder.h"
#include "FloorButton.h"
#include "LiftMotor.h"
#include "Load.h"
#include "Logger.h"
#include "Queue.h"


Door door;
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
String _tempString;
int _stepMoved;
const int STEPS = 24;


void setup()
{
  bool log = true;
  nextFloor = 1;
  elevatorStatus = 1;
  doorStatus = 1;
  firstTimeEl = true;
  firstTimeDoor = false;
  startupDoorMessage = true;
  _stepMoved = STEPS;
  Serial.begin(9600);
  delay(1500);
  Serial.println();

  door.Begin();
  elevator.Begin();
  eBtn1.Begin(23,48);
  eBtn2.Begin(24,47);
  eBtn3.Begin(25,46); 
  eBtn4.Begin(26,45);
  encoder.Begin();
  fBtn1Up.Begin();
  fBtn2Up.Begin();
  fBtn2Down.Begin();
  fBtn3Up.Begin();
  fBtn3Down.Begin();
  fBtn4Down.Begin();
  liftMotor.Begin();
  load.Begin();
  queue.Begin();
}

void loop()
{
  LCDOnOff(); // to be removed when done with the program
  MainSequence();
}

// Checks whether any elevator or floor buttons have been pressed,
// and adds the requested floors to the queue.
void CheckButtons()
{
  GetStatusFloorBtn();
  GetStatusElevatorBtn();
}

// Chooses the next floor using the queue, current floor, and last direction.
void DecideNextFloor()
{
  nextFloor = queue.GetNextFloor(elevator.lastDirection, elevator.currentFloor);
  if (nextFloor == 0)
  {
    nextFloor = elevator.currentFloor;
  }
}



// Runs the main sequence.
void MainSequence()
{
  switch (elevatorStatus)
  {
    case 1: // Stop
    {
      elevator.lastDirection = elevator.actualDirection;
      if (firstTimeEl) 
      {
        elevator.currentFloor = nextFloor;
        _tempString = "Elevator stopped at floor ";
        _tempString += String(elevator.currentFloor);
        logMessage(_tempString); 
        String tempRow = "Stop at floor ";
        tempRow += String(elevator.currentFloor);
        lcd.WriteToRow(0, tempRow);
        elevator.isMoving = false;
      };      
      DoorSequence(firstTimeEl);
      firstTimeEl = false;   
      CheckButtons();
      DecideNextFloor();     
      if (doorStatus == 1 && !queue.isEmpty && nextFloor != elevator.currentFloor)
      {
        if (nextFloor > elevator.currentFloor)
        {
          elevatorStatus = 2;
          firstTimeEl = true;
        }
        else
        {
          elevatorStatus = 3;
          firstTimeEl = true;
        }
      }
      break;
    }
    case 2: // Going up
    { 
      if (firstTimeEl) 
      {
        logMessage("Elevator going up"); 
        String row = "Moving up       ";  
        lcd.WriteToRow(0, row);
        firstTimeEl = false;
        elevator.isMoving = true;
        elevator.actualDirection = 1;
      }
      
      liftMotor.Move(encoder, nextFloor, elevator.currentFloor);

      elevator.currentFloor = 2;
      elevatorStatus = 1;      
      firstTimeEl = true;
      firstTimeDoor = true;
      break;
    }
    case 3: // Going down
    { 
      if (firstTimeEl) 
      {
        logMessage("Elevator going down"); 
        String row = "Moving down     ";
        lcd.WriteToRow(0, row);
        firstTimeEl = false;
        elevator.isMoving = true;
        elevator.actualDirection = 2;
      }
    
      liftMotor.Move(encoder,  nextFloor, elevator.currentFloor);
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


// Runs the door sequence: opening, waiting, and closing.
void DoorSequence(bool firstTimeEl)
{
  switch (doorStatus) 
  {
    case 1: // Closed
    {
      // First message at start up
      if (startupDoorMessage)
      {
        lcd.WriteToRow(1, "Door closed     ");
        logMessage("Door closed");
        startupDoorMessage = false;
      }

      // The elevator has just arrived at the floor
      if (firstTimeDoor) 
      {
        lcd.WriteToRow(1, "Door closed     ");
        logMessage("Door closed"); 
        doorStatus = 2;
        firstTimeDoor = false;
      }      
      break;
    }
    case 2: // Opening
    {
      if (_stepMoved==STEPS) 
      {
        if (queue.RemoveFromQueue(elevator.currentFloor))
        {
          ClearFloorLights(elevator.currentFloor);
        }
      }
      lcd.WriteToRow(1, "Opening door    ");
      logMessage("Opening door"); 
      while (_stepMoved>0) 
      {         
        door.Open();
        _stepMoved--;
      }      

      doorStatus = 3;
      break;
    }  
    case 3: // Open
    {
      lcd.WriteToRow(1, "Door open       ");
      logMessage("Door open"); 
      CheckLoad();
      doorStatus = 4;
      break;
    }  
    case 4: // Closing
    {
      bool closeComplete = true;
      lcd.WriteToRow(1, "Closing door    ");
      logMessage("Closing door");
      _stepMoved = 0;
      while (_stepMoved<STEPS) 
      {
        if (!GetStatusFloorBtn() && !door.GetCollisionSensorStatus()) 
        {
          door.Close();
          _stepMoved++;
        }
        else
        {
          closeComplete = false;
          break;
        }
      }
      if (closeComplete) 
      {
        doorStatus = 1;   
        lcd.WriteToRow(1, "Door closed     ");
        logMessage("Door closed");
      }      
      else  
      {
        logMessage("Close sequence stopped");
        doorStatus = 2;   
      }
      delay(2000);
      break;
    }  
    default:
    break;
  }
}

// Checks floor buttons, queues requested floors, and turns on their button lights.
bool GetStatusFloorBtn()
{
  bool sameFloorSelected = false;
  int tempFloor;
  int actualFloor = elevator.currentFloor;
  if (Serial.available() > 0) 
  {
    char key = Serial.read();
    if (fBtn1Up.GetStatus(key)) 
    {
      tempFloor = 1;   

      if (actualFloor != tempFloor) 
      {
        queue.AddToQueue(tempFloor);
        fBtn1Up.SetButtonLight(true);     
      }
      else 
      {
        sameFloorSelected = true;
      }
    }

    if (fBtn2Up.GetStatus(key)) 
    {
      tempFloor = 2;   
      if (actualFloor != tempFloor) 
      {
        queue.AddToQueue(tempFloor);
        fBtn2Up.SetButtonLight(true);     
      }
      else 
      {
        sameFloorSelected = true;
      }
    }

    if (fBtn3Up.GetStatus(key)) 
    {
      tempFloor = 3;   
      if (actualFloor != tempFloor) 
      {
        queue.AddToQueue(tempFloor);
        fBtn3Up.SetButtonLight(true);     
      }
      else 
      {
        sameFloorSelected = true;
      }      
    }

    if (fBtn2Down.GetStatus(key)) 
    {
      tempFloor = 2;   
      if (actualFloor != tempFloor) 
      {
        queue.AddToQueue(tempFloor);
        fBtn2Down.SetButtonLight(true);     
      }
      else 
      {
        sameFloorSelected = true;
      }      
    }

    if (fBtn3Down.GetStatus(key)) 
    {
      tempFloor = 3;   
      if (actualFloor != tempFloor) 
      {
        queue.AddToQueue(tempFloor);
        fBtn3Down.SetButtonLight(true);     
      }
      else 
      {
        sameFloorSelected = true;
      }      
    }
    
    if (fBtn4Down.GetStatus(key)) 
    {
      tempFloor = 4;   
      if (actualFloor != tempFloor) 
      {
        queue.AddToQueue(tempFloor);
        fBtn4Down.SetButtonLight(true);     
      }
      else 
      {
        sameFloorSelected = true;
      }      
    }
  }
  return sameFloorSelected;
}

// Checks elevator buttons, queues requested floors, and turns on their button lights.
void GetStatusElevatorBtn()
{
  int tempFloor;
  int actualFloor = elevator.currentFloor;
  if (eBtn1.GetStatus()) 
  {
    tempFloor = 1;   
    if (actualFloor != tempFloor) 
    {
      queue.AddToQueue(tempFloor);
      eBtn1.SetButtonLight(true);     
    }
  }
  if (eBtn2.GetStatus()) 
  {
    tempFloor = 2;   

    if (actualFloor != tempFloor) 
    {
      queue.AddToQueue(tempFloor);
      eBtn2.SetButtonLight(true);     
    }
  }
  if (eBtn3.GetStatus()) 
  {
    tempFloor = 3;   
    if (actualFloor != tempFloor) 
    {
      queue.AddToQueue(tempFloor);
      eBtn3.SetButtonLight(true);     
    }
  }
  
  if (eBtn4.GetStatus()) 
  {
    tempFloor = 4;   
    
    if (actualFloor != tempFloor) 
    {
      queue.AddToQueue(tempFloor);
      eBtn4.SetButtonLight(true);     
    }
  }
 
}

// Checks whether the elevator load exceeds the allowed limit.
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
    CheckButtons();
  }
  delay(2000);
}

// Turns off all button lights associated with the arrived floor.
void ClearFloorLights(int floorNr)
{
  switch (floorNr)
  {
    case 1:
    {
      eBtn1.SetButtonLight(false);
      fBtn1Up.SetButtonLight(false);
      break;
    }
    case 2:
    {
      eBtn2.SetButtonLight(false);
      fBtn2Up.SetButtonLight(false);
      fBtn2Down.SetButtonLight(false);
      break;
    }
    case 3:
    {
      eBtn3.SetButtonLight(false);
      fBtn3Up.SetButtonLight(false);
      fBtn3Down.SetButtonLight(false);
      break;
    }
    case 4:
    {
      eBtn4.SetButtonLight(false);
      fBtn4Down.SetButtonLight(false);
      break;
    }
    default:
    break;
  };
}
