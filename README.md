# justforeveryday
Upload code everyday.建个目录督促自己每天往上边传点东西。

**希望能够多多坚持吧，努力争取坚持三位数天数**


1、搭建物联网

  https://github.com/phodal/designiot
  这个原项目的GitHub地址，原本想直接fork，但是感觉还是要有自己的东西会比较好就自己创建个玩玩


2、额，现在还不知道，可能在树莓派里头放个挖矿机吧

3、还是不知道，可能玩玩apt攻击？

Problems：

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