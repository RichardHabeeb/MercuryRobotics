/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: RobotControl.ino
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/


/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "RobotControl.h"

/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/
RobotControl* RobotControl::instance = NULL;

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Methods
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Function: RobotControl
*
* Description:
*------------------------------------------------------------------------------------*/
RobotControl::RobotControl()
{

	iris.attach(2);
	iris.write(MIN_PULSE_WIDTH);

	arm.attach(3);
	arm.write(MIN_PULSE_WIDTH);

	comm = new Communication();
//	motors = new StepperMotors(
//		9,
//		22,
//		6,
//		0, //TODO
//		0,
//		0,
//		0,
//		0,
//		StepperMotorStepWrapper
//		);
}

/*-----------------------------------------------------------------------------------
* Function: ~RobotControl
*
* Description:
*------------------------------------------------------------------------------------*/
RobotControl::~RobotControl()
{
}


/*-----------------------------------------------------------------------------------
* Function: getInstance
*
* Description:
*------------------------------------------------------------------------------------*/
RobotControl* RobotControl::getInstance()
{
	if (instance == NULL) instance = new RobotControl();

	return instance;
}


/*-----------------------------------------------------------------------------------
* Function: runRobot
*
* Description:
*------------------------------------------------------------------------------------*/
void RobotControl::runRobot()
{
	motor_control_packet_t packet;

	while (1)
	{
                Serial.println("Waiting...");
		comm->waitForNextPacket(packet);
                Serial.print("Recieved packet: ");
                Serial.print(packet.left_drive_throttle);
                Serial.print(", ");
                Serial.print(packet.right_drive_throttle);
                Serial.print(", ");
                Serial.println(packet.iris_angle_deg);
                Serial.print(", ");
                Serial.print(packet.arm_angle_deg);

                
		arm.write(map(packet.arm_angle_deg, 0.0f, 180.0f, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
		iris.write(map(packet.iris_angle_deg, 0.0f, 180.0f, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));

//		motors->set_left_target_velocity(fabs(packet.left_drive_throttle));
//		motors->set_right_target_velocity(fabs(packet.right_drive_throttle));
//
//		motors->set_left_rotation_direction(signbit(packet.left_drive_throttle) ? REVERSE : FORWARD);
//		motors->set_right_rotation_direction(signbit(packet.right_drive_throttle) ? REVERSE : FORWARD);

	}
}

/*-----------------------------------------------------------------------------------
* Function: StepperMotorStepWrapper
*
* Description:
*------------------------------------------------------------------------------------*/
void StepperMotorStepWrapper(void)
{
	RobotControl::getInstance()->motors->step();
}
