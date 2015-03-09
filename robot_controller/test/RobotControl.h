/*
*header for Robot Control class
*written by: Brandon R Dunn, Daniel 
*/

#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <Servo.h>
//#include "Stepper.h"

class RobotControl
{
	private:
		int closedPos, openPos, aperatureCurrPos, irisCurrPos;
		Servo iris, aperature;
	public:
		void toggleAperature(void);
		void toggleIris(void);
                void initialize(void);
};


//void setLeftMotorSpeed(float);
//void setRightMotorSpeed(float);

#endif
