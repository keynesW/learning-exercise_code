#include <linux/module.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#include "dev_desc.h"

#define GPX1SIZE 8

extern struct bus_type bus_desc;
static struct dev_inf * pdev_inf;

/*
#define GPX1CON 0x11000c20
unsigned int addr = 0x11000c20;
int b2m = 0;
int cb2m = 0;
*/

struct led_desc{
	unsigned int *gpx1con;
	unsigned int *gpx1dat;
	
	unsigned int dev_major ;
	int kernel_val ;
	struct class * chr_class;
	struct device * dev;
}led_desc_t;

static struct led_desc *ptr_led_dev;

int chr_dev_open (struct inode *inode,\
    struct file *fp)
{
	printk("----%s-----\n",__FUNCTION__);
	
	return 0;
}

ssize_t chr_dev_read (struct file *fp,\
    char __user * buff, size_t cunt, loff_t * pos)
{
	int ret = 0;
	printk("----%s-----\n",__FUNCTION__);
	ret = copy_to_user(buff,\
        &ptr_led_dev->kernel_val,cunt);
	if(ret < 0)
		printk("copy_to_user error");
	return 0;
}

ssize_t chr_dev_write (struct file *fp,\
    const char __user *buff, size_t cunt,\
    loff_t *pos)
{
	int ret = 0;
	//printk("----%s-----\n",__FUNCTION__);
    
	ret = copy_from_user(\
        &ptr_led_dev->kernel_val,buff,cunt);
	
    if(!ptr_led_dev->kernel_val)
        writel(readl(ptr_led_dev->gpx1dat)\
            &~(1 << pdev_inf->pin_num),\
            ptr_led_dev->gpx1dat);
    else
        writel(readl(ptr_led_dev->gpx1dat)\
            | (1 << pdev_inf->pin_num),\
            ptr_led_dev->gpx1dat);

	return 0;
}

int chr_dev_release (struct inode *inode,\
    struct file *fp)
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

static int __init chr_drv_init(\
    struct device *dev)
{
	int ret = 0;
    int num = 0;
/*
	printk("addr :%#x ,b2m : %d,cb2m : %d\n",\
    addr,b2m,cb2m);
*/
	printk("----%s-----\n",__FUNCTION__);

	ptr_led_dev = kmalloc(sizeof(led_desc_t),\
        GFP_KERNEL);
	ptr_led_dev->dev_major = 250;

	if((ret = register_chrdev(\
                ptr_led_dev->dev_major,\
                "chr0",&my_fops))<0)
		printk("register chrdev failed\n");
	
	ptr_led_dev->chr_class = class_create(\
        THIS_MODULE,"chr0");
	ptr_led_dev->dev = device_create(\
        ptr_led_dev->chr_class,NULL,\
        MKDEV(ptr_led_dev->dev_major,0),\
        NULL,"chr_%d",num);
/*	
    printk("reg_base : %#x\n",\
            pdev_inf->reg_base);
    printk("pin : %d\n",pdev_inf->pin_num);
*/
	ptr_led_dev->gpx1con = ioremap(\
        pdev_inf->reg_base,GPX1SIZE);
    ptr_led_dev->gpx1dat = \
                ptr_led_dev->gpx1con + 1;
    *ptr_led_dev->gpx1con = \
                ((*ptr_led_dev->gpx1con \
                    &~(0xf << pdev_inf->pin_num))\
                    | (1 << pdev_inf->pin_num));

	return 0;
}

static void __exit chr_drv_exit(void)
{
	printk("----%s-----\n",__FUNCTION__);

	iounmap(ptr_led_dev->gpx1con);

	device_destroy(ptr_led_dev->chr_class,\
        MKDEV(ptr_led_dev->dev_major,0));
	class_destroy(ptr_led_dev->chr_class);
	unregister_chrdev(ptr_led_dev->dev_major,\
        "chr_0");
}

int drv_probe(struct device *dev)
{
    printk("-------%s---------\n",__FUNCTION__);
    pdev_inf = dev->platform_data;
    printk("reg_base : %#x\n",pdev_inf->reg_base);
    printk("pin : %d\n",pdev_inf->pin_num);

    chr_drv_init(dev);
    return 0;
}

int drv_remove(struct device * dev)
{
    printk("-------%s---------\n",__FUNCTION__);
    chr_drv_exit( );

    return 0;
}

struct device_driver drv_desc = {
    .name = "led_test",
    .bus = &bus_desc,
    .probe = drv_probe,
    .remove = drv_remove,
};

static int __init drv_init(void)
{
    int ret;
    printk("-------%s---------\n",__FUNCTION__);

    if ((ret = driver_register(&drv_desc)) < 0){
        printk("drv register failed\n");
        return -1;
    }
    return 0;
}


static void __exit drv_exit(void)
{
    driver_unregister(&drv_desc);
}

module_init(drv_init);
module_exit(drv_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("bus mode");
MODULE_ALIAS("drv");
