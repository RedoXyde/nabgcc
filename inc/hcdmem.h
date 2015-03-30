/*******************************************************************************
    hcdmem.h

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    Mar.31,2003 rev1.00
*******************************************************************************/

#ifndef _HCDMEM_H_
#define _HCDMEM_H_

/* Memory allocator */

int hcd_malloc_init(unsigned long, unsigned long, unsigned long, int);
void *hcd_malloc(unsigned long, int,int);
int hcd_free(void *);
void hcd_malloc_info(int);
int hcd_malloc_check(void *);
int hcd_malloc_rest(int);

#endif /* _HCDMEM_H_ */
