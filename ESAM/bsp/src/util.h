#ifndef  _UTIL_H
#define  _UTIL_H

/*
#define  uint8_t  unsigned  char 
#define  uint16_t unsigned  short
#define  uint16_t unsigned  int 
*/



void     delay_us(unsigned  int  cnt);
void     delay_ms(unsigned  int  cnt);
void    _memcpy(void  *dest,void*  src,int  lrn);
unsigned  char   Lrc(unsigned  char  *data,int  len);

 
#endif