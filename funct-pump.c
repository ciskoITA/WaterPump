#include "hw.h"

//function to setting up the direction of GPIOPIN (input/output)
void gpio_setup_pump () {
	/*
	initialize hw setting up the IO pin
	if DIR 0=read, else 1=write
	function dir setting: 0,1,2,3 input, 4,5 ouptut --> 0..011-0000, hex 0x30
	#define SET_GPIO1DIR	0x30
	regs[REG_GPIO1DIR]=SET_GPIO1DIR;
	*/
	regs[REG_GPIO1DIR]=0x30;
}

//function to turn on or off the pump:
//use only 1 or 0: 1=pump on, 0=pump off
void pump_power(int val) {
	regs[POWER]=(val<<4);
	// if val=1 val<<4 is 0x10-power on, if 0 is 0x0-power off
}

//function to turn on or off the alarm system
//use only 1 or 0: 1=alarm on, 0=alarm off
void alarm_power(int val) {
	regs[ALARM]=(val<<5);
	// if val=1 val<<5 is 0x20-alarm on, if 0 is 0x0-alarm off
}

//function to read the water level
int read_level () {
	return regs[LEVEL];
}

//function to read a posssible overflow (ninth level of the pump)
int read_warning () {
	//return 1 if true --> overflow:YES else return 0
	return (regs[WARNING]==8);
}
