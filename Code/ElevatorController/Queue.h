/*Queue
This class manages the list of requested elevator floors.

History:

revision  date        description
0.0.3     19.10.2026  Start implementing queue functions
0.0.2     12.10.2026  Added isEmpty and functions placeholder
0.0.1     01.10.2026  File created

*/
const int QUEUE_SIZE = 4;

class Queue
{
  private:
  bool _log;
  int _queueCount = 0;


  public:
  bool isEmpty;
  int elevatorQueue[QUEUE_SIZE];

  void Begin(bool log)
  {
    _log = log;
    isEmpty = true;
  };

  bool AddToQueue(int floorNr)
  {
    String tmpString="";
    tmpString = "Floor ";
    tmpString += String(floorNr);

    // Check range valid
    if(floorNr < 1 || floorNr > 4)
    {
      tmpString += " outside range allowed";
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
    return true;
  }

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

      return true;
    }
  }

  Serial.print("Floor ");
  Serial.print(floorNr);
  Serial.println(" was not found in queue");

  return false;
  }

  int GetFromQueue()
  {
    // Some code to get next destination from queue
  }

  void printQueue() 
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