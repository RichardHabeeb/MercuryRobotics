/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: StepperMotor.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
**************************************************************************************************/

#ifndef STEPPERMOTOR_INCLUDED_H
#define STEPPERMOTOR_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "Pin.h"

/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/
#define MAX_STEP_PERIOD_US             (10000) /* period here is refering to 1/2 T (we count a toggle as a period) */
#define WHEEL_RADIUS                   (3.0f*.0254f) /*3 inches*/
#define STEPS_PER_REVOLUTION           (200.0f)
#define TICKS_PER_STEP                 (2.0f) 
#define TICKS_PER_REVOLUTION           (STEPS_PER_REVOLUTION * TICKS_PER_STEP)
#define WHEEL_CIRCUMFERENCE            (2.0f * PI * WHEEL_RADIUS)
#define MIN_VELOCITY                   (0.0f)  /* Forward velocity (not angular). */
#define MAX_VELOCITY                   (1.5f)  /* Forward velocity (not angular). */
#define ACCELERATION                   (1.0f) /* arbitrary TODO */

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/
const volatile float PERIOD_CONVERSION_RATIO = (100000.0f * 2.f * PI * WHEEL_RADIUS) / TICKS_PER_REVOLUTION;

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/
/* TODO */
typedef void(*step_function_t)(void);

/* TODO */
typedef uint8_t motor_direction_t;
enum
{
	FORWARD,
	REVERSE
};

/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Class: StepperMotors
*
* Description: TODO update to camelcase, get start and stop working,
*------------------------------------------------------------------------------------*/
class StepperMotor
{
public:  /* Methods */
	StepperMotor
		(
		pin_t stepPin,
		pin_t directionPin,
		pin_t microSelect1Pin,
		pin_t microSelect2Pin,
		pin_t microSelect3Pin
		);
	~StepperMotor(void);
	void setTargetVelocity(float v);
	unsigned long getStepPeriodMicroSeconds() const { return (unsigned long)(interruptTimeMicroSeconds); }
	void setRotationDirection(motor_direction_t d) { rotationDirection = d; }
	bool isStopped(void) const {
		return MIN_VELOCITY >= fabs(targetVelocity);
	}
	void step(void);

private: /* Methods */

public:  /* Fields */

private: /* Fields */
	pin_t stepPin;
	pin_t directionPin;
	volatile float targetVelocity;
	volatile long interruptTimeMicroSeconds;
	motor_direction_t rotationDirection;
};

#endif /* STEPPERMOTORS_INCLUDED_H */
