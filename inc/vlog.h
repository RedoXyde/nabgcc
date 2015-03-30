// VLISP Virtual Machine - 2006 - by Sylvain Huet
// Lowcost IS Powerfull

#ifndef _LOGGER_
#define _LOGGER_

#ifdef VSIMU
#define consolestr(val) printf("%s",val)
#define consolebin(val,len) printf("%s",val)
#define consoleint(val) printf("%d",val)
#define consolehx(val) printf("%x",val)
#endif
#ifdef VREAL
#define consolestr(val) putst_uart(val)
#define consolebin(val,len) putbin_uart(val,len)
#define consoleint(val) putint_uart(val)
#define consolehx(val) puthx_uart(val)
#endif

void logSecho(int p,int nl);
void logIecho(int i,int nl);
void logGC();

void dump(uchar *src,int len);

int sysLoad(char *dst,int i,int ldst,char *filename,int j,int len);
int sysSave(char *dst,int i,int ldst,char *filename,int j,int len);

int sysTimems();
int sysTime();
int sysRand();
void sysSrand(int seed);
void sysReboot();
void sysFlash(char* firmware,int len);

void mystrcpy(char *dst,char *src,int len);

void sysCpy(char *dst,int i,int ldst,char *src,int j,int lsrc,int len);
int sysCmp(char *dst,int i,int ldst,char *src,int j,int lsrc,int len);
int sysFind(char *dst,int i,int ldst,char *src,int j,int lsrc,int len);
int sysFindrev(char *dst,int i,int ldst,char *src,int j,int lsrc,int len);
int sysStrgetword(unsigned char *src,int len,int ind);
void sysStrputword(unsigned char *src,int len,int ind,int val);
int sysAtoi(char* src);
int sysHtoi(char* src);
void sysCtoa(int c);
void sysItoa(int v);
void sysItoh(int v);
void sysCtoh(int c);
void sysItobin2(int c);
int sysListswitch(int p,int key);
int sysListswitchstr(int p,char* key);


void sysLed(int led,int col);
void sysMotorset(int motor,int sens);
int sysMotorget(int motor);
int sysButton2();
int sysButton3();

char* sysRfidget();
void sysRfidgetList();
void sysRfidread(char* id,int bloc);
int sysRfidwrite(char* id,int bloc,char* data);

int sysCrypt(char* src,int indexsrc,int len,int lensrc,unsigned int key,int alpha);
int sysUncrypt(char* src,int indexsrc,int len,int lensrc,unsigned int key,int alpha);

// Prototype des fonction pour l'I2C
int sysI2cRead(unsigned char addr_i2c, int bufsize);
int sysI2cWrite(unsigned char addr_i2c, unsigned char *data, unsigned int bufsize);


#endif

