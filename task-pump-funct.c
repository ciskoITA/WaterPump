#include "thos.h"
#include "hw.h"
#include "pump_conv_table.c"
#include "pump-function.c"
#include "led-state.c"

//static int pump_status=0; //0 pump is off, 1 pump is on

static int pump_init(void *unused)
{
	//initialize hw
	//setting up the IO pin
	gpio_Setup();
	//at startup PUMP & ALARM off
	pump_Off();
	alarm_Off();
	
	//pump_status=0;
	//next version read first level when initialize

	//init led
	int led_ok=led_init(0);
	
	//write init status	
	puts("led init: ");
	serial_write(led_ok);
	puts(" - ");
	
	if (led_ok==0) {
		return 0;
	}
	else {
		return -1;
	}
}

static void *pump(void *arg)
{
	//read old value and write to serial	
	int old_value=(int)arg;
	puts("Old state: ");
	serial_write(old_value);
	puts(" - ");
	//read new value
	int value=read_Level();

	//write value to serial	
	puts("Readed: ");
	serial_write(value);
	puts(" - ");
	//turn on the led
	led((void*)value);

	//check value readed
	int diff=value-old_value;
	/*
	diff>2 example:
	value=5, old_value=3 --> diff=2; ok
	value=5, old_value=2 --> diff=3; error!

	diff<2 example:
	value=3, old_value=5 --> diff=-2; ok
	value=3, old_value=4 --> diff=-1; ok
	value=2; old_value=5 --> diff=-3; error!
	*/
	if(diff>2 || diff<-2) {
		puts("Error! Diff readed: ");
		if (diff<0) {
			puts("-");
			diff=0-diff; //transform negative number to positive
		}
		serial_write(diff);
		puts("!!!! - "); // !!!! plus standard spacing

		//read it again and if the data is still wrong, use it anyway
		value=regs[LEVEL];
	}
	
	//values from 0 to 4 are ok, if it is 5 or greater: pump on, if it is 7 buzzer on
	//when pump is on, turn it off only when level is 2 to avoid damage due to multiple on/off
	if(value>4) {
		pump_On();
		//pump_status=1;
		if(value==7) {
			alarm_On();
			if (read_Warning()==1){
			//1: Warning=TRUE
			//ok, warning but do nothing for now			
			}
		}//end if
		alarm_Off();
	}//end if
	//else value<=4; if <=2 pump off
	else if (value<=2) {
		//regs[POWER]=POWER_OFF;
		pump_Off();
		alarm_Off();
		//pump_status=0;
	}
	//else value is 3 or 4, if the pump is on leave it on, else the pump is off and leave it off
	else {
	}
	
	return (void*) value;
}//end task

static struct thos_task __task t_pump = {
	.name = "pump", .period = HZ,
	.init = pump_init, .job = pump,
	.release = 10
};
