/*************************************************************************************/
/*                                                                                   */
/*      Copyright (C) 2005 Oki Electric Industry Co., LTD.                           */
/*                                                                                   */
/*      System Name     :  ML674051/ML67Q4061                                        */
/*      Module Name     :  Demo code for AME-51 Board                                */
/*      File   Name     :  demo.c                                                    */
/*      Revision        :  1.00                                                      */
/*      Date            :  2005/05/18                                                */
/*                          Initial version                                          */
/*                                                                                   */
/*************************************************************************************/
#include "ML674061.h"
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
#include "rfid.h"
#include<stdio.h>
#include<string.h>

#include"vmem.h"
#include"vloader.h"
#include"vinterp.h"
#include"vnet.h"
#include"vaudio.h"
#include"vlog.h"


#define MHz      (1000000L)
#define TMRCYC   (10)             /* interval of timer interrupt (ms) */
//#define CCLK     (32*MHz)       /* CCLK (Hz) */
#define CLKGEAR  (1)              /* clock gear */
//#define CLKTMR   (CCLK/CLKGEAR) /* frequency of CLKTMR terminal (Hz) */
#define SYSCLK	(32)	          /* SYSCLK (MHz)*/
#define VALUE_OF_TMRLR            /* reload value of timer */\
                (65536 - (TMRCYC * SYSCLK * 1000) / 16)

#if ((VALUE_OF_TMRLR) < 0 || 0x10000 <= (VALUE_OF_TMRLR))
#error "Invalid value : VALUE_OF_TMRLR"
#endif

/*************/
/* Functions */
/*************/
int main(void);                     /* main routine */
static void reg_irq_handler(void);  /* registration of IRQ handler */
void FIQ_handler(void);
void init_io(void);
void push_button_interrupt(void);
void uart0_interrupt(void);
void timer_handler(void);

/* JOB */
void *okijob_open( void );
int32_t okijob_close( void* );
int32_t okijob_bulk( void*, unsigned char, void*, unsigned long );
int32_t okijob_number(void*);

/********************/
/* Global variables */
/********************/
extern uint8_t dummy_buffer[100];
uint8_t UART_BUFFER[UART_BUFFER_SIZE];
volatile uint8_t uart_buffer_pointer;
uint8_t motor_state=0;

volatile int32_t counter_timer;
volatile int32_t counter_timer_s;
volatile int32_t counter_timer_sbuf;


//USB variables
int32_t old_state = 0;
int32_t connect_request = 0;
int32_t transfer_request = 0;

#ifndef DATABUFFER
  #define DATABUFFER		0
#endif

/* DATABUFFER==0 ML60841内部RAMをバッファにする */
/* DATABUFFER==1 外部RAMをバッファにする        */
#if (DATABUFFER==0)
  #define MALLOC(a)			usbh_malloc(a)
  #define FREE(a)			usbh_free(a)
#else
  #define MALLOC(a)			malloc(a)
  #define FREE(a)			free(a)
#endif

extern const uint8_t dumpbc[21204];





//const uint8_t TAB_32K[100000];

/****************************************************************************/
/*  Init clock system to have 32MHz with 8MHz external crystal              */
/*  Function : init_pll                                                     */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   0                                                   */
/****************************************************************************/
void init_pll(void)
{
  //Configure PLLA and PLLB
  put_wvalue(PLL1, 0x31013110);
  put_wvalue(PLL2, 0x00030101);
    //PLLDIVA=0x01
    //DVCOA=0x10=0d16
    //DREFA=0x01
    //SVCOA=0x3
    //PLLDIVB=0x01
    //DVCOB=0x01
    //DREFB=0x01
    //SVCOB=0x3
    //PLLDIVC=0x03
  //setup of CLOCK register (CLKCNT@0xB700_0010)
  put_wvalue(CLKCNT, 0x000D0109);
     //APB Clock = CPU Clock
    //System Clock active
    //Ring oscillator active
    //PLLA active
    //PLLA inactive
    //Source = Ring oscillator
    //CLKDIVA = 1/4
    //CLKDIVB = 8/8
  clr_wbit(CLKCNT, 0x00000300);
    //Source = Sysclock
  clr_wbit(CLKCNT, 0x00040000);
    //Stop Ring oscillator
  set_wbit(PECLKCNT,0x18000000);
    //active GPIO11 and GPIO12 peripheral clock => XD16 to XD31
}

void wdt_start(void)
{
  put_value(INTST,0x3c);  //release write protection
  put_value(INTST,0x00);  //Clear status bit

  put_value(TBGCON,0x5A);  //release write protection
  put_value(TBGCON,0x45);  //Watchdog clock = APB_CLK/1024 => 32us @32MHz => overflow each 2.09s
                           //generates reset when overflow ; Turn ON counter

  put_value(OVFAST,0x63);  //assert time to be ouput from the RSTOUT_N pin of 100us

  put_value(WDTCON,0x3C);  //Start watchdog

  //Clear watchdog
//  put_value(WDTCON,0xC3);
//  put_value(WDTCON,0x3C);

}

char dbg_buffer[256];
static struct rt2501_scan_result sresult;

uint8_t * scanssid;
void scantest(struct rt2501_scan_result *scan_result, void *userparam)
{
    if (!strcmp((char*)scan_result->ssid,(char*)scanssid))
	memcpy(&sresult, scan_result, sizeof(struct rt2501_scan_result));
}

void dump(uint8_t *src,int32_t len)
{
  int32_t i,j;
  uint8_t buffer[64];
  putst_uart((uint8_t*)"\r\n");
  for(i=0;i<len;i+=16)
  {
    sprintf((char*)buffer,"%04lx ",i);
    putst_uart(buffer);
    for(j=0;j<16;j++) if (i+j<len)
    {
      sprintf((char*)buffer,"%02x ",src[i+j]); putst_uart(buffer);
    }
    else putst_uart((uint8_t*)"   ");
    for(j=0;j<16;j++) if (i+j<len) putch_uart(((src[i+j]>=32)&&(src[i+j]<128))?src[i+j]:'.');
    putst_uart((uint8_t*)"\r\n");
//    DelayMs(100);
  }
}

void dumpbin(uint8_t * p,int32_t n,int32_t ln)
{
  int32_t i;
  uint8_t buffer[6];
  for(i=0;i<n;i++)
  {
    sprintf((char*)buffer,"%02x.",(p[i])&255);
    putst_uart(buffer);
  }
  if (ln) putst_uart((uint8_t*)"\r\n");
}

uint8_t tstarp[]=
{
  0xaa,0xaa,0x03,0x00,0x00,0x00,0x08,0x06,

  0x00,0x01,0x08,0x00,
  0x06,0x04,0x00,0x01,
  0,0,0,0,0,0,
  0,0,0,0,
  0xff,0xff,0xff,0xff,0xff,0xff,
  0,0,0,0

//  0x00,0x0c,0xf6,0x1b,0xa8,0x06,
//  192,168,1,100,
//  0xff,0xff,0xff,0xff,0xff,0xff,
//  192,168,1,2
};

uint8_t myip[4]={  192,168,1,100 };
uint8_t targetip[4]={  192,168,100,1 };
uint8_t targetmac[6]={255,255,255,255,255,255};

extern uint8_t rt2501_mac[6];

void mkarp(uint8_t* ip)
{
DBG("1\r\n");
  memcpy(tstarp+16,rt2501_mac,6);
DBG("2\r\n");
  memcpy(tstarp+22,myip,4);
DBG("3\r\n");
  memcpy(tstarp+32,ip,4);
DBG("4\r\n");
}

uint8_t checkflag,checklo,checkhi;

void init_checksum()
{
    checkflag = checkhi = checklo = 0;
}

/* Add byte to checksum value */
void check_byte(uint8_t b)
{
    if (checkflag)
    {
        checklo += b;
        if (checklo < b)
        {
            if (++checkhi == 0)
                checklo++;
        }
    }
    else
    {
        checkhi += b;
        if (checkhi < b)
        {
            if (++checklo == 0)
                checkhi++;
        }
    }
    checkflag = !checkflag;
}

uint8_t tstudp[]=
{
  0xaa,0xaa,0x03,0x00,0x00,0x00,0x08,0x00,

  0x45,0,0,20+8+6,
  0,1,0,0,
  100,17,0,0,
  0,0,0,0,
  0,0,0,0,

  8,0,16,0,
  0,8+6,0,0,
  'f','o','o','b','a','r'
};

uint8_t tstfoo[]=
{
  192,168,1,2,
  192,168,1,6
};

char idudp;

void mkudp()
{
  int32_t i;
  idudp=0;
  tstudp[8+5]=idudp++;
  memcpy(tstudp+8+12,myip,4);
  memcpy(tstudp+8+16,targetip,4);
  init_checksum();
  for(i=0;i<20;i++)check_byte(tstudp[8+i]);

  tstudp[8+10]=~checkhi;
  tstudp[8+11]=~checklo;

  init_checksum();
  for(i=0;i<8+6;i++)check_byte(tstudp[8+20+i]);

  for(i=12;i<20;i++)check_byte(tstudp[8+i]);
//  for(i=0;i<8;i++)check_byte(tstfoo[i]);
  check_byte(0);
  check_byte(17);
  check_byte(0);
  check_byte(8+6);

  tstudp[8+20+6]=~checkhi;
  tstudp[8+20+7]=~checklo;

  DBG("checksum :"); dumpbin((uint8_t *)(tstudp+8+10),2,1);
  DBG("checksum :"); dumpbin((uint8_t *)(tstudp+8+20+6),2,1);

}

void mypassword_to_pmk(const uint8_t *password, uint8_t *ssid, int32_t ssidlength, uint8_t *pmk);

extern uint8_t buffer_temp[4096];

/****************************************************************************/
/*  Entry point                                                             */
/*  Function : main                                                         */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   0                                                   */
/****************************************************************************/

int32_t stacktest;
int32_t *foo;//=&stacktest;//(int*)0xD000FFFC;

int main(void)
{
    int32_t iii;
	int32_t ret;
//        int st;
//        int sendarp=0;
        uint8_t *ptest;
        //~ uint8_t buf[64];

  uint8_t *address; /* address of read/write area */
/*  ulong data_width_received;
  ushort cmpt_audio_block;
  ushort sampling_frequency;
*/
  //Disable interrupts
  __disable_interrupt();

#if (PCB_RELEASE == LLC2_3) || (PCB_RELEASE == LLC2_4c)
  //Init clock system
  init_pll();
#elif PCB_RELEASE == LLC2_2
  //setup of CLOCK register (CLKCNT@0xB700_0010)
  put_wvalue(CLKCNT, 0x00080000);
      //Disactive ring oscillator and RTCCLK
     //APB Clock = CPU Clock
#endif
  //setup of CLOCK peripheral register
  set_bit(PECLKCNT, 0x08000000);
//  set_bit(PECLKCNT, 0x10000000);

  //Init I/O directions and default values
  init_io();
  //initialize IRQ
  init_irq();
    //Setup external SRAM/ROM
  setup_ext_sram_rom();

  //Flash ROM programming is permitted
  init_uc_flash();
//  set_bit(FLACON,0x01);

  wdt_start();

  //Init System timer
  // Overflow in ms = ( 16 x (65536-value of TMRLR) x 1000 ) / (SystemClock)
  put_hvalue(TMRLR, 0xF830);  // set TMRLR for 1ms @ 32MHz
//  put_hvalue(TMRLR, 0xF800);  // set TMRLR for 1ms @ 32.768MHz
  put_value(TMEN, 0x01);      //Run timer
  counter_timer=0;
  counter_timer_s=0;
  counter_timer_sbuf=0;

  //registration of IRQ handler
  reg_irq_handler();

  setup_malloc();

  //Enable interrupts
  __enable_interrupt();

  //Init ADC
  put_hvalue(ADCON0, 0x0000);
  put_hvalue(ADCON1, ADCON1_CH2);   //Set Channel
  put_hvalue(ADCON2, ADCON2_CLK32);   //Set conversion time, minimum 800ns, so 33MHz/32 => 100

  //Configure SPI0
  init_spi();
  //Init LED driver
  init_led_rgb_driver();
  //Configure I2C
  init_i2c();
  //Init Audio
  init_vlsi();

  //Init PWM module for DC motors
  init_pwm();
  stop_motor(1);
  stop_motor(2);

  //Init RAM of USB host
	for(address=(uint8_t*)ComRAMAddr;
	    address<(uint8_t*)(ComRAMAddr+ComRAMSize);
	    address++)
		put_value(address, 0x00);

  //Init Uart
  uart_buffer_pointer=0;
  init_uart();
  putst_uart((uint8_t*)"\r\n/****Start\r\n");
  ptest=(uint8_t *)&iii;
  iii=1;
  if (ptest[0]) putst_uart((uint8_t*)"Little Endian.\r\n");
  if (ptest[3]) putst_uart((uint8_t*)"Big Endian.\r\n");

  // Configure USB
	usbctrl_host_driver_set(NULL, usbhost_interrupt);
	ret = usbctrl_init(USB_HOST);
	if(ret != OK) return ret;

	reg_irq_handler();
        put_value(FIQEN, 0x00 );

	__enable_interrupt();

//xmodem_recv((uuint8_t *)SRAM_BASE);


        ret = usbhost_init();
	if(ret != OK) return ret;

	ret = rt2501_driver_install();
	if(ret != OK) return ret;

       	DBG("Nabaztag firmware ready.\r\n");
//      while(rt2501_state() != RT2501_S_IDLE) usbhost_events();

 /*       dumpbin(rt2501_mac,6,1);
	while(rt2501_state() != RT2501_S_IDLE)
		usbhost_events(); // Handle peripherals connecting and disconnecting
*/
//rt2501_setmode(IEEE80211_M_MASTER, "NabaztagAP", 1);
/*
        while(1)
{
  uint8_t buffer[128];
    usbhost_events(); // Handle peripherals connecting and disconnecting
    sprintf(buffer,"state %d\r\n",rt2501_state());
    DBG(buffer);
}
*/
/*    uint8_t key64[8]={1,2,3,4,5,0,0,0};
    uint8_t key128[16]={1,2,3,4,5,6,7,8,9,0x10,0x11,0x12,0x13,0,0,0};
    uint8_t mypmk[]={
      0x05,0x68,0x57,0x9b,0xba,0x4a,0x67,0x07,
      0x2c,0x02,0x66,0x8e,0xd5,0x1f,0x02,0x51,
      0x03,0x07,0xb6,0x87,0xcc,0xd1,0x18,0x50,
      0xd2,0xd6,0xf5,0x6e,0x63,0x58,0x4e,0x03
    };


        uint8_t * ssid="ConnectionPoin";
	mypassword_to_pmk("foobarfoobar",ssid,strlen(ssid), bpmk);
*/
/*
      while(rt2501_state() != RT2501_S_IDLE)
		usbhost_events();

      	DBG_WIFI("Computing PMK...");
        uint8_t bpmk[64];

//        uint8_t * ssid="WANADOO-96B0";
//	mypassword_to_pmk("DEAD5EC03E2690D68171CB26EC",ssid,strlen(ssid), bpmk);

//        uint8_t * ssid="ConnectionPoin";
//	mypassword_to_pmk("foobarfoobar",ssid,strlen(ssid), bpmk);

        uint8_t * ssid="NETGEAR";
	mypassword_to_pmk("test tagtag",ssid,strlen(ssid), bpmk);

        scanssid=ssid;
	rt2501_scan(ssid, scantest, NULL);
        sprintf(buf,"auth %s\n",sresult.ssid);
        putst_uart(buf);

	rt2501_auth(sresult.ssid, sresult.mac, sresult.bssid, sresult.channel,
		    sresult.rateset,
		    IEEE80211_AUTH_OPEN,
		    IEEE80211_CRYPT_WPA,
		    bpmk);

        putst_uart("Loop\n");

        int32_tk;
        int32_tlastk=-1;
        int32_tt0=sysTimems();
        while(1)
        {
          struct rt2501buffer *r;
          uint8_t buffer[64];
          usbhost_events();
          k=rt2501_state();
          if (k!=lastk)
          {
            putst_uart("state=");
            putint_uart(k);
            putst_uart("\n");
            if (k==4)
            {
              mkarp(targetip);
              putst_uart("send arp\n");
              dump(tstarp, 8+7*4);
              rt2501_send((const uint8_t *)tstarp, 8+7*4,targetmac,1,1);
            }
          }
          lastk=k;
           while(r=rt2501_receive())
           {
              sprintf(buffer,"receive frame size %d from ",r->length);
              putst_uart(buffer);
              dumpbin(r->source_mac,6,0);
              putst_uart(" to ");
              dumpbin(r->dest_mac,6,1);

              dump((uuint8_t *)r->data,r->length);
              disable_ohci_irq();
              hcd_free(r);
              enable_ohci_irq();
            }
          int32_tt=sysTimems();
          if (t-t0>1000)
          {
            t0=t;
            rt2501_timer();
            putst_uart(".");
          }

        }
*/

  putst_uart((uint8_t*)"vmemInit\r\n");

		vmemInit(0);

putst_uart((uint8_t*)"loaderInit\r\n");

//                loaderInit((uint8_t *)SRAM_BASE);
		loaderInit((uint8_t *)dumpbc);
putst_uart((uint8_t*)"Done\r\n");
putst_uart((uint8_t*)"dumpShort\r\n");
		vmemDumpShort();
//		vmemDump();

//		for(i=0;i<6;i++) printf("fun %d at %d\n",i,loaderFunstart(i));
putst_uart((uint8_t*)"main\r\n");

		VPUSH(INTTOVAL(0));
		interpGo();
		(void)VPULL();
                int32_t counttimer=0;


                while(1)
//                for(iii=0;iii<10000;iii++)
		{
                    int32_t t;
                        CLR_WDT;

			VPUSH(VCALLSTACKGET(sys_start,SYS_CBLOOP));
			if (VSTACKGET(0)!=NIL) interpGo();
			(void)VPULL();
                        t=sysTimems();
                        do
                        {
//                           uint8_t buffer[64];
                           struct rt2501buffer *r;
                           play_check(0);
                           rec_check();

                           CLR_WDT;


                           usbhost_events();
                           while((sysTimems()-t<1000)&&(r=rt2501_receive()))
                           {
                              CLR_WDT;

//                              sprintf(buffer,"receive frame size %d\r\n",r->length);
//                              DBG(buffer);
//                              dump((uuint8_t *)r->data,r->length);
                              netCb((uint8_t *)r->data,r->length,(uint8_t *)r->source_mac);
                              disable_ohci_irq();
                              hcd_free(r);
                              enable_ohci_irq();
                              play_check(0);
                              rec_check();
                            }

                        }while(sysTimems()-t<50);
                        counttimer=(counttimer+1)&3;
                        if (!counttimer)
                        {
                          rt2501_timer();
                          putst_uart((uint8_t*)".");
//                          int32_txx=sysButton3();
//                          int32_txx=get_motor_position(1);
//                          putint_uart(xx);

/*                          foo=(int*)0xD000FFFC;
                          asm (
                               " PUSH {R0,R1}\n"
                               " MOV R0,R13\n"
                                 " MOV R1,#0xd0\n"
                               " LSL R1,R1,#16\n"
                                 " ADD R1,R1,#0xFF\n"
                               " LSL R1,R1,#8\n"
                                 " ADD R1,R1,#0xFC\n"
                               //  " LDR R1,foo\n"
//                                "MOV R1,#0x2FFF0004\n"
                               " STR R0,[R1]\n"
                               " POP {R0,R1}\n"
                               );
                          puthx_uart(*foo);
//                          puthx_uart(t);
*/
//                               "  MOV R0,#805240836\n"
//                               "  STR R13,805240836"
                        }

//			DelayMs(50);
		}


/*
     putst_uart("test flash\n");
   sysSrand(0);
   int32_tj;
   for(j=0;j<16;j++)
//   while(1)
   {
     uint8_t buffer[256];
     uint8_t res[256];
     putint_uart(j);
     putst_uart(":loop\n");

     int32_ti;
     for(i=0;i<256;i++)
     {
       int32_tx=0x3ff&sysRand();
       if (x>=0x300) x=0xff;
       else if (x>=0x200) x=0;
       else x&=0xff;

       buffer[i]=x;
     }
//       dump(buffer,256);
     putst_uart("x");
  __disable_interrupt();
        write_uc_flash(0,buffer,256,buffer_temp);
  __enable_interrupt();
//     putst_uart("y");
        read_uc_flash(0,res,256);
     putst_uart("z");
     int32_terr=0;
     for(i=0;i<256;i++) if (res[i]!=buffer[i])
     {
       puthx_uart(i);
       putst_uart(",");
       err=1;
     }
     if (err)
     {
       putst_uart("\n");
       dump(buffer,256);
       dump(res,256);
     }
     else putst_uart(" ok\n");

   }

*/
/*
  {
    int32_ti,is,j,k,t0;
    int32_tcol;
    int32_t*tb;
    uint8_t buffer[256];
    while(1)
    {

      // test timer
      putst_uart("Timer test\r\n");
      is=counter_timer;
      for(i=0;i<10000;i++)
      {
        j=(counter_timer-is)&0xffff;
        sprintf((uint8_t *)buffer,"\r%d",j); putst_uart((uint8_t*)buffer);
      }
      putst_uart("\r\n");

// test moteurs
      putst_uart("Motor test\r\n");
      stop_motor(1);
      stop_motor(2);

      run_motor(1,0xff,REVERSE);
      i=0;
      j=get_motor_position(1);
      while(1)
      {
        k=get_motor_position(1);
        if (k!=j)
        {
          sprintf((uint8_t *)buffer,"motor FORWARD deltaCount=%d during %d\r\n",j,i);
          putst_uart((uint8_t*)buffer);
          j=k;
          i=0;
        }
        DelayMs(100);
        i++;
      }
      for(i=1;i<=2;i++)
      {
        k=get_motor_position(i);
        run_motor(i,0xff,FORWARD);
        DelayMs(4000);
        k=get_motor_position(i)-k;
        sprintf((uint8_t *)buffer,"motor %d FORWARD deltaCount=%d\r\n",i,k); putst_uart((uint8_t*)buffer);
        k=get_motor_position(i);
        run_motor(i,0xff,REVERSE);
        DelayMs(4000);
        k=get_motor_position(i)-k;
        sprintf((uint8_t *)buffer,"motor %d REVERSE deltaCount=%d\r\n",i,k); putst_uart((uint8_t*)buffer);
        stop_motor(i);
      }

// test memory
      tb=(int*)SRAM_BASE;
      k=128*1024;

      putst_uart("RAM read-write test\r\n");

      for(i=0;i<k;i++) tb[i]=i;
      for(i=0;i<k;i++) if (tb[i]!=i)
      {
        putst_uart("Memory error\r\n");
        i=k;
      }

      putst_uart("RAM gc test\r\n");
      t0=counter_timer;
      i=0;
      is=0;
      while(is<k)
      {
        for(j=0;j<256;j++) tb[i+j]=tb[is+j];
        i+=256;
        is+=512;
      }
      t0=counter_timer-t0;
      sprintf((uint8_t *)buffer,"delta %d ms\r\n",t0); putst_uart((uint8_t*)buffer);

// test leds
      putst_uart("Leds test\r\n");
      col=0x7f0000;
      for(j=0;j<3;j++)
      {
        for(i=0;i<5;i++) set_led(i,0);
        for(i=0;i<5;i++)
        {
          set_led(i,col);
          DelayMs(250);
        }
        col>>=8;
      }
      for(k=0;k<3;k++)
      {
        col=0;
        for(j=0;j<=128;j++)
        {
          for(i=0;i<5;i++) set_led(i,col);
          col+=0x010101;
          DelayMs(20);
        }
      }
    }
  }
  */
/*****************/
/* DEBUG END */
/*****************/

/********************
      MAIN LOOP
********************/
/*
  putst_uart("Host transfer Cancel\r\n");
  transfer_request = 0;
  while(1)
  {
    if( old_state != STATE_HOST_ACTV ){
      putst_uart("USB Host Active!\r\n");
      ret = usbhost_init();
      if( ret != OK ){
        return ret;
      }
      old_state = STATE_HOST_ACTV;
    }
    usbhost_main();
  }
*/
}

/****************************************************************************/
/*  Registration of IRQ Handler                                             */
/*  Function : reg_irq_handler                                              */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/*  Note : Initialize of IRQ needs to be performed before this process.     */
/****************************************************************************/
void reg_irq_handler(void)
{
    /* register IRQ handlers into handler table */
    IRQ_HANDLER_TABLE[INT_EXINT2] = usbctrl_interrupt;
//    IRQ_HANDLER_TABLE[INT_EXINT3] = push_button_interrupt;
    IRQ_HANDLER_TABLE[INT_UART0] = uart0_interrupt;
    IRQ_HANDLER_TABLE[INT_SYSTEM_TIMER] = timer_handler;

    /* setup interrupt level */
    //Configure EXINT2 for USB interrupt
    clr_hbit(EXIDM,IDM_IDM36 & IDM_IDMP36); //set Low level for IRQ
    //Clear EXINT2 interrupt
    set_hbit(EXIRQB,IRQB_IRQ36);
    //Enable EXINT2 interrupts
    set_wbit(EXILCB,ILC_ILC36 & ILC_INT_LV7);

    /* setup interrupt level */
/*
    //Configure EXINT3 for Push Button interrupt
    clr_hbit(EXIDM,IDM_IDM38 & IDM_IDMP38); //set Low level for IRQ
    //Clear EXINT3 interrupt
    set_hbit(EXIRQB,IRQB_IRQ38);
    //Enable EXINT3 interrupts
    set_wbit(EXILCB,ILC_ILC38 & ILC_INT_LV6);
*/
    /* setup interrupt level */
    //Enable UART0 interrupts
    set_wbit(ILC1, ILC1_ILR9 & ILC1_INT_LV7 );

    /* setup interrupt level */
    //Enable System Timer interrupt
    set_wbit(ILC0, ILC0_ILR0 & ILC0_INT_LV7);

    return;
}

/****************************************************************************/
/*  Process of the System Timer interrupt                                   */
/*  Function : timer_handler                                                */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void timer_handler(void)
{
    counter_timer++;            //increment 1ms, 10ms or 100ms cycle counter
    counter_timer_sbuf++;
    if (counter_timer_sbuf>=1000)
    {
      counter_timer_s++;
      counter_timer_sbuf=0;
    }
    put_value(TMOVF,0x01);      //clear overflow register (write '1' in TMOVF[0])
    return;
}

/****************************************************************************/
/*  Process of the FIQ interrupt                                            */
/*  Function : FIQ_handler                                                  */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void FIQ_handler(void)
{
    /* Clear FIQ flag*/
     put_value(EXFIQ, 0x01 );
     __no_operation();
    return;
}

/****************************************************************************/
/*  Process of the UART0 interrupt                                          */
/*  Function : uart0_interrupt                                              */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void uart0_interrupt(void)
{
    //Save received byte in the UART buffer
    uint8_t c=get_value(UARTRBR0);
    UART_BUFFER[uart_buffer_pointer] = c;

    // update write pointer
    uart_buffer_pointer++;
    if(uart_buffer_pointer >= UART_BUFFER_SIZE)
        uart_buffer_pointer = 0;
}

/****************************************************************************/
/*  Process of the Push button interrupt                                    */
/*  Function : push_button_interrupt                                        */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void push_button_interrupt(void)
{
  //delay to avoid multiple interrupts
    DelayMs(250);

    //Run USB transmit
    transfer_request=1;

    //Update motor state
    if(motor_state++==6)
      motor_state=0;

    //Clear EXINT3 interrupt
    set_hbit(EXIRQB,IRQB_IRQ38);
}

int32_t push_button_value()
{
  if (INT_SWITCH_READ&INT_SWITCH_BIT) return 0;
  return 1;
}

/****************************************************************************/
/*  Init GPIO initial directions and values ; define the function of pins   */
/*  Function : init_io                                                      */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void init_io(void)
{
  //Set primary functions of ports
  put_wvalue(PORTSEL1,0x00000000);
  put_wvalue(PORTSEL2,0x00000000);
  put_wvalue(PORTSEL3,0x00000000);
  put_wvalue(PORTSEL4,0x00000000);
  put_wvalue(PORTSEL5,0x00000000);
  //Set all pins as inputs
  put_value(PM0,0x00);
  put_value(PM1,0x00);
  put_value(PM2,0x00);
  put_value(PM3,0x00);
  put_value(PM4,0x00);
  put_value(PM5,0x00);
  put_value(PM6,0x00);
  put_value(PM7,0x00);
  put_value(PM8,0x00);
  put_value(PM9,0x00);
  put_value(PM10,0x00);
  put_value(PM11,0x00);
  put_value(PM12,0x00);
  put_value(PM13,0x00);
  put_value(PM14,0x00);

  //Set secondary function for XD16 to XD31 => GPIO
  set_wbit(PORTSEL4,0x00000040);
#if (PCB_RELEASE == LLC2_3) || (PCB_RELEASE == LLC2_4c)
#ifdef MOTOR_SPEED_CONTROL
  //Set secondary function for PF0 to PF3  => Timer0 to Timer 5
  set_wbit(PORTSEL3,0x05550000);
#else
  //Set secondary function for PF0 to PF1  => Timer0 to Timer 1
  set_wbit(PORTSEL3,0x00050000);
#endif
#elif PCB_RELEASE == LLC2_2
  //Set secondary function for PF0 to PF5  => Timer0 to Timer 5
  set_wbit(PORTSEL3,0x05550000);
#endif
  //Set secondary function for PB0 and PB1  => TX_RS232 and RX_RS232
  set_wbit(PORTSEL1,0x00050000);
  //Set tertiary function for PD0 => EXINT2, secondary funtion for PD2 => ADC2
  //tertiary funtion for PD1 => EXINT3
  set_wbit(PORTSEL2,0x001A0000);
  //Set secondary function for PB4 and PB5  => I2C bus : SCL + SDA
  set_wbit(PORTSEL1,0x05000000);

#if PCB_RELEASE == LLC2_4c

  //Set I/O directions
  CS_AUDIO_AMP_AS_OUTPUT;
  CS_LED_AS_OUTPUT;
  MODE_LED_AS_OUTPUT;
  CS_AUDIO_SCI_AS_OUTPUT;
  INT_AUDIO_AS_INPUT;
  WAIT_USB_AS_INPUT;
  RST_AUDIO_AS_OUTPUT;
  INT_USB_AS_INPUT;
  INT_SWITCH_AS_INPUT;
  CS_AUDIO_SDI_AS_OUTPUT;
  PWM_MCC1_AS_OUTPUT;
  PWM_MCC2_AS_OUTPUT;
  PWM_MCC3_AS_OUTPUT;
  PWM_MCC4_AS_OUTPUT;

  //Set I/O initial values
  CS_AUDIO_AMP_CLEAR;
  CS_LED_SET;
  MODE_LED_CLEAR;
  CS_AUDIO_SCI_SET;
  RST_AUDIO_CLEAR;
  CS_AUDIO_SDI_SET;
  PWM_MCC1_CLEAR;
  PWM_MCC2_CLEAR;
  PWM_MCC3_CLEAR;
  PWM_MCC4_CLEAR;

#elif PCB_RELEASE == LLC2_3

  //Set I/O directions
  CS_AUDIO_AMP_AS_OUTPUT;
  CS_LED_AS_OUTPUT;
  MODE_LED_AS_OUTPUT;
  CS_AUDIO_SCI_AS_OUTPUT;
  INT_AUDIO_AS_INPUT;
  WAIT_USB_AS_INPUT;
  RST_AUDIO_AS_OUTPUT;
  CS_FLASH_AS_OUTPUT;
  INT_USB_AS_INPUT;
  INT_SWITCH_AS_INPUT;
  CS_AUDIO_SDI_AS_OUTPUT;
  PWM_MCC1_AS_OUTPUT;
  PWM_MCC2_AS_OUTPUT;
  PHASE_MCC1_AS_OUTPUT;
  PHASE_MCC2_AS_OUTPUT;

  //Set I/O initial values
  CS_AUDIO_AMP_CLEAR;
  CS_LED_SET;
  MODE_LED_CLEAR;
  CS_AUDIO_SCI_SET;
  RST_AUDIO_CLEAR;
  CS_FLASH_SET;
  CS_AUDIO_SDI_SET;
  PWM_MCC1_CLEAR;
  PWM_MCC2_CLEAR;
  PWM_MCC3_CLEAR;
  PWM_MCC4_CLEAR;
  PHASE_MCC1_CLEAR;
  PHASE_MCC2_CLEAR;

#elif PCB_RELEASE == LLC2_2
  //Set I/O directions
  CS_LED_AS_OUTPUT;
  MODE_LED_AS_OUTPUT;
  CS_AUDIO_AMP_AS_OUTPUT;
  RST_AUDIO_AS_OUTPUT;
  CS_AUDIO_SDI_AS_OUTPUT;
  CS_AUDIO_SCI_AS_OUTPUT;
  CMD_MCC0_AS_OUTPUT;
  CMD_MCC1_AS_OUTPUT;
  CMD_MCC2_AS_OUTPUT;
  CMD_MCC3_AS_OUTPUT;
  WAIT_USB_AS_INPUT;
  INT_USB_AS_INPUT;
  INT_AUDIO_AS_INPUT;
  INT_SWITCH_AS_INPUT;

  //Set I/O initial values
  CS_LED_SET;
  MODE_LED_CLEAR;
  CS_AUDIO_AMP_CLEAR;
  RST_AUDIO_CLEAR;
  CS_AUDIO_SDI_SET;
  CS_AUDIO_SCI_SET;
  CMD_MCC0_CLEAR;
  CMD_MCC1_CLEAR;
  CMD_MCC2_CLEAR;
  CMD_MCC3_CLEAR;
#endif
}

void reset_uc(void)
{
  put_value(INTST,0x3c);  //release write protection
  put_value(INTST,0x00);  //Clear status bit

  put_value(TBGCON,0x5A);  //release write protection
  put_value(TBGCON,0x40);  //Watchdog clock = APB_CLK/32 => 1us @32MHz => overflow each 65536us
                           //generates reset when overflow ; Turn ON counter

  put_value(OVFAST,0x63);  //assert time to be ouput from the RSTOUT_N pin of 100us

  put_value(WDTCON,0x3C);  //Start watchdog

  //Clear watchdog
//  put_value(WDTCON,0xC3);
//  put_value(WDTCON,0x3C);

  put_hvalue(WDTCNT,0x5A5A);  //release write protection
  put_hvalue(WDTCNT,0xFF00);  //rewrite counter register to overflow => overflow in 256us
  while(1);
}

