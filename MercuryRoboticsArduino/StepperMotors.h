/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: StepperMotor.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
**************************************************************************************************/

#ifndef STEPPERMOTORS_INCLUDED_H
#define STEPPERMOTORS_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"

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
class StepperMotors
{
public:  /* Methods */
	StepperMotors
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
		);
	~StepperMotors(void);
	void start(void);
	void stop(void);
	void set_left_target_velocity(float v) { left_target_velocity = min(MAX_VELOCITY, max(MIN_VELOCITY, v)); }
	void set_right_target_velocity(float v) { right_target_velocity = min(MAX_VELOCITY, max(MIN_VELOCITY, v)); }
	void set_left_rotation_direction(motor_direction_t d) { left_rotation_direction = d; }
	void set_right_rotation_direction(motor_direction_t d) { right_rotation_direction = d; }
	void step(void);

private: /* Methods */
	long getNextInterruptTimeUS(float v);
	void handleLeftStep(void);
	void handleRightStep(void);
	void updateAcceleration(void);

public:  /* Fields */

private: /* Fields */
	uint8_t timer_pin;
	uint8_t left_step_pin;
	uint8_t right_step_pin;
	uint8_t left_direction_pin;
	uint8_t right_direction_pin;
	uint8_t micro_select_1_pin;
	uint8_t micro_select_2_pin;
	uint8_t micro_select_3_pin;
	volatile uint8_t left_signal_state;
	volatile uint8_t right_signal_state;
	volatile float left_velocity;
	volatile float left_target_velocity;
	volatile float right_velocity;
	volatile float right_target_velocity;
	volatile long left_time_remaining_us;
	volatile long right_time_remaining_us;
	volatile long interrupt_time_us;
	motor_direction_t left_rotation_direction;
	motor_direction_t right_rotation_direction;
	step_function_t step_function_wrapper;
};

#endif /* STEPPERMOTORS_INCLUDED_H */
