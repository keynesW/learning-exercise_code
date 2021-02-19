#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define GPX2CON 0x11000C40
#define GPX2SIZE 8
#define GPX1CON 0x11000c20
#define GPX1SIZE 8
#define GPF3CON 0X114001e0
#define GPF3SIZE 8

struct led_dev_stu{
	unsigned int *gpx2con;
	unsigned int *gpx2dat;
	unsigned int *gpx1con;
	unsigned int *gpx1dat;
	unsigned int *gpf3con;
	unsigned int *gpf3dat;
	
	unsigned int dev_major ;
	int kernel_val[2] ;
	struct class * chr_class;
	struct device * dev;
}led_dev_t;

static struct led_dev_stu *ptr_led_dev;

extern int my_add(int ,int );
extern int my_add_p(int* ,int* );
	
int chr_dev_open (struct inode *inode, struct file *fp)
{
	printk("----%s-----\n",__FUNCTION__);
	ptr_led_dev->gpx2con = ioremap(GPX2CON,GPX2SIZE);
	ptr_led_dev->gpx2dat = ptr_led_dev->gpx2con + 1;
	*ptr_led_dev->gpx2con = ((*ptr_led_dev->gpx2con &~(0xf << 28))|(1 << 28));

	ptr_led_dev->gpx1con = ioremap(GPX1CON,GPX1SIZE);
	ptr_led_dev->gpx1dat = ptr_led_dev->gpx1con + 1;
	*ptr_led_dev->gpx1con = ((*ptr_led_dev->gpx1con &~(0xf << 0))|(1 << 0));

	ptr_led_dev->gpf3con = ioremap(GPF3CON,GPF3SIZE);
	ptr_led_dev->gpf3dat = ptr_led_dev->gpf3con + 1;
	*ptr_led_dev->gpf3con = ((*ptr_led_dev->gpf3con &~(0xff << 16))|(0x11 << 16));
	
	return 0;
}

ssize_t chr_dev_read (struct file *fp, char __user * buff, size_t cunt, loff_t * pos)
{
	int ret = 0;
	printk("----%s-----\n",__FUNCTION__);
	ret = copy_to_user(buff,ptr_led_dev->kernel_val,cunt);
	if(ret < 0)
		printk("copy_to_user error");
	return 0;
}

ssize_t chr_dev_write (struct file *fp, const char __user *buff, size_t cunt, loff_t *pos)
{
	int ret = 0;
	//printk("----%s-----\n",__FUNCTION__);
	ret = copy_from_user(ptr_led_dev->kernel_val,buff,cunt);
	
	switch(ptr_led_dev->kernel_val[0]){
		case 0:
			writel(readl(ptr_led_dev->gpx2dat)|(1 << 7),ptr_led_dev->gpx2dat);
			writel((readl(ptr_led_dev->gpx1dat)&~(1 << 0)) | (0 << 0),ptr_led_dev->gpx1dat);
			writel((readl(ptr_led_dev->gpf3dat)&~(1 << 4)) | (0 << 4),ptr_led_dev->gpf3dat);
			writel((readl(ptr_led_dev->gpf3dat)&~(1 << 5)) | (0 << 5),ptr_led_dev->gpf3dat);
			break;
		case 1:
			writel((readl(ptr_led_dev->gpx2dat)&~(1 << 7)) | (0 << 7),ptr_led_dev->gpx2dat);
			writel(readl(ptr_led_dev->gpx1dat) |(1 << 0),ptr_led_dev->gpx1dat);
			writel((readl(ptr_led_dev->gpf3dat)&~(1 << 4)) | (0 << 4),ptr_led_dev->gpf3dat);
			writel((readl(ptr_led_dev->gpf3dat)&~(1 << 5)) | (0 << 5),ptr_led_dev->gpf3dat);
			break;
		case 2:
			writel((readl(ptr_led_dev->gpx2dat)&~(1 << 7)) | (0 << 7),ptr_led_dev->gpx2dat);
			writel((readl(ptr_led_dev->gpx1dat)&~(1 << 0)) | (0 << 0),ptr_led_dev->gpx1dat);
			writel(readl(ptr_led_dev->gpf3dat) |(1 << 4),ptr_led_dev->gpf3dat);
			writel((readl(ptr_led_dev->gpf3dat)&~(1 << 5)) | (0 << 5),ptr_led_dev->gpf3dat);
			break;
		case 3:
			writel((readl(ptr_led_dev->gpx2dat)&~(1 << 7)) | (0 << 7),ptr_led_dev->gpx2dat);
			writel((readl(ptr_led_dev->gpx1dat)&~(1 << 0)) | (0 << 0),ptr_led_dev->gpx1dat);
			writel((readl(ptr_led_dev->gpf3dat)&~(1 << 4)) | (0 << 4),ptr_led_dev->gpf3dat);
			writel(readl(ptr_led_dev->gpf3dat) |(1 << 5),ptr_led_dev->gpf3dat);
			break;
		default:
			printk("default\n");
			break;
	}
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
    printk("myadd : %d",my_add(ret,num+3));
	ptr_led_dev = kmalloc(sizeof(led_dev_t),GFP_KERNEL);
	ptr_led_dev->dev_major = 250;
	
	printk("----%s-----\n",__FUNCTION__);
	if((ret = register_chrdev(ptr_led_dev->dev_major,"chr0",&my_fops))<0)
		printk("register chrdev failed\n");
	
	ptr_led_dev->chr_class = class_create(THIS_MODULE,"chr0");
	ptr_led_dev->dev = device_create(ptr_led_dev->chr_class,NULL,MKDEV(ptr_led_dev->dev_major,0),NULL,"chr_%d",num);
	
	return 0;
}

static void __exit chr_drv_exit(void)
{
	printk("----%s-----\n",__FUNCTION__);

	iounmap(ptr_led_dev->gpx2con);
	iounmap(ptr_led_dev->gpx1con);
	iounmap(ptr_led_dev->gpf3con);

	device_destroy(ptr_led_dev->chr_class,MKDEV(ptr_led_dev->dev_major,0));
	class_destroy(ptr_led_dev->chr_class);
	unregister_chrdev(ptr_led_dev->dev_major,"chr0");
}

module_init(chr_drv_init);
module_exit(chr_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("keynes");
MODULE_DESCRIPTION("char dev development test");
MODULE_ALIAS("led");
