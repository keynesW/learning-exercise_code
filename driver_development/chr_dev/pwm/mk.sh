#!/bin/bash 
make
cp ./pwm_drv.ko ../../../transplant_nfs_tftp/rootfs/work/
cp ./test_pwm ../../../transplant_nfs_tftp/rootfs/work/ 

