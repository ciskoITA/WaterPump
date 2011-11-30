#include "funct-pump.h"
#include "funct-general.h"
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
	regs[REG_GPIO1DIR]=0xc00;
}

//function to turn on or off the pump:
//use only 1 or 0: 1=pump on, 0=pump off
void pump_power(int val) {
	//on GPIO1
	// if val=1 val<<10 is 0x400-power on, if 0 is 0x0-power off
	write_to_register(REG_GPIO1DAT, create_mask_bit(BIT_POWER), val, BIT_POWER);
}

//function to turn on or off the alarm system
//use only 1 or 0: 1=alarm on, 0=alarm off
void alarm_power(int val) {
	// if val=1 val<<11 is 0x800-alarm on, if 0 is 0x0-alarm off
	write_to_register(REG_GPIO1DAT, create_mask_bit(BIT_ALARM), val, BIT_ALARM);
}

//function to read the water level
int read_level (void) {
	//on GPIO1
	return (read_from_register(REG_GPIO1DAT, MASK_LEVEL));
}

//function to read a posssible overflow (ninth level of the pump)
int read_warning (void) {
	//on GPIO1
	//return 1 if true --> overflow:YES else return 0
	return (read_from_register(REG_GPIO1DAT, create_mask_bit(BIT_WARNING))!=0);
}
