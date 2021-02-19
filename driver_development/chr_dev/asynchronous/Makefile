#Makefile

CROSS_COMPLIE=arm-none-linux-gnueabi-
CC=$(CROSS_COMPLIE)gcc
APP_NAME = test_key_app
KERNELDIR ?= /home/keynes/embeded_linux/linux-3.14
PWD := $(shell pwd)
MODULE_NAME=key_async_drv

ifeq ($(KERNELRELEASE),) 
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CC) $(APP_NAME).c -o $(APP_NAME)
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
else
	obj-m := $(MODULE_NAME).o
endif

