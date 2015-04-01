/*******************************************************************************
    hcdmem.h

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    Mar.31,2003 rev1.00
*******************************************************************************/

#ifndef _HCDMEM_H_
#define _HCDMEM_H_

/* Memory allocator */

int8_t hcd_malloc_init(uint32_t, uint32_t, uint32_t, uint8_t);
void *hcd_malloc(uint32_t, int8_t,int32_t);
int8_t hcd_free(void *);
void hcd_malloc_info(int32_t);
int8_t hcd_malloc_check(void *);
int32_t hcd_malloc_rest(uint8_t);

#endif /* _HCDMEM_H_ */
