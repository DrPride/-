# Just for everyday
Upload code everyday.建个目录督促自己每天往上边传点东西。

**希望能够多多坚持吧，努力争取坚持三位数天数**


_1、搭建物联网_

  https://github.com/phodal/designiot
  这个原项目的GitHub地址，原本想直接fork，但是感觉还是要有自己的东西会比较好就自己创建个玩玩

现在是做到了api写出来了，然后正在纠结前后端交互的事情，COAP我觉得可以放到最后，现在也不在乎连接的速度。

然后之后要做的东西有：

1）树莓派上服务器的配置

2）数据传到后台——我想了一下，思路应该是把实时传入的数据进行格式修正（应该是选用调包的那个程序，然后根据第一个传感器相关返回值确认是否读入）后写入数据库吧，主要还是查一下，怎么从外部写入django数据库。

```
#用arduino写入json可能最为规范
导出数据库到db_bak.json
python manage.py dumpdata > db_bak.json
导入db.json到数据库
python manage.py loaddata db.json
```




_2、额，现在还不知道，可能在树莓派里头放个挖矿机吧_

_3、还是不知道，可能玩玩apt攻击？_

其实也不知道这个是什么意思，但是作为计院的学生不玩玩信安方面的东西感觉就是浪费了四年时光。

_4、安卓内核相关知识学习——这个应该主要是笔记，放在博客里吧。 http://drpride.github.io_



_back to work/5.21_

现在是不知道是应该看nn方面的内容还是跟着撸个os。

还是先跟着撸个os吧···



## Problems：

1）hjc还是有一些问题.比如

```
<style type="text/css" href="style.css"></style>
```

好像起不到链接css文件的作用。只有换成

```
<link href="./style.css" rel="stylesheet" type="text/css" />
```

才行。

而且

```
<p class="para2 para_bg">
```

使用para_bg类并不能对这个p产生影响

```
p{
    text_align = left;
}
```

也没能实现左对齐





