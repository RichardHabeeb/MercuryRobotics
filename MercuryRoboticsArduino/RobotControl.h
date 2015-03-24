
/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: RobotControl.h
*
* Description: 
*
* Created: 3/9/2015, by Richard Habeeb, Brandon Dunn, Daniel Marts
**************************************************************************************************/
  
#ifndef ROBOTTCONTROL_INCLUDED_H
#define ROBOTTCONTROL_INCLUDED_H
 
/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "StepperMotors.h"
#include "Communication.h"

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
* Class: RobotControl
*
* Description: 
*------------------------------------------------------------------------------------*/
class RobotControl
{
  public:  /* Methods */
    RobotControl();
    ~RobotControl();
    void runRobot();
    void toggleAperature(void);
    void toggleIris(void);
    void rightMotorStepWrapper(void);
    void leftMotorStepWrapper(void);
    
  private: /* Methods */
  public:  /* Fields */
  private: /* Fields */
    Communication *comm;
    int closedPos, openPos, aperatureCurrPos, irisCurrPos;
    Servo iris, aperature;
    StepperMotors *motors;

};

#endif /* ROBOTTCONTROL_INCLUDED_H */
