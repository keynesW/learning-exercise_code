#Makefile

CROSS_COMPILE = arm-none-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc

KERNEL_DIR=/home/keynes/embeded_linux/linux-3.14/
ROOTFS_DIR=/home/keynes/transplant_nfs_tftp/rootfs

MODULE_NAME = i2c_drv_mpu6050
APP_NAME = test_mpu6050
CUR_DIR = $(shell pwd)

ifeq ($(KERNELRELEASE), )
all :
	make -C  $(KERNEL_DIR) M=$(CUR_DIR) modules
	$(CC) $(APP_NAME).c  -o $(APP_NAME)
clean :
	make -C  $(KERNEL_DIR) M=$(CUR_DIR) clean
	rm -rf $(APP_NAME)	
install:
	cp -raf *.ko $(APP_NAME)   $(ROOTFS_DIR)/work
else 
	obj-m += $(MODULE_NAME).o
endif

#i2c_drv_mpu6050.c
#Makefile
#mpu6050.h
#READM.c
#test_mpu6050.c
