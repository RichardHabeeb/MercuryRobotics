
#include <Servo.h> 


typedef struct 
{
	float 	left_drive_throttle;  	/* Value from -1 -> 1 (-100% to 100%) */
	float 	right_drive_throttle; 	/* Value from -1 -> 1 (-100% to 100%) */
	long 	aperature_open;
	long 	lower_arm;
} motor_control_packet_t;

Servo iris;
Servo aperature;
int openPos = 180;
int closePos = 0;

void setup() 
{
  Serial.begin(9600);
  iris.attach(2);
  aperature.attach(3);
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
    Serial.println(packet.aperature_open);
    if(packet.aperature_open == 1)
    {
      iris.write(openPos);
    }
    else if(packet.aperature_open == 0)
    {
       iris.write(closePos); 
    }
    
    if(packet.lower_arm == 1)
    {
      aperature.write(openPos);
    }
    else if(packet.lower_arm == 0)
    {
       aperature.write(closePos); 
    }
  }
}
