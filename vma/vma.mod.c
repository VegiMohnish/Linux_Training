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
	{ 0x8e6402a9, "module_layout" },
	{ 0x4caf37f7, "param_ops_int" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xfe5cf5ad, "cdev_del" },
	{ 0xc959d152, "__stack_chk_fail" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0xc0fdf3d5, "cdev_add" },
	{ 0xf4161c9f, "cdev_init" },
	{ 0x195bd423, "remap_pfn_range" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4033F08BB5939F57ABF377F");
