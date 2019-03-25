#include "debug.h"
#include "util.h"
#include <stdint.h>
#include "stm32f10x_conf.h"

/*****Esam   Pin  Config****/
#define	SAM_SPIx              SPI2
#define	GPIO_SAM_SPI	        GPIOB
#define	Pin_SAM_NSS		        GPIO_Pin_12
#define	Pin_SAM_SCK		        GPIO_Pin_13
#define	Pin_SAM_MISO	        GPIO_Pin_14
#define	Pin_SAM_MOSI          GPIO_Pin_15
/***************************/

/********Esam  Pin  State****/
#define SAM_CS_HIGH()        (GPIO_SetBits(GPIO_SAM_SPI, Pin_SAM_NSS))
#define SAM_CS_LOW()         (GPIO_ResetBits(GPIO_SAM_SPI, Pin_SAM_NSS))
#define SAM_READ_BUSY()      (GPIO_ReadInputDataBit(GPIO_SAM_SPI, Pin_SAM_MISO))
/****************************/

/*≈‰÷√SPI  π‹Ω≈∫Õ ∆¨—°π‹Ω≈*/
static  void EsamPinInit()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	   
	  /*≈‰÷√SPi   Mosi Miso  π‹Ω≈ƒ£ Ω*/
    GPIO_InitStructure.GPIO_Pin = Pin_SAM_SCK|Pin_SAM_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_SAM_SPI, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = Pin_SAM_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_SAM_SPI, &GPIO_InitStructure);
    
	  /*≈‰÷√∆¨—°π‹Ω≈*/
    GPIO_InitStructure.GPIO_Pin = Pin_SAM_NSS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_SAM_SPI, &GPIO_InitStructure);
}


/*≈‰÷√Esam Spi ƒ£ Ω≈*/
static  void EsamSpiConfig(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
    //------------ SPI configuration---------
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SAM_SPIx, &SPI_InitStructure);
    //--------- Enable SPI---------------------
    SPI_Cmd(SAM_SPIx, ENABLE);
}


/*…˙≥…ÕÍ’˚µƒ ˝æ›º”–£—È*/
static  void     GernerateCmd(unsigned  char *pdatain,unsigned  char  *pdataout,int  lrn)
{
	    int  i;
	    unsigned  char  lrc;
	    *pdataout = 0x55; pdataout++;
	    lrc       = Lrc(pdatain,lrn);
	    _memcpy(pdataout,pdatain,lrn);
	     pdataout+=lrn;
	    *pdataout =lrc;
}


/*Esam spi  ∑¢ÀÕ≤¢ªÒµ√“ª∏ˆ◊÷Ω⁄*/
static  unsigned  char   EsamTransmitReceiveByte(unsigned char  byte )
{		   
  	 unsigned int i=0;
     while( ( SPI_I2S_GetFlagStatus(SAM_SPIx, SPI_I2S_FLAG_TXE) == 0 ) && ( ( ++i ) < 1000 ));
     SPI_I2S_SendData(SAM_SPIx, byte);	 
	
     i=0;
     while( ( SPI_I2S_GetFlagStatus(SAM_SPIx, SPI_I2S_FLAG_RXNE) == 0 ) && ( ( ++i ) < 1000));
     return SPI_I2S_ReceiveData(SAM_SPIx);
 }

/*Esam  ∑¢ÀÕ≤¢ªÒµ√◊÷∑˚¥Æ ˝æ›*/
static   void            EsamTransmitReceiveArry(unsigned  char  *ptx,unsigned  char *prx,int  len)
{
	   int  i  =0 ;
	   if(!ptx || !prx || len <=0){
        return  ;
     }
	   for(i = 0;i <  len ;i++){
        prx[i] = EsamTransmitReceiveByte(*ptx++);
     }		 
}

/*Esam  Spi∑¢ÀÕ ˝æ›*/
static  void   EsamTransmit(unsigned  char *data,int  len)
{
	  int       i;
	  if(!data || len <= 0){
        return  ;
    }
		
		SAM_CS_LOW();
	  delay_us(100);
	  for(i = 0; i < len; i++)
	  {
		     EsamTransmitReceiveByte(*data++);
	       delay_us(15);
	  }
    delay_us(5);
	  SAM_CS_HIGH();
	  delay_us(15);
	 
}	


/*µ»¥˝Esamªÿ∏¥≤¢≈–∂œ «∑Ò≥¨ ±*/
static   int   EsamWaitRespone(int  itime)
{
     while(itime -- ){
		    if(0x55 == EsamTransmitReceiveByte(0x00)){
          return   1;
        }
	 	    delay_ms(1);
    }
	  return           0;
}


/*∑¢ÀÕÕÍ’˚÷∏¡Óµ√µΩªÿ∏¥ ˝æ›*/
static   int    EsamTransmitRespon(unsigned  char *pincmd,int  lrn,unsigned  char  *poutcmd)
{
	    uint8_t  lrc;
	    uint16_t ilen; 
	    uint8_t  duumy[256]  = {0x00};

	    SAM_CS_LOW();
      EsamTransmit(pincmd,lrn);
      delay_us(100);
      EsamTransmit(&pincmd[lrn-1],1);
      delay_us(100);

      SAM_CS_HIGH();
	    delay_us(15);
	    SAM_CS_LOW();
	    delay_us(100);

      if(EsamWaitRespone(3000)){   
			     EsamTransmitReceiveArry(duumy,poutcmd,2);
			     if(poutcmd[0]==0x90 && poutcmd[1] == 0x00){   
               EsamTransmitReceiveArry(duumy,&poutcmd[2],2);
				       ilen  =  poutcmd[2]*256 + poutcmd[3];
               EsamTransmitReceiveArry(duumy,&poutcmd[4],ilen+1);
						 	 SAM_CS_HIGH();
               return  ilen + 5;
						 
			     }else{
               return   0;
           }
    }else{                       
			  SAM_CS_HIGH();
			  return   0;
    }
}


/*Esam  ≥ı ºªØ*/
void   EsamInit(void)
{
	   EsamPinInit();
	   SAM_CS_HIGH();
	   EsamSpiConfig();
}

/*∂¡»°Esam µƒ–Ú¡–∫≈*/
int    EsamGetID(unsigned  char *idnum,int  ilen)
{   
	   uint8_t  len;
	   uint8_t  cmd[8]   =  {0x00};
     uint8_t  res[512] =  {0x00};
	   uint8_t  data[]   =  {0x80,0x0E,0x00,0x02,0x00,0x00};
     
     GernerateCmd(data,cmd,sizeof(data));
     len =  EsamTransmitRespon(cmd,sizeof(cmd),res);
     if(len > 0){
			   
			   _memcpy(idnum,res,len);
			   return  len;
     }
		 return   0;
}  

/*∂¡»°¿Îœﬂº∆ ˝∆˜*/
int    EsamGetCalcuNum(unsigned  char  *calcu,int  ilen)
{
     uint8_t  len;
	   uint8_t  cmd[8]  =  {0x00};
     uint8_t  res[512] = {0x00};
	   uint8_t  data[]   = {0x80,0x0E,0x00,0x03,0x00,0x00};
     
     GernerateCmd(data,cmd,sizeof(data));
     len =  EsamTransmitRespon(cmd,sizeof(cmd),res);
     if(len > 0){
			   _memcpy(calcu,res,len);
			   return  len;
     }
		 return   0;
}

/*∂¡»°–æ∆¨◊¥Ã¨*/
int    EsamGetState(unsigned  char  *calcu,int  ilen)
{
     uint8_t  len;
	   uint8_t  cmd[8]  =  {0x00};
     uint8_t  res[512] = {0x00};
	   uint8_t  data[]   = {0x80,0x0E,0x00,0x05,0x00,0x00};
     
     GernerateCmd(data,cmd,sizeof(data));
     len =  EsamTransmitRespon(cmd,sizeof(cmd),res);
     if(len > 0){
			   _memcpy(calcu,res,len);
			   return  len;
     }
		 return   0;
}

/*∂¡»°√ÿ‘ø∞Ê±æ*/
int    EsamGetSecretketVer(unsigned  char  *calcu,int  ilen)
{
     uint8_t  len;
	   uint8_t  cmd[8]  =  {0x00};
     uint8_t  res[512] = {0x00};
	   uint8_t  data[]   = {0x80,0x0E,0x00,0x06,0x00,0x00};
     
     GernerateCmd(data,cmd,sizeof(data));
     len =  EsamTransmitRespon(cmd,sizeof(cmd),res);
     if(len > 0){
			   _memcpy(calcu,res,len);
			   return  len;
     }
		 return   0;
}


/*∂¡»°÷§ È–Ú¡–∫≈*/
int    EsamGetTestSecretVer(unsigned  char  *calcu,int  ilen)
{
     uint8_t  len;
	   uint8_t  cmd[8]  =  {0x00};
     uint8_t  res[512] = {0x00};
	   uint8_t  data[]   = {0x80,0x32,0x00,0x02,0x00,0x00};
     
     GernerateCmd(data,cmd,sizeof(data));
     len =  EsamTransmitRespon(cmd,sizeof(cmd),res);
     if(len > 0){
			   _memcpy(calcu,res,len);
			   return  len;
     }
		 return   0;
}

/*∂¡»°≤‚ ‘÷§ Èµƒ–Ú¡–∫≈*/
int    EsamGetPubSecretVer(unsigned  char  *calcu,int  ilen)
{
     uint8_t  len;
	   uint8_t  cmd[8]  =  {0x00};
     uint8_t  res[512] = {0x00};
	   uint8_t  data[]   = {0x80,0x32,0x01,0x02,0x00,0x00};
     
     GernerateCmd(data,cmd,sizeof(data));
     len =  EsamTransmitRespon(cmd,sizeof(cmd),res);
     if(len > 0){
			   _memcpy(calcu,res,len);
			   return  len;
     }
		 return   0;
}

/*∏¸–¬÷’∂À÷§  , ∑µªÿ÷’∂Àπ´‘ø–≈œ¢*/
int   EsamUpdataSecret(unsigned  char *pulickey,int  ilen)
{
     uint8_t  len;
	   uint8_t  cmd[8]  =   {0x00};
     uint8_t  res[512] =  {0x00};
	   uint8_t  data[]   =  {0x80,0x2c,0x00,0x01,0x00,0x00};
     
     GernerateCmd(data,cmd,sizeof(data));
     len =  EsamTransmitRespon(cmd,sizeof(cmd),res);
     if(len > 0){
			   _memcpy(pulickey,res,len);
			   return  len;
     }
		 return   0;
}



 
 
