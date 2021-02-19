#Makefile

CROSS_COMPLIE=arm-none-linux-gnueabi-
CC=$(CROSS_COMPLIE)gcc
KERNEL_DIR=/home/keynes/embeded_linux/linux-3.14
CUR_DIR=$(shell pwd)
MODULE_NAME=bus
MODULE_NAME1=driver
MODULE_NAME2=device
ROOTFS_DIR=/home/keynes/transplant_nfs_tftp/rootfs/

ifeq ($(KERNELRELEASE), )
all:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) modules
clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
install:
	cp *.ko  $(ROOTFS_DIR)/work

else
	obj-m += $(MODULE_NAME).o $(MODULE_NAME1).o $(MODULE_NAME2).o
endif
