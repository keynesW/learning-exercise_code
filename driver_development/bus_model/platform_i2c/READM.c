主要内容：
1，mpu6050驱动实现的模型
	2条总线：platform_bus , i2c_bus
	2个设备：i2c控制器，mpu6050
	2个驱动：i2c控制器驱动，mpu6050驱动

	

2，i2c子系统驱动框架
	platform_driver_register(&s3c24xx_i2c_driver);//
	make menuconfig
		Device Drivers  --->
			-*- I2C support  ---> //编译i2c-core.c
				I2C Hardware Bus support  --->
					<*> S3C2410 I2C Driver // i2c-s3c2410.c
	请仔细阅读i2c-s3c2410.c文件。
	static int __init i2c_adap_s3c_init(void)
	{
		return platform_driver_register(&s3c24xx_i2c_driver);  //i2c总线控制器以平台总线的形式注册进内核。
	}

	/sys/bus/i2c/
	/sys/bus/i2c/devices/i2c-0 
	[root@farsight i2c-0]# cat name
	                       s3c2410-i2c

3, I2c子系统中涉及到的设备树文件：
	i2c控制器地址
		0x1386_0000, 
		0x1387_0000,
		0x1388_0000, 
		0x1389_0000,
		0x138A_0000,
		0x138B_0000, ------ MPU6050
		0x138C_0000, 
		0x138D_0000, 
		0x138E_0000
	
	MPU6050: 从设备地址是0x68
		soc GPB_3---	I2C_SCL5
			GPB_3---  I2C_SDA5
			GPX3_3--- GYRO_INT

	
	在内核中默认就有了i2c0--13860000.i2c


	模板：
		控制器对应的设备树：arch/arm/boot/dts/exynos4.dtsi
		  i2c_0: i2c@13860000 {
                #address-cells = <1>;
                #size-cells = <0>;
                compatible = "samsung,s3c2440-i2c";
                reg = <0x13860000 0x100>;
                interrupts = <0 58 0>;
                clocks = <&clock 317>;
                clock-names = "i2c";
                pinctrl-names = "default";
                pinctrl-0 = <&i2c0_bus>;
                status = "disabled";
        };

		  i2c_5: i2c@138B0000 {
                #address-cells = <1>;
                #size-cells = <0>;
                compatible = "samsung,s3c2440-i2c";
                reg = <0x138B0000 0x100>;
                interrupts = <0 63 0>;
                clocks = <&clock 322>;
                clock-names = "i2c";
                status = "disabled";
        };
    注：该节点匹配成功，即会执行s3c24xx_i2c_probe函数。
	其中就会装载驱动所使用的adapter，
	i2c->adap.algo = &s3c24xx_i2c_algorithm;
	
	描述从设备信息的设备树的模板
		arch/arm/boot/dts/exynos4412-fs4412.dts


		 i2c@13860000 {
                #address-cells = <1>;
                #size-cells = <0>;
                samsung,i2c-sda-delay = <100>;
                samsung,i2c-max-bus-freq = <20000>;
                pinctrl-0 = <&i2c0_bus>;
                pinctrl-names = "default";
                status = "okay";

                s5m8767_pmic@66 {
                        compatible = "samsung,s5m8767-pmic";
                        reg = <0x66>;
				}
					
		}

	新增加i2c从设备，
    arch/arm/boot/dts/exynos4412-fs4412.dts增加i2c5控制和它包含了设备设备

	    i2c@138B0000 {/*i2c adapter5信息*/
                #address-cells = <1>;
                #size-cells = <0>;
                samsung,i2c-sda-delay = <100>;
                samsung,i2c-max-bus-freq = <20000>;
                pinctrl-0 = <&i2c5_bus>;
                pinctrl-names = "default";
                status = "okay";   //其实是对"./arch/arm/boot/dts/exynos4.dtsi +387"处的status = "disabled"的重写
	                               //相同的节点的不同属性信息都会被合并，相同节点的相同的属性会被重写
                mpu6050@68 { /*i2c client信息*/
                        compatible = "invensense,mpu6050";
                        reg = <0x68>;
				};
        };

		保存后make dtbs

		cp -raf arch/arm/boot/dts/exynos4412-fs4412.dtb /tftpboot/

     参看：cat /sys/bus/platform/devices/138b0000.i2c/i2c-5/5-0068/name
	 
	 I2C控制器驱动s3c24xx_i2c_driver

	static struct platform_driver s3c24xx_i2c_driver = {
		.probe		= s3c24xx_i2c_probe, 
		.remove		= s3c24xx_i2c_remove,
		.id_table	= s3c24xx_driver_ids,
		.driver		= {
			.owner	= THIS_MODULE,
			.name	= "s3c-i2c",
			.pm	= S3C24XX_DEV_PM_OPS,
			.of_match_table = of_match_ptr(s3c24xx_i2c_match),
		},
	};
	static int s3c24xx_i2c_probe(struct platform_device *pdev)
	{
		...
		i2c->adap.algo = &s3c24xx_i2c_algorithm; //添加实现i2c数据传输的方法
		ret = i2c_add_numbered_adapter(&i2c->adap); //将挂在i2c controller下的i2c从设备
		                                   （其中就有mpu6050子节点）以i2c_client的形式注册到i2c_bus_type
										   总线中，并将adapter适配器赋值给每个i2c_client
		...
	}	
	创建i2c_client的函数
	s3c24xx_i2c_probe
		i2c_add_numbered_adapter
			|
			__i2c_add_numbered_adapter
				|
				i2c_register_adapter
					|
					device_register
					of_i2c_register_devices  //通过对dt进行解析，对挂在i2c controller下的i2c从设备进行注册
						|
						i2c_new_device
							status = device_register(&client->dev);
	struct i2c_client *i2c_new_device(struct i2c_adapter *adap, struct i2c_board_info const *info)

4,mpu6050 driver驱动的编写：
	a， 添加i2c client的信息，必须包含在控制器对应的节点中
	b，直接编写i2c driver
		1，构建i2c driver，并注册到i2c总线
		2，实现probe：
			|
			申请设备号，实现fops
			创建设备文件
			通过i2c的接口去初始化i2c从设备

	几个常用的对象：
	struct i2c_driver {//表示是一个从设备的驱动对象
		int (*probe)(struct i2c_client *, const struct i2c_device_id *);
		int (*remove)(struct i2c_client *);
		struct device_driver driver; //继承了父类
					|
					const char		*name;
					const struct of_device_id	*of_match_table;
		const struct i2c_device_id *id_table;//用于做比对，非设备树的情况
	}
	注册和注销
		int i2c_add_driver( struct i2c_driver *driver);
		void i2c_del_driver(struct i2c_driver *);

    添加设备节点，内核就会为我们在内核中构造一个i2c_client对象并挂接到i2c总线对象的设备链表中以待匹配，这个设备类如下
	struct i2c_client {//描述一个从设备的信息,不需要在代码中创建，因为是由i2c adapter帮我们创建
		unsigned short addr;		//从设备地址，来自于设备树中<reg>
		char name[I2C_NAME_SIZE]; //用于和i2c driver进行匹配，来自于设备树中compatible
		struct i2c_adapter *adapter;//指向当前从设备所存在的i2c adapter
		struct device dev;		// 继承了父类
	};

	struct i2c_adapter {//描述一个i2c控制器，也不是我们要构建，原厂的代码会帮我们构建
		const struct i2c_algorithm *algo; //算法
					|
					int (*master_xfer)(struct i2c_adapter *adap, struct i2c_msg *msgs,int num);
		            //s3c24xx_i2c_doxfer()
		struct device dev; //继承了父类，也会被加入到i2c bus
		int nr; //编号

	}
	注册和注销：
	int i2c_add_adapter(struct i2c_adapter * adapter);
	void i2c_del_adapter(struct i2c_adapter * adap);

		const struct of_device_id  of_mpu6050_id[] = {
				{
					.compatible = "invensense,mpu6050",
				},
				{/*northing to be done*/},

		};


		const struct i2c_device_id mpu_id_table[] = {
				{"mpu6050_drv", 0x1111},
				{/*northing to be done*/},
		};
			
		struct i2c_driver mpu6050_drv = {
			.probe = mpu6050_drv_probe,
			.remove = mpu5060_drv_remove,
			.driver = {
				.name = "mpu6050_drv",//随便写，/sys/bus/i2c/driver/mpu6050_drv
				.of_match_table = of_match_ptr(of_mpu6050_id),
			},
			
			.id_table = mpu_id_table,//非设备树情况下的匹配,在设备树的模式下不需要使用

		};
		
		
	struct i2c_msg {//描述一个从设备要发送的数据的数据包
		__u16 addr;	 //从设备地址，发送给那个从设备
		__u16 flags; //读1还是写0
		__u16 len;		//发送数据的长度
		__u8 *buf;		//指向数据的指针
	};
	//写从设备
	int i2c_master_send(const struct i2c_client * client,const char * buf,int count)
	//读从设备
	int i2c_master_recv(const struct i2c_client * client,char * buf,int count)
	以上两个函数都调用了：
	int i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)

    内核实现原理参考：https://blog.csdn.net/flaoter/article/details/72991086
	                  https://www.cnblogs.com/xiaojiang1025/p/6500540.html
					  https://www.cnblogs.com/downey-blog/p/10485596.html 
	总结：
	1.系统启动时会在/sys/bus目录下创建一个I2C总线。由postcore_initcall(i2c_init)实现，
	  在内核中的名称为i2c_bus_type。
    2.CPU内部的I2C控制器是一个设备，ta的硬件信息在设备树中描述，系统启动的时候，扫描设备树，
	  将该设备节点以设备的形式注册到platform_bus下。该device对应的驱动由i2c-s3c2410.c中的程序实现，
	  其对应的驱动名称为s3c24xx_i2c_driver。它们会以设备树的形式进行匹配（compatible属性）。该驱动
	  中的probe方法完成两件事，第一，创建i2c_adapter（适配器）结构体变量，该结构体中有一个
	  名为algo.master_xfer的方法，用于发送i2c_msg（所有通过I2C接口发送的数据都封装在该结构体当中）。
	  第二，通过对dt进行解析，将挂在i2c controller下的i2c从设备（其中就有mpu6050子节点）以i2c_client的
	  形式注册到i2c_bus_type总线中，并将adapter适配器赋值给每个i2c_client（注：i2c_client就是总线模型中
	  的device，只是换了个名字）。
    3.编写我们的mpu6050的driver程序，和i2c_bus_type总线中的i2c_client匹配，匹配成功后取出i2c_client中
	  的adapter适配器，利用其中的algo.master_xfer方法发送I2C数据包i2c_msg。
					  
					  
					  
5，陀螺仪和加速度工作原理，它们的应用
	陀螺仪的作用：
		原理：
			小时候玩过陀螺，如果给它一定的旋转速度，陀螺会竖立旋转起来而不会倒,
			主要因为高速旋转有抗拒方向改变的趋向
			
			陀螺仪就是内部的转子高速旋转，形成一个固定的初始化的参考平面，
			这样就可以通过测量初始的参考平面偏差计算出物体的旋转情况
			陀螺仪的强项在于测量设备自身的旋转运动

		陀螺仪的产生：
			1850年法国的物理学家福柯(J.Foucault)为了研究地球自转，首先发现高速转动中的转子(rotor)，
			由于惯性作用它的旋转轴永远指向一固定方向，他用希腊字gyro(旋转)和skopein(看)
			两字合为gyro scopei一字来命名这种仪表

		陀螺仪的基本部件：
			(1) 陀螺转子，转子装在一支架内
			(2)内、外环，它是使陀螺自转轴获得所需角转动自由度的结构
				内环可环绕平面两轴作自由运动
				在内环架外加上一外环架，可以环绕平面做三轴作自由运动
			(3) 附件(是指力矩马达、信号传感器等)。

		陀螺仪的数据获取：		
			XYZ分别代表设备围绕XYZ三个轴旋转的角速度，陀螺仪可以捕捉很微小的运动轨迹变化，
			因此可以做高分辨率和快速反应的旋转检测，但不能测量当前的运行方向

		应用：
			1，陀螺仪用于飞行体运动的自动控制系统中，作为水平、垂直、俯仰、航向和角速度传感器
			2，手机上的摄像头配合使用，比如防抖
			3，各类手机游戏的传感器，包括一些第一视角类射击游戏，陀螺仪完整监测游戏者手的位移
			   手机中的陀螺仪最早被iphone4应用，所以被大家所熟知
			4，导航，手机配合GPS，导航能力已经可以达到专用的gps导航仪
	
	重力加速度：
		原理：
			重力施加在物体上,使它产生一个加速度，重力大小和此物体的质量成正比
			物体在不同的运行中，会产生不同的重力，从而可以测量出物体的运动情况

		重力加速度的数据获取：
			加速度测量传感器有x、y、z三轴，注意在手机上屏幕的坐标，以左上角作为原点的，而且Y向下。
			注意区分这两个不同的坐标系。
			加速传感器的单位是加速度m/s2。如果手机平放好，x，y在位置为0，
			而z轴方向加速度=当前z方向加速度-g。由于g（重力加速度）垂直向下，
			则g=-9.81m/s2，即z轴 a=0-(-9.81)=9.81m/s2
		应用：
			1，图像自动翻转
			2，游戏控制
			3，计步器功能

6,寄存器：
		#define PWR_MGMT_1		0x6B //电源管理 典型值：0x00(正常启用)
		#define SMPLRT_DIV		0x19 //采样频率寄存器-25 典型值：0x07(125Hz)
									//寄存器集合里的数据根据采样频率更新
		#define CONFIG			0x1A	//配置寄存器-26-典型值：0x06(5Hz)
										//DLPF is disabled（DLPF_CFG=0 or 7）
		#define GYRO_CONFIG		0x1B//陀螺仪配置-27,可以配置自检和满量程范围
									//典型值：0x18(不自检，2000deg/s)
		#define ACCEL_CONFIG		0x1C	//加速度配置-28 可以配置自检和满量程范围及高通滤波频率
										//典型值：0x01(不自检，2G，5Hz)
		#define ACCEL_XOUT_H	0x3B //59-65,加速度计测量值 XOUT_H
		#define ACCEL_XOUT_L	0x3C  // XOUT_L
		#define ACCEL_YOUT_H	0x3D  //YOUT_H
		#define ACCEL_YOUT_L	0x3E  //YOUT_L
		#define ACCEL_ZOUT_H	0x3F  //ZOUT_H
		#define ACCEL_ZOUT_L	0x40 //ZOUT_L---64
		#define TEMP_OUT_H		0x41 //温度测量值--65
		#define TEMP_OUT_L		0x42
		#define GYRO_XOUT_H		0x43 //陀螺仪值--67，采样频率（由寄存器 25 定义）写入到这些寄存器
		#define GYRO_XOUT_L		0x44
		#define GYRO_YOUT_H		0x45
		#define GYRO_YOUT_L		0x46
		#define GYRO_ZOUT_H		0x47
		#define GYRO_ZOUT_L		0x48 //陀螺仪值--72



7, ioctl:　给驱动发送不同指令
	 应用程序：
		ioctl(fd, cmd, args);
	========================================
	驱动中：xxx_ioctl()
	{
			switch(cmd){
			
			}
	}

	如何定义命令：
		1， 直接定义一个数字
			#define IOC_GET_ACCEL  0x9999
		2, 通过系统的接口
			_IO(x,y)
			_IOR(x,y,z)
			_IOW(x,y,z)

			参数1：表示magic，字符
			参数2：区分不同命令，整数　
			参数３：传给驱动数据类型

			在驱动程序里， ioctl() 函数上传送的变量 cmd 是应用程序用于区别设备驱动程序请求处理内容的值。cmd除了可区别数字外，还包含有助于处理的几种相应信息。 cmd的大小为 32位，共分 4 个域：
			bit31~bit30 2位为 “区别读写” 区，作用是区分是读取命令还是写入命令。
			bit29~bit15 14位为 "数据大小" 区，表示 ioctl() 中的 arg 变量传送的内存大小。
			bit20~bit08  8位为 “魔数"(也称为"幻数")区，这个值用以与其它设备驱动程序的 ioctl 命令进行区别。
			bit07~bit00   8位为 "区别序号" 区，是区分命令的命令顺序序号。
			_IO (魔数， 基数);
			_IOR (魔数， 基数， 变量型)
			_IOW  (魔数， 基数， 变量型)
			_IOWR (魔数， 基数，变量型 )
			
			#define IOC_GET_ACCEL  _IOR('M', 0x34,union mpu6050_data)
			#define IOC_GET_GYRO   _IOR('M', 0x35,union mpu6050_data)
			#define IOC_GET_TEMP   _IOR('M', 0x36,union mpu6050_data)

8,mpu6050的数据
		陀螺仪可测范围为 欧拉角格式±250，±500，±1000，±2000°/秒（dps） ，加速度计可测范围为±2，±4，±8，±16g
		加速度读取的值为：
		AFS_SEL      Full scale rang                  LSB  Sensitivy
			0				+-2g -----------------------16384 LSB/g
			1				+-4g -----------------------8192 LSB/g
			2				+-8g -----------------------4096 LSB/g
			3				+-16g------------------------2048 LSB/g
		
		温度值：
				C = (TEMP_OUT Register Value )/340 + 36.53
			
		陀螺仪值：
			FS_SEL      Full scale rang                  LSB  Sensitivy
			0				+-250 度/s ------------------131 LSB 度/s
			1				+-500 度/s ------------------65.5 LSB 度/s
			2				+-1000 度/s -----------------32.8 LSB 度/s
			3				+-2000 度/s ------------------16.4 LSB 度/s


