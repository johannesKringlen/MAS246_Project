/*Elevator
This class represents the elevator’s current state, including its floor, direction, and movement status.

History:

revision  date        description
0.0.1     01.10.2026  file created

*/

#include "Encoder.h"

Encoder encoder;

class Elevator
{
  public:
  void begin()
  {
    encoder.begin();
  };
};