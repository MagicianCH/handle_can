# handle_can
科大邱林斌老师项目

## 说明
### cantest.c
实现Linux下Socket CAN的接收。
包括接收并判断数据的正确性然后将有用数据取出传递给命令处理函数。
### cmd.c
解析数据并进行相应操作。
### config.sh
脚本，用于启动can并设置波特率（1000k）
