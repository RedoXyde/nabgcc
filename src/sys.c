#include <stdio.h>
#include <stdint.h>
extern int32_t __heap_start__;
extern int32_t __heap_end__;

extern void *_sbrk(int32_t incr)
{
    static uint8_t *heap = NULL;
    uint8_t *prev_heap;

    if (heap == NULL) {
        heap = (uint8_t *)&__heap_start__;
    }
    prev_heap = heap;

    if ((heap + incr) >= (uint8_t *)&__heap_end__) {
        return 0;
    }
    heap += incr;
    return (void *)prev_heap;
}

extern void _port_disable_thumb(void);
extern void _port_enable_thumb(void);
void __disable_interrupt(void)
{
  _port_disable_thumb();
}

void __enable_interrupt(void)
{
  _port_enable_thumb();
}
/*

@ int di();

.thumb
di:
bx pc
nop
.arm
di_arm:
mrs r0,cpsr
orr r1,r0,#0xc0
msr cpsr_c,r1
bx lr
.thumb

@ void ei(int oldmask);
.thumb
ei:
bx pc
nop
.arm
ei_arm:
and r0,r0,#0xc0 @ only modify F and I
mrs r1,cpsr
bic r1,r1,r0
msr cpsr_c,r1
bx lr
*/


