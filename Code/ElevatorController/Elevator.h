/*Elevator
This file will take care of elevator floor request

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