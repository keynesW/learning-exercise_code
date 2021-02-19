#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define GPX1CON 0x11000c20
#define GPX1SIZE 8

unsigned int addr = 0x11000c20;
int b2m = 0;
int cb2m = 0;

struct led_dev_stu{
	unsigned int *gpx1con;
	unsigned int *gpx1dat;
	
	unsigned int dev_major ;
	int kernel_val ;
	struct class * chr_class;
	struct device * dev;
}led_dev_t;

static struct led_dev_stu *ptr_led_dev;

int chr_dev_open (struct inode *inode, struct file *fp)
{
	printk("----%s-----\n",__FUNCTION__);

	ptr_led_dev->gpx1con = ioremap(addr,GPX1SIZE);
	ptr_led_dev->gpx1dat = ptr_led_dev->gpx1con + 1;
	*ptr_led_dev->gpx1con = ((*ptr_led_dev->gpx1con &~(0xf << cb2m))|(1 << cb2m));
	
	return 0;
}

ssize_t chr_dev_read (struct file *fp, char __user * buff, size_t cunt, loff_t * pos)
{
	int ret = 0;
	printk("----%s-----\n",__FUNCTION__);
	ret = copy_to_user(buff,&ptr_led_dev->kernel_val,cunt);
	if(ret < 0)
		printk("copy_to_user error");
	return 0;
}
ssize_t chr_dev_write (struct file *fp, const char __user *buff, size_t cunt, loff_t *pos)
{
	int ret = 0;
	//printk("----%s-----\n",__FUNCTION__);
    
	ret = copy_from_user(&ptr_led_dev->kernel_val,buff,cunt);
	
    if(!ptr_led_dev->kernel_val)
        writel(readl(ptr_led_dev->gpx1dat)&~(1 << b2m),ptr_led_dev->gpx1dat);
    else
        writel(readl(ptr_led_dev->gpx1dat) |(1 << b2m),ptr_led_dev->gpx1dat);

	return 0;
}
int chr_dev_release (struct inode *inode, struct file *fp)
{
	printk("----%s-----\n",__FUNCTION__);
	return 0;
}


static const struct file_operations my_fops ={
	.open = chr_dev_open,
	.read = chr_dev_read,
	.write = chr_dev_write,
	.release = chr_dev_release,
};

static int __init chr_drv_init(void)
{
	int ret = 0;
    int num = 0;
	printk("addr :%#x ,b2m : %d,cb2m : %d\n",addr,b2m,cb2m);

	ptr_led_dev = kmalloc(sizeof(led_dev_t),GFP_KERNEL);
	ptr_led_dev->dev_major = 250;

	printk("----%s-----\n",__FUNCTION__);
	if((ret = register_chrdev(ptr_led_dev->dev_major,"chr0",&my_fops))<0)
		printk("register chrdev failed\n");
	
	ptr_led_dev->chr_class = class_create(THIS_MODULE,"chr0");
	ptr_led_dev->dev = device_create(ptr_led_dev->chr_class,NULL,\
        MKDEV(ptr_led_dev->dev_major,0),NULL,"chr_%d",num);
	
	return 0;
}
static void __exit chr_drv_exit(void)
{
	printk("----%s-----\n",__FUNCTION__);

	iounmap(ptr_led_dev->gpx1con);

	device_destroy(ptr_led_dev->chr_class,MKDEV(ptr_led_dev->dev_major,0));
	class_destroy(ptr_led_dev->chr_class);
	unregister_chrdev(ptr_led_dev->dev_major,"chr_0");
}

module_init(chr_drv_init);
module_exit(chr_drv_exit);

module_param(addr,uint,0644);
module_param(b2m,int,0644);
module_param(cb2m,int,0644);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("keynes");
MODULE_DESCRIPTION("char dev development test");
MODULE_ALIAS("led");
