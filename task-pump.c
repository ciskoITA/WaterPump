#include "thos.h"
#include "hw.h"

static int pump_init(void *unused)
{
	//regs[REG_IODIR] |= 7 << 19; /* gpio 19, 20, 21 */
	//return 0;
	
	//setto i GPIO come pin di lettura
}

static void *pump(void *arg)
{
	/*int i = (int)arg & 7;

	regs[REG_IOSET] = i << 19;
	regs[REG_IOCLR] = (i^7) << 19;
	return (void *)++i;*/
}

static struct thos_task __task t_led = {
	.name = "pump", .period = HZ / 2,
	.init = pump_init, .job = pump,
	.release = 10
};
