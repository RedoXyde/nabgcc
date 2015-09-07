#include "ml674061.h"
#include "common.h"
#include "delay.h"



/****************************************************************************/
/*  Delay routine in ms which uses hardware timer                           */
/*  Function : DelayMs                                                      */
/*      Parameters                                                          */
/*          Input   :   number of ms in 16bits => 65,535sec max             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void DelayMs(int16_t cmpt_ms)
{
  int t=counter_timer;
  CLR_WDT;

  while(cmpt_ms>(counter_timer-t))CLR_WDT;
}
