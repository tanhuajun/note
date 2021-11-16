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

static int major;
struct cdev hello_cdev;

static struct class *hello_class;
static char kernel_buf[1024];
#define MIN(a, b) (a < b ? a : b)

int hello_open(struct inode *node, struct file *file) {
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

ssize_t hello_read(struct file *file, char __user *buf, size_t size, loff_t *offset) {
	int ret;

	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	ret = copy_to_user(buf, kernel_buf, MIN(1024, size));
	return ret;
}

ssize_t hello_write(struct file *file, const char __user *buf, size_t size, loff_t *offset) {
	int ret;

	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	ret = copy_from_user(kernel_buf, buf, MIN(1024, size));
	return ret;
}

int hello_close(struct inode *node, struct file *file) {
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static struct file_operations hello_operations = {
	.owner   = THIS_MODULE,
	.open    = hello_open,
	.read    = hello_read,
	.write   = hello_write,
	.release = hello_close
};
	
static int __init hello_init(void) {
	int ret;
	dev_t devid;
	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
//	major = register_chrdev(0, "hello", &hello_operations);
	alloc_chrdev_region(&devid, 0, 1, "hello");
	major = MAJOR(devid);
	cdev_init(&hello_cdev, &hello_operations);
	cdev_add(&hello_cdev, devid, 1);
	
	hello_class = class_create(THIS_MODULE, "hello_class");
	ret = PTR_ERR(hello_class);
	if(IS_ERR(hello_class)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "hello");
		return -1;
	}
	device_create(hello_class, NULL, MKDEV(major, 0), NULL, "hello");

	return 0;
}

static void __exit hello_exit(void) {
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	device_destroy(hello_class, MKDEV(major, 0));
	class_destroy(hello_class);
//	unregister_chrdev(major, "hello");
	cdev_del(&hello_cdev);
	unregister_chrdev_region(MKDEV(major, 0), 1);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");

/*
1. 确定主设备号
2. 定义file_operation，实现对应的函数
3. 将字符设备和file_operation关联
4. 将字符设备注册进内核
5. 自动创建设备节点 class_create  device_create
*/



