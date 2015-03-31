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
float SensorValue;
float a = -.00000020356;
float b = .00029411;
float c = -.152859;
float d = 33.29;
pin_t pin;
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
	for (int i = 0; i < 40; i++)
	{
		SensorValue += analogRead(pin);
	}
	SensorValue /= 40;

	return (a * pow(SensorValue, 3) + b*pow(SensorValue, 2) + c * SensorValue + d);
}