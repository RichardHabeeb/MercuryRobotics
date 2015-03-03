pwd
rm -v robot_server
g++ -o robot_server robot_server.cpp
nc -ulk 4444 | ./robot_server
