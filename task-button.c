#include "hw.h"
#include "thos.h"
#include "task-pump.h"
#include "funct-button.h"

static int lvl_on_off=1; //if=0 setup for level_on if=1 setup for level_off
static int default_but_timer=10;
static int select_but_timer;

/*static void update_but_timer() {
	select_but_timer=30*THOS_QUARTZ;
}

static void switch_lvl_on_off() {
	if (lvl_on_off==1) {
		lvl_on_off=0;
	}
	else {
		lvl_on_off=1;
}*/

static int button_init(void *unused)
{
	select_but_timer=default_but_timer;
	puts("setup complete\n");
	return 0;
}

static void *button(void *arg)
{
	if(button1_pressed()==1) { //if pressed
		if(lvl_on_off==1) { //lvl_on
			set_level_on(get_level_on()+1);
		}
		else {
			set_level_off(get_level_off()-1);
		}
		check_level();
		puts("New level - On: ");
		putint(get_level_on());
		puts(" Off: ");
		putint(get_level_off());
		puts("\n");
		//sleep for 1/2 second
		int sleep;
		for (sleep=0; sleep<(THOS_QUARTZ); sleep++) {
			//sleep
		}
		select_but_timer=default_but_timer; //counter to select to set level on or level off
	}
	select_but_timer--;
	if (select_but_timer==0) {
		puts("switch possible\n");
		//switch lvl_on_off();
		if (lvl_on_off==1) {
			lvl_on_off=0;
		}
		else {
			lvl_on_off=1;
		}
	}
	return (void*) 0;
}//end task

static struct thos_task __task t_button = {
	.name = "button", .period = HZ/2,
	.init = button_init, .job = button,
	.release = 2
};
