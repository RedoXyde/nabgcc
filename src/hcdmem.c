/*******************************************************************************
    hcdmem.c

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    Mar.31,2003 rev1.00
*******************************************************************************/

#include <stdio.h>
#include "ML674061.h"
#include "common.h"
#include "hcdmem.h"
#include "debug.h"
#include "delay.h"

#define max(a,b)	( ( (a) > (b) ) ? (a) : (b) )

/*--------------------------------------------------------------------------*/
typedef struct _memory {
	struct _memory *Next;
	unsigned long Address;
	unsigned long Area;
	unsigned long Size;
	unsigned long tag;
	unsigned int time;
} MMDL, *PMMDL;

typedef struct _buffer{
	PMMDL MMDLs;
	unsigned long Address;
	unsigned long PhyAddress;
	unsigned long Size;
	unsigned long Boundary;
} MBDL, *PMBDL;

/*--------------------------------------------------------------------------*/
#define BufferBanks		3

static MBDL BufferTable[BufferBanks] = {
	{ NULL, 0, 0, 0 ,0},
	{ NULL, 0, 0, 0 ,0},
	{ NULL, 0, 0, 0 ,0}
};

/*--------------------------------------------------------------------------*/
#define SetBoundary(Addr, Boundary) (((Addr) % (Boundary) == 0 ) ? (Addr) : \
									(((Addr) / (Boundary) + 1) * (Boundary)))
int hcd_malloc_init(unsigned long Address, unsigned long Size,
                    unsigned long Boundary, int Bank)
{
#ifdef DEBUG
        sprintf(dbg_buffer, "Set up memory bank %d, addr 0x%08x, size %d\r\n",
		Bank, Address, Size);
        DBG(dbg_buffer);
#endif
	
	if(Bank>=0 && Bank<BufferBanks){
		BufferTable[Bank].MMDLs = NULL;
		BufferTable[Bank].Address = Address;
		BufferTable[Bank].Size = Size;
		BufferTable[Bank].Boundary = Boundary;
		BufferTable[Bank].PhyAddress = Address;

	} else {
		DBG_USB(" hcd_malloc: Bad number of Bank.\n");
		return -1;
	}

	return 0;
}

int hcd_malloc_check(void * Address)
{
	int Bank;

	for(Bank = 0; Bank < BufferBanks; Bank++){
		if(((unsigned long)Address	< (unsigned long)BufferTable[Bank].Address
										+ BufferTable[Bank].Size)
		&& ((unsigned long)Address	>= (unsigned long)BufferTable[Bank].Address)){
			return Bank;
		}
	}

	return -1;
}

void *hcd_malloc(unsigned long Size, int Bank,int tag)
{
	PMMDL	pLastMMDL;
	PMMDL	pNextMMDL;
	PMMDL	pNewMMDL;
	unsigned long	NextBufferAddress;
	PMBDL	Buffer;
	unsigned long	Area;
	
	if(Bank>=0 && Bank<BufferBanks){
		Buffer = &BufferTable[Bank];
	}else{
		DBG(" hcd_malloc: Bad number of Bank.\r\n");
		return NULL;
	}
	
	if(Buffer->Address == 0){
		DBG("hcd_malloc: No memory for buffer.\r\n");
		return NULL;
	}

	if(Size==0) return NULL;

    if( Size > (Buffer->Size - sizeof(MMDL)) ){
	DBG("hcd_malloc: Size > (Buffer->Size - sizeof(MMDL)\r\n");
        return NULL;
    }

	Area = Size + sizeof(MMDL);
	switch(Area % 4){
		case 1: Area = Area + 3; break;
		case 2: Area = Area + 2; break;
		case 3: Area = Area + 1; break;
        default:                 break;
	}
	
	if(Buffer->MMDLs == NULL){
		NextBufferAddress = Buffer->Address;
		pLastMMDL = NULL;
		pNextMMDL = NULL;
	}
	else{
		NextBufferAddress = SetBoundary(Buffer->Address, Buffer->Boundary);
		pLastMMDL = NULL;
		pNextMMDL = Buffer->MMDLs;

		while(pNextMMDL != NULL){
		
			if(NextBufferAddress + Area <= pNextMMDL->Address){
				break;
			}

			NextBufferAddress = SetBoundary(pNextMMDL->Address + pNextMMDL->Area, Buffer->Boundary);
			pLastMMDL = pNextMMDL;
			pNextMMDL = pLastMMDL->Next;
		}

	}

	if(NextBufferAddress + Area > Buffer->Address + Buffer->Size)
        {
          	DBG("hcd_malloc: NextBufferAddress + Area > Buffer->Address + Buffer->Size\r\n");
                pNextMMDL = Buffer->MMDLs;
		while(pNextMMDL != NULL)
                {
                    sprintf(dbg_buffer,"addr=%x area=%x size=%x tag=%d time=%d\n",pNextMMDL->Address,pNextMMDL->Area,pNextMMDL->Size,pNextMMDL->tag,pNextMMDL->time);
                    DBG(dbg_buffer);
                    pNextMMDL = pNextMMDL->Next;
                }
                 sprintf(dbg_buffer,"time=%d\n",counter_timer);
                  DBG(dbg_buffer);
		return NULL;
	}

	pNewMMDL = (PMMDL)(NextBufferAddress + Area - sizeof(MMDL));
	
	pNewMMDL->Address = NextBufferAddress;
	pNewMMDL->Area = Area;
	pNewMMDL->Size = Size;
        pNewMMDL->tag=tag;
        pNewMMDL->time=counter_timer;

	if(pLastMMDL == NULL){
		Buffer->MMDLs = pNewMMDL;
	}else{
		pLastMMDL->Next = pNewMMDL;
	}

	pNewMMDL->Next = pNextMMDL;
	
/*
        if (tag==19)
        {
          sprintf(dbg_buffer,"malloc addr=%x area=%x size=%x tag=%d time=%d\n",pNewMMDL->Address,pNewMMDL->Area,pNewMMDL->Size,pNewMMDL->tag,pNewMMDL->time);
          DBG(dbg_buffer);
        }
*/
/*        sprintf(dbg_buffer, "hcd_malloc: %08lX (%d,%d)\r\n", NextBufferAddress, Size, Area);
        DBG(dbg_buffer);*/

	return (unsigned char *)NextBufferAddress;
}

int hcd_free(void * pAddress)
{
	PMMDL	pLastMMDL;
	PMMDL	pNowMMDL;
	PMBDL	Buffer;
	int		Bank;


	Bank = hcd_malloc_check(pAddress);
	if(Bank<0) return 0;

	Buffer = &BufferTable[Bank];

	if(pAddress == NULL) return 0;

	if(Buffer->MMDLs == NULL) return 0;

	pNowMMDL = Buffer->MMDLs;
	if((unsigned char *)pNowMMDL->Address == (unsigned char *)pAddress){

/*          if (pNowMMDL->tag==19)
          {
            sprintf(dbg_buffer,"hcd_free: %x\r\n", pAddress);
            DBG(dbg_buffer);
          }
*/

		Buffer->MMDLs = pNowMMDL->Next;
		/*free(pNowMMDL);*/
		return 1;
	}

	pLastMMDL = Buffer->MMDLs;
	while(pLastMMDL->Next != NULL){

		pNowMMDL = pLastMMDL->Next;

		if((unsigned char *)pNowMMDL->Address == (unsigned char *)pAddress){
/*
          if (pNowMMDL->tag==19)
          {
            sprintf(dbg_buffer,"hcd_free: %x\r\n", pAddress);
            DBG(dbg_buffer);
          }
*/
			pLastMMDL->Next = pNowMMDL->Next;
			/*free(pNowMMDL);*/
			return 1;
		}

		pLastMMDL = pNowMMDL;
	}

	return 0;
}

int hcd_malloc_rest(int Bank)
{
	PMMDL	pLastMMDL;
	unsigned long	LastBufferAddress;
	PMBDL	Buffer;
	unsigned long Gap2MaxSize = 0;
	unsigned long FreeMaxSize;
	unsigned long rest;

	if(Bank>=0 && Bank<BufferBanks){
		Buffer = &BufferTable[Bank];
	}else{
		DBG_USB(" hcd_malloc_rest: Bad number of Bank.\r\n");
        return -1;
	}

	pLastMMDL = Buffer->MMDLs;
	LastBufferAddress = Buffer->Address;

	while(pLastMMDL != NULL){
		if(LastBufferAddress != pLastMMDL->Address){
				Gap2MaxSize = max(Gap2MaxSize, (int)(pLastMMDL->Address - LastBufferAddress));
			}

		LastBufferAddress = pLastMMDL->Address + pLastMMDL->Area;
		pLastMMDL = pLastMMDL->Next;
	}

	FreeMaxSize = Buffer->Size - (int)(LastBufferAddress - Buffer->Address);

	rest = max(Gap2MaxSize, FreeMaxSize)-sizeof(MMDL);

	return (int)rest;
}

