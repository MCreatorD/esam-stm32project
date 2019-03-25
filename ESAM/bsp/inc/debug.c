#include <stdio.h>
#include "stm32f10x_conf.h"


#define DEBUG1_TX_BYTE(byte)     USART_SendData(USART1, byte);  \
                                                        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)  


/*配置串口管脚*/																												
void UsartPinInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}


/*配置串口波特率*/
void UsartConfig(void)
{
    USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef  USART_ClockInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockInit(USART1, &USART_ClockInitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);

}


/*配置打印串口功能*/
void UsartPrintConfig(void)
{
	 UsartPinInit();
	 UsartConfig();
}

/*打印字符串*/
void   pre_string(unsigned char * describe)
{
    while (*describe != '\0')
    {
        DEBUG1_TX_BYTE(*describe);
        describe++;
    }
}

/*转换并打印数据*/
void   _pre_hex(unsigned  char  *pdata)
{
	  unsigned  char  temp[6] = {0x00};
    sprintf((char *)temp,"0x%02X",*pdata);
    pre_string(temp);
}

/*打印数据*/
void   pre_data(unsigned  char* data,int  len)
{  
   unsigned  char  temp[2];
    while (len--)
    {
        sprintf((char *)temp, "%02X", *data++);
        pre_string(temp);
        pre_string(" ");
    }
    pre_string("\r\n");
}
