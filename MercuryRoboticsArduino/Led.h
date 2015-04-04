/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: Led.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
**************************************************************************************************/

#ifndef LED_INCLUDED_H
#define LED_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "Pin.h"

/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/
typedef uint8_t LedState;
enum
{
	ON = HIGH,
	OFF = LOW,
};
/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Class: Communication
*
* Description:
*------------------------------------------------------------------------------------*/

class Led
{
public:  /* Methods */
	Led(uint8_t);
	~Led();
	void setState(LedState);

private: /* Methods */
public:  /* Fields */
private: /* Fields */
	pin_t pin;
};


#endif /* COMMUNICATION_INCLUDED_H */
