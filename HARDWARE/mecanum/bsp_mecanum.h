#ifndef __BSP_MECANUM_H
#define __BSP_MECANUM_H

#include "stm32f4xx.h"

/*
									|~|~~~~~~~~~~~~~~~~~~~~~|~|
							  A |\|											|/| B
									|_|					 /|\				|_|
										|					/	|	\				|
										|				 /	|	 \			|
										|						|					|
										|						|					|
										|						|					|
										|						|					|
										|						|					|
										|						|					|
										|											|
										|											|
									|~|                     |~|
								C |/|											|\| D
									|_|_____________________|_|
 */

//// 							A-----------PD4、PD5、PD6
#define 	 A_RCC_GPIO	  RCC_AHB1Periph_GPIOD
#define    A_GPIO				GPIOD
#define    A_DIR				GPIO_Pin_6
#define    A_EN					GPIO_Pin_4

////							B-----------PE11、PE12、PE13
#define 	 B_RCC_GPIO	  RCC_AHB1Periph_GPIOE
#define    B_GPIO				GPIOE
#define    B_DIR				GPIO_Pin_13
#define    B_EN					GPIO_Pin_11

//// 							C-----------PE4、PE3、PE2
#define 	 C_RCC_GPIO	  RCC_AHB1Periph_GPIOE
#define    C_GPIO				GPIOE
#define    C_DIR				GPIO_Pin_4
#define    C_EN					GPIO_Pin_2

//// 							D-----------PA7、PA6、PA5
#define 	 D_RCC_GPIO	  RCC_AHB1Periph_GPIOA
#define    D_GPIO				GPIOA
#define    D_DIR				GPIO_Pin_7
#define    D_EN					GPIO_Pin_5

void MECANUM_Init(void);
#endif
