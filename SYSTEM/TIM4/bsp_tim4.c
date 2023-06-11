#include "bsp_tim4.h"

//比较值
extern uint16_t CCR1_Val;
extern uint16_t CCR2_Val;
extern uint16_t CCR3_Val;
extern uint16_t CCR4_Val;

uint32_t capture = 0;

void TIM_PWMOUTPUT_Config(uint16_t arr,uint16_t psc)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;

		/*--------------------GPIO 结构体初始化-------------------------*/
		// 开始 GPIO 端口时钟
		RCC_AHB1PeriphClockCmd(GENERAL_OCPWM_GPIO_CLK, ENABLE);
		// 通用定时器时钟源 TIMxCLK = 2*PCLK1=84MHz
		RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE);
	
		// 通用定时器复用引脚
		GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,CH1_GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF);
		GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,CH2_GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF);
		GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,CH3_GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF);
		GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,CH4_GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF);

		// 通用定时器 PWM 输出引脚
		GPIO_InitStructure.GPIO_Pin = CH1_GENERAL_OCPWM_PIN | CH2_GENERAL_OCPWM_PIN | CH3_GENERAL_OCPWM_PIN | CH4_GENERAL_OCPWM_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GENERAL_OCPWM_GPIO_PORT, &GPIO_InitStructure);
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
		/*--------------------时基结构体初始化-------------------------*/
		// 配置周期，这里配置为 100K
		// 开启 TIMx_CLK

		// 累计 TIM_Period 个后产生一个更新或者中断 */
		TIM_TimeBaseStructure.TIM_Period = arr;
		// 驱动 CNT 计数器的时钟 = TIMxCLK/(psc+1)
		TIM_TimeBaseStructure.TIM_Prescaler = psc;
		// 采样时钟分频
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		// 计数方式
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
		// 初始化定时器 TIMx
		TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
		/*--------------------输出比较结构体初始化-------------------*/
		// 配置为 PWM 模式 1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
		// 输出使能
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		// 输出通道电平极性配置
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		
		// 输出比较值配置
		TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
		TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Disable);
	
		// 输出比较值配置
		TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
		TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Disable);
	
		// 输出比较值配置
		TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
		TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Disable);
		
		// 输出比较值配置
		TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
		TIM_OC4Init(GENERAL_TIM, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(GENERAL_TIM, TIM_OCPreload_Disable);
		
		TIM_OCStructInit(&TIM_OCInitStructure);
		
		// 使能定时器
		TIM_Cmd(GENERAL_TIM, DISABLE);
		TIM_ITConfig(TIM4,TIM_IT_CC1,ENABLE);
		TIM_ITConfig(TIM4,TIM_IT_CC2,ENABLE);
		TIM_ITConfig(TIM4,TIM_IT_CC3,ENABLE);
		TIM_ITConfig(TIM4,TIM_IT_CC4,ENABLE);
}

void TIM4_IRQHandler(void)
{
		uint32_t capture1 = 0;
		uint32_t capture2 = 0;
		uint32_t capture3 = 0;
		uint32_t capture4 = 0;
	
		if(TIM_GetITStatus(TIM4,TIM_IT_CC1) != RESET)
		{
				TIM_ClearITPendingBit(TIM4,TIM_IT_CC1);
				capture1 = TIM_GetCapture1(TIM4);
				TIM_SetCompare1(TIM4,capture1 + CCR1_Val);
		}
		if(TIM_GetITStatus(TIM4,TIM_IT_CC2) != RESET)
		{
				TIM_ClearITPendingBit(TIM4,TIM_IT_CC2);
				capture2 = TIM_GetCapture2(TIM4);
				TIM_SetCompare2(TIM4,capture2 + CCR2_Val);
		}
		if(TIM_GetITStatus(TIM4,TIM_IT_CC3) != RESET)
		{
				TIM_ClearITPendingBit(TIM4,TIM_IT_CC3);
				capture3 = TIM_GetCapture3(TIM4);
				TIM_SetCompare3(TIM4,capture3 + CCR3_Val);
		}
		if(TIM_GetITStatus(TIM4,TIM_IT_CC4) != RESET)
		{
				TIM_ClearITPendingBit(TIM4,TIM_IT_CC4);
				capture4 = TIM_GetCapture4(TIM4);
				TIM_SetCompare4(TIM4,capture4 + CCR4_Val);
		}
}


