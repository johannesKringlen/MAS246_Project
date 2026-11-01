/*Door
This class controls opening and closing the elevator doors.
*/
#include "dac.h"
#include "Logger.h"

class Door
{
  private:
  int i;
  // Stepper motor pins
  static const int pinDoorSensor = 27; // D27 connected to SW5
  static const int pinEnableA = A15; // pin 69 connected to enable A
  static const int pinPhaseA = A14; // pin 68 connected to phase A
  static const int pinEnableB = A13; // pin 67 connected to enable B
  static const int pinPhaseB = A12; // pin 66 connected to phase B
  static const int stepsPerRev = 200; // defining steps per revolution (360 degrees)
  int _stepsToMove;
  int _delayStep;
  String _tempString;

  public:
  // Initializes the stepper motor
  void Begin()
  {
    pinMode(pinDoorSensor, INPUT);
    pinMode(pinEnableA, OUTPUT);
    pinMode(pinEnableB, OUTPUT);
    pinMode(pinPhaseA, OUTPUT); 
    pinMode(pinPhaseB, OUTPUT);
    dac_init();
    set_dac(4095,4095); //1A per motor phase
    logMessage("Door motor initialized"); 
    _stepsToMove = 12;
    _delayStep = 10000;
  };

  // Sequence to open the door one step
  void Open() 
  {
    digitalWrite(pinEnableA, HIGH); //STEP 8
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 7
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, LOW); //STEP 6
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 5
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (_delayStep); 

    digitalWrite(pinEnableA, HIGH); //STEP 4
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 3
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);   

    digitalWrite(pinEnableA, LOW);  //STEP 2
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);   

    digitalWrite(pinEnableA, HIGH);  //STEP 1
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);
  }  

  // Sequence to close the door one step
  void Close() 
  {
    digitalWrite(pinEnableA, HIGH);  //STEP 1
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, LOW);  //STEP 2
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 3
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 4
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 5
    digitalWrite(pinPhaseA, LOW);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, LOW); //STEP 6
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 7
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, HIGH);
    digitalWrite(pinPhaseB, LOW);
    delayMicroseconds (_delayStep);

    digitalWrite(pinEnableA, HIGH); //STEP 8
    digitalWrite(pinPhaseA, HIGH);
    digitalWrite(pinEnableB, LOW);
    digitalWrite(pinPhaseB, HIGH);
    delayMicroseconds (_delayStep);
  }

  // Reads the door obstacle sensor
  bool GetCollisionSensorStatus()
  {
    bool tmpDetected = digitalRead(pinDoorSensor);
    if (tmpDetected) 
    {
      logMessage("Door obstacle detected"); 
    }    
    return tmpDetected;
  }

};