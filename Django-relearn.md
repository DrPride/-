---
title: Django relearn（1）
date: 2018-04-01 21:53:24
tags: Django
---

from www.comingnext.cn Django 编写RESTful API

其实是想学习一下怎么讲Django的Views传到前端去渲染（JQuery + Highcharts），然而在查资料的时候发现之前抄的东西改动的地方实在是太糙了，所以就先跟着靠谱的教程自己写个能看的东西出来。

环境： Django2.0.1+python3.6(Anaconda)

## 开启项目的标准流程

一切推到重来

 首先第一个：先创立个项目，还是熟悉的代码

```
django-admin.py startproject iot
```

然后写个web应用

```
cd iot #进入目录，根据官方文档的说法，这个目录的名字是可以随便改的，只有/iot/iot这个文件夹的名字是有用的
python manage.py startapp restAPI
```

然后我们tree一下看看发生了什么

```
tree
#这里会出现你iot下的文件的分布
```

主要要注意的东西还是iot下的setting.py, urls.py还有restAPI下的models.py, views.py。

因为这些东西是我们主要要改动的文件。

```
题外话：说一下iot下的wsgi.py。wsgi是web server gateway interface的缩写，简单说就是规范下服务器和web应用间要怎么对话，这玩意因为用不到，就先放在这好了。
另外，我们现在在自己电脑上这么简单的建站，使用runserver命令跑起来的只是框架，并不是一个真正的服务器，真的要用还有一系列的部署。
```

//hold here

