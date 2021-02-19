#Makefile

CROSS_COMPLIT=arm-none-linux-gnueabi-
CC=$(CROSS_COMPLIT)gcc
KERNEL_DIR=/home/keynes/embeded_linux/linux-3.14
CUR_DIR=$(shell pwd)
MODULE_NAME=platform_driver
MODULE_NAME1=platform_device
APPNAME=test_platform
ROOTFS_DIR=/home/keynes/transplant_nfs_tftp/rootfs

ifeq ($(KERNELRELEASE), )
all:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) modules
clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
	$(CC)  $(APPNAME).c -o $(APPNAME)
install:
	cp *.ko  $(ROOTFS_DIR)/work

else
	obj-m += $(MODULE_NAME).o $(MODULE_NAME1).o 
endif
