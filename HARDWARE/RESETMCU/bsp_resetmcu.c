#include "bsp_resetmcu.h"
#include "oled.h"
#include "usart.h"

static void TIMx_NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
		// �����ж���Ϊ 0
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		// �����ж���Դ
		NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn;
		// ������ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		// ���������ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void TIM_Mode_Config(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

		// ���� TIMx_CLK
		RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);

		/* �ۼ� TIM_Period �������һ�����»����ж� */
		//����ʱ���� 0 ������ 4999����Ϊ 5000 �Σ�Ϊһ����ʱ����
		TIM_TimeBaseStructure.TIM_Period = 5000-1;

		//��ʱ��ʱ��Դ TIMxCLK = 2 * PCLK1
		// PCLK1 = HCLK / 4
		// => TIMxCLK=HCLK/2=SystemCoreClock/2=84MHz
		// �趨��ʱ��Ƶ��Ϊ =TIMxCLK/(TIM_Prescaler+1)=10000Hz
		TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;
		// ��ʼ����ʱ�� TIMx
		TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);

		// �����ʱ�������жϱ�־λ
		TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	  TIMx_NVIC_Configuration();
		// ������ʱ�������ж�
		TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
		// ʹ�ܶ�ʱ��
		TIM_Cmd(BASIC_TIM, ENABLE);
}

void BASIC_TIM_IRQHandler(void)
{
	if(TIM_GetITStatus( BASIC_TIM, TIM_IT_Update)!= RESET) 
	{	
		TIM_ClearITPendingBit(BASIC_TIM , TIM_IT_Update);
		OLED_Refresh();            // ����OLED��
		pack_send_data(3);         // ���ڷ�������
	}
}





