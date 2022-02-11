#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>

dev_t dev = 0;

/* module init function */
static int __init scull_init(void)
{
	/* allocating major number */
	if((alloc_chrdev_region(&dev,0,1,"scull")) < 0) {
		printk(KERN_INFO "Cannot allocate major number for the device \n");
		return -1;
	}
	printk("Dynamic Allocation of major and minor number\n");
	printk(KERN_INFO "Major = %d , Minor = %d \n",MAJOR(dev), MINOR(dev));
	printk(KERN_INFO "Kernel Module Inserted Successfully \n");
	return 0;
}

/* Module exit function */
static void __exit scull_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Kernel Module Removed Successfully \n");
}

module_init(scull_init);
module_exit(scull_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vegi Mohnish");
MODULE_DESCRIPTION("Dynamic Allocation of major and minor number\n");


