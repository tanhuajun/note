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
#include <asm/io.h>
#include "led_opr.h"

#define PH_GPIO_REG_BASE_ADD            0x47e200000
#define OFFSET_GPFSEL2                  0x08
#define OFFSET_GPIO_PUP_PDN_CNTRL_REG1  0xe8
#define OFFSET_GPSET0                   0x1c
#define OFFSET_GPCLR0                   0x28

#define PH_GPFSEL2_REG_ADD              PH_GPIO_REG_BASE_ADD + OFFSET_GPFSEL2
#define PH_GPIO_PUP_PDN_CNTRL_REG1      PH_GPIO_REG_BASE_ADD + OFFSET_GPIO_PUP_PDN_CNTRL_REG1
#define PH_GPSET0                       PH_GPIO_REG_BASE_ADD + OFFSET_GPSET0
#define PH_GPCLR0                       PH_GPIO_REG_BASE_ADD + OFFSET_GPCLR0

static volatile unsigned int *va_gpfsel2;
static volatile unsigned int *va_pup_reg1;
static volatile unsigned int *va_gpset0;
static volatile unsigned int *va_gpclr0;

static int rasp_led_init(int witch) {
	printk("%s %s line %d, led %d\n", __FILE__, __FUNCTION__, __LINE__, witch);

	va_gpfsel2 = ioremap(PH_GPFSEL2_REG_ADD, 4);
	va_pup_reg1 = ioremap(PH_GPIO_PUP_PDN_CNTRL_REG1, 4);
	va_gpset0 = ioremap(PH_GPSET0, 4);
	va_gpclr0 = ioremap(PH_GPCLR0, 4);
	
	switch(witch) {
		case 0:
			//gpio23
			*va_gpfsel2 &= ~(7<<9);
			*va_gpfsel2 |= (1<<9);

			*va_pup_reg1 &= ~(3<<14);
			*va_pup_reg1 |= (1<<15);
		break;

		case 1:
			//gpio24
			*va_gpfsel2 &= ~(7<<12);
			*va_gpfsel2 |= (1<<12);

			*va_pup_reg1 &= ~(3<<16);
			*va_pup_reg1 |= (1<<17);
		break;

		default:
		break;
	}
	
	return 0;
}

static int rasp_led_ctl(int witch, int status) {
	printk("%s %s line %d, led %d, %s\n", __FILE__, __FUNCTION__, __LINE__, witch, status ? "on" : "off");

	switch(witch) {
		case 0:
			if(status == 1)
				*va_gpset0 |= (1<<23);
			else 
				*va_gpclr0 |= (1<<23);
		break;
		case 1:
			if(status == 1)
				*va_gpset0 |= (1<<24);
			else 
				*va_gpclr0 |= (1<<24);
		break;
		default:
		break;
	}

	return 0;
}

void rasp_led_close(void) {
	iounmap(va_gpfsel2);
	iounmap(va_pup_reg1);
	iounmap(va_gpset0);
	iounmap(va_gpclr0);
}


struct led_operations rasp_led_opr = {
	.num   = 2,
	.init  = rasp_led_init,
	.close = rasp_led_close,	
	.ctl   = rasp_led_ctl
};

struct led_operations *get_board_led_opr(void) {
	return &rasp_led_opr;
}


