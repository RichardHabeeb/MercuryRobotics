/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: StepperMotor.ino
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/


/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "StepperMotors.h"


/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Methods
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Function: StepperMotor
*
* Description:
*------------------------------------------------------------------------------------*/
StepperMotors::StepperMotors
(
uint8_t timer_pin,
uint8_t left_step_pin,
uint8_t right_step_pin,
uint8_t left_direction_pin,
uint8_t right_direction_pin,
uint8_t micro_select_1_pin,
uint8_t micro_select_2_pin,
uint8_t micro_select_3_pin,
step_fuction_t step_function_wrapper
)
{
	this->timer_pin = timer_pin;
	this->left_step_pin = left_step_pin;
	this->right_step_pin = right_step_pin;
	this->left_direction_pin = left_direction_pin;
	this->right_direction_pin = right_direction_pin;
	this->micro_select_1_pin = micro_select_1_pin;
	this->micro_select_2_pin = micro_select_2_pin;
	this->micro_select_3_pin = micro_select_3_pin;
	this->step_function_wrapper = step_function_wrapper;

	left_signal_state		= HIGH;
	right_signal_state		= HIGH;
	left_velocity			= 0.0;
	right_velocity			= 0.0;
	left_target_velocity	= 0.1;
	right_target_velocity	= 0.1;

	pinMode(right_step_pin, OUTPUT);
	pinMode(left_step_pin, OUTPUT);
	pinMode(left_direction_pin, OUTPUT);
	pinMode(right_direction_pin, OUTPUT);
	digitalWrite(right_step_pin, right_signal_state);
	digitalWrite(left_step_pin, left_signal_state);

	Timer1.initialize();
	Timer1.pwm(timer_pin, 512, getNextInterruptTimeUS());
	Timer1.attachInterrupt(step_function_wrapper);

}

/*-----------------------------------------------------------------------------------
* Function: ~StepperMotor
*
* Description:
*------------------------------------------------------------------------------------*/
StepperMotors::~StepperMotors()
{
	//TODO
}

/*-----------------------------------------------------------------------------------
* Function: stepper_motor
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotors::start(void)
{

}

/*-----------------------------------------------------------------------------------
* Function: ~stepper_motor
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotors::step()
{
	//motor_signal_state = !motor_signal_state;
	//digitalWrite(step_pin, motor_signal_state);

	//float time_since_last_interrupt = getNextInterruptTimeUS() * .000001f;

	//if (target_velocity > velocity)
	//{
	//	velocity += ACCELERATION * (time_since_last_interrupt);

	//	velocity = min(target_velocity, velocity);
	//	velocity = min(MAX_VELOCITY, velocity);

	//	/* for testing only */
	//	if (velocity >= target_velocity) {
	//		target_velocity = 0.0f;
	//	}


	//	Timer1.pwm(timer_pin, 512, getNextInterruptTimeUS());

	//}

	//if (target_velocity < velocity)
	//{
	//	velocity -= ACCELERATION * (time_since_last_interrupt);

	//	velocity = max(target_velocity, velocity);
	//	velocity = max(MIN_VELOCITY, velocity);

	//	/* for testing only */
	//	if (velocity <= target_velocity)
	//	{
	//		target_velocity = 0.1f;
	//	}


	//	Timer1.pwm(timer_pin, 512, getNextInterruptTimeUS());

	//}
}

/*-----------------------------------------------------------------------------------
* Function: getNextInterruptTimeUS
*
* Description:
*------------------------------------------------------------------------------------*/
unsigned long StepperMotors::getNextInterruptTimeUS()
{ 
	//return min(MAX_STEP_PERIOD_US, (100000.0f * WHEEL_CIRCUMFERENCE / (TICKS_PER_REVOLUTION * velocity))); 
}


/*-----------------------------------------------------------------------------------
* Function: handleLeftStep
*
* Description:
*------------------------------------------------------------------------------------*/
unsigned long StepperMotors::handleLeftStep(void)
{
	if (interrupt_time_us >= left_period_us)
	{
		left_signal_state = !left_signal_state;
		digitalWrite(left_step_pin, left_signal_state);
	}

	//TODO

}

/*-----------------------------------------------------------------------------------
* Function: getNextInterruptTimeUS
*
* Description:
*------------------------------------------------------------------------------------*/
unsigned long StepperMotors::handleRightStep(void)
{
	if (interrupt_time_us >= right_period_us)
	{
		right_signal_state = !right_signal_state;
		digitalWrite(right_step_pin, right_signal_state);
	}

	//TODO
}