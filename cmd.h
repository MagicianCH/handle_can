#ifndef _CMD_H_
#define _CMD_H_

#include <stdio.h>

#define CONTRL_PIN        2
#define WARNING_LED_PIN   3
#define POWER_PIN         8
#define FRONT_LED_PIN     9
#define BACK_LED_PIN      10
#define GO_AHEAD_PIN      11
#define GO_BACK_PIN       60
#define BEEPER_PIN        74
#define SYSTEM_START_PIN  75


void handle_cmd (unsigned char *data);

void cmd_stop();

void cmd_start();

void cmd_warningled_set(int on);

void cmd_stop_slowly();

void cmd_power_set(int on);

void cmd_frontled_set(int on);

void cmd_backled_set(int on);

void cmd_goahead();

void cmd_goback();

void cmd_beeper_set(int on);

void cmd_system_set(int on);



#endif 
