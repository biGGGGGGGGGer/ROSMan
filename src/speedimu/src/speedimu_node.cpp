#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/Float64.h>
#include<iostream>

uint16_t CRC16_Check(const uint8_t *data,uint8_t len);

typedef union
{
    float data;
    uint8_t datas[4];
}imudata;

imudata pitch;
imudata roll;
imudata yaw;
uint8_t temp[17];

//创建串口对象 
serial::Serial ser;
//创建获取的距离信息保存的数据变量
std_msgs::Float64 distance;

int main (int argc, char** argv)
{
	//创建ros节点
    ros::init(argc, argv, "speedimu_node");
    ros::NodeHandle nh;
    //创建发布者
    ros::Publisher imu_pub=nh.advertise<std_msgs::Float64>("imu",1000);
    ros::Publisher speed_pub=nh.advertise<std_msgs::Float64>("speed",1000);

    uint16_t CRC16;

    //打开串口设备
    try
    {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(9600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException & e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }
 
    if(ser.isOpen())
    {
        ROS_INFO_STREAM("Serial Port open");
    }
    else
    {
       return -1;
    }
    //设置运行频率
    ros::Rate loop_rate(50);
    while(ros::ok())
    {
        //读取串口数据
        size_t n=ser.available();
        if(n!=0)
        {
            //buffer长度可以根据自己的通信协议来修改，可以改大一点如100
            uint8_t buffer[300];
            n = ser.read(buffer,n);
            for(int j = 0;j < 17;j++)
            {
                temp[j] = buffer[j];
            }

            if(buffer[0] == 0xA5 && buffer[1] == 0x5A)
            {
                // CRC校验
                CRC16 += buffer[17];
                CRC16 << 8;
                CRC16 += buffer[18];
                if(CRC16 == CRC16_Check(temp,21))
                {
                    // 接收pitch、roll、yaw数据。
                    for(int n = 0;n < 3;n++)
                    {
                        if(n == 0)
                        {
                            for(int p = 3;p < 7;p++)
                            {
                                pitch.datas[p-3] = buffer[p];
                            }
                        }
                        if(n == 1)
                        {
                            for(int p = 8;p < 12;p++)
                            {
                                pitch.datas[p-8] = buffer[p];
                            }
                        }
                        if(n == 2)
                        {
                            for(int p = 13;p < 17;p++)
                            {
                                pitch.datas[p-13] = buffer[p];
                            }
                        }
                    }
                }




            }
        }


    }

    // 发布std_msgs::Float64类型的距离数据
    // imu_pub.publish(imu);
            
    loop_rate.sleep();
}

uint16_t CRC16_Check(const uint8_t *data,uint8_t len)
{
    uint16_t CRC16 = 0xFFFF;
    uint8_t state,i,j;
    for(i = 0; i < len; i++ )
    {
        CRC16 ^= data[i];
        for( j = 0; j < 8; j++)
        {
            state = CRC16 & 0x01;
            CRC16 >>= 1;
            if(state)
            {
                CRC16 ^= 0xA001;
            }
        }
    }
    return CRC16;
}

