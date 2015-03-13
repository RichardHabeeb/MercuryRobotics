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
void Motor_Control_Packet::SetVals(float l, float r, long a, long i)
{
  left_drive_throttle = l;
  right_drive_throttle = r;
  aperature_open = a;
  lower_arm = i;
}

Motor_Control_Packet::Motor_Control_Packet()
{
  left_drive_throttle = 0.0;
  right_drive_throttle = 0.0;
  aperature_open = 0;
  lower_arm = 0;
}
