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


##  x client 与 x server 通信

### 1. x client 连接 x server

```angular2html
 0.00: Client (pid 97079 x-draw-line.run) -->   48 bytes
	          byte-order: LSB first
	       major-version: 000b
	       minor-version: 0000
	authorization-protocol-name: "MIT-MAGIC-COOKIE-1"
	authorization-protocol-data: "\230\270A^X^N\323^P^I\201^K\343\2153^A~1"
 0.00: 					14612 bytes <-- X11 Server (pid 1463 Xorg)
					protocol-major-version: 000b
					protocol-minor-version: 0000
					      release-number: 00b8a590
					    resource-id-base: 03c00000
					    resource-id-mask: 001fffff
					  motion-buffer-size: 00000100
					    image-byte-order: LSB first
					bitmap-format-bit-order: LSB first
					bitmap-format-scanline-unit: 20
					bitmap-format-scanline-pad: 20
					         min-keycode: 8 (^H)
					         max-keycode: 255 (\377)
					              vendor: "The X.Org Foundation"
					      pixmap-formats: (7)
					               roots: (1)
```