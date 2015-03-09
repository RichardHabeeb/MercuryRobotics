#include "RobotControl.h"



void RobotControl::Setup()
{
	openPos = 180;
	closedPos = 0;
	iris.attach(2);
	aperature.attach(3);
	//leftMotor.dir.attach(4);
	//leftMotor.step.attach(5);
	//rightMotor.dir.attach(6);
	//rightMotor.step.attach(7);
	aperatureCurrPos = aperature.read();
	irisCurrPos = iris.read();
}

void RobotControl::toggleAperature()
{
	aperatureCurrPos = aperature.read();
	if (aperatureCurrPos == openPos)
	{
		aperature.write(closedPos);
	}
	else if (aperatureCurrPos == closedPos)
	{
		aperature.write(openPos);
	}
}

void RobotControl::toggleIris()
{
	irisCurrPos = iris.read();
	if (irisCurrPos == openPos)
	{
		iris.write(closedPos);
	}
	else if (irisCurrPos == closedPos)
	{
		iris.write(openPos);
	}
}