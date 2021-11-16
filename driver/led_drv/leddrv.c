#include <linux/module.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
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


struct led_operations *board_led_opr;
static int major;
struct class *led_class;

static int led_open(struct inode *node, struct file *file) {
	int minor = iminor(node);
	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	board_led_opr->init(minor);
	
	return 0;
}

int led_close (struct inode *node, struct file *file) {
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static ssize_t led_read(struct file *file, char __user *buf, size_t size, loff_t *offset) {
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static ssize_t led_write(struct file *file, const char __user *buf, size_t size, loff_t *offset) {
	int ret;
	struct inode *node = file_inode(file);
	int minor = iminor(node);
	int status;

	ret = copy_from_user(&status, buf, size);

	board_led_opr->ctl(minor, status);

	return 0;
}

struct file_operations led_opr = {
	.owner   = THIS_MODULE,
	.open    = led_open,
	.read    = led_read,
	.write   = led_write,
	.release = led_close
};


static int __init led_init(void) {
	int i, ret;	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

	major = register_chrdev(0, "led", &led_opr);
	
	led_class = class_create(THIS_MODULE, "led_class");
	ret = PTR_ERR(led_class);
	if(IS_ERR(led_class)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "led");
		return -1;
	}
	board_led_opr = get_board_led_opr();
	
	for(i=0; i<board_led_opr->num; i++)
		device_create(led_class, NULL, MKDEV(major, i), NULL, "led%d", i);
	return 0;
}

static void __exit led_exit(void) {
	int i;	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	for(i=0; i<board_led_opr->num; i++)
		device_destroy(led_class, MKDEV(major, i));
	class_destroy(led_class);
	unregister_chrdev(major, "led");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");






