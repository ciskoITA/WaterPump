#include "funct-buttons.h"
#include "funct-general.h"
#include "hw.h"

int button1_pressed(void) {
	#if 0
	button 1 on gpio2: 512 if is NOT pressed, 0 if it pressed
	return 1 if pressed, 0 if NOT pressed
	equal to:
	int mask=create_mask_bit(BIT_BUT1);
	int value=read_from_register(REG_GPIO2DAT, mask);
	if (value==0) ...
	#endif
	if (read_from_register(REG_GPIO2DAT, create_mask_bit(BIT_BUT1))==0) {
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
	equal to:
	int mask=create_mask_bit(BIT_BUT2);
	int value=read_from_register(REG_GPIO1DAT, mask);
	if (value==0) ...
	#endif
	if (read_from_register(REG_GPIO1DAT, create_mask_bit(BIT_BUT2))==0) {
		return 1;
	}
	else {
		return 0;
	}
}
