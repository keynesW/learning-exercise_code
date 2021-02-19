#!/bin/bash 
#cp /mnt/hgfs/Share/char_dev/char_dev.c ./ 
make
cp ./key_block_io.ko ../../../transplant_nfs_tftp/rootfs/work/
cp ./test_key_block_app ../../../transplant_nfs_tftp/rootfs/work/ 

