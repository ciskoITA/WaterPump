#include "hw.h"
#include "thos.h"
#include "task-pump.h"
#include "funct-buttons.h"

//static int lvl_on_off=1; //if=0 setup for level_on if=1 setup for level_off
static int default_timer=10;
static int timer;
static int but_press=0;

static int buttons_init(void *unused)
{
	timer=default_timer;
	puts("setup complete\n");
	return timer; //not passed to button --> NO buttons(timer) BUT buttons(0)
}

static void *buttons(void *arg)
{
	timer=(int)arg; //timer start from 0 at startup
	if(button1_pressed()==1) { //if pressed
		set_level_on(get_level_on()+1);
		timer=default_timer; //update timer for countdown
		but_press=1;
		puts("New level on set: ");
		putint(get_level_on());
		puts("\n");
	}
	if(button2_pressed()==1) { //if pressed
		set_level_off(get_level_off()-1);
		timer=default_timer; //update timer for countdown
		but_press=1;
		puts("New level off set: ");
		putint(get_level_off());
		puts("\n");
	}
	if (but_press==1 && timer==0) {
		check_level(); //check correct value of 2 levels
		puts("Final level set: On: ");
		putint(get_level_on());
		puts(" Off: ");
		putint(get_level_off());
		puts("\n");
	}
	return (void*) (timer-1);
}//end task

static struct thos_task __task t_buttons = {
	.name = "buttons", .period = HZ/2,
	.init = buttons_init, .job = buttons,
	.release = 2
};
