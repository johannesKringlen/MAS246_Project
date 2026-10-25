/*Queue
This class manages the list of requested elevator floors.
*/
const int QUEUE_SIZE = 4;

class Queue
{
  private:
  int _queueCount = 0;

  public:
  bool isEmpty;
  int elevatorQueue[QUEUE_SIZE];

  void Begin()
  {
    isEmpty = true;
  };

  // Adds a new floor request to the queue in sorted order if it isn’t already present.
  bool AddToQueue(int floorNr)
  {
    String tmpString="";
    tmpString = "Floor ";
    tmpString += String(floorNr);

    // Check range valid
    if(floorNr < 1 || floorNr > 4)
    {
      tmpString += " outside allowed range";
      Serial.println(tmpString);
      return false;
    }
    if(_queueCount >= QUEUE_SIZE)
    {
      Serial.println("The queue is full");
      return false;
    }
    // Don't add already existing floor in queue
    for (int i = 0; i< _queueCount; i++) 
    {
      if(elevatorQueue[i] == floorNr)
      {
        tmpString += " already in queue";
        Serial.println(tmpString);        
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
    tmpString += " added to queue";
    Serial.println(tmpString);
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

        Serial.print("Floor ");
        Serial.print(floorNr);
        Serial.println(" removed from queue");
        PrintQueue();
        if(_queueCount == 0)
        {
          isEmpty = true;
        }
        return true;
      }
    }
    Serial.print("Floor ");
    Serial.print(floorNr);
    Serial.println(" was not found in queue");
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
    Serial.print("The existing queue is: ");
    if (_queueCount == 0) 
    {
      Serial.println("empty");
      return;
    }

    for (int i = 0; i < _queueCount; i++) 
    {
      Serial.print(elevatorQueue[i]);
      if (i < _queueCount - 1) 
      {
        Serial.print(", ");
      }
    }
    Serial.println();
  }
};