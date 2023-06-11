#ifndef __BSP_TIM4_H
#define __BSP_TIM4_H

#include "stm32f4xx.h"

/* ********************* 通用定时器TIM4 四路PWM 输出 **************************** */
/* PWM 输出引脚 */
#define GENERAL_OCPWM_GPIO_PORT     		GPIOD
#define GENERAL_OCPWM_GPIO_CLK      		RCC_AHB1Periph_GPIOD

#define CH1_GENERAL_OCPWM_PIN           GPIO_Pin_12
#define CH1_GENERAL_OCPWM_PINSOURCE     GPIO_PinSource12
#define CH2_GENERAL_OCPWM_PIN           GPIO_Pin_13
#define CH2_GENERAL_OCPWM_PINSOURCE     GPIO_PinSource13
#define CH3_GENERAL_OCPWM_PIN           GPIO_Pin_14
#define CH3_GENERAL_OCPWM_PINSOURCE     GPIO_PinSource14
#define CH4_GENERAL_OCPWM_PIN           GPIO_Pin_15
#define CH4_GENERAL_OCPWM_PINSOURCE     GPIO_PinSource15

#define GENERAL_OCPWM_AF            		GPIO_AF_TIM4

/* 通用定时器 */
#define GENERAL_TIM        							TIM4
#define GENERAL_TIM_CLK     						RCC_APB1Periph_TIM4

void TIM_PWMOUTPUT_Config(uint16_t arr,uint16_t psc);
void TIM4_IRQHandler(void);
#endif
