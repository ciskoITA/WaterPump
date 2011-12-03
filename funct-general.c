#include "funct-general.h"
#include "hw.h"
#include "thos.h"
int array_dir[3]; //use to set REG_GPIOxDIR

#if 0
int create_mask_bit(int bit) {
	//example: mask 0...010, bit to mask: 1 --> 1<<1: 01<<1=010
	return (1<<bit);
}

int read_from_register(int reg, int mask) {
	//read value from REG_GPIOxDAT and do an AND with the mask
	return ((regs[reg])&(mask));
}

void write_to_register(int reg, int mask, int val, int bit) {
	#if 0
	example: write 1 in bit 10 of GPIO1
	REG_GPIO1DAT=0x50013ffc AND 0xffff0000 = 0x5001-0000
	mask<<2 --> 1-0000-0000-0000=0x1000
	0x5001-0000 OR (mask<<2)= 0x5001-0000 | 0x1000 = 0x5001-1000
	write 1: regs[0x5001-1000]=(1<<10)

	NOTE:
	if I would to write more than 1 bit pass correct mask and: or a shifted val and bit=0 or correct val with bit=correct shift
	example: write 11=3 in bit  4 and 5 of a GPIO: mask is 11-0000 in bit=0x30
	0x500y-0000
	mask<<2 0x30<<2 = 1100-0000 = 0xc0
	0x500y-0000 | 0xc0 = 0x500y-00c0
	write case 1: val=3, bit=4
	regs[0x500y-00c0]=(3<<4)
	write case 2: val=48 (for 3) and bit=0
	regs[0x500y-00c0]=(48<<0)
	#endif
	int reg_final=reg&(0xffff0000); //500y-0000
	int tmp_mask=(mask<<2);
	reg_final=reg_final|tmp_mask;
	regs[reg_final]=(val<<bit);
}
#endif

void set_gpiodir_bit(int port, int dir, int bit) {
	array_dir[(port-1)] |=(dir<<bit);
}
void set_gpiodir_multi(int port, int dir, int mask, int shift) {
	array_dir[(port-1)] |=((mask<<shift)*dir);
}

int setup_gpio(void) {
	puts("gpio setup: ");
	array_dir[0]=0x0; //for gpiodir1
	array_dir[1]=0x0; //for gpiodir2
	array_dir[2]=0x0; //for gpiodir3
	
	//gpio1
	set_gpiodir_multi(CFG_LEVEL_PORT, DIR_LEVEL, CFG_LEVEL_MASK, CFG_LEVEL_SHIFT); //set level
	set_gpiodir_bit(CFG_WARNING_PORT, DIR_WARNING, CFG_WARNING_BIT); //set warning
	set_gpiodir_bit(CFG_POWER_PORT, DIR_POWER, CFG_POWER_BIT); //set power
	set_gpiodir_bit(CFG_ALARM_PORT, DIR_ALARM, CFG_ALARM_BIT); //set alarm
	set_gpiodir_bit(CFG_BUT2_PORT, DIR_BUT2, CFG_BUT2_BIT); //set but2
	puts("gpio1: ");
	putint(array_dir[0]);
	puts(" - ");
	
	//gpio2
	set_gpiodir_bit(CFG_BUT1_PORT, DIR_BUT1, CFG_BUT1_BIT); //set but1
	set_gpiodir_multi(CFG_LED47_PORT, DIR_LED47, CFG_LED47_MASK, CFG_LED47_SHIFT); //set led47
	puts("gpio2: ");
	putint(array_dir[1]);
	puts(" - ");	
	
	//gpio3
	set_gpiodir_multi(CFG_LED03_PORT, DIR_LED03, CFG_LED03_MASK, CFG_LED03_SHIFT); //set led03
	puts("gpio3: ");
	putint(array_dir[2]);
	puts(" - ");
	
	regs[REG_GPIO1DIR]=array_dir[0];
	regs[REG_GPIO2DIR]=array_dir[1];
	regs[REG_GPIO3DIR]=array_dir[2];
	puts("\n");
	return 1; //1 if all ok
}

#if 0 //old version of setup_gpio
int setup_gpio(void) {
	puts("gpio setup: ");
	
	//gpio1
	int d1=0x0;
	d1=d1|((CFG_LEVEL_MASK << CFG_LEVEL_SHIFT)*DIR_LEVEL);
	d1=d1|(DIR_WARNING << CFG_WARNING_BIT);
	d1=d1|(DIR_POWER << CFG_POWER_BIT);
	d1=d1|(DIR_ALARM << CFG_ALARM_BIT);
	d1=d1|(DIR_BUT2 << CFG_BUT2_BIT);
	puts("gpio1: ");
	putint(d1);
	puts(" - ");
	regs[REG_GPIO1DIR]=d1;
	
	//gpio2
	int d2=0x0;
	d2=d2| (DIR_BUT1 << CFG_BUT1_BIT);
	puts("gpio2: ");
	putint(d2);
	puts(" - ");
	regs[REG_GPIO2DIR]=d2;
	
	//gpio3
	int d3=0x0;
	puts("gpio3: ");
	putint(d3);
	puts(" - ");
	regs[REG_GPIO3DIR]=d3;

	puts("\n");
	return 1; //1 if all ok
}
#endif

int setup(void) {
	int setup_ok=1; //1 if all ok
	setup_ok=(setup_ok) & (setup_gpio());
	//other if necessary
	return setup_ok;
}
