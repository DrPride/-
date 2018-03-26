#COAP

## CoAP-Cli

我现在只能理解到，Coap简单来讲就是一种开销更低的HTTP方式，之前的通过jQuery得到数据的方法，其实我没看懂···

然后现在是看这个CoAP-cli。

这玩意有很多坑。

一个一个讲。

###1、安装

首先你安装的不是Coap-Cli而是node.js

去官网下个LTS（latest stable）然后解压。

解压的方式，我是老老实实两重解压

```
xz -d ***.tar.xz
tar -xvf ***.tar
```

你如果看教程会教你怎么设全局变量，去/etc/profile里写设置对吧？

额，反正我source /etc/profile了半天，人家也照样给我报个node 尚未安装的msg.

怎么做呢？

```
ls -s /path/to/node/bin/node /usr/local/bin/node
ls -s /path/to/node/bin/npm /usr/local/bin/npm
```

然后

```
node -v
#v8.10.0
```

Finally。

想想还有点小成就感。

###2、访问

_coap://vs0.inf.ethz.ch/_这个估计就是用来测试的通用网站，然而出现timeout问题，然后firefox的coap插件又报版本不合····有点小尴尬。