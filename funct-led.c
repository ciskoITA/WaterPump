#include "funct-led.h"
#include "funct-general.h"
#include "hw.h"

static int led_position[8];
void generate_led_pos() {
	led_position[0]=0x50030004;
	led_position[1]=0x50030008;
	led_position[2]=0x50030010;
	led_position[3]=0x50030020;
	led_position[4]=0x50020040;
	led_position[5]=0x50020080;
	led_position[6]=0x50020100;
	led_position[7]=0x50020200;
}

//function to setting up the direction of GPIOPIN (input/output)
void gpio_setup_led () {
	regs[REG_AHBCLKCTRL] |= REG_AHBCLKCTRL_GPIO;
	#if 0
	initialize hw setting up the IO pin
	if DIR 0=read, else 1=write
	function dir setting: 0,1,2,3, ouptut --> 0..0-1111, hex 0xf
	#define SET_GPIO3DIR	0x0f
	regs[REG_GPIO3DIR]=SET_GPIO3DIR;
	#endif
	regs[REG_GPIO3DIR]=0xf;
	#if 0
	function dir setting: 4,5,6,7 ouptut --> 0..0-1111-0000, hex 0xf0
	#define SET_GPIO2DIR	0xf0
	regs[REG_GPIO2DIR]=SET_GPIO2DIR;
	#endif
	regs[REG_GPIO2DIR]=0xf0;
	//NOTE BUTTON 1 is dir=0 in GPIO2_9--> OK 0xf0;
	generate_led_pos();
}

//function to turn on or off a led. for status use only 0 or 1: 1=on, 0=off
void led_status(int num_led, int status) {
	int val=(led_position[num_led])/4;
	if (status==1) {
		regs[val]=0xff;
	}
	else {
		regs[val]=0x0;
	}
}
