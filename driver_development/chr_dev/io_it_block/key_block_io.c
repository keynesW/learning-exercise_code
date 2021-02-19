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

#define GPX2CON 0x11000c20
#define GPX3CON 0x11000c60

struct event{
    int code;
    int value;
};
struct key_desc{
	unsigned int dev_major;
	unsigned int dev_major1;
	unsigned int dev_major2;
	struct class *cls;
	struct class *cls1;
	struct class *cls2;
	void *reg_base;
	void *reg_base2;
    int irqno;	
    int irqno1;	
    int irqno2;	
    struct event ev;
	wait_queue_head_t wq_head;
    int key_cond;
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
    int pin_status1;
    int pin_status2;
    struct key_desc *ptr_keyds = (struct key_desc *)devid;

    ptr_keyds->key_cond = 1;
	wake_up_interruptible(&ptr_keyds->wq_head);

    printk("-------%s-------------\n", __FUNCTION__);
    pin_status = readl(ptr_keyds->reg_base+4) & (1 << 2);
    pin_status1 = readl(ptr_keyds->reg_base+4) & (1 << 1);
    pin_status2 = readl(ptr_keyds->reg_base2+4) & (1 << 2);
    
    switch(irqno)
    {
    case 167:
        ptr_keyds->ev.code = 1;
        printk("irqno : %d\n",ptr_keyds->irqno);
        if (pin_status)
            //printk("key up\n");
            ptr_keyds->ev.value = 1;
        else
            //printk("key down\n");
            ptr_keyds->ev.value = 2;
        break;

    case 168:
        ptr_keyds->ev.code = 2;
        printk("irqno : %d\n",ptr_keyds->irqno1);
        if (pin_status1)
            ptr_keyds->ev.value = 1;
        else
            ptr_keyds->ev.value = 2;
        break;

    case 169:
        ptr_keyds->ev.code = 3;
        printk("irqno : %d\n",ptr_keyds->irqno2);
        if (pin_status2)
            ptr_keyds->ev.value = 1;
        else
            ptr_keyds->ev.value = 2;
        break;

    default:
        printk("unknown irqno\n");
        break;
    }

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

int key_drv_close (struct inode *inode, struct file *filp)
{
	printk("-------%s-------------\n", __FUNCTION__);
	return 0;
}

const struct file_operations key_fops = {
	.open = key_drv_open,
	.read = key_drv_read,
	.write = key_drv_write,
	.release = key_drv_close,
};

static int __init key_drv_init(void)
{
	//演示如何获取到中断号
	int ret;

	// 1，设定一个全局的设备对象
	key_dev2 = kzalloc(sizeof(struct key_desc),  GFP_KERNEL);
    //key_dev2 = kzalloc(sizeof(struct key_desc),  GFP_KERNEL);

    init_waitqueue_head(&key_dev2->wq_head);

	// 2,申请主设备号
	key_dev2->dev_major = register_chrdev(0, "key_drv", &key_fops);
	key_dev2->dev_major1 = register_chrdev(0, "key_drv1", &key_fops);
	key_dev2->dev_major1 = register_chrdev(0, "key_drv2", &key_fops);

	// 3,创建设备节点文件
	key_dev2->cls = class_create(THIS_MODULE, "key_cls");
	key_dev2->cls1 = class_create(THIS_MODULE, "key_cls1");
	key_dev2->cls2 = class_create(THIS_MODULE, "key_cls2");
	device_create(key_dev2->cls, NULL, MKDEV(key_dev2->dev_major,0), NULL, "key3");
	device_create(key_dev2->cls1, NULL, MKDEV(key_dev2->dev_major1,0), NULL, "key2");
	device_create(key_dev2->cls2, NULL, MKDEV(key_dev2->dev_major2,0), NULL, "key4");

    //struct device_node *np = of_find_node_by_path("/key_drv_node");
    
    key_dev2->irqno = get_irqno_from_node("/key_drv_node");
    key_dev2->irqno1 = get_irqno_from_node("/key_drv2_node");
    key_dev2->irqno2 = get_irqno_from_node("/key_drv3_node");

    key_dev2->reg_base = ioremap(GPX2CON,4);
    key_dev2->reg_base2 = ioremap(GPX3CON,4);

    // bind the irqnum with an isr

    ret = request_irq(key_dev2->irqno, key_irq_handler,\
        IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, \
        "key3_eint10", key_dev2);
    ret = request_irq(key_dev2->irqno1, key_irq_handler,\
        IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, \
        "key2_eint9", key_dev2);
    ret = request_irq(key_dev2->irqno2, key_irq_handler,\
        IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, \
        "key4_eint26", key_dev2);

    if(ret != 0)
    {
        printk("request_irq error\n");
        return ret;
    }			

	return 0;
}
static void __exit key_drv_exit(void)
{
	//free_irq(key_dev2->irqno,key_dev2);
	free_irq(key_dev2->irqno,key_dev2);
	device_destroy(key_dev2->cls, MKDEV(key_dev2->dev_major,0));
	class_destroy(key_dev2->cls);
	unregister_chrdev(key_dev2->dev_major, "key_drv");
	//kfree(key_dev2);

	free_irq(key_dev2->irqno1,key_dev2);
	device_destroy(key_dev2->cls1, MKDEV(key_dev2->dev_major1,0));
	class_destroy(key_dev2->cls1);
	unregister_chrdev(key_dev2->dev_major1, "key_drv1");

	free_irq(key_dev2->irqno2,key_dev2);
	device_destroy(key_dev2->cls2, MKDEV(key_dev2->dev_major2,0));
	class_destroy(key_dev2->cls2);
	unregister_chrdev(key_dev2->dev_major1, "key_drv2");

	kfree(key_dev2);
}

module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");
