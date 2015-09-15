/**
 * @file vlog.c
 * @author Sylvain Huet - 2006 - Initial version
 * @author RedoX <dev@redox.ws> - 2015 - GCC Port, cleanup
 * @date 2015/09/07
 * @brief VLISP Virtual Machine - Logging functions
 */
#include <stdint.h>
#include"vmem.h"
#include"vloader.h"
#ifdef VSIMU
#include<windows.h>
#include<stdio.h>
#include<time.h>
#endif
#ifdef VREAL
#include "ml674061.h"
#include "common.h"
#include "irq.h"
#include "spi.h"
#include "led.h"
#include "mem.h"
#include "uart.h"
#include "debug.h"
#include "usbh.h"

#include "delay.h"
#include "audio.h"
#include "motor.h"
#include "usbctrl.h"
#include "ml60842.h"
#include "hcdmem.h"
#include "hcd.h"
#include "i2c.h"
#include "rt2501usb.h"
#include "mem.h"
#include<stdio.h>
#include<string.h>

#include"led.h"
#include"motor.h"
#include"delay.h"
#include"rfid.h"
#endif
#include"vlog.h"

void logSecho(int32_t p,int32_t nl)
{
	if (p==NIL) consolestr("NIL");
	else consolebin((uint8_t*)VSTARTBIN(VALTOPNT(p)),VSIZEBIN(VALTOPNT(p)));
	if (nl) consolestr(ENDLINE);
}

void logIecho(int32_t i,int32_t nl)
{
	if (i==NIL) consolestr("NIL");
	else consoleint(VALTOINT(i));
	if (nl) consolestr(ENDLINE);
}

extern int32_t currentop;
void logGC()
{
	consolestr("#GC : sp=");consoleint(-vmem_stack);
	consolestr(" hp=");consoleint(vmem_heapindex);
	consolestr(" used=");consoleint((vmem_heapindex-vmem_stack)*100/VMEM_LENGTH);
	consolestr("%"ENDLINE);
        consolestr(" b:");consolehx((int)vmem_heap);
        consolestr(" bc:");consolehx((int)bytecode);
        consolestr(" st:");consolehx(vmem_start);
        consolestr(" op:");consolehx(currentop);
	consolestr(ENDLINE);

}


// pour le firmware, le "fichier" ouvert est toujours l'eeprom
int32_t sysLoad(uint8_t *dst,int32_t i,int32_t ldst,uint8_t *filename,int32_t j,int32_t len)
{
#ifdef VSIMU
	FILE *f;
	if ((j<0)||(i<0)||(len<=0)) return 0;
	if (i+len>ldst) len=ldst-i;
	if (len<=0) return 0;
	f=fopen(filename,"rb");
	if (!f) return 0;
	fseek(f,j,SEEK_SET);
	len=fread(dst,1,len,f);
	fclose(f);
	return len;
#endif
#ifdef VREAL
/*        set_vlsi_volume(0);          //volume on 8bits, 0x00 => maximum
        encode_adpcm((UBYTE*)dst+i,(ldst-i-256)>>8, j);
        return 0;
*/
	if ((j<0)||(i<0)||(len<=0)) return 0;
	if (i+len>ldst) len=ldst-i;
	if (len<=0) return 0;
	if (j+len>4096) len=4096-j;
	if (len<=0) return 0;
        read_uc_flash(j,(uint8_t*)dst,len);
        return len;
#endif
}

static uint8_t  buffer_temp[4096];

// pour le firmware, le "fichier" ouvert est toujours l'eeprom
int32_t sysSave(uint8_t *dst,int32_t i,int32_t ldst,uint8_t *filename,int32_t j,int32_t len)
{
#ifdef VSIMU
	FILE *f;
	if ((j<0)||(i<0)||(len<=0)) return 0;
	if (i+len>ldst) len=ldst-i;
	if (len<=0) return 0;
	f=fopen(filename,"rb+");
	if (!f) f=fopen(filename,"wb+");
	if (!f) return 0;
	fseek(f,j,SEEK_SET);
	len=fwrite(dst,1,len,f);
	fclose(f);
	return len;
#endif
#ifdef VREAL
	if ((j<0)||(i<0)||(len<=0)) return 0;
	if (i+len>ldst) len=ldst-i;
	if (len<=0) return 0;
	if (j+len>4096) len=4096-j;
	if (len<=0) return 0;
  __disable_interrupt();
        write_uc_flash(j,(uint8_t*)dst,len,buffer_temp);
  __enable_interrupt();
        return len;
#endif
}

int32_t sysTimems()
{
#ifdef VSIMU
	return GetTickCount();
#endif
#ifdef VREAL
        return counter_timer;
#endif
}

int32_t sysTime()
{
#ifdef VSIMU
	time_t timet;
	time(&timet);
	return timet;
#endif
#ifdef VREAL
	return counter_timer_s;
#endif
}


int32_t rndval;

// retourne une valeur aléatoire entre 0 et 65535
int32_t sysRand()
{
	rndval=rndval*0x1234567+11;
	return (rndval>>8)&0xffff;
}
void sysSrand(int32_t seed)
{
	rndval=seed;
}


void sysCpy(uint8_t *dst,int32_t i,int32_t ldst,uint8_t *src,int32_t j,int32_t lsrc,int32_t len)
{
	if ((i<0)||(j<0)||(len<=0)) return;
        if (i+len>ldst) len=ldst-i;
        if (len<=0) return;
	if (j+len>lsrc) len=lsrc-j;
        if (len<=0) return;
	dst+=i;
	src+=j;
	while((len--)>0) *(dst++)=*(src++);
}

int32_t sysCmp(uint8_t *dst,int32_t i,int32_t ldst,uint8_t *src,int32_t j,int32_t lsrc,int32_t len)
{
	if ((i<0)||(j<0)||(len<=0)) return 0;
	if ((i+len>ldst)&&(j+len>lsrc))
        {
          if (ldst-i>lsrc-j) len=ldst-i;
          else len=lsrc-j;
        }
	dst+=i;
	src+=j;
	while((len--)>0) if (((uint8_t)*dst)>((uint8_t)*src)) return 1;
	else  if (((uint8_t)*(dst++))<((uint8_t)*(src++))) return -1;
	return 0;
}

int32_t mystrcmp(uint8_t *dst,uint8_t *src,int32_t len)
{
	while((len--)>0) if ((*(dst++))!=(*(src++))) return 1;
	return 0;
}

void mystrcpy(uint8_t *dst,uint8_t *src,int32_t len)
{
	while((len--)>0) *(dst++)=*(src++);
}

int32_t sysFind(uint8_t *dst,int32_t i,int32_t ldst,uint8_t *src,int32_t j,int32_t lsrc,int32_t len)
{
	if ((j<0)||(j+len>lsrc)) return NIL;
	src+=j;
	if (i<0) i=0;
	while(i+len<=ldst)
	{
		if (!mystrcmp(dst+i,src,len)) return INTTOVAL(i);
		i++;
	}
	return NIL;
}

int32_t sysFindrev(uint8_t *dst,int32_t i,int32_t ldst,uint8_t *src,int32_t j,int32_t lsrc,int32_t len)
{
	if ((j<0)||(j+len>lsrc)) return NIL;
	src+=j;
	if(i+len>ldst) i=ldst-len;
	while(i>=0)
	{
		if (!mystrcmp(dst+i,src,len)) return INTTOVAL(i);
		i--;
	}
	return NIL;
}

int32_t sysStrgetword(uint8_t *src,int32_t len,int32_t ind)
{
	int32_t n;
  if ((ind<0)||(ind+2>len)) return -1;
  n=(src[ind]<<8)+src[ind+1];
  return n;
}

void sysStrputword(uint8_t *src,int32_t len,int32_t ind,int32_t val)
{
  if ((ind<0)||(ind+2>len)) return;
  src[ind+1]=val; val>>=8;
  src[ind]=val;
}

// lecture d'une chaîne décimale (s'arrête au premier caractère incorrect)
int32_t sysAtoi(uint8_t* src)
{
  int32_t x,c,s;
  x=s=0;
  if ((*src)=='-') { s=1; src++; }
  while((c=*src++))
  {
    if ((c>='0')&&(c<='9')) x=(x*10)+c-'0';
    else return (s?(-x):x);
  }
  return (s?(-x):x);
}

// lecture d'une chaîne hexadécimale (s'arrête au premier caractère incorrect)
int32_t sysHtoi(uint8_t* src)
{
	int32_t x,c;
	x=0;
	while((c=*src++))
	{
		if ((c>='0')&&(c<='9')) x=(x<<4)+c-'0';
		else if ((c>='A')&&(c<='F')) x=(x<<4)+c-'A'+10;
		else if ((c>='a')&&(c<='f')) x=(x<<4)+c-'a'+10;
		else return x;
	}
	return x;
}
void sysCtoa(int32_t c)
{
  uint8_t res[1];
  res[0]=c;
  VPUSH(PNTTOVAL(VMALLOCSTR((uint8_t*)res,1)));
}

const int32_t itoarsc[10]={
  1000000000,100000000,10000000,
  1000000   ,100000   ,10000,
  1000      ,100      ,10,
  1
};;
void sysItoa(int32_t v)
{
  uint8_t res[16];
  int32_t ires=0;
  if (v==0)
  {
    res[ires++]='0';
  }
  else
  {
    int32_t start=1;
    int32_t imul=0;
    if (v<0)
    {
      v=-v;
      res[ires++]='-';
    }
    while(imul<10)
    {
      int32_t k=0;
      while(v>=itoarsc[imul])
      {
        k++;
        v-=itoarsc[imul];
      }
      if ((k)||(!start))
      {
        start=0;
        res[ires++]='0'+k;
      }
      imul++;
    }
  }

  VPUSH(PNTTOVAL(VMALLOCSTR(res,ires)));

}

void sysItoh(int32_t v)
{
  uint8_t res[16];
  int32_t ires=0;
  if (v==0)
  {
    res[ires++]='0';
  }
  else
  {
    int32_t start=1;
    int32_t imul=28;
    while(imul>=0)
    {
      int32_t c=(v>>imul)&15;
      if ((c)||(!start))
      {
        start=0;
        res[ires++]=(c<10)?'0'+c:'a'+c-10;
      }
      imul-=4;
    }
  }
  VPUSH(PNTTOVAL(VMALLOCSTR(res,ires)));
}

void sysCtoh(int32_t c)
{
  uint8_t res[2];
  int32_t v=(c>>4)&15;
  res[0]=(v<10)?'0'+v:'a'+v-10;
  v=c&15;
  res[1]=(v<10)?'0'+v:'a'+v-10;
  VPUSH(PNTTOVAL(VMALLOCSTR((uint8_t*)res,2)));
}

void sysItobin2(int32_t c)
{
  uint8_t res[2];
  res[1]=c;
  c>>=8;
  res[0]=c;
  VPUSH(PNTTOVAL(VMALLOCSTR((uint8_t*)res,2)));
}

int32_t sysListswitch(int32_t p,int32_t key)
{
  while(p!=NIL)
  {
    int32_t q=VALTOPNT(VFETCH(p,0));
    if ((q!=NIL)&&(VFETCH(q,0)==key)) return VFETCH(q,1);
    p=VALTOPNT(VFETCH(p,1));
  }
  return NIL;
}

int32_t sysListswitchstr(int32_t p,uint8_t* key)
{
  while(p!=NIL)
  {
    int32_t q=VALTOPNT(VFETCH(p,0));
    if (q!=NIL)
    {
      int32_t r=VALTOPNT(VFETCH(q,0));
      if ((r!=NIL)&&(!strcmp((char*)VSTARTBIN(r),(char*)key))) return VFETCH(q,1);
    }
    p=VALTOPNT(VFETCH(p,1));
  }
  return NIL;
}

void simuSetLed(int32_t i,int32_t val);
void set_motor_dir(int32_t num_motor, int32_t sens);
int32_t get_motor_val(int32_t i);
int32_t getButton();
int32_t get_button3();
uint8_t* get_rfid();
int32_t check_rfid_n();
uint8_t* get_nth_rfid(int32_t i);

void sysLed(int32_t led,int32_t col)
{
#ifdef VSIMU
	simuSetLed(led,col);
#endif
#ifdef VREAL
        set_led((uint32_t)led,(uint32_t)col);
#endif
}

void sysMotorset(int32_t motor,int32_t sens)
{
#ifdef VSIMU
	set_motor_dir(motor,sens);
#endif
#ifdef VREAL
//        uint8_t buffer[256];
        motor=1+(motor&1);

//        sprintf(buffer,"setmotor %d sens %d\r\n",motor,sens);
//        consolestr(buffer);

        if (sens==0) stop_motor(motor);
        else run_motor(motor,255,(sens>0)?REVERSE:FORWARD/*:REVERSE*/);
#endif
}

int32_t kmotor[3];
int32_t kvmotor[3];

int32_t sysMotorget(int32_t motor)
{
#ifdef VSIMU
	return get_motor_val(motor);
#endif
#ifdef VREAL
//        uint8_t buffer[256];
        int32_t kx;
        motor=1+(motor&1);
        kx=(int)get_motor_position(motor);
/*        k=(int)get_motor_position(motor);
        if (kmotor[motor]!=k)
        {
          kmotor[motor]=k;
          kvmotor[motor]++;
        }
        kx=kvmotor[motor];
*/

//        sprintf(buffer,"getmotor %d pos %x / %x\r\n",motor,k,kx);
//        if(motor==2)
//        consolestr(buffer);
        return kx;
#endif
}

extern uint8_t push_button_value(void);
int32_t sysButton2()
{
#ifdef VSIMU
	return getButton();
#endif
#ifdef VREAL
  return push_button_value();
#endif
}

int32_t sysButton3()
{
#ifdef VSIMU
	return get_button3();
#endif
#ifdef VREAL
	return 255-get_adc_value();
#endif
}

uint8_t* sysRfidget()
{
#ifdef VSIMU
        return get_rfid();
#endif
#ifdef VREAL
        return get_rfid_first_device();
#endif
}

int32_t check_rfid_n();
uint8_t* get_nth_rfid(int32_t i);
int32_t rfid_read(uint8_t* id,int32_t bloc,uint8_t* data);
int32_t rfid_write(uint8_t* id,int32_t bloc,uint8_t* data);

void sysRfidgetList()
{
#ifdef VSIMU
  VPUSH(NIL);
#endif
#ifdef VREAL
  int32_t n=0;
  n=check_rfid_n();
  if (n<=0)
  {
    VPUSH(NIL);
    return;
  }
  int32_t i;
  for(i=0;i<n;i++)
  {
    VPUSH(PNTTOVAL(VMALLOCSTR(get_nth_rfid(i),8)));
  }
  VPUSH(NIL);
  while(n--) VMKTAB(2);
#endif
}
void sysRfidread(uint8_t* id,int32_t bloc)
{
#ifdef VSIMU
  VPUSH(NIL);
#endif
#ifdef VREAL
  uint8_t buf[4];
  int32_t k=rfid_read(id,bloc,buf);
  if (k)
  {
    VPUSH(NIL);
    return;
  }
  VPUSH(PNTTOVAL(VMALLOCSTR(buf,4)));
#endif
}
int32_t sysRfidwrite(uint8_t* id,int32_t bloc,uint8_t* data)
{
#ifdef VSIMU
  return 0;
#endif
#ifdef VREAL
  int32_t k=rfid_write(id,bloc,data);
  return k;
#endif
}
void sysReboot()
{
#ifdef VSIMU
    printf("REBOOT NOW.....");
    getchar();
    exit(0);
#endif
#ifdef VREAL
    reset_uc();
#endif

}

void sysFlash(uint8_t* firmware,int32_t len)
{
#ifdef VSIMU
    printf("REBOOT AND FLASH NOW.....");
    getchar();
    exit(0);
#endif
#ifdef VREAL
  __disable_interrupt();
  flash_uc((uint8_t*)firmware,len,buffer_temp);
#endif

}

const uint8_t  inv8[128]=
{
1,171,205,183,57,163,197,239,241,27,61,167,41,19,53,223,225,139,173,151,25,131,165,207,209,251,29,135,9,243,21,191,193,107,141,119,249,99,133,175,177,219,253,103,233,211,245,159,161,75,109,87,217,67,101,143,145,187,221,71,201,179,213,127,129,43,77,55,185,35,69,111,113,155,189,39,169,147,181,95,97,11,45,23,153,3,37,79,81,123,157,7,137,115,149,63,65,235,13,247,121,227,5,47,49,91,125,231,105,83,117,31,33,203,237,215,89,195,229,15,17,59,93,199,73,51,85,255
};

int32_t decode8(uint8_t* src,int32_t len,uint8_t  key,uint8_t  alpha)
{
	while(len--)
	{
		uint8_t  v=((*src)-alpha)*key;
		*(src++)=v;
		key=v+v+1;
	}
	return key;
}

int32_t encode8(uint8_t* src,int32_t len,uint8_t  key,uint8_t  alpha)
{
	while(len--)
	{
		uint8_t  v=*src;
		*(src++)=alpha+(v*inv8[key>>1]);
		key=v+v+1;
	}
	return key;
}



int32_t sysCrypt(uint8_t* src,int32_t indexsrc,int32_t len,int32_t lensrc,uint32_t key,int32_t alpha)
{
  if ((indexsrc<0)||(indexsrc+len>lensrc)||(len<=0)) return -1;
  return encode8(src+indexsrc,len,key,alpha);
}
int32_t sysUncrypt(uint8_t* src,int32_t indexsrc,int32_t len,int32_t lensrc,uint32_t key,int32_t alpha)
{
  if ((indexsrc<0)||(indexsrc+len>lensrc)||(len<=0)) return -1;
  return decode8(src+indexsrc,len,key,alpha);
}

// Fonctions pour les périphérique I2C
// Arg 1 : Adresse du périphérique
// Arg 2 : Taille du buffer qu'on souhaite récupérer
int32_t sysI2cRead(uint8_t addr_i2c, int32_t bufsize)
{
  uint8_t* data=NULL;
  int32_t nmax=1000;
  // Tente la lecture jusqu'à ce qu'elle soit faite.
  while((nmax>0)&&(read_i2c(addr_i2c,data,bufsize)==FALSE)){ nmax--;__no_operation(); }
  // Retour pour le ByteCode
  VPUSH(PNTTOVAL(VMALLOCSTR((uint8_t*)data,bufsize)));
  return nmax;
}

// Fonction pour l'écriture sur le périphérique
// Arg1 : Adresse du périphérique
// Arg2 : Contenu à écrire
// Arg3 : Taille du contenu à écrire
int32_t sysI2cWrite(uint8_t addr_i2c, uint8_t *data, uint32_t bufsize)
{
  int32_t nmax=1000;
  // Tente l'écriture jusqu'à sa réussite
  while((nmax>0)&&(write_i2c(addr_i2c,data,bufsize)==FALSE)){ nmax--;__no_operation(); }
  return nmax;
}
