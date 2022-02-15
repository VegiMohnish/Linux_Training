/* procfs1.c − create a "file" in /proc */
#include <linux/module.h>    
#include <linux/kernel.h>
#include <linux/proc_fs.h> /* necessary because we use the proc fs  */
#include <linux/uaccess.h> /*for copy_from_user  */
#include <linux/string.h>
#include <linux/vmalloc.h>


#define procfs_max_size		1024
#define procfs_name 		"helloworld"


/* This structure hold information about the /proc file */
struct proc_dir_entry *Our_Proc_File;

/* the buffer used to store character for this module */
static char procfs_buffer[procfs_max_size];

/* the size of the buffer  */
static unsigned long procfs_buffer_size = 0;

int procfile_read(char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data)
{

	int ret;
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);

	if (offset > 0) {
		/* we have finished to read, return 0 */
		ret = 0;
		} 
	else {
		/* fill the buffer, return the buffer size */
		ret = sprintf(buffer, "HelloWorld!\n");
		}
	return ret;
}

int procfile_write(struct file *file, const char *buffer, unsigned long count, void *data)
{

	/* get buffer size */
	procfs_buffer_size = count;
	if (procfs_buffer_size > procfs_max_size ) {
		procfs_buffer_size = procfs_max_size;
		}
	/* write data to the buffer */
	if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
		}
	return procfs_buffer_size;
}

int init_module()
{
	/*  create the /proc file  */
	Our_Proc_File = proc_create(procfs_name, 0644, NULL);
	if (Our_Proc_File == NULL) {
		remove_proc_entry(procfs_name, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
		}
	Our_Proc_File -> read_proc  =  procfile_read;
	Our_Proc_File -> write_proc =  procfile_write;
	Our_Proc_File -> owner	    =  THIS_MODULE;
	Our_Proc_File -> mode	    =  S_IFREG | S_IRUGO;
	Our_Proc_File -> uid   	    =  0;
	Our_Proc_File -> gid        =  0;
	Our_Proc_File -> size       =  37;

	printk(KERN_INFO "/proc/%s created\n", procfs_name);
	return 0;
	/* everything is ok */
}

void cleanup_module()
{
	remove_proc_entry(procfs_name, &proc_root);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}
