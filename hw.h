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

/* gpio port 1 --> water pump */
#define REG_GPIO1DAT		(0x50013ffc / 4)
#define REG_GPIO1DIR		(0x50018000 / 4)

/* gpio port 2 --> led 6 and 7 */
#define REG_GPIO2DAT		(0x50023ffc / 4)
#define REG_GPIO2DIR		(0x50028000 / 4)

/* gpio port 3 --> led 0 to 5 */
#define REG_GPIO3DAT		(0x50033ffc / 4)
#define REG_GPIO3DIR		(0x50038000 / 4)

//============== SETUP ==========================
/* gpio port 1 --> water pump input
4 bits used:
GPIO1_0 to GPIO1_2 the 3 bits used to read the level from 74148,
GPIO1_3 is NOT[NOT(GS)&EO] from 74148 to detect overflow --> I have 8 standard level (values 0 to 7) plus another for warning function */
#define LEVEL			(0x5001001c / 4) //read values from 0 to 7
#define WARNING			(0x50010020 / 4) //read value 8 if WARNING==true

/* gpio port 1 --> water pump output
2 bits used:
GPIO1_4 for pump on/off,
GPIO1_5 for alarm */
#define POWER			(0x50010040 / 4) //to set pump on/off
#define ALARM			(0x50010080 / 4) //to set alarm on/off

// gpio port 2 --> button 1
#define BUT1			(0x50020800 / 4) //to read button1
