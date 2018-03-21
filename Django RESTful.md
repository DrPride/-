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

**2、开始**

https://www.jianshu.com/p/8a449edea617

```
django-admin.py startproject rest_api
cd rest_api
python manage.py startapp restAPI
```

然后开始浪。

先写model

```
#restAPI/models.py
#这之后的代码都是抄人家的，只是练手，不是我需要的
class Post(models.Model):
    title = models.CharField(max_length=100, blank=True, default='')
    body = models.TextField()
    pub_time = models.DateTimeField(auto_now_add=True)
    tags = models.ManyToManyField('Tag', related_name='posts', blank=True)
    author = models.ForeignKey('auth.User', related_name='posts', on_delete=models.CASCADE)
    class Meta:
        ordering = ('-pub_time',)
class Tag(models.Model):
    name = models.CharField(max_length=50)
```

然后在命令行里

```
python manage.py makemigrations
python manage.py migrate
```

这个在改models之后都要跑一下

然后构建Serializer

```
from django.contrib.auth.models import User
from restAPI.models import Post, Tag 
class PostSerializer(serializers.HyperlinkedModelSerializer): 
	class Meta: 
		model = Post 
		fields = ('url', 'id', 'title', 'pub_time', 'author', 'body', 'tags') 
class TagSerializer(serializers.HyperlinkedModelSerializer): 
	class Meta: 
		model = Tag 
		fields = ('url', 'id', 'name', 'posts') 
class UserSerializer(serializers.HyperlinkedModelSerializer): 
	class Meta: 
		model = User 
		fields = ('url', 'id', 'username', 'posts')
```

写view

```
from rest_framework import viewsets, permissions, mixins
from django.contrib.auth.models import User
from restAPI.models import Post, Tag
from restAPI.serializers import PostSerializer, TagSerializer, UserSerializer
from restAPI.permissions import IsAuthorOrReadOnly
class PostViewSet(viewsets.ModelViewSet):

    """

    处理 /api/posts/ GET POST , 处理 /api/post/<pk>/ GET PUT PATCH DELETE

    """
    queryset = Post.objects.all()
    serializer_class = PostSerializer
    permission_classes = (permissions.IsAuthenticatedOrReadOnly, IsAuthorOrReadOnly)
    def perform_create(self, serializer):

    """

    重写 perform_create

    user 信息不在 request.data 中, 在保存时加入 user 信息

    """
    serializer.save(author=self.request.user)
    

class TagViewSet(mixins.CreateModelMixin,mixins.ListModelMixin,mixins.RetrieveModelMixin, viewsets.GenericViewSet):

    """

    处理 /api/tags/ GET POST, 处理 /api/tags/<pk>/ GET

    """
	queryset = Tag.objects.all()
    serializer_class = TagSerializer
    permission_classes = (permissions.IsAuthenticatedOrReadOnly,)

class UserViewSet(viewsets.ReadOnlyModelViewSet):

    """

    处理 /api/users/ GET, 处理 /api/users/<pk>/ GET

    """
    queryset = User.objects.all()
    serializer_class = UserSerializer
```

构建urls

项目

```
urlpatterns = [
    path('admin/', admin.site.urls),
    path('api/', include('restAPI.urls'))
]
```

app urls：

```
from django.urls import path, include
from rest_framework.routers import DefaultRouter
from restAPI.views import PostViewSet, TagViewSet, UserViewSet
router = DefaultRouter()
router.register(r'posts', PostViewSet)
router.register(r'tags', TagViewSet)
router.register(r'users', UserViewSet)
urlpatterns = [
    path('', include(router.urls)),
    path('api-auth/', include('rest_framework.urls')),
]
```

到这里就能用了。

```
python manage.py runserver
```

去浏览器里打localhost:8000/api去访问你的网站了。

然后人家router给你留了这些东西

include(router.urls) 会帮我们直接生成好

- /api/posts/
- /api/posts/<pk>/
- /api/users/
- /api/users/<pk>/
- /api/tags/
- /api/tags/<pk>/

有时间截个效果图看看。