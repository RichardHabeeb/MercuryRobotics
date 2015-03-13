/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: Motor_Control_Packet.ino
*
* Description: 
*
* Created: 3/12/2015, by Daniel Marts
***************************************************************************************************/

 
/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Motor_Control_Packet.h"

 
/*-------------------------------------------------------------------------------------------------
*                                            Methods
*------------------------------------------------------------------------------------------------*/

void Robot_Control::toggleAperature()
{
	if (aperatureCurrPos == 1)
	{
		aperature.write(closedPos);
                aperatureCurrPos = 0;
	}
	else if (aperatureCurrPos == 0)
	{
		aperature.write(openPos);
                aperatureCurrPos = 1;
	}
}


void Robot_Control::toggleIris()
{
	if (irisCurrPos == 1)
	{
		iris.write(closedPos);
                irisCurrPos = 0;
	}
	else if (irisCurrPos == 0)
	{
		iris.write(openPos);
                irisCurrPos = 1;
	}
}


/*-----------------------------------------------------------------------------------
* Function: Robot_Control
*
* Description: Constructor for Robot_Control.
*------------------------------------------------------------------------------------*/

Robot_Control::Robot_Control()
{
    openPos = 180;
    closedPos = 0;
    iris.attach(2);
    aperature.attach(3);
    iris.write(closedPos);
    irisCurrPos = 0;//0 for closed, 1 for open
    aperature.write(closedPos);
    aperatureCurrPos = 0;//0 for closed, 1 for open
}
