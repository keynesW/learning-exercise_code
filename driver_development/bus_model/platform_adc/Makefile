

CROSS_COMPILE=arm-none-linux-gnueabi-
CC=$(CROSS_COMPILE)gcc
KERNEL_DIR=/home/keynes/embeded_linux/linux-3.14
CUR_DIR=$(shell pwd)
ROOTFS_DIR=/home/keynes/transplant_nfs_tftp/rootfs/
MODULE_NAME=adc_driver
APP_NAME=test

ifeq ($(KERNELRELEASE), )

all:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) modules
	$(CC) $(APP_NAME).c -o $(APP_NAME)
clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
install:
	cp *.ko $(APP_NAME)  $(ROOTFS_DIR)/work
else

	obj-m += $(MODULE_NAME).o
endif


