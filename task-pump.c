#include "thos.h"
#include "hw.h"
#include "funct-pump.h"
#include "funct-led.h"
#include "task-pump.h"

static int level_on, level_off, empty;
static int max=7;
static int min=0;

static int pump_init(void *unused)
{
	//initialize hw
	//setting up the IO pin
	gpio_setup_pump();
	//at startup PUMP & ALARM off
	pump_power(0);
	alarm_power(0);
	//default level
	level_on=4;
	level_off=2;
	//empty=OFF
	empty=0;

	//gpio_setup_led();
	//led_status(0, 1);

	puts("setup complete\n");
	return 0;
}

static void *pump(void *arg)
{
	if(empty==1) { //empties the tank until the minimum level set
		if (read_level()==level_off) {
			pump_power(0); //pump off
			empty=0;
		}
		return (void*) read_level();
	}/* use empty method if you would to force the emptying of the tank for maintenance, to prepare the tank to receive a large influx of water or other */
	
	else {
		empty=0;
		//read old value and write to serial	
		int old_value=(int)arg;
		puts("Old state: ");
		putint(old_value);
		puts(" / ");
		//read new value
		int value=read_level();

		//write value to serial	
		puts("Read: ");
		putint(value);
		puts(" / ");

		//check value readed
		int diff=value-old_value;
		#if 0
		diff>2 example:
		value=5, old_value=3 --> diff=2; ok
		value=5, old_value=2 --> diff=3; error!

		diff<2 example:
		value=3, old_value=5 --> diff=-2; ok
		value=3, old_value=4 --> diff=-1; ok
		value=2; old_value=5 --> diff=-3; error!
		#endif
		if(diff>2 || diff<-2) {
			puts("Error! Diff read: ");
			putint(diff);
			puts("!!!! / "); // !!!! plus standard spacing

			//read it again //and if the data is still wrong, use the worst case
			int new_read=read_level();
			puts("New Read: ");
			putint(new_read);
			puts(" / ");
			#if 0
			if(value<new_read) {
				//use the worst case
				//value=new_read;
			
				//print info
				puts("New Read: ");
				putint(new_read);
				puts(" / ");
			}
			#endif
			//else value=value
		}
	
		//DEFAULT: values from 0 to 4 are ok, if it is 5 or greater: pump on, if it is 7 buzzer on
		//when pump is on, turn it off only when level is 2 to avoid damage due to multiple on/off
		if(value>level_on) {
			pump_power(1); //pump on
			if(value==7) {
				alarm_power(1); //alarm on
				if (read_warning()==1){
					puts("WARNING=TRUE!!!");
					//1: Warning=TRUE
					//ok, warning but do nothing for now			
				}
			}//end if
			else {
				alarm_power(0); //alarm off
			}
		}//end if
		//else value<=4; if <=2 pump off
		else if (value<=level_off) {
			pump_power(0); //pump off
			alarm_power(0); //alarm off
		}
		//else value is 3 or 4, if the pump is on leave it on, else the pump is off and leave it off
		else {
		}
		puts("\n");
		return (void*) value;
	}
}//end task

int get_level_on(void) {
	return level_on;
}

int get_level_off(void) {
	return level_off;
}

void set_level_on(int val) {
	if (val>max) {
		val=min;
	}
	if (val<min) {
		val=max;
	}
	level_on=val;
}

void set_level_off(int val) {
	if (val>max) {
		val=min;
	}
	if (val<min) {
		val=max;
	}
	level_off=val;
}

void check_level(void) {
	if (level_off==level_on) {
		set_level_off(level_off--);
		check_level(); //is possible to set a value <0, --> use function and a new check
	}
	if (level_off>level_on) { //swap
		int tmp=level_off;
		level_off=level_on;
		level_on=tmp;
	}
}

void set_empty() {
	empty=1;
	pump_power(1); //pump on
}

static struct thos_task __task t_pump = {
	.name = "pump", .period = HZ/5,
	.init = pump_init, .job = pump,
};
