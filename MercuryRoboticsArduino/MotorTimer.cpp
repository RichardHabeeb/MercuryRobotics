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
	PORTD ^= _BV(PORTD6);
	MotorTimer::getInstance()->interruptA();
}

ISR(TIMER1_COMPB_vect)
{
	PORTD ^= _BV(PORTD7);
	MotorTimer::getInstance()->interruptB();
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
	this->motorA = leftMotor;
	this->motorB = rightMotor;

	TCCR1B = _BV(WGM13) | _BV(CS10);
	ICR1 = 0x0ffff;


	updateInterruptTimers();

	TIMSK1 = _BV(OCIE1A) | _BV(OCIE1B);

}

/*-----------------------------------------------------------------------------------
* Function: interruptLeft
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::interruptA()
{
	motorA->step();
	updateInterruptTimers();
}

/*-----------------------------------------------------------------------------------
* Function: interruptLeft
*
* Description:
*------------------------------------------------------------------------------------*/
void MotorTimer::interruptB()
{
	motorB->step();
	updateInterruptTimers();
}


volatile void MotorTimer::updateInterruptTimers()
{
	OCR1A = (unsigned int)(F_CPU / 2000000) * motorA->get_step_period_us();
	OCR1B = (unsigned int)(F_CPU / 2000000) * motorB->get_step_period_us();

	/* interrupt A needs to be longer than B */
	if (OCR1B > OCR1A)
	{
		StepperMotor* temp = motorA;
		motorA = motorB;
		motorB = temp;

		unsigned int temp_reg = OCR1A;
		OCR1A = OCR1B;
		OCR1B = temp_reg;

	}
}