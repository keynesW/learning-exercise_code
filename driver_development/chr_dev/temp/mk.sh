#!/bin/bash 
#cp /mnt/hgfs/Share/char_dev/char_dev.c ./ 
make
#cp ./char_dev.ko /home/keyens/transplant_nfs_tftp/rootfs/work/
cp ./key_driver.ko ../../../transplant_nfs_tftp/rootfs/work/
cp ./key_app ../../../transplant_nfs_tftp/rootfs/work/ 

