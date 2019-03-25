#ifndef  _ESAM_H
#define  _ESAM_H

void    EsamInit(void);
int     EsamGetID(unsigned  char *idnum,int  ilen);
int     EsamGetCalcuNum(unsigned  char  *calcu,  int  ilen);
int     EsamGetState(unsigned     char  *calcu,  int  ilen);
int     EsamGetSecretketVer(unsigned   char  *calcu,int  ilen);
int     EsamGetTestSecretVer(unsigned  char  *calcu,int  ilen);
int     EsamGetPubSecretVer(unsigned   char  *calcu,int  ilen);
int     EsamUpdataSecret(unsigned  char *pulickey,int  ilen);

#endif