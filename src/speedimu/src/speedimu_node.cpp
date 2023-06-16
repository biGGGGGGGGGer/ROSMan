#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/Float32.h>
#include <speedimu/imuspeed.h>
#include<iostream>

uint16_t CRC16_Check(const uint8_t *data,uint8_t len);

typedef union
{
    float data;
    uint8_t datas[4];
}imudata;

imudata pitch;
imudata yaw;
imudata roll;
uint8_t temp[17]; 

//创建串口对象
serial::Serial ser;

int main (int argc, char** argv)
{
	//创建ros节点
    ros::init(argc, argv, "speedimu_node");
    ros::NodeHandle nh;
    //创建发布者
    ros::Publisher pitch_pub=nh.advertise<std_msgs::Float32>("pitch",1000);
    ros::Publisher yaw_pub=nh.advertise<std_msgs::Float32>("yaw",1000);
    ros::Publisher roll_pub=nh.advertise<std_msgs::Float32>("roll",1000);

    ros::Publisher speed_pub=nh.advertise<std_msgs::Float32>("speed",1000);

    uint16_t CRC16 = 0x0000;   

    speedimu::imuspeed pitchIMU;
    speedimu::imuspeed yawIMU;
    speedimu::imuspeed rollIMU;

    //打开串口设备
    try
    {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(115200);
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
    while(ros::ok())
    {
        //读取串口数据
        size_t n=ser.available();
        if(n!=0)
        {
            uint8_t buffer[300];
            n = ser.read(buffer,n);
            for(int i=0;i<n;i++)
	        {
	     	    std::cout<<std::hex<<(buffer[i]&0xff)<<" ";
	        }
            printf("\n");
            for(int p = 0;p < 17;p++)
            {
                temp[p] = buffer[p];
            }
            if(buffer[0] == 0xA5 && buffer[1] == 0x5A)
            {
                // CRC校验
                CRC16 = buffer[17];
                CRC16 <<= 8;
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
                                yaw.datas[p-8] = buffer[p];
                            }
                        }
                        if(n == 2)
                        {
                            for(int p = 13;p < 17;p++)
                            {
                                roll.datas[p-13] = buffer[p];
                            }
                        }
                    }
                }
            }
            pitchIMU.a = pitch.data;
            rollIMU.a = roll.data;
            yawIMU.a = yaw.data;
            printf("pitch = %.3f     roll = %.3f    yaw = %.3f\n",pitch.data,roll.data,yaw.data);
            pitch_pub.publish(pitchIMU);
            yaw_pub.publish(yawIMU);
            roll_pub.publish(rollIMU);
        }
    }            
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

