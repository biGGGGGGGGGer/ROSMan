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
float pitch,roll,yaw; 		 //ŷ����
short aacx,aacy,aacz;		   //���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	 //������ԭʼ����	
int i;
extern float temperature;//�¶�
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;     
extern void Set_ch1_frequence(int a,int b,int c);

uint16_t CCR1_Val = 15000;
uint16_t CCR2_Val = 15000;
uint16_t CCR3_Val = 15000;
uint16_t CCR4_Val = 15000;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	delay_init(168);
	MECANUM_Init();
	TIM_PWMOUTPUT_Config(65535,0);
	EXTI_MPU6050_Config();
	Debug_USART_Config();
	OLED_Init();					//��ʼ��OLED
	PS2_Init();  					//=====ps2�����˿ڳ�ʼ��
	PS2_SetInit(); 					//=====ps2���ó�ʼ��,���á����̵�ģʽ������ѡ���Ƿ�����޸�
	TIM_Mode_Config();    			// ������ʱ���жϣ����ڷ������ݣ�����OLED��
	MPU_Init();						//��ʼ��MPU6050
	while(mpu_dmp_init() !=0)
	{
		printf("DMP��ʼ��ʧ�ܣ�\n");
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


// �жϷ���

	/*
		ResetBits   ʹA����ǰת��
		SetBits   	ʹA�����ת��
	
		SetBits   	ʹB����ǰת��
		ResetBits 	ʹB�����ת��
	
		ResetBits   ʹC����ǰת��
		SetBits     ʹC�����ת��
	
		ResetBits   ʹD�����ת��
		SetBits     ʹD����ǰת��

   */
void judge_Dir_Speed(void)
{
		// ǰ��
		if(PS2_KEY == 5)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("5");
			GPIO_ResetBits(A_GPIO,A_DIR);
			GPIO_SetBits(B_GPIO,B_DIR);
			GPIO_ResetBits(C_GPIO,C_DIR);
			GPIO_SetBits(D_GPIO,D_DIR);
		}
		// ����
		if(PS2_KEY == 7)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);				
			printf("7");
			GPIO_SetBits(A_GPIO,A_DIR);
			GPIO_ResetBits(B_GPIO,B_DIR);
			GPIO_SetBits(C_GPIO,C_DIR);
			GPIO_ResetBits(D_GPIO,D_DIR);
		}
		// ����
		if(PS2_KEY == 8)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);		
			printf("8");		
			GPIO_SetBits(A_GPIO,A_DIR);
			GPIO_SetBits(B_GPIO,B_DIR);
			GPIO_ResetBits(C_GPIO,C_DIR);
			GPIO_ResetBits(D_GPIO,D_DIR);
			
		}
		// ����
		if(PS2_KEY == 6)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("6");
			GPIO_ResetBits(A_GPIO,A_DIR);
			GPIO_ResetBits(B_GPIO,B_DIR);
			GPIO_SetBits(C_GPIO,C_DIR);
			GPIO_SetBits(D_GPIO,D_DIR);		
		}
		// ����
		if(PS2_KEY == 16)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("����");
			GPIO_SetBits(A_GPIO,A_DIR);
			GPIO_SetBits(B_GPIO,B_DIR);
			GPIO_SetBits(C_GPIO,C_DIR);
			GPIO_SetBits(D_GPIO,D_DIR);		
		}
		// ����
		if(PS2_KEY == 14)
		{
			TIM_Cmd(GENERAL_TIM, ENABLE);
			printf("����");
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

