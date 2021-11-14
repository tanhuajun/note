### 参考链接

[树莓派Ubuntuwiki](https://wiki.ubuntu.com/ARM/RaspberryPi?&_ga=2.250707910.1753555623.1636804496-140765808.1622099065#Packages)

[树莓派官方教程](https://www.raspberrypi.com/documentation/computers/linux_kernel.html)



### 树莓派安装Ubuntu

[下载树莓派Ubuntu Server 20.04.3 LTS](https://ubuntu.com/download/raspberry-pi)



### Ubuntu上操作

1. Ubuntu安装arm64交叉编译工具

```shell
sudo apt install git make gcc gcc-aarch64-linux-gnu
```

2. 下载树莓派Linux内核

```shell
git clone --depth=1 --branch <branch> https://github.com/raspberrypi/linux  #<branch>为内核版本
```

3. 编译树莓派内核

```shell
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcm2711_defconfig
make -j8 ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
```

4. ubuntu安装nfs文件服务

```shell
sudo apt-get install nfs-kernel-server        #安装nfs文件服务
mkdir ~/work/nfs                              #nfs目录
sudo vim /etc/exports                         #修改nfs配置文件
home/zynq/linux/nfs *(rw,sync,no_root_squash) #exports文件末尾添加内容
sudo service nfs-kernel-server restart        #重启nfs服务
showmount -e                                  #显示nfs共享目录
```

5. 树莓派挂在nfs文件系统到/mnt目录

```shell
sudo mount -t nfs -o nolock,vers=3 192.168.31.35:/home/thj/work/nfs /mnt
#上述命令若不成功可尝试
sudo busybox mount -t nfs -o nolock,vers=3 192.168.31.35:/home/thj/work/nfs /mnt
```

6. 树莓派ubuntu固件存放位置

```shell
Machine: Raspberry Pi 4 Model B Plus
DTB-Id: bcm2710-rpi-3-b-plus.dtb
Boot-DTB-Path: /boot/firmware/bcm2710-rpi-3-b-plus.dtb
Boot-Kernel-Path: /boot/firmware/vmlinuz
Boot-Initrd-Path: /boot/firmware/initrd.img

If you need to manually copy across the kernel and initrd files (note, the system-boot partition is mounted at /boot/firmware):
sudo cp /boot/vmlinuz /boot/firmware/
sudo cp /boot/initrd.img /boot/firmware/
```

7. 将编译出的内核拷贝到内核固件位置

```shell
cp ../raspberry/linux/arch/arm64/boot/Image.gz ~/work/nfs   #将新编译的内核Image.gz拷贝到nfs共享目录
cp /mnt/Image.gz /boot/firmware/vmlinuz                     #在树莓派上将新内核文件拷贝到存放内核固件位置，并且重命名vmlinuz
uname -a                                                    #查看当前内核版本
sudo reboot                                                 #重启
uname -a                                                    #查看更新后的内核版本
```

8. 编译树莓派的设备树

```shell
cat /proc/device-tree                                                  #查看设备树节点
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs
cp linux/arch/arm64/boot/dts/broadcom/bcm2711-rpi-4-b.dtb ~/work/nfs   #编译出的设备树拷贝到nfs共享文件夹
cp /mnt/bcm2711-rpi-4-b.dtb /boot/firmware/                            #将设备树拷贝到树莓派固件目录
```



