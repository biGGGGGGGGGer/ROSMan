#include "usart.h"

extern float pitch,roll,yaw; 		//ŷ����

typedef union
{
	float a;
	uint8_t data[4];
}data_union;

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
//static void NVIC1_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  /* Ƕ�������жϿ�������ѡ�� */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//  /* ����USARTΪ�ж�Դ */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* �������ȼ�Ϊ1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* �����ȼ�Ϊ1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}

static void NVIC2_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
  /* �������ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  DEBUG_USART GPIO ����,����ģʽ���á�115200 8-N-1 ���жϽ���ģʽ
  * @param  ��
  * @retval ��
  */
void Debug_USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK,ENABLE);
  /* ʹ�� USART ʱ�� */
  RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);
  /* GPIO��ʼ�� */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* ����Tx����Ϊ���ù���  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;  
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
  /* ����Rx����Ϊ���ù��� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
 /* ���� PXx �� USARTx_Tx*/
  GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE,DEBUG_USART_RX_AF);
  /*  ���� PXx �� USARTx__Rx*/
  GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE,DEBUG_USART_TX_AF);
  /* ���ô�DEBUG_USART ģʽ */
  /* ���������ã�DEBUG_USART_BAUDRATE */
  USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
  /* �ֳ�(����λ+У��λ)��8 */
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* ֹͣλ��1��ֹͣλ */
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* У��λѡ��ʹ��У�� */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  /* Ӳ�������ƣ���ʹ��Ӳ���� */
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  /* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* ���USART��ʼ������ */
  USART_Init(DEBUG_USART, &USART_InitStructure); 
  /* Ƕ�������жϿ�����NVIC���� */
//	NVIC1_Configuration();
	/* ʹ�ܴ��ڽ����ж� */
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
  /* ʹ�ܴ��� */
  USART_Cmd(DEBUG_USART, ENABLE);
	
	/*
											����2 ��ʼ��
	*/
  RCC_AHB1PeriphClockCmd(DEBUG_USART2_RX_GPIO_CLK|DEBUG_USART2_TX_GPIO_CLK,ENABLE);
  /* ʹ�� USART ʱ�� */
  RCC_APB1PeriphClockCmd(DEBUG_USART2_CLK, ENABLE);
  /* GPIO��ʼ�� */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* ����Tx����Ϊ���ù���  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin =  DEBUG_USART2_TX_PIN;  
  GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);
  /* ����Rx����Ϊ���ù��� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_PIN;
  GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
  /* ���� PXx �� USARTx_Tx*/
  GPIO_PinAFConfig(DEBUG_USART2_TX_GPIO_PORT,DEBUG_USART2_TX_SOURCE,DEBUG_USART2_TX_AF);
  /*  ���� PXx �� USARTx__Rx*/
  GPIO_PinAFConfig(DEBUG_USART2_RX_GPIO_PORT,DEBUG_USART2_RX_SOURCE,DEBUG_USART2_RX_AF);
  /* ���USART��ʼ������ */
  USART_Init(DEBUG_USART2, &USART_InitStructure); 
  /* Ƕ�������жϿ�����NVIC���� */
	NVIC2_Configuration();
	/* ʹ�ܴ��ڽ����ж� */
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);
  /* ʹ�ܴ��� */
  USART_Cmd(DEBUG_USART2, ENABLE);	
}
	
/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
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


///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}


// 								����2�������ݣ�����������������
//								һ���ֽ�һ���ֽڵķ��ͣ�������
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
	cmd�������ֽ�
	�ο���https://blog.csdn.net/XHL9434826546/article/details/126097374
 */
void pack_send_data(uint8_t cmd)
{
	uint8_t buf[300],i = 0,cnt = 0;
	uint16_t crc16;
	
/*
	���IMU����
	�ýṹ��������ݲ�֡�
	���������һ��datas�����ݰ���pitch��yaw��roll��
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
	��������˶�״̬
 */

		/*
			�������֡
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
					��������֡
		 */
		sendData(buf,cnt);
}




/*********************************************END OF FILE**********************/
