#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct MotorControlPacket
{
	double LeftDriveThrottle;  /* Value from -1 -> 1 (-100% to 100%) */
	double RightDriveThrottle; /* Value from -1 -> 1 (-100% to 100%) */
	bool ApatureOpen;
	bool LowerArm;
};


void process_motor_control_packet(struct MotorControlPacket * packet)
{
	//AdjustMotors();
	cout << "L:" << packet->LeftDriveThrottle << "\n";
}


int main()
{
	string data;
	struct MotorControlPacket packet;
	
    while(1)
	{
		cin >> data;
		
		memcpy((void*)&packet, data.c_str(), data.length());
		
		process_motor_control_packet(&packet);
		
	}
	
	return 0;
}


