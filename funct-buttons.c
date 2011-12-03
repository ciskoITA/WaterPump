#include "funct-buttons.h"
#include "hw.h"

int button1_pressed(void) {
	#if 0
	button 1 on gpio2: 512 if is NOT pressed, 0 if it pressed
	return 1 if pressed, 0 if NOT pressed
	#endif
	if ((regs[REG_BUT1])==0) {
		return 1;
	}
	else {
		return 0;
	}
}
int button2_pressed(void) {
	#if 0
	button 2 on gpio1: 16 if is NOT pressed, 0 if it pressed
	return 1 if pressed, 0 if NOT pressed
	#endif
	if ((regs[REG_BUT2])==0) {
		return 1;
	}
	else {
		return 0;
	}
}
int button3_pressed(void) {
	if((regs[REG_BUT3])==0) {
		return 1;
	}
	else {
		return 0;
	}
}
