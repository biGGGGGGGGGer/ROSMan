#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f4xx.h"

//Òý½Å¶¨Òå
#define MPU6050_INT_GPIO_PORT 					GPIOB
#define MPU6050_INT_GPIO_CLK 						RCC_AHB1Periph_GPIOB
#define MPU6050_INT_GPIO_PIN 						GPIO_Pin_5
#define MPU6050_INT_EXTI_PORTSOURCE		  EXTI_PortSourceGPIOB
#define MPU6050_INT_EXTI_PINSOURCE 		  EXTI_PinSource5
#define MPU6050_INT_EXTI_LINE 				  EXTI_Line5
#define MPU6050_INT_EXTI_IRQ 				    EXTI9_5_IRQn
#define MPU6050_IRQHandler				      EXTI9_5_IRQHandler

void EXTI_MPU6050_Config(void);
void EXTI9_5_IRQHandler(void);
#endif
