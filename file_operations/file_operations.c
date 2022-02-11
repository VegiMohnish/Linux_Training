#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h> /* for the character driver support */

static int __init main_init(void);
static void __exit main_exit(void);
static int main_open(struct inode *inode, struct file *file);
static ssize_t main_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t main_write(struct file *filp, const char *buf, size_t len, loff_t *off);
static int main_release(struct inode *inode, struct file *file);

/* to hold the file operations performed on this device */
/* variable that contains the type of operations performed on this device */
static struct file_operations char_file_operations = {
	/* functions for performing the file operations  */
	.owner   = THIS_MODULE,
	.open    = main_open,
	.read    = main_read,
	.write   = main_write,
	.release = main_release,	
};

static int main_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Inside the %s function \n" , __FUNCTION__);
	return 0;
}

static ssize_t main_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Inside the %s function \n" , __FUNCTION__);
	return 0;
}

static ssize_t main_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Inside the %s function \n" , __FUNCTION__);
	return len;
}

static int main_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Inside the %s function \n", __FUNCTION__);
	return 0;
}


/* when this init function is called it will register the char device driver with the kernel */
static int __init main_init(void)
{
	printk(KERN_INFO "Inside the %s function \n", __FUNCTION__);
	/* register with the kernel and indicate that we are registering a character device driver */
	register_chrdev(220 /*major number*/,
			"simple char driver" /* name of the driver */,
			&char_file_operations /*file operations */);

	return 0;

}

void __exit main_exit(void) 
{
	printk(KERN_INFO "Inside the %s function \n", __FUNCTION__);

	/* unregister the character device driver */
	unregister_chrdev(220, "simple char driver");
}

module_init(main_init);
module_exit(main_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vegi Mohnish");
MODULE_DESCRIPTION("file operations");
