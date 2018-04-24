---
title: Tips on arduino
date: 2018-04-24 20:20:08
tags: arduino
---

## 关于Arduino的程序上传

当我们上传一段代码上板子，程序是存储在板子（flash空间）里头的，并不会因为断电而失去程序。

要想清空程序，我们需要烧入空白程序。



## 程序复位

程序复位意味着程序重新运行。

硬复位就是按下res键(不敢相信我在写这个的时候板子居然不在我旁边)

软复位有两种方法：

```
1) 外接线 - 找任何一个IO口与复位脚连接，在程式内设定那IO为低电平，那便达到软件控制硬件复位。
(2) 纯软件 - 定义一个function
void(* resetFunc) (void) = 0;   //declare reset function at address 0
任何时候想要复位就call function
resetFunc();    // call reset
```



## 关于数据

用EEPROM保存数据不会因为断电而消除。

https://blog.csdn.net/sdlgq/article/details/51931900

```
//写入
#include <EEPROM.h>
int addr = 0;
void setup()
{
}
void loop()
{
  //每次写入1个字节，注意不要溢出。
  //比如要保存模拟值，模拟值读出后是一个0-1024的值，但每字节的大小为0-255，容纳不了，所以这里可以变通一下，将值除以4再存储到val，就能够容纳了。使用的时候读出来再乘以4还原回来。  
  int val = analogRead(0) / 4;
  EEPROM.write(addr, val);

  addr = addr + 1;
  if (addr == 512)  // 当读写位置到了最大容量时，注意不要溢出。
    addr = 0;
  delay(100);
}
```

```
//读取
#include <EEPROM.h>
int address = 0;
byte value;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // 读入一个字节
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  // 到下一个地址
  address = address + 1;

  // 注意地址不要溢出
  if (address == 512)
    address = 0;

  delay(500);
}
```

```
//清空
#include <EEPROM.h>
void setup()
{
  // 让EEPROM的512字节内容全部清零
  for (int i = 0; i < 512; i++)
    EEPROM.write(i, 0);
}
void loop()
{
}
```



@这个还待研究

## 关于和Respberry Pi的连接

https://blog.csdn.net/win_lin/article/details/50545678

简单说就是用树莓派的usb口去通电。

https://github.com/winlinvip/raspi-tools

这个是串口通信的一些办法

