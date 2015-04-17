/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: SensorTimer.ino
*
* Description:
*
* Created: 4/16/2015
***************************************************************************************************/


/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "SensorTimer.h"


/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/
SensorTimer *SensorTimer::instance = NULL;

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Methods
*------------------------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------
* Function: SensorTimer
*
* Description:
*------------------------------------------------------------------------------------*/
SensorTimer::SensorTimer()
{
}



SensorTimer::~SensorTimer()
{
}

/*-----------------------------------------------------------------------------------
* Function: getInstance
*
* Description:
*------------------------------------------------------------------------------------*/
SensorTimer* SensorTimer::getInstance(void)
{
	if (!instance) instance = new SensorTimer();

	return instance;
}

/*-----------------------------------------------------------------------------------
* Function: setup
*
* Description:
*------------------------------------------------------------------------------------*/
void SensorTimer::setup(Sensor *rear_left_sensor, Sensor *front_right_sensor, Sensor *front_left_sensor, Sensor *rear_right_sensor, ICommunication *comm)
{
	sdata = new SensorData();
	this->front_left_sensor = front_left_sensor;
	this->front_right_sensor = front_right_sensor;
	this->rear_left_sensor = rear_left_sensor;
	this->rear_right_sensor = rear_right_sensor;
	this->comm = comm;

	sensorTimer = &Timer8;

	sensorTimer->attachInterrupt(SensorTimer::interruptSend);

	sensorTimer->setPeriod(100000);
	sensorTimer->start();
}

/*-----------------------------------------------------------------------------------
* Function: interruptSend
*
* Description:
*------------------------------------------------------------------------------------*/
void SensorTimer::interruptSend()
{
	SensorTimer* sTimer = getInstance();

	sTimer->sdata->front_left_sensor = sTimer->front_left_sensor->GetSensorData();
	sTimer->sdata->front_right_sensor = sTimer->front_right_sensor->GetSensorData();
	sTimer->sdata->rear_left_sensor = sTimer->rear_left_sensor->GetSensorData();
	sTimer->sdata->rear_right_sensor = sTimer->rear_right_sensor->GetSensorData();

	sTimer->comm->sendSensorDataPacket(sTimer->sdata);
}
