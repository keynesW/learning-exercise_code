#include <linux/init.h>/*{{{*/
#include <linux/module.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/device.h>

#include <asm/io.h>
#include <asm/uaccess.h>

struct key_desc{
	unsigned int dev_major;
	struct class *cls;
	void *reg_base;
	
};

struct key_desc *key_dev;



int key_drv_open(struct inode *inode, struct file *filp)
{
	printk("-------%s-------------\n", __FUNCTION__);
	return 0;
}

ssize_t key_drv_read(struct file *filp, char __user *buf, size_t count, loff_t *fpos)
{
	printk("-------%s-------------\n", __FUNCTION__);
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
	//��ʾ��λ�ȡ���жϺ�
	int ret;

	// 1���趨һ��ȫ�ֵ��豸����
	key_dev = kzalloc(sizeof(struct key_desc),  GFP_KERNEL);

	// 2,�������豸��
	key_dev->dev_major = register_chrdev(0, "key_drv", &key_fops);

	// 3,�����豸�ڵ��ļ�
	key_dev->cls = class_create(THIS_MODULE, "key_cls");
	device_create(key_dev->cls, NULL, MKDEV(key_dev->dev_major,0), NULL, "key3");

	return 0;
}


static void __exit key_drv_exit(void)
{
	
	device_destroy(key_dev->cls, MKDEV(key_dev->dev_major,0));
	class_destroy(key_dev->cls);
	unregister_chrdev(key_dev->dev_major, "key_drv");
	kfree(key_dev);
}

module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");


1���жϺ�--����һ�����룬��Ҫͨ��һ���ķ�ʽȥ��ȡ��
	��3.14.0�ں��У����豸���л�ȡ

	��ȡ�жϺŵ�������
		1�� �궨��
				IRQ_EINT(����)
		2���豸���ļ���
			arch/arm/boot/dts/exynos4412-fs4412.dts
			
	Ӳ�����ӣ�
			key ---- gpx1_2--- EINT10
	

		arch/arm/boot/dts/exynos4412.dtsi
	�豸���ļ���arch/arm/boot/dts/exynos4x12-pinctrl.dtsi
		 gpx1: gpx1 {
                        gpio-controller;
                        #gpio-cells = <2>;

                        interrupt-controller;
                        interrupt-parent = <&gic>;
                        interrupts = <0 24 0>, <0 25 0>, <0 26 0>, <0 27 0>,
                                     <0 28 0>, <0 29 0>, <0 30 0>, <0 31 0>;
                        #interrupt-cells = <2>;
                };

			��ʽ�е�<X Y Z>
			X��GIC_SPI����GIC_PPI
			Y�������жϺ�
			Z��������ʽ
			1 = low-to-high edge triggered
			2 = high-to-low edge triggered 
			4 = active high level-sensitive
			8 = active low level-sensitive
			
		gic��exynos4.dtsi�ļ��ж������£�  
			gic: interrupt-controller@10490000 {
				compatible = "arm,cortex-a9-gic";
				#interrupt-cells = <3>;
				interrupt-controller;
				reg = <0x10490000 0x1000>, <0x10480000 0x100>;
			};
		gic�����ļ�Ϊdrivers/irqchip/irq-gic.c �� drivers/irqchip/irqchip.c 
		��ʼ������Ϊirqchip_init
		�ο���https://blog.csdn.net/fchyang/article/details/82893045
		
	�ڱ�̹����У���Ҫ�����Լ��Ľڵ�--������ǰ�豸�õ��жϺ� 
		 arch/arm/boot/dts/exynos4412-fs4412.dts  +51
			
			key_drv_node{
                compatible = "test_key";
                interrupt-parent = <&gpx1>;
                interrupts = <2 4> ;
			};

			
	�����豸���ļ���
		make dtbs
	����dtbs�ļ���
		cp -raf arch/arm/boot/dts/exynos4412-fs4412.dtb  /tftpboot/
		
	���������壺ls /proc/device-tree/key_drv_node/	
	
2,��������ȥͨ�������ȡ���жϺţ����������ж�(ʵ���жϴ�����)

	a,��ȡ���жϺ��룺
		int get_irqno_from_node(void)
		{
			int irqno;
			// ��ȡ���豸���е��ڵ�
			struct device_node *np = of_find_node_by_path("/key_drv_node");
			if(np){
				printk("find node ok\n");
			}else{
				printk("find node failed\n");
			}

			// ͨ���ڵ�ȥ��ȡ���жϺ���
			irqno =  irq_of_parse_and_map(np, 0);
			printk("irqno = %d\n", irqno);
			
			return irqno;
		}
		key_dev->irqno = get_irqno_from_node();


	b�������ж�
	int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char * name, void * dev)

		����1�� �豸��Ӧ���жϺ�
		����2�� �жϵĴ�����
				typedef irqreturn_t (*irq_handler_t)(int, void *);
		����3��������ʽ
				#define IRQF_TRIGGER_NONE	    0x00000000  //�ڲ������������жϵ�ʱ��ı�־
				#define IRQF_TRIGGER_RISING	    0x00000001 //������
				#define IRQF_TRIGGER_FALLING	0x00000002 //�½���
				#define IRQF_TRIGGER_HIGH	    0x00000004  // �ߵ�ƽ
				#define IRQF_TRIGGER_LOW	    0x00000008 //�͵�ƽ����
		����4���жϵ��������Զ���,��Ҫ�Ǹ��û��鿴��
				/proc/interrupts
		����5�����ݸ�����2�к���ָ���ֵ
		����ֵ�� ��ȷΪ0�������0

        ret = request_irq(key_dev->irqno, key_irq_handler,\
                            IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, \
                            "key3_eint10", NULL);
		if(ret != 0)
		{
			printk("request_irq error\n");
			return ret;
		}			
		
		����2�ĸ�ֵ��
		irqreturn_t key_irq_handler(int irqno, void *devid)
		{
			printk("-------%s-------------\n", __FUNCTION__);
			return IRQ_HANDLED;
		}

		
		�ͷ��жϣ�
			void free_irq(unsigned int irq, void *dev_id)
			����1�� �豸��Ӧ���жϺ�
			����2����request_irq�е�5����������һ��
			free_irq(key_dev->irqno, NULL);
			ע�⣺��ж������ʱ����free_irq(key_dev->irqno, NULL) �������ٴμ�����������ִ���
3�������н�Ӳ�������������ݴ��ݸ��û�
	a��Ӳ����λ�ȡ����
		key�� ���º�̧�� 1/0
		��ȡkey��Ӧ��gpio��״̬�������жϰ��»���̧��
		
		��ȡkey��Ӧgpio�ļĴ���--���ݼĴ���
		
		//��ȡ���ݼĴ���
		key_dev->reg_base  = ioremap(GPX1CON, 8);
		
		int value = readl(key_dev->reg_base + 4) & (1<<2);

	b��������δ��ݸ��û�
		struct key_event{
			int code; // ��ʾ����������:  home, esc, Q,W,E,R,T, ENTER
			int value; // ��ʾ���»���̧�� 1 / 0
		};
		���жϴ�����������ݣ�
			key_dev->event.code = KEY_ENTER;
			key_dev->event.value = 0;


		��xxx_read�н����ݴ��ݸ��û�
			ret = copy_to_user(buf, &key_dev->event,  count);

	c���û�����õ�--��дӦ�ó���
		while(1)
		{
			read(fd, &event, sizeof(struct key_event));

			if(event.code == KEY_ENTER)
			{
				if(event.value)
				{
					printf("APP__ key enter pressed\n");
				}else{
					printf("APP__ key enter up\n");
				}
			}
		}

4��ʵ���ļ�IOģ��֮һ��������ͬ������
	�ļ�ioģ�ͣ�
			1��������
			2������
			3����·����--select/poll
			4, �첽�ź�֪ͨfasync

	����: �������ڶ�ȡ�ⲿ�豸����Դ(����)����Դû��׼���ã����̾ͻ�����
		linuxӦ���У��󲿷ֵĺ����ӿڶ�������
			scanf();
			read();
			write();
			accept();
	��������Ҫ����
		1,����ǰ���̼��뵽�ȴ�����ͷ��
			add_wait_queue(wait_queue_head_t * q, wait_queue_t * wait)
		2������ǰ����״̬���ó�TASK_INTERRUPTIBLE
			set_current_state(TASK_INTERRUPTIBLE)
		3���ó�����--����
			schedule(void)
	
	�������ܵĽӿڣ���ͬ������������ӿڣ�
		wait_event_interruptible(wq, condition)

	�������ȥд����
		1���ȴ�����ͷ
				wait_queue_head_t

				init_waitqueue_head(wait_queue_head_t *q);
		
		2������Ҫ�ȴ�(û������)��ʱ�򣬽�������
			wait_event_interruptible(wait_queue_head_t wq, condition) // �ڲ��ṹ��һ���ȴ�������/�ڵ�wait_queue_t
			����1�� �ȴ�����ͷ
			����2�� �����������Ϊ�٣��ͻ�ȴ������Ϊ�棬�Ͳ���ȴ�
					������һ��־λ������ʾ�Ƿ�������


		3����һ�����ʵ�ʱ��(������)���Ὣ���̻���
			wake_up_interruptible(wait_queue_head_t *q)

			�÷���
				wake_up_interruptible(&key_dev->wq_head);
				//ͬʱ���ñ�־λ
				key_dev->key_state  = 1;
	
5�� �������� �ڶ�д��ʱ�����û�����ݣ����̷��أ����ҷ���һ��������
		�õĻ�Ƚ��٣���Ϊ�ȽϺ���Դ

	open("/dev/key0", O_RDWR|O_NONBLOCK);
	------------------------------------
	��������Ҫȥ���֣���ǰģʽ���������Ƿ�����
	//�����ǰ�Ƿ�����ģʽ������û�����ݣ�������һ��������
	if(filp->f_flags & O_NONBLOCK && !key_dev->key_state)
		return -EAGAIN;

6����·����--select��poll
	poll��Ӧ�ã�
	1�� ��Ҫ�򿪶���ļ�(����豸)

	2�� ����poll��ʵ�ּ��fd�Ķ���д������
		#include <poll.h>

       int poll(struct pollfd *fds, nfds_t nfds, int timeout);
	   ����1�� ��ʾ����ļ�����������
			struct pollfd���������ļ�����������Ϣ
			struct pollfd {
               int   fd;  //�ļ�������
               short events;   //ϣ�����fd��ʲô�¼�������д������
							POLLIN ����
							POLLOUT д��
							POLLERR����
               short revents;    //�����������ʾ��ǰ��fd�Ƿ��ж���д������
							//�����жϣ����ں��Զ���ֵ
							POLLIN ����
							POLLOUT д��
							POLLERR����
			};
		����2������ص�fd�ĸ���
		����3�� ��ص�ʱ�䣺
					���� ��ʾ��ض���ms
					������ ���޵�ʱ��ȥ���
					0�� �ȴ�0ms�������ڷ�����
		����ֵ�� ����������
				����0����ʾfd��������
				����0�� ʱ�䵽

	
		
7,���Ӧ����ʹ��poll���豸�ļ������˼�أ���ô�豸�����ͱ���ʵ��poll�ӿ�
	unsigned int key_drv_poll(struct file *filp, struct poll_table_struct *pts)
	{
		
		// ����һ��maskֵ
		unsigned int mask;
		// ����poll_wait,����ǰ�ȴ�����ע��ϵͳ��
		poll_wait(filp, &key_dev->wq_head, pts);
		
		// 1����û�����ݵ�ʱ�򷵻�һ��0
		if(!key_dev->key_state)
			mask = 0;

		// 2�������ݷ���һ��POLLIN
		if(key_dev->key_state)
			mask |= POLLIN;

		return mask;
		
	}

	const struct file_operations key_fops = {
		.poll = key_drv_poll,
		
	};
	��app����  
	 poll();  
	��kernel:��  
	 do_sys_poll  
	 |----do_poll
    �ο���https://blog.csdn.net/u012830148/article/details/80465789}}}
	
8���첽�ź�֪ͨ�� /*{{{*/

    ���ж��źţ�signal���ּ��Ϊ�źţ�����֪ͨ���̷������첽�¼��������������Ƕ��жϻ��Ƶ�һ��ģ�⣬
    ��ԭ���ϣ�һ�������յ�һ���ź��봦�����յ�һ���ж��������˵��һ���ġ��ź��ǽ��̼�ͨ�Ż�����Ψһ
    ���첽ͨ�Ż��ƣ�һ�����̲���ͨ���κβ������ȴ��źŵĵ����ʵ�ϣ�����Ҳ��֪���źŵ���ʲôʱ�򵽴
    ����֮����Ի���ͨ��ϵͳ����kill�������ж��źš��ں�Ҳ������Ϊ�ڲ��¼��������̷����źţ�֪ͨ���̷�����ĳ���¼���
    �źŻ��Ƴ��˻���֪ͨ�����⣬�����Դ��ݸ�����Ϣ��

	�յ��źŵĽ��̶Ը����ź��в�ͬ�Ĵ����������������Է�Ϊ���ࣺ

	��һ����       �����жϵĴ�����򣬶�����Ҫ������źţ����̿���ָ�����������ɸú���������
	�ڶ��ַ����ǣ�����ĳ���źţ��Ը��źŲ����κδ�������δ������һ����
	�����ַ����ǣ��Ը��źŵĴ�����ϵͳ��Ĭ��ֵ������ȱʡ�������Դ󲿷ֵ��źŵ�ȱʡ������ʹ�ý�����ֹ��


	����ͨ��ϵͳ����signal��ָ�����̶�ĳ���źŵĴ�����Ϊ��
	
	�������ݵ�ʱ�������ᷢ���ź�(SIGIO)��Ӧ�ã��Ϳ����첽ȥ��д���ݣ���������ȥ��д

	a,Ӧ��--�����źţ���Ҫ�Ƕ�д����
		void catch_signale(int signo)
		{
			if(signo == SIGIO)
			{
				printf("we got sigal SIGIO");
				// ��ȡ����
				read(fd, &event, sizeof(struct key_event));
				if(event.code == KEY_ENTER)
				{  
					if(event.value)
					{
						printf("APP__ key3 down\n");
					}else
					{
						printf("APP__ key3 up\n");
					}
				}
			}
		}

		// 1,�����źŴ�����
		signal(SIGIO,catch_signale);
		// 2������ǰ�������ó�SIGIO����������
		fcntl(fd, F_SETOWN, getpid());

		// 3����ioģʽ���ó��첽ģʽ
		int flags  = fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, flags | FASYNC );
		
		ע��
		ʵ���첽֪ͨ���ں���Ҫ֪�������������ĸ��ļ�(filp)��ʲô�ź�(SIGIIO)�������ĸ�����(pid)��
		�յ��źź���ʲô(sig_handler)����Щ��������ǰ������������ˣ�����ǰ���������ں˰�æʵ���ˣ�
		���ԣ�����ֻ��Ҫʵ�ֵ����������һ���򵥵Ĵ��Ρ�
		
		signal()����
		#include <signal.h>
		typedef void (*sighandler_t)(int);
		sighandler_t signal(int signum, sighandler_t handler);
		��һ������signum��ָ������Ҫ������ź����ͣ�������ȡ����SIGKILL��SIGSTOP����κ�һ���źš� �� 
		�ڶ�������handler�����������źŹ����Ķ�����������ȡ��������ֵ�� 
		(1)SIG_IGN ��
		������ű�ʾ���Ը��źš� 
		(2)SIG_DFL 
		������ű�ʾ�ָ����źŵ�ϵͳĬ�ϴ�����д�˴�����Ĭ��Ҳ��ִ��ϵͳĬ�ϲ�����
		(3)sighandler_t���͵ĺ���ָ��
		
	b������--�����ź�
		1����Ҫ�ͽ��̽��й���--��¼�źŸ÷��͸�˭
			���ʵ��һ��fasync�Ľӿ�
			struct fasync_struct *fasync;
            fasync_struct�ṹ��������Ŷ�Ӧ�豸�ļ�����Ϣ(��fd, filp)�������ں�������
			int key_drv_fasync(int fd, struct file *filp, int on)
			{
				//ֻ��Ҫ����һ��������¼�źŸ÷��͸�˭
				return fasync_helper(fd, filp, on,  &key_dev->fasync);

			}
		2����ĳ���ض���ʱ��ȥ�����źţ��������ݵ�ʱ��
			//�����ź�
			kill_fasync(&key_dev->fasync, SIGIO, POLLIN);
		3.�ر��豸
			int key_drv_close (struct inode *inode, struct file *filp)
			{
				printk("-------%s-------------\n", __FUNCTION__);
				
				return key_drv_fasync(-1, filp, 0);

			}
		ע��
		Ҫʵ�ִ��Σ�������Ҫ��һ���ṹ��struct fasync_struct��ӵ��ں˵��첽�����У�
		����ṹ��������Ŷ�Ӧ�豸�ļ�����Ϣ(��fd, filp)�������ں�������һ���յ��źţ�
		�ں˾ͻ��������ν���첽����ͷ�ҵ���Ӧ���ļ�(fd)������filp->owner���ҵ���Ӧ�Ľ���PID��
		���ҵ��ö�Ӧ��sig_handler�ˡ�
		
		fasync��Ϊ��ʹ�����Ķ�д��Ӧ�ó���Ķ�д�ֿ���ʹ��Ӧ�ó��������������д��ʱ��ȥ������¡�
		Ӧ�ó���ͨ��fcntl���Լ���SIGIO�źŰ�װ�Լ�����Ӧ������
		����ͨ��kill_fasync(&async, SIGIO, POLL_IN); ��SIGIO�źŸ�Ӧ�ó���Ӧ�ó���͵����Լ���װ����Ӧ����ȥ����
		fasync_helper���þ��ǳ�ʼ��fasync������������������ڴ���������ԣ������������release���fasync_helper��ʼ���Ķ���free����
		/*}}}*/

9-�жϵ��°벿
	�ж���һ���ܰԵ��Ķ�����������һ�����յ��жϣ��ͻ�������ִ�еĴ��룬�����жϴ�������������жϴ�������û�н�ֹ�жϣ����жϴ�����ִ�й��������п��ܱ������жϴ�ϡ�����������ԭ�򣬴�Ҷ�ϣ���жϴ�����ִ�е�Խ��Խ�á�

    ���⣬�ж��������в�����������Ҳ�������ж����������ܸɵ��¡�
    ���������ԭ���ں˽��������жϴ������̷�Ϊ���ϰ벿���°벿���ϰ벿����֮ǰ��˵���жϴ�����������������Ӧ�жϣ�������һЩ�������ж���Ӧ֮������Ҫ�������顣��һЩ��Ҫ���жϴ����������ִ�еĲ������ں˽�����������°벿ִ�С�

    ����������������linux�ں��У�������һ�����ܵ����ݣ�������ͨ���жϸ����ں˴������ݣ��ں˻��������жϴ��������ϰ벿��ִ��һЩ����Ӳ���ı�Ҫ���ã���Ϊ�������ж���Ӧ����Ҫ�ɵ����顣���ţ��ں˵��ö�Ӧ���°벿�����������������յ������ݣ���Ϊ���ݴ���û��Ҫ���жϴ�������������ִ�У����Խ��ж��ó����������ȵ����顣
	
	���������ַ�����ʵ���°벿��

	1��softirq�� ����ȽϿ죬�����ں˼���Ļ��ƣ���Ҫ�޸������ں�Դ�룬���Ƽ�Ҳ������
	2��tasklet�� �ڲ�ʵ��ʵ�ʵ�����softirq
				 tasklet��ʵ���ǽ�������������жϵĻ���֮�ϵģ���HI_SOFTIRQ��TASKLET_SOFTIRQ��������û��ʲô����
				 ֻ����HI_SOFTIRQ�����ȼ�����һЩ
	3, workqueue: ��������
	
	1��tasklet��
		struct tasklet_struct
		{
			struct tasklet_struct *next;
			unsigned long state;
			atomic_t count;
			void (*func)(unsigned long); // �°벿��ʵ���߼�
			unsigned long data; // ���ݸ�func
		};

		a�� ��ʼ��
			struct tasklet_struct mytasklet;

			tasklet_init(struct tasklet_struct * t, void(* func)(unsigned long), unsigned long data)
			������
			t��tasklet_struct�ṹ��ָ��
			func: �����°벿�ص�������
			data: �ص����������ṹ�������ַ��
			tasklet_init(&key_dev->mytasklet, key_tasklet_half_irq, 45);
			
			���ӣ�
			void key_tasklet_half_irq(unsigned long data)
			{
				// ��ʾ������,��Ҫȥ������������/�ȴ�����
				wake_up_interruptible(&key_dev->wq_head);
				//ͬʱ���ñ�־λ
				key_dev->key_state  = 1;

				//�����ź�
				kill_fasync(&key_dev->faysnc, SIGIO, POLLIN);
			}

			tasklet_init(&key_dev->mytasklet, key_tasklet_half_irq, 45);
			void tasklet_init(struct tasklet_struct *t,
					  void (*func)(unsigned long), unsigned long data)
			{
				t->next = NULL;
				t->state = 0;
				atomic_set(&t->count, 0);
				t->func = func;
				t->data = data;
			}

		b�����ϰ벿�з��뵽�ں��߳���--����
			// �����°벽
			tasklet_schedule(&key_dev->mytasklet);
			
			void __tasklet_schedule(struct tasklet_struct *t)
			{
				unsigned long flags;

				local_irq_save(flags);
				t->next = NULL;
				*__this_cpu_read(tasklet_vec.tail) = t;
				__this_cpu_write(tasklet_vec.tail, &(t->next));
				raise_softirq_irqoff(TASKLET_SOFTIRQ);
				local_irq_restore(flags);
			}
		�������жϳ�ʼ������
			void __init softirq_init(void)
			{
				int cpu;

				for_each_possible_cpu(cpu) {
					per_cpu(tasklet_vec, cpu).tail =
						&per_cpu(tasklet_vec, cpu).head;
					per_cpu(tasklet_hi_vec, cpu).tail =
						&per_cpu(tasklet_hi_vec, cpu).head;
				}

				open_softirq(TASKLET_SOFTIRQ, tasklet_action);
				open_softirq(HI_SOFTIRQ, tasklet_hi_action);
			}
			
		c��ģ��ж�ص�ʱ��
			tasklet_kill(&key_dev->mytasklet);
			
		@taskletֻ������һ��CPU��ͬ����ִ�У���ͬ��tasklet�����ڲ�ͬ��CPU��ͬ����ִ�С�
		@tasklet��ʵ���ǽ�������������жϵĻ���֮�ϵģ���HI_SOFTIRQ��TASKLET_SOFTIRQ��������û��ʲô����
		  ֻ����HI_SOFTIRQ�����ȼ�����һЩ
		@����tasklet�������ж���ʵ�ֵģ����������ж�һ������˯�ߡ������������������ڲ��ܺ��е���˯�ߵĶ���
		  ������ź��������û��ռ俽�����ݻ��ֹ������ڴ�ȡ�
		@һ��tasklet�ܹ�����ֹ����֮������ʹ��,������ִ��ֱ������ʹ�ܵĴ����뱻��ֹ�Ĵ�����ͬ.
		@tasklet�Ĵ��л�ʹtasklet���������ǿ������,��˼����豸�������򿪷��ߵĹ�����
		@ÿ��cpuӵ��һ��tasklet_vec�����������ĸ�cpu��tasklet_vec�����Ǹ��ݵ�ǰ�߳����������ĸ�cpu�������ġ�

	�ο���https://blog.csdn.net/fontlose/article/details/8279113
	2���������к͹���
		�������к� tasklet���Ĳ�ͬ�ǹ������еĺ�������ʹ�����ߣ���tasklet�ĺ����ǲ�����ʹ�����ߵġ�
		
		typedef void (*work_func_t)(struct work_struct *work);

		struct work_struct {
			atomic_long_t data;
			struct list_head entry;
			work_func_t func;
		};

		a�� ��ʼ��
			
			void work_irq_half(struct work_struct *work)
			{
				printk("-------%s-------------\n", __FUNCTION__);
				// ��ʾ������,��Ҫȥ������������/�ȴ�����
				wake_up_interruptible(&key_dev->wq_head);
				//ͬʱ���ñ�־λ
				key_dev->key_state  = 1;

				//�����ź�
				kill_fasync(&key_dev->faysnc, SIGIO, POLLIN);
				
			}
			struct work_struct mywork;

			INIT_WORK(struct work_struct *work, work_func_t func);

		b, ���ϰ벿�з��뵽�ں��߳���--����

			schedule_work(&key_dev->mywork);
			
		c.ж��ʱ���ٹ�������	
		destroy_workqueue(&key_dev->mywork);
