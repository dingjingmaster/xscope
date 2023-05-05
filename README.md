# xscope

## 什么是xscope

xscope是一个程序，用于监视X11窗口服务器和客户机程序之间的连接。xscope是一个单独运行的进程。通过设置X11客户机的`host`和`DISPLAY`编号，客户机将连接到xscope而不是X11，然后xscope再连接到X11，就像它是客户机一样。来自客户端的所有字节都被发送到xscope, xscope将它们传递给X11;来自X11的所有字节都被发送到xscope, xscope再将它们发送到客户机。xscope对客户机和X11是透明的。

```
  --------------               --------------             --------------
  |            |               |            |             |            |
  |            | ------------> |            | ----------> |            |
  |   client   |               |  xscope    |             |   server   |
  |            |               |            |             |            |
  |            | <-----------  |            | <---------- |            |
  |            |               |            |             |            |
  --------------               --------------             --------------
                                     |
                                     |
                                     v
                            trace output to stdout
```

## 目前还未开始实现...
计划学完X后开始实现...

## X相关文档翻译工作

X相关文档翻译项目：[https://github.com/dingjingmaster/x-doc](https://github.com/dingjingmaster/x-doc)


