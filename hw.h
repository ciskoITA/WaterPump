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

/* gpio BASE register */
#define REG_GPIOxBASE		0x50000000
#define REG_GPIOxDAT		0x3ffc
#define REG_GPIOxDIR		0x8000

/* gpio port 1 */
#define PORT_GPIO1		1
#define REG_GPIO1DAT		((REG_GPIOxBASE + (PORT_GPIO1 << 16)) + REG_GPIOxDAT) / 4 // (0x50013ffc / 4)
#define REG_GPIO1DIR		((REG_GPIOxBASE + (PORT_GPIO1 << 16)) + REG_GPIOxDIR) / 4 // (0x50018000 / 4)

/* gpio port 2 */
#define PORT_GPIO2		2
#define REG_GPIO2DAT		((REG_GPIOxBASE + (PORT_GPIO2 << 16)) + REG_GPIOxDAT) / 4 // (0x50023ffc / 4)
#define REG_GPIO2DIR		((REG_GPIOxBASE + (PORT_GPIO2 << 16)) + REG_GPIOxDIR) / 4 // (0x50028000 / 4)

/* gpio port 3 */
#define PORT_GPIO3		3
#define REG_GPIO3DAT		((REG_GPIOxBASE + (PORT_GPIO3 << 16)) + REG_GPIOxDAT) / 4 // (0x50033ffc / 4)
#define REG_GPIO3DIR		((REG_GPIOxBASE + (PORT_GPIO3 << 16)) + REG_GPIOxDIR) / 4 // (0x50038000 / 4)

//============== SETUP ==========================
//============== GPIO 1 =========================
/* gpio port 1 --> water pump input
4 bits used:
GPIO1_0 to GPIO1_2 the 3 bits used to read the level from 74148,
GPIO1_3 is NOT[NOT(GS)&EO] from 74148 to detect overflow --> I have 8 standard level (values 0 to 7) plus another for warning function */
// LEVEL
#define CFG_LEVEL_PORT		1
#define CFG_LEVEL_MASK		7
#define CFG_LEVEL_SHIFT		0 // offset relative to the bit in position 0, in this case offset is 0
#define LEVEL_GPIO_BASE		(REG_GPIOxBASE + (CFG_LEVEL_PORT << 16))
#define REG_LEVEL		(LEVEL_GPIO_BASE + (CFG_LEVEL_MASK << (2+CFG_LEVEL_SHIFT))) / 4 /* port 1 bits 2:0 --> 0x5001001c read value from 0 to 7, shift is 0 because I read first 3 bits */
#define DIR_LEVEL		0 //input
// WARNING
#define CFG_WARNING_PORT	1
#define CFG_WARNING_BIT		3
#define WARNING_GPIO_BASE	(REG_GPIOxBASE + (CFG_WARNING_PORT << 16))
#define REG_WARNING		(WARNING_GPIO_BASE + (4 << CFG_WARNING_BIT)) / 4 /* port 1, bit 3 --> 0x50010020 read value !=0 (8) if WARNING==true */
#define DIR_WARNING		0 //input
/* gpio port 1 --> water pump output
2 bits used:
GPIO1_10 for pump on/off,
GPIO1_11 for alarm */
// POWER
#define CFG_POWER_PORT		1
#define CFG_POWER_BIT		10
#define POWER_GPIO_BASE		(REG_GPIOxBASE + (CFG_POWER_PORT << 16))
#define REG_POWER		(POWER_GPIO_BASE + (4 << CFG_POWER_BIT)) / 4 /* port 1, bit 10 --> 0x50011000 to set pump on/off */
#define DIR_POWER		1 //output
// ALARM
#define CFG_ALARM_PORT		1
#define CFG_ALARM_BIT		11
#define ALARM_GPIO_BASE		(REG_GPIOxBASE + (CFG_ALARM_PORT << 16))
#define REG_ALARM		(ALARM_GPIO_BASE + (4 << CFG_ALARM_BIT)) / 4 /* port 1, bit 11 --> 0x50012000 to set alarm on/off */
#define DIR_ALARM		1 //output

// gpio port 1 --> button 2 : GPIO1_4, input
#define CFG_BUT2_PORT		1
#define CFG_BUT2_BIT		4
#define BUT2_GPIO_BASE		(REG_GPIOxBASE + (CFG_BUT2_PORT << 16))
#define REG_BUT2		(BUT2_GPIO_BASE + (4 << CFG_BUT2_BIT)) / 4 /* port 1, bit 4 --> 0x50010040 to read button2 */
#define DIR_BUT2		0 //input

//============== GPIO 2 =========================
// gpio port 2 --> button 1 : GPIO2_9, input
#define CFG_BUT1_PORT		2
#define CFG_BUT1_BIT		9
#define BUT1_GPIO_BASE		(REG_GPIOxBASE + (CFG_BUT1_PORT << 16))
#define REG_BUT1		(BUT1_GPIO_BASE + (4 << CFG_BUT1_BIT)) / 4 /* port 2, bit 9 --> 0x50020800 to read button1 */
#define DIR_BUT1		0 //input

// gpio port 2 --> led 4:7, GPIO2_4 : GPIO2_7, output
#define CFG_LED47_PORT		2
#define CFG_LED47_MASK		15
#define CFG_LED47_SHIFT		4 // offset relative to the bit in position 0, in this case offset is 4
#define LED47_GPIO_BASE		(REG_GPIOxBASE + (CFG_LED47_PORT << 16))
#define REG_LED47		(LED47_GPIO_BASE + (CFG_LED47_MASK << (2+CFG_LED47_SHIFT))) / 4
#define DIR_LED47		1 //output

//============== GPIO 3 =========================
// gpio port 3 --> led 0:3, GPIO2_0 : GPIO2_3, output
#define CFG_LED03_PORT		3
#define CFG_LED03_MASK		15
#define CFG_LED03_SHIFT		0 // offset relative to the bit in position 0, in this case offset is 0
#define LED03_GPIO_BASE		(REG_GPIOxBASE + (CFG_LED03_PORT << 16))
#define REG_LED03		(LED03_GPIO_BASE + (CFG_LED03_MASK << (2+CFG_LED03_SHIFT))) / 4
#define DIR_LED03		1 //output
