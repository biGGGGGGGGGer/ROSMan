#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32f4xx.h"
#include <stdio.h>

//																USART_1     引脚定义																		PA9、PA10
/*******************************************************/
#define DEBUG_USART                             USART1
#define DEBUG_USART_CLK                         RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE                    115200  //串口波特率

#define DEBUG_USART_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_RX_PIN                      GPIO_Pin_10
#define DEBUG_USART_RX_AF                       GPIO_AF_USART1
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource10

#define DEBUG_USART_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_TX_PIN                      GPIO_Pin_9
#define DEBUG_USART_TX_AF                       GPIO_AF_USART1
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource9

#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
#define DEBUG_USART_IRQ                 		USART1_IRQn

/************************************************************/

//																 USART_2     引脚定义
//																		PA9、PA10
/*******************************************************/
#define DEBUG_USART2                             USART2
#define DEBUG_USART2_CLK                         RCC_APB1Periph_USART2

#define DEBUG_USART2_RX_GPIO_PORT                GPIOA
#define DEBUG_USART2_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART2_RX_PIN                      GPIO_Pin_3
#define DEBUG_USART2_RX_AF                       GPIO_AF_USART2
#define DEBUG_USART2_RX_SOURCE                   GPIO_PinSource3

#define DEBUG_USART2_TX_GPIO_PORT                GPIOA
#define DEBUG_USART2_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART2_TX_PIN                      GPIO_Pin_2
#define DEBUG_USART2_TX_AF                       GPIO_AF_USART2
#define DEBUG_USART2_TX_SOURCE                   GPIO_PinSource2

#define DEBUG_USART2_IRQHandler                  USART2_IRQHandler
#define DEBUG_USART2_IRQ                 				 USART2_IRQn
/************************************************************/

void Debug_USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void _sys_exit(int x);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
void sendData(const uint8_t *data,uint8_t len);
uint16_t CRC16_Check(const uint8_t *data,uint8_t len);
void pack_send_data(uint8_t cmd);





#endif /* __USART2_H */

