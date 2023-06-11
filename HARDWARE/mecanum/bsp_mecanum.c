#include "bsp_mecanum.h"
#include "delay.h"
#include "stdbool.h"

void MECANUM_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;

		/*
						A----初始化
		*/
		RCC_AHB1PeriphClockCmd(A_RCC_GPIO, ENABLE);//使能GPIOA时钟
		GPIO_InitStructure.GPIO_Pin = A_DIR|A_EN;//对应IO口
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
		GPIO_Init(A_GPIO, &GPIO_InitStructure);//初始化GPIO

		/*
						B----初始化
		*/
		RCC_AHB1PeriphClockCmd(B_RCC_GPIO, ENABLE);//使能GPIOA时钟
		GPIO_InitStructure.GPIO_Pin = B_DIR|B_EN;//对应IO口
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
		GPIO_Init(B_GPIO, &GPIO_InitStructure);//初始化GPIO

		/*
						C----初始化
		*/
		RCC_AHB1PeriphClockCmd(C_RCC_GPIO, ENABLE);//使能GPIOA时钟
		GPIO_InitStructure.GPIO_Pin = C_DIR|C_EN;//对应IO口
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
		GPIO_Init(C_GPIO, &GPIO_InitStructure);//初始化GPIO
		/*
						D----初始化
		*/
		RCC_AHB1PeriphClockCmd(D_RCC_GPIO, ENABLE);//使能GPIOA时钟
		GPIO_InitStructure.GPIO_Pin = D_DIR|D_EN;//对应IO口
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
		GPIO_Init(D_GPIO, &GPIO_InitStructure);//初始化GPIO
		
		GPIO_ResetBits(A_GPIO,A_EN | B_EN | C_EN | D_EN);
}




