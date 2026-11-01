# MAS246_Project

Project for MAS246, Autumn 2026.

This repository contains the documents and source code used for the project.

## The `Document` folder contains:

- The flowchart diagram
- The UML diagram
- The signal mapping

## The `Code` folder contains the source code for the elevator simulation program.

## How to Use
To run the elevator on All-in-One Servo Lab (AIOSL) [1] [2], download all the files from the `Code` folder.

The elevator starts on floor 1 with the door closed and waits for a command. 
The switches above the joystick represent the buttons on the control panel inside the elevator cabin.

When a button for a different floor is pressed, that floor is added to the queue and its corresponding LED lights up. 
If the queue is empty, the elevator moves to the requested floor immediately; otherwise, it follows the order of the queue.

The potentiometer to the right of the power button simulates the load in the elevator. 
When the elevator has stopped at a floor and the doors are open, a passenger can board. 
If the load exceeds 500 kg (approximately halfway through the potentiometer’s rotation), an overweight warning appears. 
The elevator will not proceed until the load is 500 kg or less.

The wheel on the left represents the lift motor’s pulley, while the wheel on the right represents the door motor’s pulley.

Some keyboard keys are used as floor buttons:
- 1 = Floor 1 Up
- 2 = Floor 2 Up
- w = Floor 2 Down
- 3 = Floor 3 Up
- e = Floor 3 Down
- 4 = Floor 4 Down
If a floor button for the elevator’s current floor is pressed while the doors are closing, the doors open again to allow another passenger to board.

## References

[1] F. Sanfilippo, M. Økter, T. Eie, and M. Ottestad, “Teaching motion control in mechatronics education using an open framework based on
the elevator model,” vol. 10, no. 10, p. 945. [Online]. 

Available: https://www.mdpi.com/2075-1702/10/10/945

[2] Microttus/elevator-model: An repository containing all nessesary CAD and code. [Online]. 

Available: https://github.com/Microttus/Elevator-mode
