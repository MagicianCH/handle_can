# handle_can
科大邱林斌老师项目

## 说明
### main.c
实现Linux下Socket CAN的接收。
包括接收并判断数据的正确性然后将有用数据取出传递给命令处理函数。
### cmd.c
解析数据并进行相应操作。
### serial.c
实现串口功能的封装
### config.sh
脚本，用于启动can并设置波特率（1000k）
### S91canctrl
开机启动canctrl的脚本。下载后需执行一下操作：
+ cd handle_can
+ scp S91canctrl root@192.168.1.136:/opt/canctrl/
+ ssh root@192.168.1.136
+ cd /opt/canctrl/
+ chmod +x S91canctrl
+ wr cp S91canctrl /etc/init.d/
