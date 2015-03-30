/**********************************************************************************/
/*                                                                                */
/*    Copyright (C) 2005 Oki Electric Industry Co., LTD.                          */
/*                                                                                */
/*    System Name    :  uPLAT series                                              */
/*    Module Name    :  IRQ module                                                */
/*    File   Name    :  irq.c                                                     */
/*    Revision       :  01.00                                                     */
/*    Date           :  2005/02/15 initial version                                */
/*                                                                                */
/**********************************************************************************/
#include "ML674061.h"
#include "common.h"
#include "irq.h"

/****************************************************************************/
/*  Table of IRQ handler                                                    */
/*      If interrupt of interrupt number N occurred,                        */
/*      function of IRQ_HANDLER_TABLE[N] is called.                         */
/****************************************************************************/
pIRQ_HANDLER IRQ_HANDLER_TABLE[IRQSIZE];

/****************************************************************************/
/*  Not defined interrupt                                                   */
/*  Function : null_handler                                                 */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void null_handler(void)
{
    return;
}

/****************************************************************************/
/*  Initialize interrupt control registers (IRQ interrupt)                  */
/*  Function : init_irq                                                     */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void init_irq(void)
{
    int i;

/* initialize IRQ registers */
    put_wvalue(ILC0, 0x0);  /* all interrupt level is set as 0 */
    put_wvalue(ILC1, 0x0);  /* all interrupt level is set as 0 */
    put_wvalue(EXILCA, 0x0);   /* all interrupt level is set as 0 */
    put_wvalue(EXILCB, 0x0);   /* all interrupt level is set as 0 */
    put_wvalue(EXILCC, 0x0);   /* all interrupt level is set as 0 */
	
    put_wvalue(FIQEN, 0x0);  /* FIQ is canceled */

    put_wvalue(IRQS, 0x0);  /* soft interrupt is canceled */

    put_wvalue(CIL, 0x0FE); /* CIL register is cleared
                               (write '1' in CIL[n](1<=n<=7)) */

    /* initialize IRQ handler table */
    for(i=0; i<IRQSIZE; i++){
        IRQ_HANDLER_TABLE[i] = null_handler;    /* no interrupt handler is
                                                   defined yet */
    }

    return;
}
