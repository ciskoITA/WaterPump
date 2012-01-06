#include "thos.h"
#include "hw.h"

int thos_setup(void)
{
	regs[REG_AHBCLKCTRL] |= REG_AHBCLKCTRL_CT32B1;

	/* enable timer 1, and count at HZ Hz (currently 100) */
	regs[REG_TMR32B1TCR] = 1;
	regs[REG_TMR32B1PR] = (THOS_QUARTZ / HZ) - 1;
	return 0;
}

void putc(int c)
{
	if (c == '\n')
		putc('\r');
	while ( !(regs[REG_U0LSR] & REG_U0LSR_THRE) )
		;
	regs[REG_U0THR] = c;
}

void puts(char *s)
{
	while (*s)
		putc (*s++);
}

void putint_inner(int val) {
	/*1234
	1234/10=123 remainder 4
	123/120=12 remainder 3
	12/10=1 remainder 2
	1/10=0 remainder 1
	--> print 1, print 2, print 3, print 4
	-----> number<10? print the remainder in LIFO mode
	*/
	int div=val/10;
	if (val>9) {
		putint_inner(div);		
	}
	int remainder=val%10;
	putc((0x30|remainder));
}

void putint(int val) {
	if (val<0) {
		puts("-");
		val=0-val;
	}
	putint_inner(val);
}
