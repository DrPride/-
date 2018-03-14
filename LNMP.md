#LNMP

简单写下我的问题，一个是发现安装完nginx之后输入localhost出来的apache2的欢迎页，额这个还算正常，毕竟一开始mint预装的东西应该就是apache。

然后有个问题是浏览器打不开php，后来仔细想想也是，这个肯定需要配置。

配置看网上教程写了一堆——因为都在/etc/这样的地方修改都需要root权限。

讲道理vim在没习惯之前真的是不好用啊。

虽然我知道命令行是很帅气了啦！！

嘛，总之应该是配置好了，nginx服务重启呗。

报错了····

额，那就查bug呗。

```
systemctl staus nginx.service
```

一点一点看，一点一点改呗。

讲道理你发行版在改版时修改代码位置我是能理解啦，但是求考虑用户的心理阴影面积好吧。至少做好继承方案好吗·····给个序列号什么的也行啊。

然后总算是成功启动成功。

因为apache2占了端口，所以kill掉，打开nginx成功，检查监听状态，clear。

然后打开php-fpm。

额，你又哪里去了····

为啥你打开之后的监听状况还是辣么鬼啊····

要我真拿你学php，那估计我那帮用win的同学都开始自己建站了我还在安装包里挣扎好吧。





天地良心，终于给我弄出来了···真的心力交瘁。

**1、配置乱七八糟了怎么办？**

卸载了重新安装呗。

还能怎么办。

```
sudo apt-get autoremove nginx       # 移除没用的包
sudo apt-get --purge remove nginx   # 移除应用及配置
sudo apt-get autoremove && sudo apt-get autoclean

dpkg --get-selections | grep nginx  # 罗列出与nginx相关的软件，nginx-common deinstall 然后
sudo apt-get --purge remove nginx-common
```

简单来说就是这么一回事儿呗

```
$ sudo apt-get install/delete package
$ sudo apt-get -f install                                   #修复安装
$ sudo apt-get dist-upgrade                                 #升级系统
$ sudo apt-get upgrade                                      #更新已安装的包
$ apt-get source package                                    #下载该包的源代码
$ sudo apt-get build-dep package                            #安装相关的编译环境
$ sudo apt-get clean && sudo apt-get autoclean              #清理无用的包
```

**2、其实大概是这一版本的nginx在apt方式下安装的位置不同，没法直接套教程**

比如说我们习惯性去找的nginx.conf。

这玩意你其实发现教程里该有的属性全没有，就轻飘飘给你留了两个include。

```
include /etc/nginx/conf.d/*.conf
include /etc/nginx/sites-enabled/*
```

我机子里头conf.d下没东西。然后打开这个sites-enabled.

啊哈，有个default。

讲道理按照常规操作，因为害怕这玩意修改出问题改不回来，所以通常用cp命令给复制一个出去，然而前面的代码我们也看到了，你sites-enabled里的所有东西都被引用进来了，所以你换个地方保存，放哪儿？

当然是放啥玩意儿没有，但是足够近还方便后期引用的地方呗。

喏。

```
sudo cp /etc/nginx/sites-enabled/default /etc/nginx/conf.d/default
```

你要是后期想用这个原始设定，加个后缀就行。

然后开始修改这玩意儿。

```
sudo vim /etc/nginx/sites-enabled/default
```

**3、监听方式**

核心要改的东西不多，就一个属性。

```
location ~\.php${
    include snippets/fastcgi-php.conf;
    fastcgi_pass unix:/run/php/php7.0-fpm.sock;
}
```

没错就是这个fastcgi_pass的属性值，一般代码就直接给你了，直接取消注释就完了。

可能很多人看到有这样的情况。

```
## With php7.0-cgi alone:
# fastcgi_pass 127.0.0.1:9000;
## With php7.0-fpm:
# fastcgi_pass unix:/run/php/php7.0-fpm.sock;
```

简单来说就是前者是TCP连接方式，后者是sock连接方式。

讲道理我也不知道哪个好哪个坏，总之看说法是后者更加有优势一点。就折腾后一个呗。

然后这个连接方式需要在php-fpm的设置中保持一致。

```
sudo vim /usr/local/php/etc/php-fpm.d/www.conf
```

找到 listen属性

敲上

```
listen = /run/php/php7.0-fpm.sock
```

嗯，保存退出。

emmm，为了保证你配置没出错，记得使用下面这个命令。

```
sudo nginx -t
```

检验你的配置。注意分号啊，拼写啊，括号位置等等等等这样小小的错误。多多踩坑还是能帮助你锻炼锻炼耐心的。

然后重启nginx服务和php-fpm服务。

这里是重点，也是这么多天让我心力交瘁的元凶。

命令很简单。

```
sudo service nginx restart
sudo service php-fpm restart
```

看上去很美好，但是第二个命令报错了。

·····

我直接跑到人家安装位置启动，还是报错。

然后想前想后，我试探性的写了下面这句话。

```
sudo service php7.0-fpm restart
```

然后访问 http://192.168.0.1xx(自家ip）/phpinfo.php。

终于不给我下载了·····

苦心人，天不负啊啊啊啊。





总结了一下，虽然现在nginx的诸多属性描述的位置都和教程不同，但是通过这段时间的折腾，还是对解决这类问题的方法有了一条若有若无的脉络。

简单说就是跟着代码走。

它让你往东，你就不要往西。

然后几个文件夹的作用也渐渐有了数。

要是在之后学习内核的过程里起到一点作用就好了。