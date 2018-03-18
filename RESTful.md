#RESTful API

按照教程来的话还是有一些区别的。

首先很多文件的位置是有变化的，composer建立的Laravel项目并不是全部包含在APP文件夹里头，而是彼此有彼此的目录。根据比较友好的命名方式还是能有自己的判断的。看了一下网上的说法，lavarel5的组织架构方式还是比较灵活的，如果需要自动加载什么东西，直接在composer.json里注册就好了。

主要让我有些不解的是，在教程里头出现的这个东西。

```
{
"id": 1,
"temperature": 14,
"sensors1": 12,
"sensors2": 12,
"led1": 0
}
```

到底是要写到哪里去，是要自己创建一个json文件？可是这个东西要写在哪儿呢？之说目的是产生这样的文件，意味着，这个是之后动作的产物？



然后这个命令

```
php artisan migrate:make create_athomes_table
```

一个是要在根目录里跑，另外一个这个语法现在改掉了。

变成这样了：

```
php artisan make:migration create_athomes_table
```



一开始跑这个

```
 php artisan migrate
```

报错1045。

看了一下，常规错误。

主要是.env文件的信息和database.php里头的设置没匹配好。

然后修改了后报错1698。

这是啥？

额，密码的锅。

然而密码没毛病啊。

我跑到终端直接一个

```
mysql -uroot -p
```

额？Access denied？

你需要

```
sudo mysql -uroot -p
```

方法很简单，*查看一下user表，错误的起因就是在这里， root的plugin被修改成了auth_socket，用密码登陆的plugin应该是mysql_native_password。*(由于可以用sudo mysql -uroot -p进入，所以并不需要以安全模式启动)

```
mysql> select user, plugin from mysql.user;
+-----------+-----------------------+
| user      | plugin                |
+-----------+-----------------------+
| root      | auth_socket           |
| mysql.sys | mysql_native_password |
| dev       | mysql_native_password |
+-----------+-----------------------+
3 rows in set (0.01 sec)

```

只要把auth_socket改成mysql_native_password就行了：

```
mysql> update mysql.user set authentication_string=PASSWORD('111111'), 
plugin='mysql_native_password' where user='root';
Query OK, 1 row affected, 1 warning (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 1

mysql> flush privileges;
Query OK, 0 rows affected (0.00 sec)
```

然后就好了······

之后是对RESTful的创建。

原先的方法也不对。

```
# php artisan controller:make AthomesController
php artisan make:controller AthomesController --resource
```



Lavael5的新特性其实挺多的，但是内部的代码应该是没什么变化，只是在引用上有些区别罢了，我觉得还行。

现在出现了个很尴尬的问题，就是我不知道该怎么运行一个lavarel项目，和以前使用django的感觉不太一样。这很让人迷茫。

之后的一段时间里会学习怎么使用这个东西。

而教程在这个阶段写的比之前凌乱的多，也简略的多。

需要摸索和查询的东西，自然也更多了。