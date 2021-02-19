#Makefile
ifeq ($(KERNELRELEASE),)

#ifeq ($(ARCH),arm)
ifeq (arm,arm)
	KERNELDIR ?= /home/keynes/embeded_linux/linux-3.14
	ROOTFS ?= /home/keynes/transplant_nfs_tftp/rootfs
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
endif

PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) INSTALL_MOD_PATH=$(ROOTFS) modules_install
clean:
	#rm -rf *.o *.ko *.cmd *.mod *.modules.order Module.symvers .tmp_versions
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
else

	obj-m := vser.o

endif

