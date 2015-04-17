#!/bin/bash -ex

ffserver &
ffmpeg -f v4l2 -s 1280x720 -r 30 -i /dev/video0 -f alsa -ac 1 -i hw:0 -threads 4 http://localhost:8090/feed1.ffm &

read 
pkill ffserver

#python robot_server.py &

#SCRIPT_PATH="robot_server.py"
#PYTHON="/usr/bin/python"
#$PYTHON $SCRIPT_PATH &
