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