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
step_function_t step_function_wrapper
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
	set_left_target_velocity(1.0f);
	set_right_target_velocity(1.5f);
	left_time_remaining_us  = getNextInterruptTimeUS(left_velocity);
	right_time_remaining_us = getNextInterruptTimeUS(right_velocity);
	interrupt_time_us = 20; /* Constant interrupt time works pretty well. */

	pinMode(right_step_pin, OUTPUT);
	pinMode(left_step_pin, OUTPUT);
	//pinMode(left_direction_pin, OUTPUT);
	//pinMode(right_direction_pin, OUTPUT);
	digitalWrite(right_step_pin, right_signal_state);
	digitalWrite(left_step_pin, left_signal_state);

	Timer1.initialize();
	Timer1.pwm(timer_pin, 512, interrupt_time_us);
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
	//TODO
}


/*-----------------------------------------------------------------------------------
* Function: ~stepper_motor
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotors::step()
{
	updateAcceleration();
	handleLeftStep();
	handleRightStep();
}


/*-----------------------------------------------------------------------------------
* Function: getNextInterruptTimeUS
*
* Description:
*------------------------------------------------------------------------------------*/
long StepperMotors::getNextInterruptTimeUS(float v)
{ 
	return min(MAX_STEP_PERIOD_US, (100000.0f * WHEEL_CIRCUMFERENCE / (TICKS_PER_REVOLUTION * v)));
}


/*-----------------------------------------------------------------------------------
* Function: handleLeftStep
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotors::handleLeftStep(void)
{
	left_time_remaining_us -= interrupt_time_us;
	if (left_time_remaining_us <= 0)
	{
		left_signal_state = !left_signal_state;
		digitalWrite(left_step_pin, left_signal_state);
		left_time_remaining_us = getNextInterruptTimeUS(left_velocity);
	}
}


/*-----------------------------------------------------------------------------------
* Function: handleRightStep
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotors::handleRightStep(void)
{
	right_time_remaining_us -= interrupt_time_us;
	if (right_time_remaining_us <= 0)
	{
		right_signal_state = !right_signal_state;
		digitalWrite(right_step_pin, right_signal_state);
		right_time_remaining_us = getNextInterruptTimeUS(right_velocity);
	}
}


/*-----------------------------------------------------------------------------------
* Function: updateAcceleration
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotors::updateAcceleration(void)
{
	/* Left side */
	if (left_target_velocity > left_velocity)
	{
		left_velocity += ACCELERATION * (interrupt_time_us * .000001f);

		left_velocity = min(left_target_velocity, left_velocity);
	}
	else if (left_target_velocity < left_velocity)
	{
		left_velocity -= ACCELERATION * (interrupt_time_us * .000001f);
		left_velocity = max(left_target_velocity, left_velocity);
	}

	/* Right side */
	if (right_target_velocity > right_velocity)
	{
		right_velocity += ACCELERATION * (interrupt_time_us * .000001f);
		right_velocity = min(right_target_velocity, right_velocity);
	}
	else if (right_target_velocity < right_velocity)
	{
		right_velocity -= ACCELERATION * (interrupt_time_us * .000001f);
		right_velocity = max(right_target_velocity, right_velocity);
	}
}