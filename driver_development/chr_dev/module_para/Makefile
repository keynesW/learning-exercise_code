#Makefile

CROSS_COMPLIE=arm-none-linux-gnueabi-
CC=$(CROSS_COMPLIE)gcc
APP_NAME = test_chr_dev
KERNELDIR ?= /home/keynes/embeded_linux/linux-3.14/
PWD := $(shell pwd)
MODULE_NAME=chr_dev
MODULE_NAME1=myadd

ifeq ($(KERNELRELEASE),) 
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CC) $(APP_NAME).c -o $(APP_NAME)
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
else
	obj-m := $(MODULE_NAME).o $(MODULE_NAME1).o
endif

