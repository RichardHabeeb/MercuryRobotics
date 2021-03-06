/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: StepperMotor.cpp
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "StepperMotor.h"

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
StepperMotor::StepperMotor
(
	pin_t stepPin,
	pin_t direction_pin,
	pin_t microSelect1Pin,
	pin_t microSelect2Pin,
	pin_t microSelect3Pin,
	pin_t enableVar,
	pin_t resetVar,
	pin_t sleepVar
	)
{
	this->stepPin = stepPin;
	this->directionPin = direction_pin;

	pinMode(stepPin, OUTPUT);
	pinMode(direction_pin, OUTPUT);
	pinMode(microSelect1Pin, OUTPUT);
	pinMode(microSelect2Pin, OUTPUT);
	pinMode(microSelect3Pin, OUTPUT);
	pinMode(enableVar, OUTPUT);
	pinMode(resetVar, OUTPUT);
	pinMode(sleepVar, OUTPUT);

	digitalWrite(enableVar, LOW);
	digitalWrite(resetVar, HIGH);
	digitalWrite(sleepVar, HIGH);
}

/*-----------------------------------------------------------------------------------
* Function: ~StepperMotor
*
* Description:
*------------------------------------------------------------------------------------*/
StepperMotor::~StepperMotor(void)
{
}

/*-----------------------------------------------------------------------------------
* Function: step
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotor::step(void)
{
	*(portOutputRegister(digitalPinToPort(stepPin))) ^= digitalPinToBitMask(stepPin);

}

/*-----------------------------------------------------------------------------------
* Function: setTargetVelocity
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotor::setTargetVelocity(float v)
{
	targetVelocity = min(MAX_VELOCITY, max(0.0f, v));

	interruptTimeMicroSeconds = min(MAX_STEP_PERIOD_US, PERIOD_CONVERSION_RATIO / targetVelocity);
}

