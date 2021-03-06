/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: Sensor.ino
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/


/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Sensor.h"

/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Function: Communication
*
* Description:
*------------------------------------------------------------------------------------*/

Sensor::Sensor(pin_t p)
{
	pin = p;
	SensorValue = 0;
}

float Sensor::GetSensorData()
{
  SensorValue = analogRead(pin);
      
	for (int i = 0; i < 100; i++)
	{
		SensorValue += analogRead(pin);
	}
	SensorValue /= 100;
      
	return (a * pow(SensorValue, 3) + b * pow(SensorValue, 2) + c * SensorValue + d);
}
