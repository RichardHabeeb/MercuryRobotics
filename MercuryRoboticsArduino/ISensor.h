/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: ICommunication.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
**************************************************************************************************/

#ifndef ISENSOR_INCLUDED_H
#define ISENSOR_INCLUDED_H

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


/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Class: Communication
*
* Description:
*------------------------------------------------------------------------------------*/

class ISensor
{
public:  /* Methods */
	virtual void SendSensorData() = 0;

private: /* Methods */
public:  /* Fields */
private: /* Fields */
};


#endif /* ISENSOR_INCLUDED_H */
