#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include "led_opr.h"

static int rasp_led_init(int witch) {
	printk("%s %s line %d, led %d\n", __FILE__, __FUNCTION__, __LINE__, witch);

	
	return 0;
}

static int rasp_led_ctl(int witch, int status) {
	printk("%s %s line %d, led %d, %s\n", __FILE__, __FUNCTION__, __LINE__, witch, status ? "on" : "off");
	

	return 0;
}


struct led_operations rasp_led_opr = {
	.num  = 2,
	.init = rasp_led_init,
	.ctl  = rasp_led_ctl
};

struct led_operations *get_board_led_opr(void) {
	return &rasp_led_opr;
}


