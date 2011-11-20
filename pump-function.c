#include "hw.h"

//function to setting up the direction of GPIOPIN (input/output)
void gpio_Setup () {
	//initialize hw
	//setting the IO pin
	regs[REG_GPIO1DIR]=SET_GPIO1DIR;
	//return 0;
}

//function to turn off the pump
void pump_Off () {
	regs[POWER]=POWER_OFF;
}

//function to turn on the pump
void pump_On () {
	regs[POWER]=POWER_ON;
}

//function to turn off the alarm system
void alarm_Off () {
	regs[BUZZER]=BUZZER_OFF;
}

//function to turn on the alarm system
void alarm_On () {
	regs[BUZZER]=BUZZER_ON;
}

//function to read the water level
int read_Level () {
	return regs[LEVEL];
}

//function to read a posssible overflow (ninth level of the pump)
int read_Warning () {
	if(regs[WARNING]==8) {
		return 1;
		//overflow: YES
	}
	else {
		return 0;
	}
}
