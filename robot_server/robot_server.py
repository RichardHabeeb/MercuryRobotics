#!/usr/bin/env python
#--------------------------------------------------------------------------------------------------
# Kansas State University Robotic Competition Team
# robot_server.py
#--------------------------------------------------------------------------------------------------

#------------------------------------------------
# Imports
#------------------------------------------------
import serial
import thread
import struct
import base64
import time
import socket
import os
from discover_addr import handshake


#-----------------------------------------------
# Parameters
#-----------------------------------------------
motor_packet_string = "ffffI"
sensor_packet_string = "ffff"
baseStationListener = socket.socket( socket.AF_INET,  socket.SOCK_DGRAM)
baseStationListener.bind(('', 4444))
baseStationSender = socket. socket( socket.AF_INET,  socket.SOCK_DGRAM)
baseStationIP = ""
quitThreads = False

arduino = None
for i in range(3):
	path = '/dev/ttyACM{}'.format(i)
	try:
		arduino = serial.Serial('/dev/ttyACM0', 115200)
		break
	except:
		pass
assert not arduino is None, 'Could not connect to socket.'

#-----------------------------------------------
# Functions
#-----------------------------------------------
def main():
	print "Waiting for BaseStation IP Address..."
	while(True):
		baseStationIP = baseStationListener.recv(16)
		if(len(baseStationIP) > 0):
			break
	print "Connected to ", baseStationIP, "\nStarting threads..."
	#baseStationSender.sendto(socket.gethostbyname(socket.gethostname()), (baseStationIP, 4445))
	thread.start_new_thread(wait_motor_packet, ())
	thread.start_new_thread(wait_sensor_packet, tuple([baseStationIP]))
	print "Press enter to quit."
	raw_input() or ""
	quitThreads = True


def wait_motor_packet():
	while(not quitThreads):
		data = baseStationListener.recv(struct.calcsize(motor_packet_string))
		if(len(data) == struct.calcsize(motor_packet_string)):
			arduino.write(base64.b64encode(data))
			print "Recieved motor packet ", struct.unpack(motor_packet_string, data)

def wait_sensor_packet(ip):
	while(not quitThreads):
		data = arduino.readline().strip()
		#data = "MTIzNDEyMzQxMjM0MTIzNA=="
		if(len(data) == 24):
			baseStationSender.sendto(base64.b64decode(data), (ip, 4445))
			print "Sending sensor packet to ", ip, struct.unpack(sensor_packet_string, base64.b64decode(data))

#-----------------------------------------------
# Initialization
#-----------------------------------------------
main()
