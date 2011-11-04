#include "thos.h"
#include "hw.h"

static int pump_status=0; //0 pump is off, 1 pump is on

static int pump_init(void *unused)
{
	//initialize hw
	//setting the IO pin
	regs[REG_GPIO1DIR]=SET_GPIO1DIR;
	//at startup PUMP & BUZZER off
	regs[POWER]=POWER_OFF;
	regs[BUZZER]=BUZZER_OFF;
	
	pump_status=0;
	return 0;
	//next version read first level when initialize
}

static void *pump(void *arg)
{
	//read value
	value=regs[LEVEL];
	//or value=(regs[LEVEL])&LEVEL_MASK;
	
	//values from 0 to 4 are ok, if 5 or greather pump on, 7 buzzer on
	//when pump is on, turn it off only when level is 2 to avoid damage due to multiple on/off
	/*switch(value) {
		case 0 {
			regs[POWER]=POWER_OFF;
			pump_status=0;
		}
		case 1 {WARNI
			regs[POWER]=POWER_OFF;
			pump_status=0;
		}
		case 2 {
			regs[POWER]=POWER_OFF;
			pump_status=0;
		}
		case 3 {
			if (pump_status=1) {
				regs[POWER]=POWER_ON;
			pump_status=1;
			}
		}
	}*/
	if(value>4) {
		regs[POWER]=POWER_ON;
		pump_status=1;
		if(value==7) {
			regs[BUZZER]=BUZZER_ON;
			if (WARNING==8){
			//ok, warning but do nothing for now			
			}
		}//end value 7
		regs[BUZZER]=BUZZER_OFF;
	}//end if
	//else value<=4; if <=2 pump off
	else if (value<=2) {
		regs[POWER]=POWER_OFF;
		pump_status=0;
	}
	//else value is 3 or 4, if the pump is on leave it on, else the pump is off and leave it off
	else {
	}
	

	//next version returns the value just read to the next cicle
}

static struct thos_task __task t_led = {
	.name = "pump", .period = HZ / 2,
	.init = pump_init, .job = pump,
	.release = 10
};
