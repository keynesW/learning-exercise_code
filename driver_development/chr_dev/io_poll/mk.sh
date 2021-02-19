#!/bin/bash 
#cp /mnt/hgfs/Share/char_dev/char_dev.c ./ 
make
cp ./key_interrupt_driver.ko ../../../transplant_nfs_tftp/rootfs/work/
cp ./test_key_interrupt ../../../transplant_nfs_tftp/rootfs/work/ 

