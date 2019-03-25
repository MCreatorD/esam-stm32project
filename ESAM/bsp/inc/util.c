#include "stm32f10x_conf.h"

/*System 72M hz  delay  us*/
void delay_us(unsigned  int  cnt)
{
    while(cnt--) {
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP ();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
    }
}



/*delay  ms*/
void   delay_ms(unsigned  int  cnt)
{
   while(cnt--){
       delay_us(1000);
   }
}

/*校验取反操作*/
unsigned  char   Lrc(unsigned  char  *data,int  len)
{      
	     int  i;
       unsigned  char  temp = data[0];
       for(i =1 ;i< len ;i++){
          temp^=data[i];
       }
       return  ~temp;
}

/*memccpy*/
void  _memcpy(void  *dest,void*  src,int  lrn)
{
	  char * _src   =  (char *)src;
	  char * _dest   =  (char *)dest;
    while(lrn--){
			   *_dest  =  *_src;
			    _dest++;
			    _src++;
   }
}
