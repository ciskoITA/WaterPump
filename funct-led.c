#include "hw.h"

static unsigned int led_position[8];
void generate_led_pos() {
	led_position[0]=0x50030004;
	led_position[1]=0x50030008;
	led_position[2]=0x50030010;
	led_position[3]=0x50030020;
	led_position[4]=0x50030040;
	led_position[5]=0x50030080;
	led_position[6]=0x50020100;
	led_position[7]=0x50020200;
}

//function to setting up the direction of GPIOPIN (input/output)
void gpio_setup_led () {
	regs[REG_AHBCLKCTRL] |= REG_AHBCLKCTRL_GPIO;
	/*
	initialize hw setting up the IO pin
	if DIR 0=read, else 1=write
	function dir setting: 0,1,2,3,4,5 ouptut --> 0..011-1111, hex 0x3f
	#define SET_GPIO3DIR	0x3f
	regs[REG_GPIO3DIR]=SET_GPIO3DIR;
	*/
	regs[REG_GPIO3DIR]=0x3f;
	/*
	function dir setting: 6,7 ouptut --> 0..0-1100-0000, hex 0xc0
	#define SET_GPIO2DIR	0xc0
	regs[REG_GPIO2DIR]=SET_GPIO2DIR;
	*/
	regs[REG_GPIO2DIR]=0xc0;
	//NOTE BUTTON 1 is dir=0 in GPIO2_9--> OK 0xc0;
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
