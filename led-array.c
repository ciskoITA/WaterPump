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

unsigned int led_pos(int pos) {
	return led_position[pos];
}
