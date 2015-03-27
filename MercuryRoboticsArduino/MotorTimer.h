
/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: MotorTimer.h
*
* Description:
*
* Created: 3/26/2015, by Richard Habeeb
**************************************************************************************************/

#ifndef MOTORTIMER_INCLUDED_H
#define MOTORTIMER_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "Pin.h"
#include "StepperMotor.h"


/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/

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
* Class: MotorTimer
*
* Description:
*------------------------------------------------------------------------------------*/
class MotorTimer
{
public:  /* Methods */
	static MotorTimer* getInstance(void);
	void setup(StepperMotor *leftMotor, StepperMotor *rightMotor);
	void interruptLeft(void);
	void interruptRight(void);

private: /* Methods */
	MotorTimer();
	~MotorTimer();

public:  /* Fields */



private: /* Fields */
	static MotorTimer* instance;
	StepperMotor *leftMotor; /* These could be public to improve performance */
	StepperMotor *rightMotor;

};


#endif /* MOTORTIMER_INCLUDED_H */

