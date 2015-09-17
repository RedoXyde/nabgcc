#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


#include "vm/vmem.h"
#include "vm/vinterp.h"
#include "vm/vloader.h"
#include "vm/vlog.h"

uint8_t dbg_buffer[50];
extern uint8_t *dumpbc;

uint32_t counter_timer, counter_timer_s;


int32_t _vmem_heap[VMEM_LENGTH];

int main(void)
{
  vmemInit(0);
  loaderInit((uint8_t *)&dumpbc);

  consolestr("dumpShort\r\n");
  vmemDumpShort();
  vmemDump();
  uint32_t i;
  for(i=0;i<_bc_nbfun;i++)
    printf("fun %d at %d\n",i,loaderFunstart(i));


  VPUSH(INTTOVAL(0));
  interpGo();
  (void)VPULL();

  uint8_t counttimer=0;
  while(1)
//                for(iii=0;iii<10000;iii++)
  {
//    uint32_t t;

    VPUSH(VCALLSTACKGET(_sys_start,SYS_CBLOOP));
    if (VSTACKGET(0)!=NIL)
      interpGo();
    (void)VPULL();
//    t=sysTimems();
//    do
//    {
//      struct rt2501buffer *r;
//      play_check(0);
//      rec_check();


//      usbhost_events();
//      while((sysTimems()-t<1000)&&(r=rt2501_receive()))
//      {
//        CLR_WDT;
//
//        sprintf(buffer,"receive frame size %ld"EOL,r->length);
//        DBG(buffer);
//        dump((uint8_t *)r->data,r->length);
//        netCb((uint8_t *)r->data,r->length,(uint8_t *)r->source_mac);
//        disable_ohci_irq();
//        hcd_free(r);
//        enable_ohci_irq();
//        play_check(0);
//        rec_check();
//      }
//    } while(sysTimems()-t<50);
//    counttimer=(counttimer+1)&3;
//    if (!counttimer)
//    {
//      rt2501_timer();
//      consolestr(".");
//    }
  }

  consolestr(EOL"Done !"EOL);
  getchar();
  return EXIT_SUCCESS;
}

void dump(uint8_t *src,int32_t len)
{
  int32_t i,j;
  uint8_t buffer[64];
  consolestr((uint8_t*)"\r\n");
  for(i=0;i<len;i+=16)
  {
    sprintf((char*)buffer,"%04lx ",i);
    consolestr(buffer);
    for(j=0;j<16;j++) if (i+j<len)
    {
      sprintf((char*)buffer,"%02x ",src[i+j]); consolestr(buffer);
    }
    else consolestr((uint8_t*)"   ");
    for(j=0;j<16;j++) if (i+j<len) putch_uart(((src[i+j]>=32)&&(src[i+j]<128))?src[i+j]:'.');
    consolestr((uint8_t*)"\r\n");
//    DelayMs(100);
  }
}

uint8_t push_button_value(void)
{
  return 0;
}

void reset_uc(void)
{

}
