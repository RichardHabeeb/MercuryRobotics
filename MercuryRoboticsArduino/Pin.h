
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
#define RIGHT_MOTOR_PIN					(23) 
#define RIGHT_MOTOR_DIRECTION_PIN		(25)
#define RIGHT_MOTOR_MICROSTEP_1_PIN		(27)
#define RIGHT_MOTOR_MICROSTEP_2_PIN		(29)
#define RIGHT_MOTOR_MICROSTEP_3_PIN		(31)
#define LEFT_MOTOR_PIN					(33)
#define LEFT_MOTOR_DIRECTION_PIN		(35)
#define LEFT_MOTOR_MICROSTEP_1_PIN		(37)
#define LEFT_MOTOR_MICROSTEP_2_PIN		(39)
#define LEFT_MOTOR_MICROSTEP_3_PIN		(41)
#define IR_SENSOR_1_PIN					(A0)
#define IR_SENSOR_2_PIN					(A1)
#define IR_SENSOR_3_PIN					(A2)
#define IR_SENSOR_4_PIN					(A3)
#define IR_SENSOR_5_PIN					(A4)
#define IR_SENSOR_6_PIN					(A5)
#define LED_PIN_1						(0)
#define LED_PIN_2						(0)
#define LED_PIN_3						(0)
#define LED_PIN_4						(0)
#define ARM_SERVO_PIN					(2)
#define IRIS_SERVO_PIN					(3)

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
