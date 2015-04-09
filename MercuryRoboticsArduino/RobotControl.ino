/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: RobotControl.ino
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb, Brandon Dunn
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
	comm = new Communication();

	iris.attach(IRIS_SERVO_PIN);
	iris.write(IRIS_CLOSED_ANGLE_DEG);

	arm.attach(ARM_SERVO_PIN);
	arm.write(ARM_CLOSED_ANGLE_DEG);
	
	led1 = new Led(LED_PIN_1);
	led2 = new Led(LED_PIN_2);

	left_sensor = new Sensor(IR_SENSOR_1_PIN);
	right_sensor = new Sensor(IR_SENSOR_2_PIN);
	front_sensor = new Sensor(IR_SENSOR_3_PIN);
	rear_senor = new Sensor(IR_SENSOR_4_PIN);
	sdata = new SensorData();

	left = new StepperMotor
		(
		LEFT_MOTOR_PIN,
		LEFT_MOTOR_DIRECTION_PIN,
		MOTOR_MICROSTEP_1_PIN,
		MOTOR_MICROSTEP_2_PIN,
		MOTOR_MICROSTEP_3_PIN
		);

	right = new StepperMotor
		(
		RIGHT_MOTOR_PIN,
		RIGHT_MOTOR_DIRECTION_PIN,
		MOTOR_MICROSTEP_1_PIN,
		MOTOR_MICROSTEP_2_PIN,
		MOTOR_MICROSTEP_3_PIN
		);

	left->set_target_velocity(1.0);
	right->set_target_velocity(1.0);
	
	timer = MotorTimer::getInstance();
	timer->setup(left, right);
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
		
		led1->setState(packet.led_on);
		led2->setState(packet.led_on);

		sdata->front_sensor = front_sensor->GetSensorData();
		sdata->rear_sensor = rear_senor->GetSensorData();
		sdata->left_sensor = left_sensor->GetSensorData();
		sdata->rear_sensor = right_sensor->GetSensorData();
		
		comm->sendSensorDataPacket(sdata);
		arm.write(map(packet.arm_angle_deg, 0.0f, 180.0f, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
		iris.write(map(packet.iris_angle_deg, 0.0f, 180.0f, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));

		left->set_target_velocity(fabs(packet.left_drive_throttle));
		right->set_target_velocity(fabs(packet.right_drive_throttle));

		left->set_rotation_direction(signbit(packet.left_drive_throttle) ? REVERSE : FORWARD);
		right->set_rotation_direction(signbit(packet.right_drive_throttle) ? REVERSE : FORWARD);

	}
}
