/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: CommunicationTesting.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
**************************************************************************************************/

#ifndef SENSORTESTING_INCLUDED_H
#define SENSORTESTING_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "ISensor.h"

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
* Class: Communication
*
* Description:
*------------------------------------------------------------------------------------*/
class SensorTesting : public ISensor
{
public:  /* Methods */
	SensorTesting();
	~SensorTesting();
	void SendSensorData();

private: /* Methods */
public:  /* Fields */
private: /* Fields */
};


#endif /* SENSORTESTING_INCLUDED_H */
