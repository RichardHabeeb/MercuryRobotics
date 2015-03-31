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
ISR(TIMER1_COMPA_vect)
{
	MotorTimer::getInstance()->interruptLeft();
}

ISR(TIMER1_COMPB_vect)
{
	MotorTimer::getInstance()->interruptRight();
}

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

	TCCR1B = _BV(WGM13) | _BV(CS10);
	ICR1 = 0x0ffff;

	OCR1A = 0x08fff;
	OCR1B = 0x04fff;
	TIMSK1 = _BV(OCIE1A) | _BV(OCIE1B);

}

/*-----------------------------------------------------------------------------------
* Function: interruptLeft
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::interruptLeft()
{
	leftMotor->step();
}

/*-----------------------------------------------------------------------------------
* Function: interruptLeft
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::interruptRight()
{
	rightMotor->step();
}