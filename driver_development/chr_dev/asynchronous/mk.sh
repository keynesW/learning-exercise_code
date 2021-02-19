#!/bin/bash 
#cp /mnt/hgfs/Share/char_dev/char_dev.c ./ 
make
cp ./key_async_drv.ko ../../../transplant_nfs_tftp/rootfs/work/
cp ./test_key_app ../../../transplant_nfs_tftp/rootfs/work/ 

