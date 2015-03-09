/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: stepper_motor.h
*
* Description: 
*
* Created: 3/9/2015, by Richard Habeeb
**************************************************************************************************/
  
#ifndef STEPPER_MOTOR_INCLUDED_H
#define STEPPER_MOTOR_INCLUDED_H
 
/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"

 
/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/
#define MINIMUM_STEP_PERIOD_US         (10000)
#define WHEEL_RADIUS                   (.03f)
#define STEPS_PER_REVOLUTION           (200.0f)
#define TICKS_PER_STEP                 (4.0f) 
#define TICKS_PER_REVOLUTION           (STEPS_PER_REVOLUTION * TICKS_PER_STEP)
#define WHEEL_CIRCUMFERENCE            (2.0f * PI * WHEEL_RADIUS)
#define MIN_VELOCITY                   (0.0f)  /* Forward velocity (not angular). */
#define MAX_VELOCITY                   (0.2f)  /* Forward velocity (not angular). */
#define ACCELERATION_TIME              (3.0f)

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/
/* TODO */
typedef void (*step_fuction_ptr)(void);

/* TODO */
typedef uint8_t motor_direction_t;
enum 
{
  FORWARD,
  REVERSE
};

/* TODO */
typedef boolean timer_select_t;
enum
{
  TIMER1,
  TIMER3
};
 
/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Class: stepper_motor
*
* Description: 
*------------------------------------------------------------------------------------*/
class stepper_motor
{
  public:  /* Methods */
    stepper_motor(uint8_t pwm_pin, uint8_t step_pin, uint8_t direction_pin, uint8_t micro_select_1_pin, uint8_t micro_select_2_pin, uint8_t micro_select_3_pin, timer_select_t timer_select);
    ~stepper_motor(void);
    void stop(void);
    void set_target_velocity(float v) { velocity = v; }
    void set_motor_rotation_direction(motor_direction_t d) { rotation_direction = d; }
    
  private: /* Methods */
    void step(void);
    float get_acceleration(void) const { return (target_velocity - velocity) / ACCELERATION_TIME; }
    unsigned long get_step_period(void) const { return min(MINIMUM_STEP_PERIOD_US, WHEEL_CIRCUMFERENCE / (TICKS_PER_REVOLUTION * (velocity)) * 100000); }  /* Forward velocity. Maxes out at MINIMUM_STEP_PERIOD_US microseconds */
    
  public:  /* Fields */
  
  private: /* Fields */
    uint8_t step_pin;
    uint8_t pwm_pin;
    uint8_t direction_pin;
    uint8_t micro_select_1_pin;
    uint8_t micro_select_2_pin;
    uint8_t micro_select_3_pin;
    uint8_t motor_signal_state;
    volatile float velocity;
    volatile float target_velocity;
    motor_direction_t rotation_direction;
    timer_select_t timer_select;
};

#endif /* STEPPER_MOTOR_INCLUDED_H */
