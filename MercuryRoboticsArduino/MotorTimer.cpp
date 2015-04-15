/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: RobotControl.ino
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/


/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "MotorTimer.h"


/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/
MotorTimer *MotorTimer::instance = NULL;

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Methods
*------------------------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------
* Function: MotorTimer
*
* Description:
*------------------------------------------------------------------------------------*/
MotorTimer::MotorTimer()
{
}



MotorTimer::~MotorTimer()
{
}

/*-----------------------------------------------------------------------------------
* Function: MotorTimer
*
* Description:
*------------------------------------------------------------------------------------*/
MotorTimer* MotorTimer::getInstance(void)
{
	if (!instance) instance = new MotorTimer();

	return instance;
}

/*-----------------------------------------------------------------------------------
* Function: setup
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::setup(StepperMotor *leftMotor, StepperMotor *rightMotor)
{
	this->leftMotor = leftMotor;
	this->rightMotor = rightMotor;

	leftTimer = &Timer6;
	rightTimer = &Timer7;


	leftTimer->attachInterrupt(MotorTimer::interruptLeft);
	rightTimer->attachInterrupt(MotorTimer::interruptRight);

	update();
}

/*-----------------------------------------------------------------------------------
* Function: update
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::update()
{

	if (leftMotor->isStopped())
	{
		leftTimer->stop();
	}
	else
	{
		leftTimer->setPeriod(leftMotor->getStepPeriodMicroSeconds());
		leftTimer->start();
	}
	
	if (rightMotor->isStopped())
	{
		rightTimer->stop();
	}
	else
	{
		rightTimer->setPeriod(rightMotor->getStepPeriodMicroSeconds());
		rightTimer->start();
	}
}

/*-----------------------------------------------------------------------------------
* Function: interruptLeft
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::interruptLeft()
{
	getInstance()->leftMotor->step();
}

/*-----------------------------------------------------------------------------------
* Function: interruptRight
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::interruptRight()
{
	getInstance()->rightMotor->step();
}
