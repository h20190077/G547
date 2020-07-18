#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 
#include<linux/uaccess.h>              
#include <linux/ioctl.h>
#include <linux/random.h>
 #include <asm/uaccess.h>
#define RD_VALUE _IOR('a','b',int32_t*)

static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
#define mem_size 1024
static dev_t first; // variable for device number
static struct cdev c_dev; // variable for the character device structure
static struct class *cls; // variable for the device class
static int val;
unsigned int adc;


/*****************************************************************************
STEP 4 as discussed in the lecture, 
my_close(), my_open(), my_read(), my_write() functions are defined here
these functions will be called for close, open, read and write system calls respectively. 
*****************************************************************************/

static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Mychar : open()\n");
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Mychar : close()\n");
	return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Mychar : read()\n");
        
	return 0;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Mychar : write()\n");
	return len;
}
//###########################################################################################


static struct file_operations fops =
{
  .owner 	= THIS_MODULE,
  .open 	= my_open,
  .release 	= my_close,
  .read 	= my_read,
  .unlocked_ioctl = etx_ioctl,
  .write 	= my_write
};
 
//########## INITIALIZATION FUNCTION ##################
// STEP 1,2 & 3 are to be executed in this function ### 
static int __init mychar_init(void) 
{
	printk(KERN_INFO "Namaste: my adc registered");
	
	// STEP 1 : reserve <major, minor>
	if (alloc_chrdev_region(&first, 0, 1, "BITS-PILANI") < 0)
	{
		return -1;
	}
	
	// STEP 2 : dynamically create device node in /dev directory
    if ((cls = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		unregister_chrdev_region(first, 1);
		return -1;
	}
    if (device_create(cls, NULL, first, NULL, "adc8") == NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	
	// STEP 3 : Link fops and cdev to device node
    cdev_init(&c_dev, &fops);
    if (cdev_add(&c_dev, first, 1) == -1)
	{
		device_destroy(cls, first);
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	return 0;
}


 static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
get_random_bytes(&adc,sizeof(adc));
	val = (adc);

switch(cmd){

case RD_VALUE:
       copy_to_user((int32_t*) arg, &val, sizeof(val));
	
       break;


  }
return 0;      
                
}


 
static void __exit mychar_exit(void) 
{
	cdev_del(&c_dev);
	device_destroy(cls, first);
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "Bye: my adc is unregistered\n\n");
}
 
module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("2019h1400077g-bitspilani");
MODULE_DESCRIPTION("Our First Character Driver");

