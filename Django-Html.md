---
title: Django Html
date: 2018-04-07 21:19:57
tags: Django
---

这部分是直接复制粘贴的，然后资料也是比较旧的。留了转载链接，侵删。

## 			[django中将我们的html文件呈现出来](http://www.cnblogs.com/onlyhold/p/7978721.html)		

1、先配置我们的URL，django默认为我们生成了admin的后台映射

```
urlpatterns = [
    url(r'^xadmin/', xadmin.site.urls),
    url(r'^$',TemplateView.as_view(template_name='index.html'),name= 'index'),
]
^表示已Xadmin为开头，$符号表示以/结尾

（1）在填写URL的时候，需要用上VIEW ，所以需要在app的VIEW文件中编写访问该页面的view函数


```

```
ps: 在填写URL的时候，需要用上VIEW ，所以需要在app的VIEW文件中编写访问该页面的view函数
```

编写好view函数以及配置完成URL之后，点击运行，然后浏览器访问URL，这个时候可能会出错，说不到template文件，在setting.py文件中有一个template的配置项
它指明了我们模板模板文件的处理类，在这个配置中有一个文件夹的配置'DIRS'，我们需要在这里指明template文件夹的路径，这样系统会在我们的根目录里下寻找我们的template文件

```
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [os.path.join(BASE_DIR, 'templates')],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
                'django.core.context_processors.media',
            ],
        },
    },
]

```

我们使用根目录的路径和template做一个链接
重新刷新一下浏览器，页面就出来了，但是CSS效果没有了，F12发现提示CSS文件错误，这主要涉及到CSS文件的静态路径的配置，
在setting.py中有一个STATIC的路径配置，static就是我们静态文件的路径，出错的原因是我们没有配置static文件夹的跟路径在哪里，我们之前建立了一个static文件夹，但是并没有告诉系统static文件夹就是static文件的路径
STATIC_URL = '/static/'
我们在setting.py文件中设置一个变量STATICFILES_DIRS表示static文件的跟路径，可以写多个路径
STATICFILES_DIRS = (
    os.path.join(BASE_DIR, 'static'),
)



还有一种说法，把views.py里怎么写对应函数讲的也比较清楚了。

1.第一步，在manage.py同级下新建html目录，里面新建一个index.html
这里写图片描述

    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Title</title>
    </head>
    <body>
        <h1>这是一个html页面</h1>
    </body>
    </html>

2.接着修改
这里写图片描述
Django有个函数专门用来加载网页模板
render_to_response

3.这是因为我们还需要一些配置。
来到settings.py文件，在TEMPLATES-DIRS配置项中写上

```
BASE_DIR+'/html'
```

然后访问这个index。



比如像我这样在settings-HOST里写了地址的就直接