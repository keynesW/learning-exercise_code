#include <linux/init.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/of_irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/signal.h>

#define GPX2CON 0x11000c20

struct event{
    int code;
    int value;
};

struct key_desc{
	unsigned int dev_major;
	struct class *cls;
	void *reg_base;
    int irqno;	
    struct event ev;
	wait_queue_head_t wq_head;
    int key_cond;
    struct fasync_struct *fasync_s;
};

static struct key_desc *key_dev2;

int get_irqno_from_node(const char *ptr_str)
{
    int irqno;
    // 获取到设备树中到节点
    //struct device_node *np = of_find_node_by_path("/key_drv_node");
    struct device_node *np = of_find_node_by_path(ptr_str);
    if(np){
        printk("find node ok\n");
    }else{
        printk("find node failed\n");
    }

    // 通过节点去获取到中断号码
    irqno =  irq_of_parse_and_map(np, 0);
    printk("irqno = %d\n", irqno);

    return irqno;
}

irqreturn_t key_irq_handler(int irqno, void *devid)
{
    int pin_status;
    struct key_desc *ptr_keyds = (struct key_desc *)devid;

    ptr_keyds->key_cond = 1;
	wake_up_interruptible(&ptr_keyds->wq_head);

    printk("-------%s-------------\n", __FUNCTION__);
    pin_status = readl(ptr_keyds->reg_base+4) & (1 << 2);
    printk("pin_status : %d\n",pin_status); 
    switch(irqno)
    {
    case 167:
        ptr_keyds->ev.code = 3;
        printk("irqno : %d\n",ptr_keyds->irqno);
        if (!pin_status)
            ptr_keyds->ev.value = 1;
        else
            ptr_keyds->ev.value = 2;
        break;

    default:
        printk("unknown irqno\n");
        break;
    }
    kill_fasync(&key_dev2->fasync_s,SIGIO,POLLIN);
    return IRQ_HANDLED;
}


int key_drv_open(struct inode *inode, struct file *filp)
{
	printk("-------%s-------------\n", __FUNCTION__);
	return 0;
}

ssize_t key_drv_read(struct file *filp, char __user *buf, size_t count, loff_t *fpos)
{
	//printk("-------%s-------------\n", __FUNCTION__);
	if(filp->f_flags & O_NONBLOCK && !key_dev2->key_cond)
		return -EAGAIN;

	wait_event_interruptible(key_dev2->wq_head, key_dev2->key_cond);

    if(copy_to_user(buf,&key_dev2->ev,count))
        printk("copy_to_user err\n");

    memset(&key_dev2->ev,0,count);
    key_dev2->key_cond = 0;

	return 0;

}
ssize_t key_drv_write(struct file *filp, const char __user *buf, size_t count, loff_t *fpos)
{
	printk("-------%s-------------\n", __FUNCTION__);
	return 0;
}

int key_drv_fasync(int fd,struct file * filp,int on)
{
    return fasync_helper(fd,filp,on,&key_dev2->fasync_s);
}

int key_drv_close (struct inode *inode, struct file *filp)
{
	printk("-------%s-------------\n", __FUNCTION__);

	return key_drv_fasync(-1,filp,0);
}

unsigned int key_drv_poll(struct file *filp, struct poll_table_struct *pts)
{

    // 返回一个mask值
    unsigned int mask;
    // 调用poll_wait,将当前等待队列注册系统中
    poll_wait(filp, &key_dev2->wq_head, pts);

    // 1，当没有数据到时候返回一个0
    if(!key_dev2->key_cond)
        mask = 0;

    // 2，有数据返回一个POLLIN
    if(key_dev2->key_cond)
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

	key_dev2 = kzalloc(sizeof(struct key_desc),  GFP_KERNEL);

	key_dev2->dev_major = register_chrdev(0, "key_drv", &key_fops);

	key_dev2->cls = class_create(THIS_MODULE, "key_cls");
	device_create(key_dev2->cls, NULL, MKDEV(key_dev2->dev_major,0), NULL, "key3");

    //struct device_node *np = of_find_node_by_path("/key_drv_node");
    

    key_dev2->reg_base = ioremap(GPX2CON,4);

    // bind the irqnum with an isr

    init_waitqueue_head(&key_dev2->wq_head);

    key_dev2->irqno = get_irqno_from_node("/key_drv_node");

    ret = request_irq(key_dev2->irqno, key_irq_handler,\
        IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, \
        "key3_eint10", key_dev2);

    if(ret != 0)
    {
        printk("request_irq error\n");
        return ret;
    }			

	return 0;
}
static void __exit key_drv_exit(void)
{
	free_irq(key_dev2->irqno,key_dev2);
	device_destroy(key_dev2->cls, MKDEV(key_dev2->dev_major,0));
	class_destroy(key_dev2->cls);
	unregister_chrdev(key_dev2->dev_major, "key_drv");

	kfree(key_dev2);
}

module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("fasdfjaksdjfka");
MODULE_ALIAS("dafsdf");
