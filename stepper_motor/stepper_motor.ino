/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: stepper_motor.ino
*
* Description: 
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/

 
/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "stepper_motor.h"
#include "TimerOne.h"
#include "TimerThree.h"

/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/
void motor_step_wrapper(void);

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/
stepper_motor *right_motor;
stepper_motor *left_motor;
 
/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/
void setup()
{
  right_motor = new stepper_motor(
                                 9,                  /* Timer Pin */
                                 6,                  /* Step Signal */
                                 10,                 /* Direction */ //TODO - get actual numbers for pins below
                                 10,                 /* Micro 1 */
                                 10,                 /* Micro 2 */
                                 10,                 /* Micro 3 */
                                 TIMER1,             /* Timer Select */
                                 right_motor_step_wrapper  /* function pointer to step wrapper */
                                 );
                                 
  left_motor = new stepper_motor(
                                 10,                  /* Timer Pin */
                                 7,                  /* Step Signal */
                                 10,                 /* Direction */ //TODO - get actual numbers for pins below
                                 10,                 /* Micro 1 */
                                 10,                 /* Micro 2 */
                                 10,                 /* Micro 3 */
                                 TIMER3,             /* Timer Select */
                                 left_motor_step_wrapper  /* function pointer to step wrapper */
                                 );
}

void loop()
{
}

/*-----------------------------------------------------------------------------------
* Function: right_motor_step_wrapper
*
* Description: 
*------------------------------------------------------------------------------------*/
void right_motor_step_wrapper(void)
{
  right_motor->step();
}

/*-----------------------------------------------------------------------------------
* Function: left_motor_step_wrapper
*
* Description: 
*------------------------------------------------------------------------------------*/
void left_motor_step_wrapper(void)
{
  left_motor->step();
}

/*-------------------------------------------------------------------------------------------------
*                                            Methods
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Function: stepper_motor
*
* Description: 
*------------------------------------------------------------------------------------*/
stepper_motor::stepper_motor(
                            uint8_t pwm_pin,
                            uint8_t step_pin,
                            uint8_t direction_pin,
                            uint8_t micro_select_1_pin,
                            uint8_t micro_select_2_pin,
                            uint8_t micro_select_3_pin,
                            timer_select_t timer_select,
                            step_fuction_t step_function_wrapper
                            )
{
  this->pwm_pin = pwm_pin;
  this->step_pin = step_pin;
  this->direction_pin = direction_pin;
  this->micro_select_1_pin = micro_select_1_pin;
  this->micro_select_2_pin = micro_select_2_pin;
  this->micro_select_3_pin = micro_select_3_pin;
  this->timer_select = timer_select;
  this->step_function_wrapper = step_function_wrapper;
  
  motor_signal_state = HIGH;
  velocity = 0.0f;
  target_velocity = 0.1f;
  rotation_direction = FORWARD;
  
  pinMode(step_pin, OUTPUT);
  digitalWrite(step_pin, motor_signal_state);
  
  if(timer_select == TIMER1)
  {
    Timer1.initialize();
    Timer1.pwm(pwm_pin, 512, get_step_period()); 
    Timer1.attachInterrupt(step_function_wrapper);
  }
  
  if(timer_select == TIMER3)
  {
    Timer3.initialize();
    Timer3.pwm(pwm_pin, 512, get_step_period()); 
    Timer3.attachInterrupt(step_function_wrapper);
  }
}

/*-----------------------------------------------------------------------------------
* Function: ~stepper_motor
*
* Description: 
*------------------------------------------------------------------------------------*/
stepper_motor::~stepper_motor()
{
  //TODO
}

/*-----------------------------------------------------------------------------------
* Function: stepper_motor
*
* Description: 
*------------------------------------------------------------------------------------*/
void stepper_motor::start(void)
{

}

/*-----------------------------------------------------------------------------------
* Function: ~stepper_motor
*
* Description: 
*------------------------------------------------------------------------------------*/
void stepper_motor::step()
{
  motor_signal_state = !motor_signal_state;
  digitalWrite(step_pin, motor_signal_state);
  
  float time_since_last_interrupt = get_step_period() * .000001f;
  
  if(target_velocity > velocity)
  { 
    velocity += ACCELERATION * (time_since_last_interrupt);
    
    velocity = min(target_velocity, velocity);
    velocity = min(MAX_VELOCITY,    velocity);
    
    /* for testing only */
    if(velocity >= target_velocity) {
      target_velocity = 0.0f;
      Serial.println("peaked");
      Serial.println(get_step_period());
    }
    
    if(timer_select == TIMER1)
    {
      Timer1.pwm(pwm_pin, 512, get_step_period()); 
    } 
    else
    {
      Timer3.pwm(pwm_pin, 512, get_step_period()); 
    }
  }
  
  if(target_velocity < velocity)
  {    
    velocity -= ACCELERATION * (time_since_last_interrupt);

    velocity = max(target_velocity, velocity);
    velocity = max(MIN_VELOCITY,    velocity);
    
    /* for testing only */
    if(velocity <= target_velocity) {
      target_velocity = 0.1f;
       Serial.println("valleyed");
       Serial.println(get_step_period());
    }
    
    if(timer_select == TIMER1)
    {
      Timer1.pwm(pwm_pin, 512, get_step_period()); 
    }
    else
    {
      Timer3.pwm(pwm_pin, 512, get_step_period()); 
    }
  }
}
