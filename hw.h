#include <stdint.h>

extern volatile uint32_t regs[];

#define THOS_QUARTZ		(12 * 1000 * 1000)
#define HZ			100


/* uart */
#define REG_U0THR		(0x40008000 / 4)
#define REG_U0LSR		(0x40008014 / 4)
#define REG_U0LSR_THRE		0x20

/* clock control */
#define REG_AHBCLKCTRL		(0x40048080 / 4)
#define REG_AHBCLKCTRL_CT32B0	(1 << 9)
#define REG_AHBCLKCTRL_CT32B1	(1 << 10)
#define REG_AHBCLKCTRL_GPIO	(1 << 6)

/* counter 0 */
#define REG_TMR32B0TCR		(0x40014004 / 4)
#define REG_TMR32B0TC		(0x40014008 / 4)
#define REG_TMR32B0PR		(0x4001400c / 4)
#define REG_TMR32B0MCR		(0x40014014 / 4)
#define REG_TMR32B0MR0		(0x40014018 / 4)
#define REG_TMR32B0MR1		(0x4001401c / 4)
#define REG_TMR32B0MR2		(0x40014020 / 4)
#define REG_TMR32B0MR3		(0x40014024 / 4)
#define REG_TMR32B0PWMC		(0x40014074 / 4)

/* counter 1 */
#define REG_TMR32B1TCR		(0x40018004 / 4)
#define REG_TMR32B1TC		(0x40018008 / 4)
#define REG_TMR32B1PR		(0x4001800c / 4)

/* gpio port 3 */
#define REG_GPIO3DAT		(0x50033ffc / 4)
#define REG_GPIO3DIR		(0x50038000 / 4)

/* GPIO PORT 1 --> water pump read level
4bits used:
GPIO1_0 : GPIO1_2 the 3 bits used to read the level from 74148,
GPIO1_3 is NOT[NOT(GS)*EO] from 74148 to detect overflow --> I have 8 standard level (values 0 to 7) plus another for warning function */
#define REG_GPIO1DAT		(0x50013ffc / 4)
#define REG_GPIO1DIR		(0x50018000 / 4)

//for DIR 0=read, 1=write
//to read a single bit use PIO1_n
#define PIO1_0			(0x50013ffc / 4)
#define PIO1_1			(0x50013ffd / 4)
#define PIO1_2			(0x50013ffe / 4)
#define PIO1_3			(0x50013fff / 4)

/* GPIO PORT 1 --> water pump output funtion
2 functions:
GPIO1_4 for pump on/off,
GPIO1_5 for buzzer */
#define PIO1_4			(0x50014000 / 4)
#define PIO1_5			(0x50014001 / 4)
