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
	//演示如何获取到中断号
	int ret;

	// 1，设定一个全局的设备对象
	key_dev = kzalloc(sizeof(struct key_desc),  GFP_KERNEL);

	// 2,申请主设备号
	key_dev->dev_major = register_chrdev(0, "key_drv", &key_fops);

	// 3,创建设备节点文件
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


1，中断号--就是一个号码，需要通过一定的方式去获取到
	在3.14.0内核中，从设备树中获取

	获取中断号到方法：
		1， 宏定义
				IRQ_EINT(号码)
		2，设备树文件中
			arch/arm/boot/dts/exynos4412-fs4412.dts
			
	硬件连接：
			key ---- gpx1_2--- EINT10
	

		arch/arm/boot/dts/exynos4412.dtsi
	设备树文件：arch/arm/boot/dts/exynos4x12-pinctrl.dtsi
		 gpx1: gpx1 {
                        gpio-controller;
                        #gpio-cells = <2>;

                        interrupt-controller;
                        interrupt-parent = <&gic>;
                        interrupts = <0 24 0>, <0 25 0>, <0 26 0>, <0 27 0>,
                                     <0 28 0>, <0 29 0>, <0 30 0>, <0 31 0>;
                        #interrupt-cells = <2>;
                };

			形式中的<X Y Z>
			X：GIC_SPI或者GIC_PPI
			Y：物理中断号
			Z：触发方式
			1 = low-to-high edge triggered
			2 = high-to-low edge triggered 
			4 = active high level-sensitive
			8 = active low level-sensitive
			
		gic在exynos4.dtsi文件中定义如下：  
			gic: interrupt-controller@10490000 {
				compatible = "arm,cortex-a9-gic";
				#interrupt-cells = <3>;
				interrupt-controller;
				reg = <0x10490000 0x1000>, <0x10480000 0x100>;
			};
		gic驱动文件为drivers/irqchip/irq-gic.c 和 drivers/irqchip/irqchip.c 
		初始化函数为irqchip_init
		参考：https://blog.csdn.net/fchyang/article/details/82893045
		
	在编程过程中，需要定义自己的节点--描述当前设备用的中断号 
		 arch/arm/boot/dts/exynos4412-fs4412.dts  +51
			
			key_drv_node{
                compatible = "test_key";
                interrupt-parent = <&gpx1>;
                interrupts = <2 4> ;
			};

			
	编译设备树文件：
		make dtbs
	更新dtbs文件：
		cp -raf arch/arm/boot/dts/exynos4412-fs4412.dtb  /tftpboot/
		
	重启开发板：ls /proc/device-tree/key_drv_node/	
	
2,在驱动中去通过代码获取到中断号，并且申请中断(实现中断处理方法)

	a,获取到中断号码：
		int get_irqno_from_node(void)
		{
			int irqno;
			// 获取到设备树中到节点
			struct device_node *np = of_find_node_by_path("/key_drv_node");
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
		key_dev->irqno = get_irqno_from_node();


	b，申请中断
	int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char * name, void * dev)

		参数1： 设备对应的中断号
		参数2： 中断的处理函数
				typedef irqreturn_t (*irq_handler_t)(int, void *);
		参数3：触发方式
				#define IRQF_TRIGGER_NONE	    0x00000000  //内部控制器触发中断的时候的标志
				#define IRQF_TRIGGER_RISING	    0x00000001 //上升沿
				#define IRQF_TRIGGER_FALLING	0x00000002 //下降沿
				#define IRQF_TRIGGER_HIGH	    0x00000004  // 高点平
				#define IRQF_TRIGGER_LOW	    0x00000008 //低电平触发
		参数4：中断的描述，自定义,主要是给用户查看的
				/proc/interrupts
		参数5：传递给参数2中函数指针的值
		返回值： 正确为0，错误非0

        ret = request_irq(key_dev->irqno, key_irq_handler,\
                            IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, \
                            "key3_eint10", NULL);
		if(ret != 0)
		{
			printk("request_irq error\n");
			return ret;
		}			
		
		参数2的赋值：
		irqreturn_t key_irq_handler(int irqno, void *devid)
		{
			printk("-------%s-------------\n", __FUNCTION__);
			return IRQ_HANDLED;
		}

		
		释放中断：
			void free_irq(unsigned int irq, void *dev_id)
			参数1： 设备对应的中断号
			参数2：与request_irq中第5个参数保持一致
			free_irq(key_dev->irqno, NULL);
			注意：在卸载驱动时调用free_irq(key_dev->irqno, NULL) ，否则再次加载驱动会出现错误。
3，驱动中将硬件所产生的数据传递给用户
	a，硬件如何获取数据
		key： 按下和抬起： 1/0
		读取key对应的gpio的状态，可以判断按下还是抬起
		
		读取key对应gpio的寄存器--数据寄存器
		
		//读取数据寄存器
		key_dev->reg_base  = ioremap(GPX1CON, 8);
		
		int value = readl(key_dev->reg_base + 4) & (1<<2);

	b，驱动如何传递给用户
		struct key_event{
			int code; // 表示按键的类型:  home, esc, Q,W,E,R,T, ENTER
			int value; // 表示按下还是抬起 1 / 0
		};
		在中断处理中填充数据：
			key_dev->event.code = KEY_ENTER;
			key_dev->event.value = 0;


		在xxx_read中奖数据传递给用户
			ret = copy_to_user(buf, &key_dev->event,  count);

	c，用户如何拿到--编写应用程序
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

4，实现文件IO模型之一阻塞，等同于休眠
	文件io模型：
			1，非阻塞
			2，阻塞
			3，多路复用--select/poll
			4, 异步信号通知fasync

	阻塞: 当进程在读取外部设备的资源(数据)，资源没有准备好，进程就会休眠
		linux应用中，大部分的函数接口都是阻塞
			scanf();
			read();
			write();
			accept();
	驱动中需要调用
		1,将当前进程加入到等待队列头中
			add_wait_queue(wait_queue_head_t * q, wait_queue_t * wait)
		2，将当前进程状态设置成TASK_INTERRUPTIBLE
			set_current_state(TASK_INTERRUPTIBLE)
		3，让出调度--休眠
			schedule(void)
	
	更加智能的接口，等同于上面的三个接口：
		wait_event_interruptible(wq, condition)

	驱动如何去写代码
		1，等待队列头
				wait_queue_head_t

				init_waitqueue_head(wait_queue_head_t *q);
		
		2，在需要等待(没有数据)的时候，进行休眠
			wait_event_interruptible(wait_queue_head_t wq, condition) // 内部会构建一个等待队列项/节点wait_queue_t
			参数1： 等待队列头
			参数2： 条件，如果是为假，就会等待，如果为真，就不会等待
					可以用一标志位，来表示是否有数据


		3，在一个合适的时候(有数据)，会将进程唤醒
			wake_up_interruptible(wait_queue_head_t *q)

			用法：
				wake_up_interruptible(&key_dev->wq_head);
				//同时设置标志位
				key_dev->key_state  = 1;
	
5， 非阻塞： 在读写的时候，如果没有数据，立刻返回，并且返回一个出错码
		用的会比较少，因为比较耗资源

	open("/dev/key0", O_RDWR|O_NONBLOCK);
	------------------------------------
	驱动中需要去区分，当前模式是阻塞还是非阻塞
	//如果当前是非阻塞模式，并且没有数据，立马返回一个出错码
	if(filp->f_flags & O_NONBLOCK && !key_dev->key_state)
		return -EAGAIN;

6，多路复用--select和poll
	poll的应用：
	1， 需要打开多个文件(多个设备)

	2， 利用poll来实现监控fd的读，写，出错
		#include <poll.h>

       int poll(struct pollfd *fds, nfds_t nfds, int timeout);
	   参数1： 表示多个文件描述符集合
			struct pollfd描述的是文件描述符到信息
			struct pollfd {
               int   fd;  //文件描述符
               short events;   //希望监控fd的什么事件：读，写，出错
							POLLIN 读，
							POLLOUT 写，
							POLLERR出错
               short revents;    //结果描述，表示当前的fd是否有读，写，出错
							//用于判断，是内核自动赋值
							POLLIN 读，
							POLLOUT 写，
							POLLERR出错
			};
		参数2：被监控到fd的个数
		参数3： 监控的时间：
					正： 表示监控多少ms
					负数： 无限的时间去监控
					0： 等待0ms，类似于非阻赛
		返回值： 负数：出错
				大于0，表示fd中有数据
				等于0： 时间到

	
		
7,如果应用中使用poll对设备文件进行了监控，那么设备驱动就必须实现poll接口
	unsigned int key_drv_poll(struct file *filp, struct poll_table_struct *pts)
	{
		
		// 返回一个mask值
		unsigned int mask;
		// 调用poll_wait,将当前等待队列注册系统中
		poll_wait(filp, &key_dev->wq_head, pts);
		
		// 1，当没有数据到时候返回一个0
		if(!key_dev->key_state)
			mask = 0;

		// 2，有数据返回一个POLLIN
		if(key_dev->key_state)
			mask |= POLLIN;

		return mask;
		
	}

	const struct file_operations key_fops = {
		.poll = key_drv_poll,
		
	};
	【app：】  
	 poll();  
	【kernel:】  
	 do_sys_poll  
	 |----do_poll
    参考：https://blog.csdn.net/u012830148/article/details/80465789}}}
	
8，异步信号通知： /*{{{*/

    软中断信号（signal，又简称为信号）用来通知进程发生了异步事件。在软件层次上是对中断机制的一种模拟，
    在原理上，一个进程收到一个信号与处理器收到一个中断请求可以说是一样的。信号是进程间通信机制中唯一
    的异步通信机制，一个进程不必通过任何操作来等待信号的到达，事实上，进程也不知道信号到底什么时候到达。
    进程之间可以互相通过系统调用kill发送软中断信号。内核也可以因为内部事件而给进程发送信号，通知进程发生了某个事件。
    信号机制除了基本通知功能外，还可以传递附加信息。

	收到信号的进程对各种信号有不同的处理方法。处理方法可以分为三类：

	第一种是       类似中断的处理程序，对于需要处理的信号，进程可以指定处理函数，由该函数来处理。
	第二种方法是，忽略某个信号，对该信号不做任何处理，就象未发生过一样。
	第三种方法是，对该信号的处理保留系统的默认值，这种缺省操作，对大部分的信号的缺省操作是使得进程终止。


	进程通过系统调用signal来指定进程对某个信号的处理行为。
	
	当有数据到时候，驱动会发送信号(SIGIO)给应用，就可以异步去读写数据，不用主动去读写

	a,应用--处理信号，主要是读写数据
		void catch_signale(int signo)
		{
			if(signo == SIGIO)
			{
				printf("we got sigal SIGIO");
				// 读取数据
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

		// 1,设置信号处理方法
		signal(SIGIO,catch_signale);
		// 2，将当前进程设置成SIGIO的属主进程
		fcntl(fd, F_SETOWN, getpid());

		// 3，将io模式设置成异步模式
		int flags  = fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, flags | FASYNC );
		
		注：
		实现异步通知，内核需要知道几个东西：哪个文件(filp)，什么信号(SIGIIO)，发给哪个进程(pid)，
		收到信号后做什么(sig_handler)。这些都由上述前两个步骤完成了，而这前两个步骤内核帮忙实现了，
		所以，我们只需要实现第三个步骤的一个简单的传参。
		
		signal()函数
		#include <signal.h>
		typedef void (*sighandler_t)(int);
		sighandler_t signal(int signum, sighandler_t handler);
		第一个参数signum：指明了所要处理的信号类型，它可以取除了SIGKILL和SIGSTOP外的任何一种信号。 　 
		第二个参数handler：描述了与信号关联的动作，它可以取以下三种值： 
		(1)SIG_IGN 　
		这个符号表示忽略该信号。 
		(2)SIG_DFL 
		这个符号表示恢复对信号的系统默认处理。不写此处理函数默认也是执行系统默认操作。
		(3)sighandler_t类型的函数指针
		
	b，驱动--发送信号
		1，需要和进程进行关联--记录信号该发送给谁
			添加实现一个fasync的接口
			struct fasync_struct *fasync;
            fasync_struct结构体用来存放对应设备文件的信息(如fd, filp)并交给内核来管理。
			int key_drv_fasync(int fd, struct file *filp, int on)
			{
				//只需要调用一个函数记录信号该发送给谁
				return fasync_helper(fd, filp, on,  &key_dev->fasync);

			}
		2，在某个特定的时候去发送信号，在有数据的时候
			//发送信号
			kill_fasync(&key_dev->fasync, SIGIO, POLLIN);
		3.关闭设备
			int key_drv_close (struct inode *inode, struct file *filp)
			{
				printk("-------%s-------------\n", __FUNCTION__);
				
				return key_drv_fasync(-1, filp, 0);

			}
		注：
		要实现传参，我们需要把一个结构体struct fasync_struct添加到内核的异步队列中，
		这个结构体用来存放对应设备文件的信息(如fd, filp)并交给内核来管理。一但收到信号，
		内核就会在这个所谓的异步队列头找到相应的文件(fd)，并在filp->owner中找到对应的进程PID，
		并且调用对应的sig_handler了。
		
		fasync是为了使驱动的读写和应用程序的读写分开，使得应用程序可以在驱动读写的时候去做别的事。
		应用程序通过fcntl给自己的SIGIO信号安装自己的响应函数，
		驱动通过kill_fasync(&async, SIGIO, POLL_IN); 发SIGIO信号给应用程序，应用程序就调用自己安装的响应函数去处理。
		fasync_helper作用就是初始化fasync这个东西，包括分配内存和设置属性，最后在驱动的release里把fasync_helper初始化的东西free掉。
		/*}}}*/

9-中断的下半部
	中断是一个很霸道的东西，处理器一旦接收到中断，就会打断正在执行的代码，调用中断处理函数。如果在中断处理函数中没有禁止中断，该中断处理函数执行过程中仍有可能被其他中断打断。出于这样的原因，大家都希望中断处理函数执行得越快越好。

    另外，中断上下文中不能阻塞，这也限制了中断上下文中能干的事。
    基于上面的原因，内核将整个的中断处理流程分为了上半部和下半部。上半部就是之前所说的中断处理函数，它能最快的响应中断，并且做一些必须在中断响应之后马上要做的事情。而一些需要在中断处理函数后继续执行的操作，内核建议把它放在下半部执行。

    拿网卡来举例，在linux内核中，当网卡一旦接受到数据，网卡会通过中断告诉内核处理数据，内核会在网卡中断处理函数（上半部）执行一些网卡硬件的必要设置，因为这是在中断响应后急切要干的事情。接着，内核调用对应的下半部函数来处理网卡接收到的数据，因为数据处理没必要在中断处理函数里面马上执行，可以将中断让出来做更紧迫的事情。
	
	可以有三种方法来实现下半部：

	1，softirq： 处理比较快，但是内核级别的机制，需要修改整个内核源码，不推荐也不常用
	2，tasklet： 内部实现实际调用了softirq
				 tasklet的实现是建立在两个软件中断的基础之上的，即HI_SOFTIRQ和TASKLET_SOFTIRQ，本质上没有什么区别，
				 只不过HI_SOFTIRQ的优先级更高一些
	3, workqueue: 工作队列
	
	1，tasklet：
		struct tasklet_struct
		{
			struct tasklet_struct *next;
			unsigned long state;
			atomic_t count;
			void (*func)(unsigned long); // 下半部的实现逻辑
			unsigned long data; // 传递给func
		};

		a， 初始化
			struct tasklet_struct mytasklet;

			tasklet_init(struct tasklet_struct * t, void(* func)(unsigned long), unsigned long data)
			参数：
			t：tasklet_struct结构体指针
			func: 启动下半部回调函数。
			data: 回调函数参数结构体变量地址。
			tasklet_init(&key_dev->mytasklet, key_tasklet_half_irq, 45);
			
			例子：
			void key_tasklet_half_irq(unsigned long data)
			{
				// 表示有数据,需要去唤醒整个进程/等待队列
				wake_up_interruptible(&key_dev->wq_head);
				//同时设置标志位
				key_dev->key_state  = 1;

				//发送信号
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

		b，在上半部中放入到内核线程中--启动
			// 启动下半步
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
		附：软中断初始化函数
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
			
		c，模块卸载的时候：
			tasklet_kill(&key_dev->mytasklet);
			
		@tasklet只可以在一个CPU上同步地执行，不同的tasklet可以在不同地CPU上同步地执行。
		@tasklet的实现是建立在两个软件中断的基础之上的，即HI_SOFTIRQ和TASKLET_SOFTIRQ，本质上没有什么区别，
		  只不过HI_SOFTIRQ的优先级更高一些
		@由于tasklet是在软中断上实现的，所以像软中断一样不能睡眠、不能阻塞，处理函数内不能含有导致睡眠的动作
		  如减少信号量、从用户空间拷贝数据或手工分配内存等。
		@一个tasklet能够被禁止并且之后被重新使能,它不会执行直到它被使能的次数与被禁止的次数相同.
		@tasklet的串行化使tasklet函数不必是可重入的,因此简化了设备驱动程序开发者的工作。
		@每个cpu拥有一个tasklet_vec链表，具体是哪个cpu的tasklet_vec链表，是根据当前线程是运行在哪个cpu来决定的。

	参考：https://blog.csdn.net/fontlose/article/details/8279113
	2，工作队列和工作
		工作队列和 tasklet最大的不同是工作队列的函数可以使用休眠，而tasklet的函数是不允许使用休眠的。
		
		typedef void (*work_func_t)(struct work_struct *work);

		struct work_struct {
			atomic_long_t data;
			struct list_head entry;
			work_func_t func;
		};

		a， 初始化
			
			void work_irq_half(struct work_struct *work)
			{
				printk("-------%s-------------\n", __FUNCTION__);
				// 表示有数据,需要去唤醒整个进程/等待队列
				wake_up_interruptible(&key_dev->wq_head);
				//同时设置标志位
				key_dev->key_state  = 1;

				//发送信号
				kill_fasync(&key_dev->faysnc, SIGIO, POLLIN);
				
			}
			struct work_struct mywork;

			INIT_WORK(struct work_struct *work, work_func_t func);

		b, 在上半部中放入到内核线程中--启动

			schedule_work(&key_dev->mywork);
			
		c.卸载时销毁工作队列	
		destroy_workqueue(&key_dev->mywork);
