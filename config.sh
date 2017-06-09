#/bin/sh

ifconfig can0 down
# set bitrate
/sbin/ip link set can0 type can bitrate 1000000 
ifconfig can0 up

