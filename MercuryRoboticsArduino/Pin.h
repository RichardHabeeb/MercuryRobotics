
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
#define RIGHT_MOTOR_ENABLE_PIN                  (37)
#define RIGHT_MOTOR_MICROSTEP_0_PIN		(35)
#define RIGHT_MOTOR_MICROSTEP_1_PIN		(33)
#define RIGHT_MOTOR_MICROSTEP_2_PIN		(31)
#define RIGHT_MOTOR_RESET_PIN                   (29)
#define RIGHT_MOTOR_SLEEP_PIN                   (27)
#define RIGHT_MOTOR_PIN				(25) 
#define RIGHT_MOTOR_DIRECTION_PIN		(23)

#define LEFT_MOTOR_ENABLE_PIN                   (53)
#define LEFT_MOTOR_MICROSTEP_0_PIN		(51)
#define LEFT_MOTOR_MICROSTEP_1_PIN		(49)
#define LEFT_MOTOR_MICROSTEP_2_PIN		(47)
#define LEFT_MOTOR_RESET_PIN                    (45)
#define LEFT_MOTOR_SLEEP_PIN                    (43)
#define LEFT_MOTOR_PIN		        	(41)
#define LEFT_MOTOR_DIRECTION_PIN		(39)

#define IR_SENSOR_1_PIN					(A0)
#define IR_SENSOR_2_PIN					(A1)
#define IR_SENSOR_3_PIN					(A2)
#define IR_SENSOR_4_PIN					(A3)
#define LED_PIN_1					(19)
#define LED_PIN_2					(21)
#define ARM_SERVO_PIN					(2)
#define IRIS_SERVO_PIN					(4)

/*-------------------------------------------------------------------------------------------------
*                                             Types
*------------------------------------------------------------------------------------------------*/
typedef int pin_t;

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
