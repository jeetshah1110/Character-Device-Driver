#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include <linux/uaccess.h>
#define DEVICE_NAME "Marvellous Driver 1"
#define CLASS_NAME "Marvellous Driver"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeet Shah");
MODULE_VERSION("0.1");
static int majorNumber;
static char message[256] = {0};
static short size_of_message;
static int numberOpens = 0;
static struct class *charClass = NULL;
static struct device *charDevice = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *,const char *, size_t, loff_t *);

static struct file_operations fops =
{
.open = dev_open,
.read = dev_read,
.write = dev_write,
.release = dev_release,
};

static int __init char_init(void)
{
    
    printk(KERN_INFO "Driver Loaded Successfully\n");
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0)
    {
        printk(KERN_INFO "FAILED to register major number\n");
	return majorNumber;
    }
    printk(KERN_INFO "registered correctly with major number %d\n",majorNumber);



    charClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(charClass))
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT" Failed to register device class\n");
        return PTR_ERR(charClass);
    }
    printk(KERN_INFO "Device class registered correctly\n");



    charDevice = device_create(charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(charDevice))
    {
        class_destroy(charClass);
         unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(charDevice);
    }
    printk(KERN_INFO "Device Class created properly\n");



    return 0;
}
static void __exit char_exit(void)
{
    device_destroy(charClass, MKDEV(majorNumber, 0));
    class_unregister(charClass);
    class_destroy(charClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "Goodbye from our driver\n");
}
static int dev_open(struct inode * inodep, struct file * filep)
{
    numberOpens++;
    printk(KERN_INFO "Device has been opened %d times\n",numberOpens);
    return 0;

}
static ssize_t dev_read(struct file *filep, char * buffer, size_t len, loff_t *offset)
{
    int error_count = 0;
   error_count = copy_to_user(buffer, message, size_of_message);
    if (error_count == 0)
    {
        printk(KERN_INFO "send %d characters to user\n",size_of_message);
        return(size_of_message = 0);
    }
    else
    {
        printk(KERN_INFO "failed to send %d char to user\n",error_count);
        return -EFAULT;
    }
}
static ssize_t dev_write(struct file * filep, const char * buffer, size_t len, loff_t * offset)
{
    //printk(KERN_INFO "%s",*buffer); 
    copy_from_user(message,buffer,len);    
	//sprintf(message, "%s(%d letters)",buffer,len);
    size_of_message = strlen(message);
    printk(KERN_INFO "Recieved %d char from user\n",len);	
    return len;
}
static int dev_release(struct inode * inodep, struct file * filep)
{
    printk(KERN_INFO "Device Succseefully Closed\n");
    return 0;
}
module_init(char_init);
module_exit(char_exit);


