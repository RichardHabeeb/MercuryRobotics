/**************************************************************************************************
* Kansas State University Robotic Competition Team
* File: CommunicationTesting.ino
*
* Description:
*
* Created: 3/9/2015, by Richard Habeeb
***************************************************************************************************/


/*-------------------------------------------------------------------------------------------------
*                                            Includes
*------------------------------------------------------------------------------------------------*/
#include "CommunicationTesting.h"

/*-------------------------------------------------------------------------------------------------
*                                           Prototypes
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                           Variables
*------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*                                            Functions
*------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
* Function: Communication
*
* Description:
*------------------------------------------------------------------------------------*/
CommunicationTesting::CommunicationTesting()
{
	i = 0;
	test[0].arm_angle_deg = 0;
	test[0].iris_angle_deg = 0;
	test[0].left_drive_throttle = 0;
	test[0].right_drive_throttle = 0;
	test[1].arm_angle_deg = 180;
	test[1].iris_angle_deg = 0;
	test[1].left_drive_throttle = 0;
	test[1].right_drive_throttle = 0;
	test[2].arm_angle_deg = 0;
	test[2].iris_angle_deg = 180;
	test[2].left_drive_throttle = 0;
	test[2].right_drive_throttle = 0;
	test[3].arm_angle_deg = 0;
	test[3].iris_angle_deg = 0;
	test[3].left_drive_throttle = 0.5;
	test[3].right_drive_throttle = 0;
	test[4].arm_angle_deg = 0;
	test[4].iris_angle_deg = 0;
	test[4].left_drive_throttle = 0;
	test[4].right_drive_throttle = 0.5;
	test[5].arm_angle_deg = 0;
	test[5].iris_angle_deg = 0;
	test[5].left_drive_throttle = 0;
	test[5].right_drive_throttle = 0;
	test[6].arm_angle_deg = 180;
	test[6].iris_angle_deg = 180;
	test[6].left_drive_throttle = 0;
	test[6].right_drive_throttle = 0;
	test[7].arm_angle_deg = 0;
	test[7].iris_angle_deg = 0;
	test[7].left_drive_throttle = .5;
	test[7].right_drive_throttle = 1;
	test[8].arm_angle_deg = 0;
	test[8].iris_angle_deg = 0;
	test[8].left_drive_throttle = 1;
	test[8].right_drive_throttle = .5;
	test[9].arm_angle_deg = 0;
	test[9].iris_angle_deg = 0;
	test[9].left_drive_throttle = 0;
	test[9].right_drive_throttle = 0;
	test[10].arm_angle_deg = 180;
	test[10].iris_angle_deg = 180;
	test[10].left_drive_throttle = .5;
	test[10].right_drive_throttle = .5;
	test[11].arm_angle_deg = 0;
	test[11].iris_angle_deg = 0;
	test[11].left_drive_throttle = 0;
	test[11].right_drive_throttle = 0;
}

/*-----------------------------------------------------------------------------------
* Function: ~Communication
*
* Description:
*------------------------------------------------------------------------------------*/
CommunicationTesting::~CommunicationTesting()
{
}

/*-----------------------------------------------------------------------------------
* Function: waitForNextPacket
*
* Description:
*------------------------------------------------------------------------------------*/
void CommunicationTesting::waitForNextPacket(motor_control_packet_t &packet)
{
	delay(1000);
	packet.arm_angle_deg = test[i].arm_angle_deg;
	packet.iris_angle_deg = test[i].iris_angle_deg;
	packet.left_drive_throttle = test[i].left_drive_throttle;
	packet.right_drive_throttle = test[i].right_drive_throttle;
	i++;
	if (i == 12) i = 0;
}

/*-----------------------------------------------------------------------------------
* Function: sendSensorDataPacket
*
* Description:
*------------------------------------------------------------------------------------*/
void CommunicationTesting::sendSensorDataPacket(SensorData *sDataPacket)
{       
        Serial.flush();
        char buff[SENSOR_STRUCT_SIZE];
        for (int i = 0; i < (SENSOR_STRUCT_SIZE / 4); i +=4)
        {
           buff[i] = 0;
           buff[i+1] = 0;
           buff[i+2] = 0;
           buff[i+3] = 63; 
        }
        char encoded_buff[ENCODED_SENSOR_STRUCT_SIZE];
	memcpy(buff, (void*)&sDataPacket,SENSOR_STRUCT_SIZE);
	base64_encode(encoded_buff, buff, SENSOR_STRUCT_SIZE);   
	Serial.print(encoded_buff);  
}  

