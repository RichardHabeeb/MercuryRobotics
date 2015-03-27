/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: RobotControl.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb, Brandon Dunn, Daniel Marts
**************************************************************************************************/

#ifndef ROBOTTCONTROL_INCLUDED_H
#define ROBOTTCONTROL_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "MotorTimer.h"
#include "StepperMotor.h"
#include "Communication.h"
#include "ServoTimer2.h"

/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/
#define ARM_OPEN_ANGLE_DEG		(160)
#define ARM_CLOSED_ANGLE_DEG	(0)
#define IRIS_OPEN_ANGLE_DEG		(180)
#define IRIS_CLOSED_ANGLE_DEG	(0)

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Class: RobotControl
*
* Description:
*------------------------------------------------------------------------------------*/
class RobotControl
{
public:  /* Methods */
	static RobotControl* getInstance();
	void runRobot();

private: /* Methods */
	RobotControl();
	~RobotControl();

public:  /* Fields */

private: /* Fields */

	static RobotControl* instance;
	Communication *comm;
	StepperMotor *left;
	StepperMotor *right;
	MotorTimer *timer;
	ServoTimer2 iris, arm;
	

};

#endif /* ROBOTTCONTROL_INCLUDED_H */
