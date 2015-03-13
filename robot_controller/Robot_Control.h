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
		void Setup(void);
		void toggleAperature(void);
		void toggleIris(void);
};

void Setup(void);
void toggleAperature(void);
void toggleIris(void);
//void setLeftMotorSpeed(float);
//void setRightMotorSpeed(float);

#endif