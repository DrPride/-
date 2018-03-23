#连接linux mint和windows

_1、让Windows访问Linux mint_

在Linux普通用户下执行命令：

```
sudo apt-get install samba
```

安装samba

打开smb.conf配置文件，命令其实用gedit也好，vim也好，都行，你要喜欢nano也行，都一样。

```
sudo vim /etc/samba/smb.conf
```

在最后面加上以下内容：

```
security = share
[share]
comment = share
path = /path/to/share
available = yes
browsable = yes
public = yes
writable = yes
create mask = 0777
```

保存退出。把文件夹修改成777权限（最高权限），执行命令：

```
chmod 777 /home/wsd/software
```

在Windows文件管理器地址栏输入\\192.168.1.102(Linux的ip地址，在Linux下通过ifconfig查看)就能能按照windows的逻辑为所欲为啦。

不过讲道理你还是像使用U盘一样折腾这玩意为好，毕竟两个系统之间还是有些差异的，很多东西修改了后不一定能用。