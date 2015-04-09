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
#include <Servo.h>

#include "MotorTimer.h"
#include "StepperMotor.h"
#include "Communication.h"
#include "Led.h"
#include "Sensor.h"

/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/
#define ARM_OPEN_ANGLE_DEG		(180)
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
	ICommunication *comm;
	StepperMotor *left;
	StepperMotor *right;
	MotorTimer *timer;
	Led *led1, *led2;
	Servo iris, arm;
	Sensor *left_sensor, *right_sensor, *front_sensor, *rear_senor;
	SensorData *sdata;
};

#endif /* ROBOTTCONTROL_INCLUDED_H */
