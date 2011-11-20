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
GPIO1_3 is NOT[NOT(GS)&EO] from 74148 to detect overflow --> I have 8 standard level (values 0 to 7) plus another for warning function */
#define REG_GPIO1DAT		(0x50013ffc / 4)
#define REG_GPIO1DIR		(0x50018000 / 4)
//to read values of water pump
//using the DATAMASK in GPIO1
#define LEVEL			(0x5001001c / 4) //read values from 0 to 7
#define LEVEL_MASK		0x7
//#define WARNING		(0x50010010 / 4)
#define WARNING			(0x50010020 / 4) //read value 8 if WARNING==true
#define WARNING_MASK		0x8
//usage levelread=regs[LEVEL]&LEVEL_MASK

/* GPIO PORT 1 --> water pump output funtion
2 functions:
GPIO1_4 for pump on/off,
GPIO1_5 for buzzer
using DATAMASK */
#define POWER			(0x50010040 / 4) //to set pump on/off
//#define POWER_ON		15
#define POWER_ON		0x10
//#define POWER_OFF		0
#define POWER_OFF		0x0
#define BUZZER			(0x50010080 / 4) //to set buzzer on/off
//#define BUZZER_ON		32
#define BUZZER_ON		0x20
//#define BUZZER_OFF		0
#define BUZZER_OFF		0x0
//usage: regs[POWER]=POWER_ON or POWER_OFF --> pump on/off
//usage: regs[BUZZER]=BUZZER_ON or BUZZER_OFF --> buzzer on/off
//usage regs[POWER]&POWER_ON or POWER_OFF --> pump on/oof

//writing op: bits at 1 into the register select bit to be written. AND operation with the register write bits

//if DIR 0=read, else 1=write
//function dir setting: 0,1,2,3 input, 4,5 ouptut 0000 0018 in hex
//#define SET_GPIO1DIR		18
#define SET_GPIO1DIR		0x30
//to set use regs[REG_GPIO1DIR]=SET_GPIO1DIR


