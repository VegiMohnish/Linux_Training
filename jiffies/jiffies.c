#include<linux/jiffies.h>
#include<linux/time.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int	__init my_driver_init(void);
static void	__exit my_driver_exit(void);

unsigned long j_start, j_end, j_diff;

static int __init my_driver_init(void)
{
	j_start = jiffies;
	printk("Module started.... \njiffies start time: %lu\n",j_start);
	return 0;
}


static void __exit my_driver_exit(void)
{
	j_end = jiffies;
	printk("jiffies end time: %lu\n",j_end);
	j_diff = (long)j_end - (long)j_start;
	printk("total elapsed time in jiffies: %lu\n",j_diff);
	printk("total elapsed time in seconds: %lu\n", j_diff/HZ);
	printk("Module Removed....");	
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vegi Mohnish");
MODULE_DESCRIPTION("Jiffies counter");
