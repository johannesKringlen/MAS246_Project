/*DoorMotor
This class controls opening and closing the elevator doors.
*/
#include "dac.h"

class DoorMotor
{
  private:
  bool _log;
  int i;
  // Stepper motor
  static const int pinEnableA = A15; // pin 69 connected to enable A
  static const int pinPhaseA = A14; // pin 68 connected to phase A
  static const int pinEnableB = A13; // pin 67 connected to enable B
  static const int pinPhaseB = A12; // pin 66 connected to phase B
  static const int stepsPerRev = 200; // defining steps per revolution (360 degrees)

  public:
  void Begin(bool log)
  {
    _log = log;
    pinMode(pinEnableA, OUTPUT);
    pinMode(pinEnableB, OUTPUT);
    pinMode(pinPhaseA, OUTPUT); 
    pinMode(pinPhaseB, OUTPUT);
    dac_init();
    set_dac(4095,4095); //1A per motor phase
    if (_log) 
    {
      Serial.println("Door motor initialized");
    }

  };

  // Sequence to rotate motor clockwise
  void OpenDoor(int stepsToMove, int delayStep) 
  {
    for(i = 0; i > -stepsToMove; i--)
    {
    digitalWrite(pinEnableA, HIGH); //STEP 8
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 7
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, LOW); //STEP 6
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 5
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (delayStep); 

    digitalWrite(pinEnableA, HIGH); //STEP 4
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 3
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);   

    digitalWrite(pinEnableA, LOW);  //STEP 2
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);   

    digitalWrite(pinEnableA, HIGH);  //STEP 1
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);
    }
  }  

  // Sequence to rotate motor counterclockwise
  void CloseDoor(int stepsToMove, int delayStep) 
  {
    for(i = 0; i < stepsToMove; i++)
    { 
    digitalWrite(pinEnableA, HIGH);  //STEP 1
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, LOW);  //STEP 2
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 3
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 4
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 5
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, LOW); //STEP 6
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 7
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 8
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (delayStep);
    }   
  }

};