#include "usart.h"

extern float pitch,roll,yaw; 		//欧拉角

typedef union
{
	float a;
	uint8_t data[4];
}data_union;

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
//static void NVIC1_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  /* 嵌套向量中断控制器组选择 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//  /* 配置USART为中断源 */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* 抢断优先级为1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* 子优先级为1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 使能中断 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* 初始化配置NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}

static void NVIC2_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
  /* 抢断优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  DEBUG_USART GPIO 配置,工作模式配置。115200 8-N-1 ，中断接收模式
  * @param  无
  * @retval 无
  */
void Debug_USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK,ENABLE);
  /* 使能 USART 时钟 */
  RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);
  /* GPIO初始化 */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* 配置Tx引脚为复用功能  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;  
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
  /* 配置Rx引脚为复用功能 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
 /* 连接 PXx 到 USARTx_Tx*/
  GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE,DEBUG_USART_RX_AF);
  /*  连接 PXx 到 USARTx__Rx*/
  GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE,DEBUG_USART_TX_AF);
  /* 配置串DEBUG_USART 模式 */
  /* 波特率设置：DEBUG_USART_BAUDRATE */
  USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
  /* 字长(数据位+校验位)：8 */
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* 停止位：1个停止位 */
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* 校验位选择：使用校验 */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  /* 硬件流控制：不使用硬件流 */
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  /* USART模式控制：同时使能接收和发送 */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* 完成USART初始化配置 */
  USART_Init(DEBUG_USART, &USART_InitStructure); 
  /* 嵌套向量中断控制器NVIC配置 */
//	NVIC1_Configuration();
	/* 使能串口接收中断 */
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
  /* 使能串口 */
  USART_Cmd(DEBUG_USART, ENABLE);
	
	/*
											串口2 初始化
	*/
  RCC_AHB1PeriphClockCmd(DEBUG_USART2_RX_GPIO_CLK|DEBUG_USART2_TX_GPIO_CLK,ENABLE);
  /* 使能 USART 时钟 */
  RCC_APB1PeriphClockCmd(DEBUG_USART2_CLK, ENABLE);
  /* GPIO初始化 */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* 配置Tx引脚为复用功能  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin =  DEBUG_USART2_TX_PIN;  
  GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);
  /* 配置Rx引脚为复用功能 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_PIN;
  GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
  /* 连接 PXx 到 USARTx_Tx*/
  GPIO_PinAFConfig(DEBUG_USART2_TX_GPIO_PORT,DEBUG_USART2_TX_SOURCE,DEBUG_USART2_TX_AF);
  /*  连接 PXx 到 USARTx__Rx*/
  GPIO_PinAFConfig(DEBUG_USART2_RX_GPIO_PORT,DEBUG_USART2_RX_SOURCE,DEBUG_USART2_RX_AF);
  /* 完成USART初始化配置 */
  USART_Init(DEBUG_USART2, &USART_InitStructure); 
  /* 嵌套向量中断控制器NVIC配置 */
	NVIC2_Configuration();
	/* 使能串口接收中断 */
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);
  /* 使能串口 */
  USART_Cmd(DEBUG_USART2, ENABLE);	
}
	
/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void _sys_exit(int x) 
{ 
    x = x; 
} 

int fputc(int ch, FILE *f)
{     
    while((USART2->SR&0X40)==0);
    USART2->DR = (u8) ch;      
    return ch;
}


///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}


// 								串口2发送数据！！！！！！！！！
//								一个字节一个字节的发送！！！！
void sendData(const uint8_t *data,uint8_t len)
{
		uint8_t i;
		for(i = 0;i < len;i++)
		{
				Usart_SendByte(DEBUG_USART2,data[i]);
		}
}

uint16_t CRC16_Check(const uint8_t *data,uint8_t len)
{
		uint16_t CRC16 = 0XFFFF;
		uint8_t state,i,j;
		for(i = 0;i < len;i++)
		{
				CRC16 ^= data[i];
				for(j = 0;j < 8;j++)
				{
						state = CRC16 & 0X01;
						CRC16 >>=1;	
						if(state)
						{
								CRC16 ^= 0xA001;
						}
				}
		}
		return CRC16;
}

/*
	cmd是命令字节
	参考：https://blog.csdn.net/XHL9434826546/article/details/126097374
 */
void pack_send_data(uint8_t cmd)
{
	uint8_t buf[300],i = 0,cnt = 0;
	uint16_t crc16;
	
/*
	打包IMU数据
	用结构体进行数据拆分。
	将数据组成一个datas（数据包括pitch、yaw、roll）
 */
	uint8_t ImuData[12];
	uint8_t _num = 0;	
	data_union _pitch;
	_pitch.a = pitch;
	ImuData[_num++] = _pitch.data[0];
	ImuData[_num++] = _pitch.data[1];
	ImuData[_num++] = _pitch.data[2];
	ImuData[_num++] = _pitch.data[3];

	data_union _yaw;
	_yaw.a = yaw;
	ImuData[_num++] = _yaw.data[0];
	ImuData[_num++] = _yaw.data[1];
	ImuData[_num++] = _yaw.data[2];
	ImuData[_num++] = _yaw.data[3];

	data_union _roll;
	_roll.a = roll;
	ImuData[_num++] = _roll.data[0];
	ImuData[_num++] = _roll.data[1];
	ImuData[_num++] = _roll.data[2];
	ImuData[_num++] = _roll.data[3];
		
/*
	打包底盘运动状态
 */

		/*
			打包数据帧
		 */
		buf[cnt++] = 0xA5;
		buf[cnt++] = 0x5A;

		for(int j = 0;j < cmd;j++)
		{
				buf[cnt++] = j;
				i = 0;
				do
				{
					buf[cnt++] = ImuData[j*4 + (i++)];
				}while(i < 4);
		}

		crc16 = CRC16_Check(buf,cnt+4);
		buf[cnt++] = crc16>>8;
		buf[cnt++] = crc16&0xFF;

		buf[cnt++] = 0xFF;
		
		/*
					发送数据帧
		 */
		sendData(buf,cnt);
}




/*********************************************END OF FILE**********************/
