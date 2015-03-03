typedef struct 
{
	float 	left_drive_throttle;  	/* Value from -1 -> 1 (-100% to 100%) */
	float 	right_drive_throttle; 	/* Value from -1 -> 1 (-100% to 100%) */
	long 	apature_open;
	long 	lower_arm;
} motor_control_packet_t;


void setup() 
{
  Serial.begin(9600);
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
    Serial.print("Recieved. L: ");
    Serial.println(packet.left_drive_throttle);
    Serial.print("Recieved. R: ");
    Serial.println(packet.right_drive_throttle);
    Serial.print("Recieved. iris: ");
    Serial.println(packet.apature_open);
    Serial.print("Recieved. arm: ");
    Serial.println(packet.lower_arm);
  }
}
