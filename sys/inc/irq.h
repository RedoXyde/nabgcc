#ifndef _IRQ_H_
#define _IRQ_H_

typedef void IRQ_HANDLER(void);
typedef IRQ_HANDLER *pIRQ_HANDLER;

void init_irq(void);

#define IRQSIZE 64

extern pIRQ_HANDLER IRQ_HANDLER_TABLE[IRQSIZE];

#endif
