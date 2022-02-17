#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>		/* kmalloc() */
#include<linux/uaccess.h>	/* copy_to/from_user() */
#include <linux/kthread.h>	/* kernel threads */
#include <linux/sched.h>	/* task_struct */
#include <linux/delay.h>


dev_t dev = 0;
static struct class *dev_class;
static struct cdev my_cdev;
 
static int __init my_driver_init(void);
static void __exit my_driver_exit(void);
 
static struct task_struct *my_thread;

/* driver functions */
static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t my_write(struct file *filp, const char *buf, size_t len, loff_t * off);

int thread_function(void *pv);

/* thread */
int thread_function(void *pv)
{
    int i=0;
    while(!kthread_should_stop()) {
        pr_info("Inside the Thread Function %d\n", i++);
        msleep(1000);
    }
    return 0;
}

/* file operations structure */
static struct file_operations fops =
{
        .owner		= THIS_MODULE,
        .read           = my_read,
        .write          = my_write,
        .open           = my_open,
        .release        = my_release,
};

/* this function is called when we open the device file */
static int my_open(struct inode *inode, struct file *file)
{
        printk("Device File Opened...\n");
        return 0;
}

/* this function is called when we close the device file */
static int my_release(struct inode *inode, struct file *file)
{
        printk("Device File Closed...\n");
        return 0;
}

/* this function is called when we read the device file */
static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        printk("Read function\n");
        return 0;
}

/* this function is called when we write the device file */
static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        printk("Write Function\n");
        return len;
}

/* module init function */
static int __init my_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "my_Dev")) <0){
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        printk("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&my_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&my_cdev,dev,1)) < 0){
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"my_class")) == NULL){
            pr_err("Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"my_device")) == NULL){
            pr_err("Cannot create the Device \n");
            goto r_device;
        }
 
        /* You can use this method to create and run the thread */
        my_thread = kthread_run(thread_function,NULL,"my Thread");
        if(my_thread) {
            pr_info("Kthread Created Successfully...\n");
        } else {
            pr_err("Cannot create kthread\n");
             goto r_device;
        }

        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        cdev_del(&my_cdev);
        return -1;
}

/* Module exit function */  
static void __exit my_driver_exit(void)
{
        kthread_stop(my_thread);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(my_driver_init);
module_exit(my_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vegi Mohnish");
MODULE_DESCRIPTION("A simple device driver - Kernel Thread");

