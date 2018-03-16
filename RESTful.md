#RESTful API

今天开个头。

首先很多文件的位置是有变化的，composer建立的Laravel项目并不是全部包含在APP文件夹里头，而是彼此有彼此的目录。根据比较友好的命名方式还是能有自己的判断的。

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

