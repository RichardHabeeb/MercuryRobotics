/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: Motor_Control_Packet.ino
*
* Description: 
*
* Created: 3/12/2015, by Daniel Marts
***************************************************************************************************/

 
/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Motor_Control_Packet.h"

 
/*-------------------------------------------------------------------------------------------------
*                                            Methods
*------------------------------------------------------------------------------------------------*/


//TODO Add descriptions and change case

/*-----------------------------------------------------------------------------------
* Function: set_vals
*
* Description: Sets the values for each motor and servo.
*------------------------------------------------------------------------------------*/
void Motor_Control_Packet::set_vals(float l, float r, long a, long i)
{
  left_drive_throttle = l;
  right_drive_throttle = r;
  aperature_open = a;
  lower_arm = i;
}

/*-----------------------------------------------------------------------------------
* Function: motor_control_packet
*
* Description: Constructor for motor_control_packet, initializes all fields to 0
*------------------------------------------------------------------------------------*/
Motor_Control_Packet::motor_control_packet()
{
  left_drive_throttle = 0.0;
  right_drive_throttle = 0.0;
  aperature_open = 0;
  lower_arm = 0;
}
