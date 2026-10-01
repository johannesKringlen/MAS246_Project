 #include "ElevatorMotor.h"
 #include "RotaryPotentiometer.h"
 
 //oppretter objekter
ElevatorMotor elevatorMotor;
RotaryPotentiometer rotaryPotmeter;

void setup()
{
//general
Serial.begin(9600);

elevatorMotor.begin();

rotaryPotmeter.begin();

}

void loop()
{

elevatorMotor.drive(rotaryPotmeter.readPercent());

}
