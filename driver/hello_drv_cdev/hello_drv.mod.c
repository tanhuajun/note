#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x5b7cbb39, "module_layout" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x85e0fd11, "cdev_del" },
	{ 0xc82061a5, "class_destroy" },
	{ 0xf6ce8152, "device_destroy" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x8feff010, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xe54da6c2, "__class_create" },
	{ 0xa3829e08, "cdev_add" },
	{ 0x7fd3cbfa, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x92997ed8, "_printk" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "17832966B823F06334190C3");
