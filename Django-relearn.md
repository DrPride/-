---
title: Django restful_framework（1）
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

## 然后开始最为简洁的操作

从一开始单纯的模型写起自然是没有问题，把代码从臃肿变得简约，确实让人感到心情舒畅。

不过如果你明白其中的逻辑是怎么回事，直接去抄人家最简单的代码，知道这玩意能起作用就行。

把我最后写的东西放在这儿好了。

首先是iot/settings.py.

```
INSTALLED_APPS = [
    ...
    'restframework',
    'restAPI.apps.RestapiConfig',
    ...
]
#这个静态变量简单来说就是用来登记你有什么APP的，插件也是通过这个字段登记的
#关于settings里静态变量的意义，可以上这儿看看https://www.imooc.com/video/13933 
```

然后时iot/urls.py

```
from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include('restAPI.urls')),
]
#在django2.0里面，不再使用url作为路由的函数，而是改用更为友好的path函数。
#include很好理解，简单来说就是把restAPI里的urls文件引入，没错，等下还要再restAPI里写个urls.py
```

restAPI/models.py

其实写restful api应该是从序列器写起，但是我个人觉得还是先把这些默认的东西先写好再说

```
from django.db import models
#默认models

class Post（models.Model):
	#···写你自己需要的字段···
	created = models.DateTimeField(auto_now_add = True)
	#这个是创建时间
	class Meta:
		#组织顺序设定
		ordering = ('created',)
```

然后是关键的restAPI/serializers.py

``` 
from rest_framework import serializers
from restAPI.models import Post

class restAPISerializer(serializers.ModelSerializer):
	class Meta:
		model = Post
		fields = ('id', 'created',···你写的字段···)
		#这个id字段是自动生成的，和后边的pk码一起讲，当然你也可以在上边的models写你想要的id
```

然后是关键的restAPI/views.py

```
from restAPI.models import Post
from rest_framework import generics
#查了一下generic啥意思，一般的; 类的，属性的;  [生] 属的，类的。emmm，感觉和功能没那么重合
from restAPI.serializers import restAPISerializer

class PostList(generics.ListCreateAPIView)
	quertset = Post.objects.all()
	serializer_class = restAPISerializer
	
class PostDetail(generics.RetrieveUpdateDestoryAPIView)
	quertset = Post.objects.all()
	serializer_class = restAPISerializer
```

这个跑出来之后可以用put和patch方法修改相关数据

两个方法区别在于patch是局部修改，put则是整体替换。

最后给配置下路由

restAPI/urls.py

```
from django.urls import path, include
from rest_framework.urlpatterns import format_suffix_patterns
from restAPI import views

urlpatterns = [
    path('', views.PostList.as_view()),
    path('<int:pk>', views.PostDetail.as_view()),
]

urlpatterns = format_suffix_patterns(urlpatterns)
#最后一步是格式规范化，然而不加的话暂时还没在实践中发现问题，嘛，总之先写上呗。
'''
<int:pk>这个东西是类似正则的东西，是用来匹配detail的id的，而你写id如果你没在model里头里定义是没法匹配的。如果你的id是在models里自动生成的话，就用pk码来匹配
'''
```

这样就能返回一个很简洁的界面了。

因为是自己搭建的小iot，所以关于权限之类的问题，我们放到以后再说。