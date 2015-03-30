/**********************************************************************************/
/*                                                                                */
/*    Copyright (C) 2005 Oki Electric Industry Co., LTD.                          */
/*                                                                                */
/*    System Name    :  uPLAT series                                              */
/*    Module Name    :  header file for using IRQ                                 */
/*    File   Name    :  irq.h                                                     */
/*    Revision       :  01.00                                                     */
/*    Date           :  2005/2/08 initial version                                 */
/*                                                                                */
/**********************************************************************************/

#ifndef _IRQ_H_
#define _IRQ_H_

#include "common.h"

/* type definition */
typedef void IRQ_HANDLER(void);
typedef IRQ_HANDLER *pIRQ_HANDLER;

/*************************************************************************************************/
/*  Initialize Interrupt Control Registers (IRQ interrupt)                                       */
/*  Function : init_irq                                                                          */
/*      Parameters                                                                               */
/*          Input   :   Nothing                                                                  */
/*          Output  :   Nothing                                                                  */
/*************************************************************************************************/
void init_irq(void);

#define IRQSIZE 64

/*************************************************************************************************/
/*  Table of IRQ handler                                                                         */
/*      If interrupt of interrupt number N occurred,                                             */
/*      function of IRQ_HANDLER_TABLE[N] is called.                                              */
/*************************************************************************************************/
extern pIRQ_HANDLER IRQ_HANDLER_TABLE[IRQSIZE];

#endif
