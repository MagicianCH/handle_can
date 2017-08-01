#include "cmd.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void handle_cmd(unsigned char *data)
{
	unsigned char data1, data2;
	data1 = data[0];
	data2 = data[1];

	if(data1 || data2 == 0) {
		return;
	}
	if(data1 & 0x01) {
		cmd_stop_slowly();
	}
	if(data1 & 0x02) {
		cmd_stop();
	}
	if(data1 & 0x04) {
		cmd_warningled_set(1);
	} else {
		cmd_warningled_set(0);
	}
	if(data1 & 0x08) {
		cmd_start();
	}
	if(data1 & 0x10) {
		cmd_power_set(1);	
	} else {
		cmd_power_set(0);
	}
	if(data1 & 0x20){
		cmd_frontled_set(1);
	} else {
		cmd_frontled_set(0);
	}
	if(data1 & 0x40) {
		cmd_backled_set(1);
	} else {
		cmd_backled_set(0);
	}
	if(data2 & 0x01) {
		cmd_goahead();
	} 
	if(data2 & 0x02) {
		cmd_goback();
	}
	if(data2 & 0x04) {
		cmd_beeper_set(1);
	} else {
		cmd_beeper_set(0);
	}
	if(data2 & 0x08) {
		cmd_system_set(1);
	} else {
		cmd_system_set(0);
	}

}

void cmd_start()
{
	system("echo 2 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio2/direction");
	system("echo 1 > /sys/class/gpio/gpio2/value");

	system("echo 2 > /sys/class/gpio/unexport");
}

void cmd_stop()
{	
	system("echo 2 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio2/direction");
	system("echo 0 > /sys/class/gpio/gpio2/value");

	system("echo 2 > /sys/class/gpio/unexport");
}

void cmd_warningled_set(int on)
{	
	system("echo 3 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio3/direction");
	if(on) {
		system("echo 1 > /sys/class/gpio/gpio3/value");
	}
	else {
		system("echo 0 > /sys/class/gpio/gpio3/value");
	}

	system("echo 3 > /sys/class/gpio/unexport");
}

void cmd_stop_slowly()
{
	//todo
}

void cmd_power_set(int on)
{
	system("echo 8 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio8/diretion");
	if(on) {
		system("echo 1 > /sys/class/gpio/gpio8/value");
	}
	else {
		system("echo 0 > /sys/class/gpio/gpio8/value");
	}

	system("echo 8 > /sys/class/gpio/unexport");
}

void cmd_frontled_set(int on)
{
	system("echo 9 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio9/diretion");
	if(on) {
		system("echo 1 > /sys/class/gpio/gpio9/value");
	}
	else {
		system("echo 0 > /sys/class/gpio/gpio9/value");
	}

	system("echo 9 > /sys/class/gpio/unexport");
}

void cmd_backled_set(int on)
{
	system("echo 10 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio10/diretion");
	if(on) {
		system("echo 1 > /sys/class/gpio/gpio10/value");
	}
	else {
		system("echo 0 > /sys/class/gpio/gpio10/value");
	}

	system("echo 10 > /sys/class/gpio/unexport");
}

void cmd_goahead()
{
	system("echo 11 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio11/direction");
	system("echo 1 > /sys/class/gpio/gpio11/value");

	system("echo 11 > /sys/class/gpio/unexport");
}

void cmd_goback()
{
	system("echo 60 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio60/direction");
	system("echo 1 > /sys/class/gpio/gpio60/value");

	system("echo 60 > /sys/class/gpio/unexport");
}

void cmd_beeper_set(int on)
{
	system("echo 74 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio74/diretion");
	if(on) {
		system("echo 1 > /sys/class/gpio/gpio74/value");
	}
	else {
		system("echo 0 > /sys/class/gpio/gpio74/value");
	}

	system("echo 74 > /sys/class/gpio/unexport");
}

void cmd_system_set(int on)
{
	system("echo 75 > /sys/class/gpio/export");

	system("echo out > /sys/class/gpio/gpio75/diretion");
	if(on) {
		system("echo 1 > /sys/class/gpio/gpio75/value");
	}
	else {
		system("echo 0 > /sys/class/gpio/gpio75/value");
	}

	system("echo 75 > /sys/class/gpio/unexport");
}
