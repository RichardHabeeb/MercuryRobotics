
#include <Servo.h>
#include "Robot_Control.h"

typedef struct 
{
	float 	left_drive_throttle;  	/* Value from -1 -> 1 (-100% to 100%) */
	float 	right_drive_throttle; 	/* Value from -1 -> 1 (-100% to 100%) */
	long 	aperature_open;
	long 	lower_arm;
} motor_control_packet_t;

Robot_Control* rc;

void setup() 
{
  Serial.begin(9600);  
  rc = new Robot_Control();
}

void loop() 
{
  char buff[sizeof(motor_control_packet_t)];
  memset(buff, 0, sizeof(motor_control_packet_t));
  motor_control_packet_t packet;
  
  Serial.println("waiting...");
  while(Serial.available() < sizeof(motor_control_packet_t));
  Serial.println("got it.");
  
  if(Serial.readBytes(buff, sizeof(motor_control_packet_t)) == sizeof(motor_control_packet_t));
  {
    memcpy((void*)&packet, buff, sizeof(motor_control_packet_t));
    if(packet.aperature_open == 1)
    {
      rc->toggleIris();
    }
    
    if(packet.lower_arm == 1)
    {
      rc->toggleAperature();
    }
  }
}
