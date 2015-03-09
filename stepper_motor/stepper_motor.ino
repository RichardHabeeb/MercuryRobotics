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
*                                            Methods
*------------------------------------------------------------------------------------------------*/
void setup()
{
}

void loop()
{
}

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
                            timer_select_t timer_select
                            )
{
  this->pwm_pin = pwm_pin;
  this->step_pin = step_pin;
  this->direction_pin = direction_pin;
  this->micro_select_1_pin = micro_select_1_pin;
  this->micro_select_2_pin = micro_select_2_pin;
  this->micro_select_3_pin = micro_select_3_pin;
  this->timer_select = timer_select;
  
  motor_signal_state = HIGH;
  velocity = 0.0f;
  target_velocity = 0.1f;
  rotation_direction = FORWARD;
  
  if(timer_select == TIMER1)
  {
    Timer1.initialize();
    Timer1.pwm(pwm_pin, 512, get_step_period()); 
    //Timer1.attachInterrupt((step_fuction_ptr)&stepper_motor::step);
  }
}



//void stepper_motor::step()
//{
//  motor_signal_state = !motor_signal_state;
//  digitalWrite(step_pin, motor_signal_state);
//  
//  float time_since_last_interrupt = get_step_period() * .000001f;
//  
//  if(target_velocity > velocity)
//  { 
//    velocity += get_acceleration() * (time_since_last_interrupt);
//    
//    velocity = min(target_velocity, velocity);
//    velocity = min(MAX_VELOCITY,    velocity);
//    
//    /* for testing only */
//    if(velocity >= target_velocity) {
//      target_velocity = 0.0f;
//    }
//    
//    Timer1.pwm(pwm_pin, 512, get_step_period()); 
//  }
//  
//  if(target_velocity < velocity)
//  {    
//    velocity -= get_acceleration() * (time_since_last_interrupt);
//
//    velocity = max(target_velocity, velocity);
//    velocity = max(MIN_VELOCITY,    velocity);
//    
//    /* for testing only */
//    if(velocity <= target_velocity) {
//      target_velocity = 0.1f;
//    }
//   
//    Timer1.pwm(pwm_pin, 512, get_step_period()); 
//  }
//  
//}
