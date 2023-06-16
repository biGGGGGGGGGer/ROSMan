#include "stm32f4xx.h"
#include "usart.h"
#include "stdio.h"
#include "oled.h"
#include "delay.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pstwo.h"
#include "bsp_exti.h"
#include "bsp_tim4.h"
#include "bsp_mecanum.h"
#include "stdbool.h"
#include "bsp_resetmcu.h"

void ScreenDisplay(float pitch,float roll,float yaw,int PS2_LX,int PS2_RX,int PS2_RY,int PS2_KEY);
void judge_Dir_Speed(void);
void Give_PWM(void);

int cnt = 0;
float pitch,roll,yaw; 		 //欧拉角
short aacx,aacy,aacz;		   //加速度传感器原始数据
short gyrox,gyroy,gyroz;	 //陀螺仪原始数据	
int i;
extern float temperature;//温度
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;     
extern void Set_ch1_frequence(int a,int b,int c);

uint16_t CCR1_Val = 15000;
uint16_t CCR2_Val = 15000;
uint16_t CCR3_Val = 15000;
uint16_t CCR4_Val = 15000;

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	delay_init(168);
	MECANUM_Init();
	TIM_PWMOUTPUT_Config(65535,0);
	EXTI_MPU6050_Config();
	Debug_USART_Config();
	OLED_Init();					//初始化OLED
	PS2_Init();  					//=====ps2驱动端口初始化
	PS2_SetInit(); 					//=====ps2配置初始化,配置“红绿灯模式”，并选择是否可以修改
	TIM_Mode_Config();    			// 基本定时器中断：串口发送数据；更新OLED。
	MPU_Init();						//初始化MPU6050
	while(mpu_dmp_init() !=0)
	{
		printf("DMP初始化失败！\n");
	}			
	delay_ms(1000);
			
	while(1)
	{
		PS2_Receive();
		ScreenDisplay(pitch,roll,yaw,PS2_LX,PS2_RX,PS2_RY,PS2_KEY);			
		judge_Dir_Speed();
	}
}

void ScreenDisplay(float pitch,float roll,float yaw,int PS2_LX,int PS2_RX,int PS2_RY,int PS2_KEY)
{
	OLED_ShowString(0,0,"P",16,1);
	OLED_ShowFNum(15,0,pitch,16,1);
	OLED_ShowString(0,15,"R",16,1);
	OLED_ShowFNum(15,15,roll,16,1);
	OLED_ShowString(0,30,"Y",16,1);
	OLED_ShowFNum(15,30,yaw,16,1);
	OLED_ShowString(70,0,"LX:",16,1);
	OLED_ShowNum(100,0,PS2_LX,3,16,1);
	OLED_ShowString(0,45,"KEY:",16,1);
	OLED_ShowNum(30,45,PS2_KEY,2,16,1);				
	OLED_ShowString(70,15,"RX:",16,1);
	OLED_ShowNum(100,15,PS2_RX,3,16,1);
	OLED_ShowString(70,30,"RY:",16,1);
	OLED_ShowNum(100,30,PS2_RY,3,16,1);
	OLED_Refresh();	
}


// 判断方向

	/*
		ResetBits   使A轮向前转动
		SetBits   	使A轮向后转动
	
		SetBits   	使B轮向前转动
		ResetBits 	使B轮向后转动
	
		ResetBits   使C轮向前转动
		SetBits     使C轮向后转动
	
		ResetBits   使D轮向后转动
		SetBits     使D轮向前转动

   */
void judge_Dir_Speed(void)
{
		// 前进
		if(PS2_KEY == 5)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("5");
			GPIO_ResetBits(A_GPIO,A_DIR);
			GPIO_SetBits(B_GPIO,B_DIR);
			GPIO_ResetBits(C_GPIO,C_DIR);
			GPIO_SetBits(D_GPIO,D_DIR);
		}
		// 后退
		if(PS2_KEY == 7)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);				
			printf("7");
			GPIO_SetBits(A_GPIO,A_DIR);
			GPIO_ResetBits(B_GPIO,B_DIR);
			GPIO_SetBits(C_GPIO,C_DIR);
			GPIO_ResetBits(D_GPIO,D_DIR);
		}
		// 左移
		if(PS2_KEY == 8)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);		
			printf("8");		
			GPIO_SetBits(A_GPIO,A_DIR);
			GPIO_SetBits(B_GPIO,B_DIR);
			GPIO_ResetBits(C_GPIO,C_DIR);
			GPIO_ResetBits(D_GPIO,D_DIR);
			
		}
		// 右移
		if(PS2_KEY == 6)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("6");
			GPIO_ResetBits(A_GPIO,A_DIR);
			GPIO_ResetBits(B_GPIO,B_DIR);
			GPIO_SetBits(C_GPIO,C_DIR);
			GPIO_SetBits(D_GPIO,D_DIR);		
		}
		// 左旋
		if(PS2_KEY == 16)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("左旋");
			GPIO_SetBits(A_GPIO,A_DIR);
			GPIO_SetBits(B_GPIO,B_DIR);
			GPIO_SetBits(C_GPIO,C_DIR);
			GPIO_SetBits(D_GPIO,D_DIR);		
		}
		// 右旋
		if(PS2_KEY == 14)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("右旋");
			GPIO_ResetBits(A_GPIO,A_DIR);
			GPIO_ResetBits(B_GPIO,B_DIR);
			GPIO_ResetBits(C_GPIO,C_DIR);
			GPIO_ResetBits(D_GPIO,D_DIR);		
		}
		if(PS2_KEY == 12)
		{
			TIM_Cmd(GENERAL_TIM, DISABLE);
		}
}

