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

这玩意明儿折腾。