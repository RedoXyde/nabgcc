/*******************************************************************************
    hcdmem.c

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    Mar.31,2003 rev1.00
*******************************************************************************/

#include <stdio.h>
#include "ml674061.h"
#include "common.h"
#include "hcdmem.h"
#include "debug.h"
#include "delay.h"

/**
 * @brief Get the max value
 *
 * @param a
 * @param b
 *
 * @return max(a,b)
 */
#define max(a,b)	(((a)>(b))? (a):(b))

/*--------------------------------------------------------------------------*/
typedef struct _memory
{
	struct _memory *Next;
	uint32_t Address;
	uint32_t Area;
	uint32_t Size;
	uint32_t tag;
	unsigned int time;
} MMDL, *PMMDL;

typedef struct _buffer{
	PMMDL MMDLs;
	uint32_t Address;
	uint32_t PhyAddress;
	uint32_t Size;
	uint32_t Boundary;
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
int8_t hcd_malloc_init(int32_t Address, uint32_t Size,
                    uint32_t Boundary, uint8_t Bank)
{
#ifdef DEBUG
        sprintf(dbg_buffer, "Set up memory bank %d, addr 0x%08lx, size %ld\r\n",
		Bank, Address, Size);
        DBG(dbg_buffer);
#endif

	if(Bank<BufferBanks){
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

int8_t hcd_malloc_check(void *Address)
{
	int8_t Bank;

	for(Bank = 0; Bank < BufferBanks; Bank++){
		if(((uint32_t)Address	< (uint32_t)BufferTable[Bank].Address
										+ BufferTable[Bank].Size)
		&& ((uint32_t)Address	>= (uint32_t)BufferTable[Bank].Address)){
			return Bank;
		}
	}

	return -1;
}

void *hcd_malloc(uint32_t Size, int8_t Bank,int32_t tag)
{
	PMMDL	pLastMMDL;
	PMMDL	pNextMMDL;
	PMMDL	pNewMMDL;
	uint32_t	NextBufferAddress;
	PMBDL	Buffer;
	uint32_t	Area;

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
                    sprintf(dbg_buffer,"addr=%lx area=%lx size=%lx tag=%ld time=%d\n",pNextMMDL->Address,pNextMMDL->Area,pNextMMDL->Size,pNextMMDL->tag,pNextMMDL->time);
                    DBG(dbg_buffer);
                    pNextMMDL = pNextMMDL->Next;
                }
                 sprintf(dbg_buffer,"time=%ld\n",counter_timer);
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

	return (uint8_t *)NextBufferAddress;
}

int8_t hcd_free(void * pAddress)
{
	PMMDL	pLastMMDL;
	PMMDL	pNowMMDL;
	PMBDL	Buffer;
	int8_t	Bank;


	Bank = hcd_malloc_check(pAddress);
	if(Bank<0) return 0;

	Buffer = &BufferTable[Bank];

	if(pAddress == NULL) return 0;

	if(Buffer->MMDLs == NULL) return 0;

	pNowMMDL = Buffer->MMDLs;
	if((uint8_t *)pNowMMDL->Address == (uint8_t *)pAddress){

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

		if((uint8_t *)pNowMMDL->Address == (uint8_t *)pAddress){
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

int32_t hcd_malloc_rest(uint8_t Bank)
{
	PMMDL	pLastMMDL;
	uint32_t	LastBufferAddress;
	PMBDL	Buffer;
	uint32_t Gap2MaxSize = 0;
	uint32_t FreeMaxSize;
	uint32_t rest;

	if(Bank<BufferBanks){
		Buffer = &BufferTable[Bank];
	}else{
		DBG_USB(" hcd_malloc_rest: Bad number of Bank.\r\n");
        return -1;
	}

	pLastMMDL = Buffer->MMDLs;
	LastBufferAddress = Buffer->Address;

	while(pLastMMDL != NULL){
		if(LastBufferAddress != pLastMMDL->Address){
				Gap2MaxSize = max(Gap2MaxSize, (pLastMMDL->Address - LastBufferAddress));
			}

		LastBufferAddress = pLastMMDL->Address + pLastMMDL->Area;
		pLastMMDL = pLastMMDL->Next;
	}

	FreeMaxSize = Buffer->Size - (int32_t)(LastBufferAddress - Buffer->Address);

	rest = max(Gap2MaxSize, FreeMaxSize)-sizeof(MMDL);

	return (int32_t)rest;
}

