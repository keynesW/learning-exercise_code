#include <linux/init.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/device.h>

#include <linux/of_irq.h>
#include <linux/interrupt.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <asm-generic/fcntl.h>
#include <linux/poll.h>



//KEY3  REG  KEY2 REG  all
#define GPX1CON 0x11000c20
//ioremap size
#define GPXSIZE 8


#define KEY2 2
#define KEY3 3

struct key_event{
	int code;
	int value;
};

struct key_desc{
	unsigned int dev_major;
	struct class *cls;
	void *reg_base;
	int irqno3; //key3 
	int irqno2;	//key2
	struct key_event event;
	wait_queue_head_t wq_head;// wait queue head
	int state;
	struct fasync_struct *fasync;
};

struct key_desc *key_dev;

static irqreturn_t key_interrupt_handler(int irq, void *dev_id)
{
	int pinState;
	printk("----------------------%s-------------------\n",__FUNCTION__);
	struct key_desc *p = (struct key_desc *)dev_id;
	printk("dev_major = %d\n",p->dev_major);


	if(irq == key_dev->irqno3){
			pinState = readl(key_dev->reg_base + 4) & (1 << 2);
			if(pinState == 0){
				printk("key3 down\n");
				key_dev->event.code = KEY3;
				key_dev->event.value = 0;
			}else{
				printk("key3 up\n");
				key_dev->event.code = KEY3;
				key_dev->event.value = 1;
				}
		}
	
	if(irq == key_dev->irqno2){
		pinState = readl(key_dev->reg_base + 4) & (1 << 1);
		if(pinState == 0){
			printk("key2 down\n");
			key_dev->event.code = KEY2;
			key_dev->event.value = 0;
		}else{
			printk("key2 up\n");
			key_dev->event.code = KEY2;
			key_dev->event.value = 1;
			}
		}

	wake_up_interruptible(&key_dev->wq_head);
	key_dev->state = 1;
	//发送 SIGIO Signal
	kill_fasync(&key_dev->fasync, SIGIO, POLLIN);
	return IRQ_HANDLED;
}

int get_irqno_from_node(char *name)
{
	int irqno;
	//获取到设备树种的节点
	struct device_node *np = of_find_node_by_path(name);
	if(np)
		{
		printk("find node ok\n");
	}else{
		printk("find node fail\n");
	}
	//通过节点去获取到中断号码
	irqno = irq_of_parse_and_map(np, 0);
	printk("irqno = %d\n", irqno);

	return irqno;	
}



int key_drv_open(struct inode *inode, struct file *filp)
{
	printk("-------%s-------------\n", __FUNCTION__);
	return 0;
}

ssize_t key_drv_read(struct file *filp, char __user *buf, size_t count, loff_t *fpos)
{
	//printk("-------%s-------------\n", __FUNCTION__);
	if(filp->f_flags & O_NONBLOCK && !key_dev->state)
		{
			return -EAGAIN;
		}
	wait_event_interruptible((key_dev->wq_head),key_dev->state);
	int ret;
	ret = copy_to_user(buf, &key_dev->event, count);
	if(ret > 0){
		printk("copy to user failed\n");
		return -EFAULT;
	}
	memset(&key_dev->event, 0 , count);
	key_dev->state = 0;
	return 0;

}
ssize_t key_drv_write(struct file *filp, const char __user *buf, size_t count, loff_t *fpos)
{
	printk("-------%s-------------\n", __FUNCTION__);
	return 0;
}

int key_drv_fasync(int fd, struct file *filp, int on)
{
	return fasync_helper(fd, filp, on, &key_dev->fasync);
}

int key_drv_close (struct inode *inode, struct file *filp)
{
	printk("-------%s-------------\n", __FUNCTION__);
	//删除fasync 节点
	
	return key_drv_fasync(-1, filp, 0);
}

unsigned int key_drv_poll(struct file *filp, struct poll_table_struct *pts)
{
	
	// 返回一个mask值
	unsigned int mask;
	// 调用poll_wait,将当前等待队列注册系统中
	poll_wait(filp, &key_dev->wq_head, pts);
	
	// 1，当没有数据到时候返回一个0
	if(!key_dev->state)
		mask = 0;

	// 2，有数据返回一个POLLIN
	if(key_dev->state)
		mask |= POLLIN;

	return mask;
	
}





const struct file_operations key_fops = {
	.open = key_drv_open,
	.read = key_drv_read,
	.write = key_drv_write,
	.release = key_drv_close,
	.poll = key_drv_poll,
	.fasync = key_drv_fasync,
};

static int __init key_drv_init(void)
{
	//演示如何获取到中断号
	int ret;

	// 1.设定一个全局的设备对象
	key_dev = kzalloc(sizeof(struct key_desc),  GFP_KERNEL);

	// 2.申请主设备号
	key_dev->dev_major = register_chrdev(0, "key_drv", &key_fops);

	// 3.创建设备节点文件
	key_dev->cls = class_create(THIS_MODULE, "key_cls");
	device_create(key_dev->cls, NULL, MKDEV(key_dev->dev_major,0), NULL, "key3");

	//4.虚拟地址的映射
	key_dev->reg_base = ioremap(GPX1CON, GPXSIZE);

	//5.等待队列头的初始化
	init_waitqueue_head(&key_dev->wq_head);

	
	//5.获取中断号
	///key3 get irq num
	key_dev->irqno3 = get_irqno_from_node("/key_drv_node");
	///key2 get irq num
	key_dev->irqno2 = get_irqno_from_node("/key_drv2_node");

	//6.中断函数注册
	/// key 3  regiest
	ret = request_irq(key_dev->irqno3,key_interrupt_handler, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "key3_int", key_dev);
	if(ret != 0){
		printk("request key 3 irq failed\n");
	}
	/// key 2  regiest
	ret = request_irq(key_dev->irqno2,key_interrupt_handler, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "key2_int", key_dev);
	if(ret != 0){
		printk("request key 2 irq failed\n");
	}
	
	return 0;
}




static void __exit key_drv_exit(void)
{
	free_irq(key_dev->irqno3,key_dev);
	free_irq(key_dev->irqno2,key_dev);
	device_destroy(key_dev->cls, MKDEV(key_dev->dev_major,0));
	class_destroy(key_dev->cls);
	unregister_chrdev(key_dev->dev_major, "key_drv");
	kfree(key_dev);
}

module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");





















