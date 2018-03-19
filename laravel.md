#安装配置laravel

**1、GNU/Linux安装Composer**

GNU/Linux Ubuntu/OpenSUSE下可以执行

```linux
$ curl -sS https://getcomposer.org/installer | php
```

方便起见

```linux
$ mv composer.phar composer
```

```linux
$ sudo mv composer /usr/local/bin
```

挂个国内镜像

```linux
$ composer config -g repo.packagist composer https://packagist.phpcomposer.com
```

**2、安装Laravel**

```
$ composer global require "laravel/installer=~1.1"
```

**3、遇到new不出来的情况**

我的情况是

```
The Zip PHP extension is not installed, Please install and try again
```

这玩意儿的解决办法其实很简单

```
sudo apt install php-zip
```

然后就成功new出来了。

有不少包版本上的问题，零零总总25个，不过总算出来了。

之后是插件上的缝缝补补，照着问题apt-get install或者yum就完了。

······说是这么说，pdf写的简略，我也没意识到composer方法可以直接形成laravel项目，所以折腾了很久。

**4、安装mysql**

简单一句话 

```
sudo apt-get install mysql-server php-mysql
```

中间会要求你输入数据库密码。（默认为空）方便起见，回车就是了，设密码其实贼烦。讲道理我为啥要给linux mint设密码·····自己看东西的时候真的应该是怎么方便怎么来。

**5、安装php**

也简单

```
sudo apt-get install php-fpm
```

很多教程上会要求你写老的版本号，我觉得还是按默认的来就完了，毕竟现在发布的东西支持的东西也都变了，能否继承其实还挺暧昧。

之后有问题再面向StackOverflow编程就是了，谁还不是踩着坑前进的。

**6、配置问题多如狗**

嘛，我觉得既然自己出了辣么多乱七八糟的问题，最简单的就是另起炉灶······

_配置进程池_

PHP-FPM 配置文件的其它配置内容是一个名为 Pool Definitions 的区域，这个区域里的配置用于设置每个 PHP-FPM 进程池，PHP-FPM 进程池是一系列相关的 PHP 子进程。通常，一个 PHP 应用有自己的一个 PHP-FPM 进程池。

在 Ubuntu 中，Pool Definitions 区域只有下面这行内容：

```
include=/etc/php5/fpm/pool.d/*.conf
```

这行代码的作用是让 PHP-FPM 加载 `/etc/php5/fpm/pool.d` 目录中的各个进程池定义文件。进入这个目录，应该会看到一个名为 `www.conf` 的文件，这是名为 `www` 的默认 PHP-FPM 进程池配置文件。

各个 PHP-FPM 进程池都以指定的操作系统用户和用户组的身份运行。我们要配置默认的 `www` PHP-FPM 进程池，让它以 `deploy` 用户和用户组的身份运行：

- `user = deploy`

- `group = deploy`

  （这两个我没按官方文档改，因为后边有个listen.owner属性内容和这个相同，我直接默认了）

- `listen = 127.0.0.1:9000`：PHP-FPM 进程池监听的IP地址和端口号，让 PHP-FPM 只接受 Nginx 从这里传入的请求，`127.0.0.1:9000` 让指定的 PHP-FPM 进程池监听本地端口 `9000` 进入的连接。

- `listen.allowed_clients = 127.0.0.1`：可以向这个 PHP-FPM 进程池发送请求的IP地址（一个或多个），为了安全，我把这个设置为 `127.0.0.1`，即只有当前设备能把请求转发给这个 PHP-FPM 进程池。

- `pm.max_children = 15`：这个设置设定任何时间点 PHP-FPM 进程池中最多能有多少个进程。这个设置没有绝对正确的值，你应该测试你的 PHP 应用，确定每个 PHP 进程需要使用多少内存，然后把这个设置设定为可用内存能容纳的 PHP 进程总数。

- `pm.start_servers = 3`：PHP-FPM 启动时 PHP-FPM 进程池立即可用的进程数。

- `pm.min_spare_servers = 2`：PHP 应用空闲时 PHP-FPM 进程池中可以存在的进程数量最小值。这个设置的值一般和 `pm.start_servers` 一样。

- `pm.max_spare_servers = 4`：PHP 应用空闲时 PHP-FPM 进程池中可以存在的进程数量最大值。

- `pm.max_requests = 1000`：回收进程之前，PHP-FPM 进程池中各个进程最多能处理的 HTTP 请求数量。这个设置有助于避免 PHP 扩展或库因为编写拙劣而导致内存不断泄露。

- `slowlog = /path/to/slowlog.log`：这个设置的值是一个日志文件在文件系统中的绝对路径。这个日志文件用于记录处理时间超过 `n` 秒的 HTTP 请求信息，以便找出 PHP 应用的瓶颈，进而进行调试。需要注意的是，PHP-FPM 进程池所属的用户和用户组要对这个日志文件有写权限。

- `request_slowlog_timeout = 5s`：如果当前 HTTP 请求的处理时间超过指定的值，就把请求的回溯信息写入 `slowlog` 设置指定的日志文件。

编辑之后保存文件，然后重启 PHP-FPM 主进程：

```
sudo service php5-fpm restart
```











·····滚犊子吧，我为啥要用一个我之前甚至都没接触过的一种语言去实现一个这么简单的IOT，老子直接用Django。娘希匹！！！！