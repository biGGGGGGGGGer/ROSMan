#include "bsp_exti.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "bsp_mecanum.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "oled.h"
#include "delay.h"
#include "pstwo.h"

extern float temperature;//温度
extern float pitch,roll,yaw; 		//欧拉角
extern short aacx,aacy,aacz;		//加速度传感器原始数据
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据	
extern int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;     

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* 配置 NVIC 为优先级组 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	/* 配置中断源：按键 1 */
	NVIC_InitStructure.NVIC_IRQChannel = MPU6050_INT_EXTI_IRQ;
	/* 配置抢占优先级： 1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级： 1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_MPU6050_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	/* 开启 GPIO 口的时钟 */
	RCC_AHB1PeriphClockCmd(MPU6050_INT_GPIO_CLK,ENABLE);

	/* 使能 SYSCFG 时钟 ，使用 GPIO 外部中断时必须使能 SYSCFG 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* 配置 NVIC */
	NVIC_Configuration();

	/* 选择 INT 的引脚 */
	GPIO_InitStructure.GPIO_Pin = MPU6050_INT_GPIO_PIN;
	/* 设置引脚为输入模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	/*设置引脚不上拉也不下拉 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	/* 使用上面的结构体初始化按键 */
	GPIO_Init(MPU6050_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 连接 EXTI 中断源 到 MPU6050 引脚 */
	SYSCFG_EXTILineConfig(MPU6050_INT_EXTI_PORTSOURCE,MPU6050_INT_EXTI_PINSOURCE);

	/* 选择 EXTI 中断源 */
	EXTI_InitStructure.EXTI_Line = MPU6050_INT_EXTI_LINE;
	/* 中断模式 */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 下降沿触发 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	/* 使能中断/事件线 */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI9_5_IRQHandler(void)
{
	//确保是否产生了 EXTI Line 中断
	if (EXTI_GetITStatus(MPU6050_INT_EXTI_LINE) != RESET) 
	{
		if(PBin(5) == 0)
		{
			//清楚中断标志位
			EXTI_ClearITPendingBit(MPU6050_INT_EXTI_LINE);
			mpu_dmp_get_data(&pitch,&roll,&yaw);
		}		 
	}
}

