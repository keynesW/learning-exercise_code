#!/bin/bash 
#cp /mnt/hgfs/Share/char_dev/char_dev.c ./ 
make
cp ./key_tasklet_drv.ko ../../../transplant_nfs_tftp/rootfs/work/
cp ./test_key_tasklet ../../../transplant_nfs_tftp/rootfs/work/ 

