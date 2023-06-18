# ROSMan
你好，这里是我的ROS移动机器人Jetson Nano代码!

**ATTENTION**

git命令用的不熟悉，如果在制作过程中冒犯使用了您的功能包，请及时联系我删除！

### 开发环境：
        Jetson Nano B01
        Ubuntu 18.04  && Melodic
        Astra S双目摄像头
        思岚A1雷达

        STM32F407控制底盘运动




### **2023年6月13**

目前的代码包含speedimu功能包、darknet_ros功能包、ros_astra_camera功能包。其中speedimu功能包是用来接收STM32串口发送的MPU6050数据以及底盘运动状态代码。并将代码上传至github。增加了思岚A1雷达功能包。


### **2023年6月15日**
增加了串口通信的代码。使用STM32F407VET6的UART2（PA2、PA3）进行通信。


### **2023年6月16日**
完善了串口接收MPU6050数据的代码，并将pitch、roll、yaw三个数据分别作为三个话题发布。

### **2023年6月18日**
添加了移动机器人的URDF模型文件。
后续任务是续写发布移动机器人TF话题，里程计话题。
