#include "WString.h"
/*FloorButton
This class represents a button used to request the elevator from a specific floor.

History:

revision  date        description
0.0.1     01.10.2026  file created

*/

class FloorButtons
{
  private:
  bool _log;
  int _floor; 
  String _direction;
  
  public:
  

  void Begin(bool log) 
  {
    _log =log;
  };

  void GetStatus()
  {
    if (Serial.available() > 0)
    {
      bool print = false;
      switch (Serial.read())
     {
      case '1':
      {
        _floor = 1;
        _direction = "up";
        print = true;
        break;
      }
      case '2':
      {
        _floor = 2;
        _direction = "up";
        print = true;
        break;
      }
      case 'w':
      {
        _floor = 2;
        _direction = "down";
        print = true;
        break;
      }
      case '3':
      {
        _floor = 3;
        _direction = "up";
        print = true;
        break;
      }
      case 'e':
      {
        _floor = 3;
        _direction = "down";
        print = true;
        break;
      }
      case '4':
      {
        _floor = 4;
        _direction = "down";
        print = true;
        break;
      }
      default:
      break;
      }
      if (print) 
      {
      Serial.print("Floor ");
      Serial.print(_floor);
      Serial.print(" ");
      Serial.print(_direction);
      Serial.println(" pressed");
      }
    };
  };

  void SetButtonLight(bool onOff)
  {
   
  }
};