#include <stdio.h>
#include "esam.h"
#include "debug.h"
#include "util.h"
#include "stm32f10x_conf.h"


int main(void)
{   	   
	    int      len;
	    uint8_t  ack[512] = {0x00};

      /*初始化ESAm*/
	    EsamInit();
	    UsartPrintConfig();
     
	    /*1.获得ESAM  的芯片编号*/
      len = EsamGetID(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
						  pre_string("\r\n******Get  Esam   calculate  ok*****\r\n ");
				      pre_data(ack,len);
          }
			}
			
			/*2.获得计数器*/
			len = EsamGetCalcuNum(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
            pre_string("\r\n******Get  Esam   calculate  ok*****\r\n ");
				    pre_data(ack,len);
          }
			}
			
			
			/*3.获得芯片状态*/
			len = EsamGetState(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******Get  Esam   EsamGetState  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
			
			/*4.获得秘钥版本*/
			len = EsamGetSecretketVer(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		         pre_string("\r\n******Get  Esam   EsamGetState  ok*****\r\n ");
				     pre_data(ack,len);
					}
			}
			
			/*
				6.获得当前正式的版本号
			len = EsamGetPubSecretVer(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******Get  Esam   pub  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
			*/
			
			/*5.获得当前的正式和测试秘钥版本*/
      len = EsamGetTestSecretVer(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******Get  Esam   testsecver  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
				
			/*7.重新获得公钥信息*/
      len = EsamUpdataSecret(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******updata  Esam   pubkey  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
			
			
			
}