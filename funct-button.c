#include "hw.h"

int button1_pressed() {
	//regs[BUT1]=512 if is NOT pressed, 0 if it pressed
	//return 1 if pressed, 0 if NOT pressed
	return !((regs[BUT1])>>9);
}
