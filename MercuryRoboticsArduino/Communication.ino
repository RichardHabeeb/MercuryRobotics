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
#include "Communication.h"

/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Function: Communication
*
* Description: 
*------------------------------------------------------------------------------------*/
Communication::Communication()
{
  	Serial.begin(115200);
	Serial.println("Kansas State University Robotics Competition Team");
	Serial.println("Mercury Robot (2015)");
}

/*-----------------------------------------------------------------------------------
* Function: ~Communication
*
* Description: 
*------------------------------------------------------------------------------------*/
Communication::~Communication()
{
}

/*-----------------------------------------------------------------------------------
* Function: waitForNextPacket
*
* Description: 
*------------------------------------------------------------------------------------*/
void Communication::waitForNextPacket(motor_control_packet_t &packet)
{
  /* Declare variables */
  char buff[sizeof(motor_control_packet_t)];
  
  /* Initialize */
  memset(buff, 0, sizeof(motor_control_packet_t));
  
  /* Hang until correct amount of bytes are on serial line */
  while(Serial.available() < sizeof(motor_control_packet_t));
  
  /* Read serial & parse*/
  if(Serial.readBytes(buff, sizeof(motor_control_packet_t)) == sizeof(motor_control_packet_t));
  {
    memcpy((void*)&packet, buff, sizeof(motor_control_packet_t));
  }
}
