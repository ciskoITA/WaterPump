#include "funct-general.h"
#include "hw.h"

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
