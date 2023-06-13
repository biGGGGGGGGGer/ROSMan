# **注意**
main分支对应的是STM32F407控制运动底盘的代码。

master分支对应的是Jetson Nano上位机的代码。

以后的命名main_x.0、master_x.0规则如上。


## **ROSman项目说明**

**控制板：**STM32F407VET6

STM32F407控制运动地盘，底盘由张大头步进电机闭环驱动器和步进电机组成，且含有MPU6050、OLED等外设。


### **2023年6月13日**
提交了底盘控制的代码。并将解决MPU6050的yaw轴数据漂移的问题、底盘步进电机精准控制的问题、串口发送和接受的问题。
预计6月15日将再次提交代码。



