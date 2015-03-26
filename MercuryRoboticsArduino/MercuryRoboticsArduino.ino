/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: MercuryRoboticsArduino.ino
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "TimerOne.h"
#include "RobotControl.h"

/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/
RobotControl *controller;

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/
void setup()
{
        
}

void loop()
{
	RobotControl::getInstance()->runRobot();
}
