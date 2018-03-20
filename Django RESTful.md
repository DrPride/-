# Django Makes RESTful 

**1、下载安装**

因为自己的python是直接anacoda一条龙安装成功的，然后就随意浪了。

直接

```
pip install Django
```

成功。

连接MySQL

```
pip install mysqlclient
```

然而出问题了。

报错。

```
Command "python setup.py egg_info" failed with code 1
```

这个原因在我这台机子应该就是之前安装LNMP一番配置的锅。

解决办法

```
sudo apt-get install libmysqlclient-dev
```

然后再pip一次。

done

**2、设置**

···额，这里出了点状况，版本前和版本后的东西差好多····

算了，具体的明天写吧。这个真的是让我有点头疼。