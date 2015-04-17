/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: SensorTimer.h
*
* Description:
*
* Created: 4/16/2015
**************************************************************************************************/

#ifndef SENSORTIMER_INCLUDED_H
#define SENSORTIMER_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/

#include "ISensor.h"
#include <DueTimer.h>

/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Class: SensorTimer
*
* Description:
*------------------------------------------------------------------------------------*/
class SensorTimer
{
public:  /* Methods */
	static SensorTimer* getInstance(void);
	void setup(Sensor *rear_left_sensor, Sensor *front_right_sensor, Sensor *front_left_sensor, Sensor *rear_right_sensor, ICommunication *comm);
	static void interruptSend();
private: /* Methods */
	SensorTimer();
	~SensorTimer();
public:  /* Fields */
private: /* Fields */
	static SensorTimer* instance;
	ICommunication *comm;
	Sensor *front_left_sensor, *front_right_sensor, *rear_left_sensor, *rear_right_sensor;
	DueTimer *sensorTimer;
	SensorData *sdata;
};


#endif /* SENSORTIMER_INCLUDED_H */