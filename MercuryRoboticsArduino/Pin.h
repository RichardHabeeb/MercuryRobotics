
/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: Pin.h
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb, Brandon Dunn, Daniel Marts
**************************************************************************************************/

#ifndef PIN_INCLUDED_H
#define PIN_INCLUDED_H

/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "Arduino.h"

/*-------------------------------------------------------------------------------------------------
*                                       Literal Definitions
*------------------------------------------------------------------------------------------------*/
#define RIGHT_MOTOR_PIN					(6)
#define LEFT_MOTOR_PIN					(7)
#define RIGHT_MOTOR_DIRECTION_PIN		(0)
#define LEFT_MOTOR_DIRECTION_PIN		(0)
#define MOTOR_MICROSTEP_1_PIN			(0)
#define MOTOR_MICROSTEP_2_PIN			(0)
#define MOTOR_MICROSTEP_3_PIN			(0)
#define IR_SENSOR_1_PIN					(A0)
#define IR_SENSOR_2_PIN					(A1)
#define IR_SENSOR_3_PIN					(A2)
#define IR_SENSOR_4_PIN					(A3)
#define IR_SENSOR_5_PIN					(A4)
#define IR_SENSOR_6_PIN					(A5)

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/
typedef uint8_t pin_t;

/*-------------------------------------------------------------------------------------------------
*                                           Constants
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Classes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Functions
*------------------------------------------------------------------------------------------------*/

#endif /* PIN_INCLUDED_H */