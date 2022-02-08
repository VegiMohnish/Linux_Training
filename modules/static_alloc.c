#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>

/* creating the dev with custom minor and major number */
dev_t dev = MKDEV(235,0);

/* module init function */
static int __init scull_init(void)
{
	register_chrdev_region(dev,1,"scull");
	printk(KERN_INFO "Static Allocation of major and minor number\n");
	printk(KERN_INFO "Major = %d , Minor = %d \n",MAJOR(dev), MINOR(dev));
	printk(KERN_INFO "Kernel Module Inserted Successfully \n");
	return 0;
}

/* module exit function */
static void __exit scull_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Kernel Module Removed Successfully \n");
}

module_init(scull_init);
module_exit(scull_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vegi Mohnish");
MODULE_DESCRIPTION("Static allocation of major and minor number");

