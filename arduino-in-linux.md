---
title: arduino in linux
date: 2018-04-19 23:12:22
tags: arduino
---

## IDE in linux

去官网，或者去中文社区。

https://www.arduino.cc/en/Main/Software

下载你需要的版本。

然后解压

```
xz -d arduino-1.8.5-linux64.tar.xz
tar -xvf arduino-1.8.5-linux64.tar
cd arduino-1.8.1-linux64
./install.sh
```

然后就可以像在windows里操作一样操作了



## 上传失败问题解决方案

然而这里有一点问题，就是会出现上传失败的问题

```
serial port permission denied
```

我这边解决的办法很简单

```
sudo usermod -a -G dialout <username>
#<username>就是linux的用户名——这个可能在使用树莓派连接的时候会用到
sudo chmode 666 /dev/ttyACM*
#*是你ide里显示的端口号
```

然后你就可以浪了。







