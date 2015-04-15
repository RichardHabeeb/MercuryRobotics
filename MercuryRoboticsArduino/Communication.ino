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
*                                           Constants
*------------------------------------------------------------------------------------------------*/
#define MOTOR_STRUCT_SIZE 20
#define ENCODED_MOTOR_STRUCT_SIZE 28
#define SENSOR_STRUCT_SIZE 16
#define ENCODED_SENSOR_STRUCT_SIZE 24

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
  char buff[MOTOR_STRUCT_SIZE];
  char encoded_buff[ENCODED_MOTOR_STRUCT_SIZE];
  
  do
  {
  #ifdef DEBUG_SERIAL_OUT
  Serial.print("Available: ");
  Serial.println(Serial.available());
  #endif
  
  Serial.flush();

  /* Initialize */
  memset(buff, 0, MOTOR_STRUCT_SIZE);
  memset(encoded_buff, 0, ENCODED_MOTOR_STRUCT_SIZE);
  
  /* Hang until correct amount of bytes are on serial line */
  while(Serial.available() < ENCODED_MOTOR_STRUCT_SIZE);
  
  /* Read serial & parse*/
  } while(Serial.readBytes(encoded_buff, ENCODED_MOTOR_STRUCT_SIZE) != ENCODED_MOTOR_STRUCT_SIZE);
  
  base64_decode(buff, encoded_buff, ENCODED_MOTOR_STRUCT_SIZE);
  memcpy((void*)&packet, buff, sizeof(motor_control_packet_t));
  
}

/*-----------------------------------------------------------------------------------
* Function: sendSensorDataPacket
*
* Description:
*------------------------------------------------------------------------------------*/
void Communication::sendSensorDataPacket(SensorData *sDataPacket)
{
        Serial.flush();
	char buff[SENSOR_STRUCT_SIZE];
	char encoded_buff[ENCODED_SENSOR_STRUCT_SIZE];
	memcpy(buff, (void*)sDataPacket,SENSOR_STRUCT_SIZE);
	base64_encode(encoded_buff, buff, SENSOR_STRUCT_SIZE);     
	Serial.println(encoded_buff);
}
