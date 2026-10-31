/*Queue
This class manages the list of requested elevator floors.
*/
#include "Logger.h"
const int QUEUE_SIZE = 4;

class Queue
{
  private:
  int _queueCount = 0;
  String _tempString;

  public:
  bool isEmpty;
  int elevatorQueue[QUEUE_SIZE];

  // Initializes the queue
  void Begin()
  {
    isEmpty = true;
    logMessage("Queue initialized"); 
  };

  // Adds a new floor request to the queue in sorted order if it isn’t already present.
  bool AddToQueue(int floorNr)
  {
    _tempString = "Floor ";
    _tempString += String(floorNr);
    
    // Check range valid
    if(floorNr < 1 || floorNr > 4)
    {
      _tempString += " outside allowed range";
      logMessage(_tempString); 
      //Serial.println(_tempString);
      return false;
    }
    if(_queueCount >= QUEUE_SIZE)
    {
      logMessage("The queue is full"); 
      //Serial.println("The queue is full");
      return false;
    }
    // Don't add already existing floor in queue
    for (int i = 0; i< _queueCount; i++) 
    {
      if(elevatorQueue[i] == floorNr)
      {
        _tempString += " already in queue";
        logMessage(_tempString); 
        //Serial.println(_tempString);        
        return false;
      }
    }
    int position = 0;

    // find the place in queue where to add
    while (position < _queueCount && elevatorQueue[position] < floorNr) 
    {
      position++;
    }

    // Move higher floor to right one position
    for (int i = _queueCount; i > position; i--) 
    {
      elevatorQueue[i] = elevatorQueue[i - 1];
    }
    elevatorQueue[position] = floorNr;
    _queueCount++;
    _tempString += " added to queue";
    logMessage(_tempString); 
    //Serial.println(_tempString);
    PrintQueue();
    isEmpty = false;
    return true;
  }

  // Removes the request floor from queue if it is present.
  bool RemoveFromQueue(int floorNr)
  {
    for (int i = 0; i < _queueCount; i++)
    {
      if (elevatorQueue[i] == floorNr)
      {
        // Shift all following floors one position to the left
        for (int j = i; j < _queueCount - 1; j++)
        {
          elevatorQueue[j] = elevatorQueue[j + 1];
        }

        _queueCount--;
        _tempString = "Floor ";
        _tempString += String(floorNr);
        _tempString += " removed from queue";
        logMessage(_tempString); 
        //Serial.print("Floor ");
        //Serial.print(floorNr);        
        //Serial.println(" removed from queue");
        
        PrintQueue();
        if(_queueCount == 0)
        {
          isEmpty = true;
        }
        return true;
      }
    }
    _tempString = "Floor ";
    _tempString += String(floorNr);
    _tempString += " was not found in queue";
    logMessage(_tempString);

    //Serial.print("Floor ");
    //Serial.print(floorNr);
    //Serial.println(" was not found in queue");
    return false;
  }

  //Return the next floor using the queue, current floor, and last direction.
  int GetNextFloor(int lastDir, int actFloor)
  {
    int nextFloor = 0;
    if (!isEmpty)
    {
      if (lastDir == 1)  // Going up
      {
        // Find the nearest floor above.
        for (int i = 0; i < _queueCount; i++)
        {
          int floor = elevatorQueue[i];
          if (floor > actFloor)
          {
            nextFloor = floor;
            return nextFloor;
          }
        }

        // If no floor is above, turn around and choose the highest floor below.
        if (nextFloor == 0)
        {
          for (int i = _queueCount - 1; i >= 0; i--)
          {
            int floor = elevatorQueue[i];
            if (floor < actFloor)
            {
              nextFloor = floor;
              return nextFloor;
            }
          }
        }
      }
      else  // Going down
      {
        // Find the nearest floor below by scanning from highest to lowest.
        for (int i = _queueCount - 1; i >= 0; i--)
        {
          int floor = elevatorQueue[i];
          if (floor < actFloor)
          {
            nextFloor = floor;
            return nextFloor;
          }
        }

        // If no floor is below, turn around and choose the lowest floor above.
        if (nextFloor == 0)
        {
          for (int i = 0; i < _queueCount; i++)
          {
            int floor = elevatorQueue[i];
            if (floor > actFloor)
            {
              nextFloor = floor;
              return nextFloor;
            }
          }
        }
      }
    }
    return nextFloor;
  }

  // Prints the current queue to the serial monitor.
  void PrintQueue() 
  {
    _tempString = "The existing queue is: "; 
    //Serial.print("The existing queue is: ");
    if (_queueCount == 0) 
    {
      _tempString += "empty";
      logMessage(_tempString);
      //Serial.println("empty");
      return;
    }

    for (int i = 0; i < _queueCount; i++) 
    {
      _tempString += elevatorQueue[i];
      //Serial.print(elevatorQueue[i]);
      if (i < _queueCount - 1) 
      {
        _tempString += ", ";
        //Serial.print(", ");
      }
    }
    logMessage(_tempString);
    //Serial.println();
  }
};