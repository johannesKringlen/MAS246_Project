/*Queue
This class manages the list of requested elevator floors.

History:

revision  date        description
0.0.2     12.10.2026  Added isEmpty and functions placeholder
0.0.1     01.10.2026  File created

*/

class Queue
{
  private:
  bool _log;

  public:
  bool isEmpty;

  void Begin(bool log)
  {
    _log = log;
    isEmpty = true;
  };

  void AddToQueue(int floorNr)
  {
    // Some code to add a request to queue
  }

  void RemoveFromQueue(int floorNr)
  {
    // Some code to remove a request from queue
  }

  int GetFromQueue()
  {
    // Some code to get next destination from queue
  }
};