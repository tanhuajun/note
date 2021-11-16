KERN_DIR := /home/thj/work/raspberry/linux

obj-m := hello_drv.o

all:
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KERN_DIR) M=`pwd` modules

clean:
	make -C $(KERN_DIR) M=`pwd` clean

