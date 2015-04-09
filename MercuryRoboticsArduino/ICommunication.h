/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: ICommunication.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
**************************************************************************************************/

#ifndef ICOMMUNICATION_INCLUDED_H
#define ICOMMUNICATION_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"

/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/
typedef struct
{
	float 	left_drive_throttle;  	/* Value from -1 -> 1 (-100% to 100%) */
	float 	right_drive_throttle; 	/* Value from -1 -> 1 (-100% to 100%) */
	float 	iris_angle_deg;
	float 	arm_angle_deg;
	uint8_t led_on;
} motor_control_packet_t;

typedef struct
{
	float front_sensor;
	float rear_sensor;
	float left_sensor;
	float right_sensor;
}SensorData;

/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Class: Communication
*
* Description:
*------------------------------------------------------------------------------------*/

class ICommunication
{
public:  /* Methods */
	virtual void waitForNextPacket(motor_control_packet_t &packet) = 0;
	virtual void sendSensorDataPacket(SensorData *sDataPakect) = 0;

private: /* Methods */
public:  /* Fields */
private: /* Fields */
};


#endif /* COMMUNICATION_INCLUDED_H */
