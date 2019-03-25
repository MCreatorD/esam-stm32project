#include <stdio.h>
#include "esam.h"
#include "debug.h"
#include "util.h"
#include "stm32f10x_conf.h"


int main(void)
{   	   
	    int      len;
	    uint8_t  ack[512] = {0x00};

      /*��ʼ��ESAm*/
	    EsamInit();
	    UsartPrintConfig();
     
	    /*1.���ESAM  ��оƬ���*/
      len = EsamGetID(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
						  pre_string("\r\n******Get  Esam   calculate  ok*****\r\n ");
				      pre_data(ack,len);
          }
			}
			
			/*2.��ü�����*/
			len = EsamGetCalcuNum(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
            pre_string("\r\n******Get  Esam   calculate  ok*****\r\n ");
				    pre_data(ack,len);
          }
			}
			
			
			/*3.���оƬ״̬*/
			len = EsamGetState(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******Get  Esam   EsamGetState  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
			
			/*4.�����Կ�汾*/
			len = EsamGetSecretketVer(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		         pre_string("\r\n******Get  Esam   EsamGetState  ok*****\r\n ");
				     pre_data(ack,len);
					}
			}
			
			/*
				6.��õ�ǰ��ʽ�İ汾��
			len = EsamGetPubSecretVer(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******Get  Esam   pub  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
			*/
			
			/*5.��õ�ǰ����ʽ�Ͳ�����Կ�汾*/
      len = EsamGetTestSecretVer(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******Get  Esam   testsecver  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
				
			/*7.���»�ù�Կ��Ϣ*/
      len = EsamUpdataSecret(ack,sizeof(ack));
      if(len > 0){
				  if(Lrc(ack,len)==0x00){
		        pre_string("\r\n******updata  Esam   pubkey  ok*****\r\n ");
				    pre_data(ack,len);
					}
			}
			
			
			
}