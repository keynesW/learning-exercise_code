#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define GPD0 0x114000a0

typedef struct {
	unsigned int CON;
	unsigned int DAT;
	unsigned int place_holder[4];
}gpd0_t;

#define PWM 0x139d0000

typedef struct {
	unsigned int TCFG0;
	unsigned int TCFG1;
	unsigned int TCON;
	unsigned int TCNTB0;
	unsigned int TCMPB0;
	unsigned int TCNTO0;
	unsigned int place_holder[12];
}pwm_t;

struct pwm_desc{
	unsigned int *gpd0con;
	unsigned int *gpd0dat;
	
	pwm_t * ptr_pwm;
	
	unsigned int dev_major ;
	int kernel_val[2] ;
	struct class * pwm_class;
	struct device * dev;
}pwm_desc_t;

static struct pwm_desc *ppwm_desc;
	
int pwm_open (struct inode *inode, struct file *fp)
{
	printk("----%s-----\n",__FUNCTION__);
	//ppwm_desc->ptr_pwm->TCON = (ppwm_desc->ptr_pwm->TCON &~(0xf)) | 0x9;
	return 0;
}

ssize_t pwm_read (struct file *fp, char __user * buff, size_t cunt, loff_t * pos)
{
	int ret = 0;
	printk("----%s-----\n",__FUNCTION__);
	ret = copy_to_user(buff,ppwm_desc->kernel_val,cunt);
	if(ret < 0)
		printk("copy_to_user error");
	return 0;
}

ssize_t pwm_write (struct file *fp, const char __user *buff, size_t cunt, loff_t *pos)
{
	int ret = 0;
	ret = copy_from_user(ppwm_desc->kernel_val,buff,cunt);
	return 0;
}

int pwm_release (struct inode *inode, struct file *fp)
{
	printk("----%s-----\n",__FUNCTION__);

	return 0;
}

static const struct file_operations my_fops ={
	.open = pwm_open,
	.read = pwm_read,
	.write = pwm_write,
	.release = pwm_release,
};

static int __init pwm_init(void)
{
	int ret = 0;
	int num = 0;
	ppwm_desc = kmalloc(sizeof(pwm_desc_t),GFP_KERNEL);
	ppwm_desc->dev_major = 250;
	
	printk("----%s-----\n",__FUNCTION__);
	if((ret = register_chrdev(ppwm_desc->dev_major,"pwm0",&my_fops))<0)
		printk("register chrdev failed\n");
	
	ppwm_desc->pwm_class = class_create(THIS_MODULE,"pwm0");
	ppwm_desc->dev = device_create(ppwm_desc->pwm_class,NULL,MKDEV(ppwm_desc->dev_major,0),NULL,"pwm_%d",num);
	
	ppwm_desc->gpd0con = ioremap(GPD0,sizeof(gpd0_t));
	
	ppwm_desc->gpd0dat = ppwm_desc->gpd0con + 1;
	*ppwm_desc->gpd0con = ((*ppwm_desc->gpd0con &~(0xf))|0x2);

	printk("addr gpd0: %p,sizeof pwm_t: %zd\n",ppwm_desc->gpd0con,sizeof(pwm_t));
		
	if((ppwm_desc->ptr_pwm = (void *)ioremap(PWM,sizeof(pwm_t))) == NULL)
		printk("ioremap PWM failed\n");
		
	ppwm_desc->ptr_pwm->TCFG0 = (ppwm_desc->ptr_pwm->TCFG0 &~(0xff))| 0x63;
	ppwm_desc->ptr_pwm->TCFG1 = (ppwm_desc->ptr_pwm->TCFG1 &~(0xf))| 0x3;
	
	ppwm_desc->ptr_pwm->TCNTB0 = 200;
	ppwm_desc->ptr_pwm->TCMPB0 = 100;

	ppwm_desc->ptr_pwm->TCON = (ppwm_desc->ptr_pwm->TCON &~(0xf)) | 0xa;
	
	return 0;
}

static void __exit pwm_exit(void)
{
	printk("----%s-----\n",__FUNCTION__);

	iounmap(ppwm_desc->gpd0con);
	iounmap(ppwm_desc->ptr_pwm);

	device_destroy(ppwm_desc->pwm_class,MKDEV(ppwm_desc->dev_major,0));
	class_destroy(ppwm_desc->pwm_class);
	unregister_chrdev(ppwm_desc->dev_major,"pwm0");
}

module_init(pwm_init);
module_exit(pwm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("keynes");
MODULE_DESCRIPTION("char dev development test");
MODULE_ALIAS("pwm");
