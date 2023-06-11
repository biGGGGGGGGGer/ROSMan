#include "bsp_exti.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "bsp_mecanum.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "oled.h"
#include "delay.h"
#include "pstwo.h"

extern float temperature;//�¶�
extern float pitch,roll,yaw; 		//ŷ����
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;	//������ԭʼ����	
extern int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;     

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* ���� NVIC Ϊ���ȼ��� 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	/* �����ж�Դ������ 1 */
	NVIC_InitStructure.NVIC_IRQChannel = MPU6050_INT_EXTI_IRQ;
	/* ������ռ���ȼ��� 1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* ���������ȼ��� 1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* ʹ���ж�ͨ�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_MPU6050_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	/* ���� GPIO �ڵ�ʱ�� */
	RCC_AHB1PeriphClockCmd(MPU6050_INT_GPIO_CLK,ENABLE);

	/* ʹ�� SYSCFG ʱ�� ��ʹ�� GPIO �ⲿ�ж�ʱ����ʹ�� SYSCFG ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* ���� NVIC */
	NVIC_Configuration();

	/* ѡ�� INT ������ */
	GPIO_InitStructure.GPIO_Pin = MPU6050_INT_GPIO_PIN;
	/* ��������Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	/*�������Ų�����Ҳ������ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	/* ʹ������Ľṹ���ʼ������ */
	GPIO_Init(MPU6050_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ���� EXTI �ж�Դ �� MPU6050 ���� */
	SYSCFG_EXTILineConfig(MPU6050_INT_EXTI_PORTSOURCE,MPU6050_INT_EXTI_PINSOURCE);

	/* ѡ�� EXTI �ж�Դ */
	EXTI_InitStructure.EXTI_Line = MPU6050_INT_EXTI_LINE;
	/* �ж�ģʽ */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �½��ش��� */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	/* ʹ���ж�/�¼��� */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI9_5_IRQHandler(void)
{
	//ȷ���Ƿ������ EXTI Line �ж�
	if (EXTI_GetITStatus(MPU6050_INT_EXTI_LINE) != RESET) 
	{
		if(PBin(5) == 0)
		{
			//����жϱ�־λ
			EXTI_ClearITPendingBit(MPU6050_INT_EXTI_LINE);
			mpu_dmp_get_data(&pitch,&roll,&yaw);
		}		 
	}
}

