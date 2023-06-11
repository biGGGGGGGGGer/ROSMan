#include "bsp_mecanum.h"
#include "delay.h"
#include "stdbool.h"

void MECANUM_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;

		/*
						A----��ʼ��
		*/
		RCC_AHB1PeriphClockCmd(A_RCC_GPIO, ENABLE);//ʹ��GPIOAʱ��
		GPIO_InitStructure.GPIO_Pin = A_DIR|A_EN;//��ӦIO��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
		GPIO_Init(A_GPIO, &GPIO_InitStructure);//��ʼ��GPIO

		/*
						B----��ʼ��
		*/
		RCC_AHB1PeriphClockCmd(B_RCC_GPIO, ENABLE);//ʹ��GPIOAʱ��
		GPIO_InitStructure.GPIO_Pin = B_DIR|B_EN;//��ӦIO��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
		GPIO_Init(B_GPIO, &GPIO_InitStructure);//��ʼ��GPIO

		/*
						C----��ʼ��
		*/
		RCC_AHB1PeriphClockCmd(C_RCC_GPIO, ENABLE);//ʹ��GPIOAʱ��
		GPIO_InitStructure.GPIO_Pin = C_DIR|C_EN;//��ӦIO��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
		GPIO_Init(C_GPIO, &GPIO_InitStructure);//��ʼ��GPIO
		/*
						D----��ʼ��
		*/
		RCC_AHB1PeriphClockCmd(D_RCC_GPIO, ENABLE);//ʹ��GPIOAʱ��
		GPIO_InitStructure.GPIO_Pin = D_DIR|D_EN;//��ӦIO��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
		GPIO_Init(D_GPIO, &GPIO_InitStructure);//��ʼ��GPIO
		
		GPIO_ResetBits(A_GPIO,A_EN | B_EN | C_EN | D_EN);
}




