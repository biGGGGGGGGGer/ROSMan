#include "bsp_resetmcu.h"
#include "oled.h"
#include "usart.h"
#include "pstwo.h"

static void TIMx_NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
		// 设置中断组为 0
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		// 设置中断来源
		NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn;
		// 设置抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		// 设置子优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void TIM_Mode_Config(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

		// 开启 TIMx_CLK
		RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);

		/* 累计 TIM_Period 个后产生一个更新或者中断 */
		//当定时器从 0 计数到 4999，即为 5000 次，为一个定时周期
		TIM_TimeBaseStructure.TIM_Period = 2000-1;

		//定时器时钟源 TIMxCLK = 2 * PCLK1
		// PCLK1 = HCLK / 4
		// => TIMxCLK=HCLK/2=SystemCoreClock/2=84MHz
		// 设定定时器频率为 =TIMxCLK/(TIM_Prescaler+1)=10000Hz
		TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;
		// 初始化定时器 TIMx
		TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

		// 清除定时器更新中断标志位
		TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	  TIMx_NVIC_Configuration();
		// 开启定时器更新中断
		TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
		// 使能定时器
		TIM_Cmd(BASIC_TIM, ENABLE);
}

extern int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;     

void BASIC_TIM_IRQHandler(void)
{
	if(TIM_GetITStatus( BASIC_TIM, TIM_IT_Update)!= RESET) 
	{	
		TIM_ClearITPendingBit(BASIC_TIM , TIM_IT_Update);
		pack_send_data(3);         // 串口发送数据
	}
}





