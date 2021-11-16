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
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x1fdc7df2, "_mcount" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x56470118, "__warn_printk" },
	{ 0xf6ce8152, "device_destroy" },
	{ 0xa2f8a949, "__register_chrdev" },
	{ 0xdcb764ad, "memset" },
	{ 0x8feff010, "device_create" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x92997ed8, "_printk" },
	{ 0xc82061a5, "class_destroy" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xe54da6c2, "__class_create" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4723A6B2ED7773D75810E90");
