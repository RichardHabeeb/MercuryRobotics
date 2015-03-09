/*
*Robot Control class.\
*This class is for controling the stepper motors and servo motors.
*written by: Brandon R Dunn, Daniel 
*/
#include "RobotControl.h"


//Method to assign servo and motors to there perspective pins on the arduino board, and to initialize the servo's to there start posotions. 
void RobotControl::initialize()
{
	openPos = 180;
	closedPos = 0;
	iris.attach(2);
	aperature.attach(3);
        iris.write(closedPos);
        irisCurrPos = 0;//0 for closed, 1 for open
        aperature.write(closedPos);
        aperatureCurrPos = 0;//0 for closed, 1 for open
	//leftMotor.dir.attach(4);
	//leftMotor.step.attach(5);
	//rightMotor.dir.attach(6);
	//rightMotor.step.attach(7);
}

//Method for sending postion commands to the servo that controls the opening and closing of the iris.
void RobotControl::toggleAperature()
{
	if (aperatureCurrPos == 1)
	{
		aperature.write(closedPos);
                aperatureCurrPos = 0;
	}
	else if (aperatureCurrPos == 0)
	{
		aperature.write(openPos);
                aperatureCurrPos = 1;
	}
}

//Function for sending the commands to the servo the controls the lowering and raising of the armrature.
void RobotControl::toggleIris()
{
	if (irisCurrPos == 1)
	{
		iris.write(closedPos);
                irisCurrPos = 0;
	}
	else if (irisCurrPos == 0)
	{
		iris.write(openPos);
                irisCurrPos = 1;
	}
}
