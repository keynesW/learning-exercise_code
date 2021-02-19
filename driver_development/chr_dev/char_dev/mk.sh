#!/bin/bash 
cp /mnt/hgfs/Share/char_dev/char_dev.c ./ 
make
#cp ./char_dev.ko /home/keyens/transplant_nfs_tftp/rootfs/work/
cp ./char_dev.ko ../../../transplant_nfs_tftp/rootfs/work/
cp ./test_chr_dev ../../../transplant_nfs_tftp/rootfs/work/ 

