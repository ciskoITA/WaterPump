#include "funct-pump.h"
#include "hw.h"

//function to setting up the direction of GPIOPIN (input/output)
void gpio_setup_pump (void) {
	#if 0
	initialize hw setting up the IO pin
	if DIR 0=read, else 1=write
	function dir setting: 0,1,2,3 input, 10,11 ouptut --> 0..1100-0000-0000, hex 0xc00
	#define SET_GPIO1DIR	0xc00
	regs[REG_GPIO1DIR]=SET_GPIO1DIR;
	#endif
	//regs[REG_GPIO1DIR]=0xc00;
	#if 0
	setup();
	#endif

	//do nothing
}

//function to turn on or off the pump:
//use only 1 or 0: 1=pump on, 0=pump off
void pump_power(int val) {
	//on GPIO1
	// if val=1 val<<10 is 0x400-power on, if 0 is 0x0-power off
	regs[REG_POWER]=(val<<CFG_POWER_BIT);
	#if 0
	alternative:
	if (val==1) {
		regs[REG_POWER]=0xffff
	}
	else {
		regs[REG_POWER]=0x0
	}
	#endif
}

//function to turn on or off the alarm system
//use only 1 or 0: 1=alarm on, 0=alarm off
void alarm_power(int val) {
	//on GPIO1
	// if val=1 val<<11 is 0x800-alarm on, if 0 is 0x0-alarm off
	regs[REG_ALARM]=(val<<CFG_ALARM_BIT);
	#if 0
	alternative:
	if (val==1) {
		regs[REG_ALARM]=0xffff
	}
	else {
		regs[REG_ALARM]=0x0
	}
	#endif
}

//function to read the water level
int read_level (void) {
	//on GPIO1
	return (regs[REG_LEVEL]>>CFG_LEVEL_SHIFT);
	/* if lower bit isn't in postion 0 with shift return standard int value
	example: read value from 0 to 7
	value in bits from 0 to 2 --> shift=0 read values from 0 to 7, shifted read again values from 0 to 7
	value in bits from 3 to 5 --> shift=3 read values 0, 8, 16, 17, 32, 40, 48, 56, shifted read values from 0 to 7 */
}

//function to read a posssible overflow (ninth level of the pump)
int read_warning (void) {
	//on GPIO1
	//return 1 if true --> overflow:YES else return 0
	//return 0,if warning=0, else return 1
	return (regs[REG_WARNING]!=0);
}
