#--------------------------------------------------------------------------------------------------
# Kansas State University Robotic Competition Team
# robot_server.py
#--------------------------------------------------------------------------------------------------

#------------------------------------------------
# Imports
#------------------------------------------------
import serial
import struct
import thread

#-----------------------------------------------
# Parameters
#-----------------------------------------------
arduino = serial.Serial('/dev/ttyACM99', 9600)

#-----------------------------------------------
# Functions
#-----------------------------------------------
def serial_reader():
	while (True):
		print arduino.readline()

def network_reader():
	while (True):
		raw_packet = raw_input()
		if (len(raw_packet) > 0):
			print "##Sending serial packet", str(struct.unpack("ffII", raw_packet))
			arduino.write(raw_packet)

#-----------------------------------------------
# Initialization
#-----------------------------------------------
thread.start_new_thread( serial_reader, () )
network_reader()



