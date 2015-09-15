/**
 * @file vmem.c
 * @author Sylvain Huet - 2006 - Initial version
 * @author RedoX <dev@redox.ws> - 2015 - GCC Port, cleanup
 * @date 2015/09/07
 * @brief VLISP Virtual Machine - Memory functions
 */
#include <stdint.h>
#include <string.h>

#include"vmem.h"
#include"vloader.h"
#include"vlog.h"

void play_check(int32_t nocb);

#ifdef VSIMU
int32_t vmem_heap[VMEM_LENGTH];
#endif


int32_t vmem_heapindex;
int32_t *vmem_top;
int32_t vmem_stack;
int32_t vmem_start;
int32_t vmem_broken;

// initialisation de la mémoire
void vmemInit(int32_t start)
{
	vmem_top=&vmem_heap[VMEM_LENGTH];
	vmem_stack=0;
	vmem_start=vmem_heapindex=start;
        vmem_broken=0;
}

void vmemSetstart(int32_t start)
{
	int32_t size;

	if (start>=vmem_start-HEADER_LENGTH) return;

	size=((vmem_start-HEADER_LENGTH-start)<<2)-1;

	vmem_heap[start]=(size<<8)+(TYPE_BINARY);
	vmem_heap[start+HEADER_GC]=0;
	vmem_heap[start+HEADER_LIST]=0;

	vmem_start=start;
}


void vmemGCfirst()
{
	int32_t i,k,j,n;
	int32_t first;

	first=-1;
	for(i=vmem_stack;i<0;i++)
	{
		k=vmem_top[i];
		if ((ISVALPNT(k))&&(k!=NIL))
		{
			k=VALTOPNT(k);
//                        if ((k<0)||(k>=VMEM_LENGTH)) consolestr("1.k out of space\n");
			if (!HEADER_USED(k))
			{
				HEADER_MARK(k);
				vmem_heap[k+HEADER_LIST]=first;
				first=k;
			}
		}
	}
	while(first!=-1)
	{
		k=first;
//                if ((k<0)||(k>=VMEM_LENGTH)) consolestr("1.first out of space\n");
		first=vmem_heap[k+HEADER_LIST];
		if (HEADER_TYPE(k))        // bloc table
		{
			n=VSIZE(k);
			j=k+HEADER_LENGTH;
			for(i=0;i<n;i++)
			{
				k=vmem_heap[j+i];
				if ((ISVALPNT(k))&&(k!=NIL))
				{
					k=VALTOPNT(k);
//                   if ((k<0)||(k>=VMEM_LENGTH)) consolestr("1.k2 out of space\n");
					if (!HEADER_USED(k))
					{
						HEADER_MARK(k);
						vmem_heap[k+HEADER_LIST]=first;
						first=k;
					}
				}
			}
		}
	}
}
void dumpheap()
{
	int32_t pos,realsize;

	pos=vmem_start;

	while(pos < vmem_heapindex)
	{
		realsize=VSIZE(pos)+HEADER_LENGTH;
                consolehx(pos); consolestr(":pos ");consolehx(realsize);
    consolestr(":realsize\n");
  if ((realsize<0)||(realsize>=VMEM_LENGTH))
  {
    consolestr("2.realsize out of range\n");
    dump((uint8_t*)&vmem_heap[pos-32],128);
    return;
  }
    dump((uint8_t*)&vmem_heap[pos],32);
		pos+=realsize;
	}
}
void vmemGCsecond()
{
	int32_t pos,newpos,realsize;

	pos=newpos=vmem_start;

	while(pos < vmem_heapindex)
	{
		realsize=VSIZE(pos)+HEADER_LENGTH;
/*  if ((realsize<0)||(realsize>=VMEM_LENGTH))
  {
    dumpheap();
//    consolestr("2.realsize out of range\n");
//    dump((uint8_t*)&vmem_heap[pos-32],128);
  }
*/
                if (HEADER_USED(pos))
		{
			vmem_heap[pos+HEADER_GC]=newpos<<1;
			newpos+=realsize;
		}
		pos+=realsize;
	}
}

void vmemGCthird()
{
	int32_t i,k,j,n;
	int32_t first;

	first=-1;
	for(i=vmem_stack;i<0;i++)
	{
		k=vmem_top[i];
		if ((ISVALPNT(k))&&(k!=NIL))
		{
			k=VALTOPNT(k);
			vmem_top[i]=vmem_heap[k+HEADER_GC]|1;	// attention, hack
			if (!HEADER_USED(k))
			{
				HEADER_MARK(k);
				vmem_heap[k+HEADER_LIST]=first;
				first=k;
			}
		}
	}
	while(first!=-1)
	{
		k=first;
		first=vmem_heap[k+HEADER_LIST];
		if (HEADER_TYPE(k))        // bloc table
		{
			n=VSIZE(k);
			j=k+HEADER_LENGTH;
			for(i=0;i<n;i++)
			{
				k=vmem_heap[j+i];
				if ((ISVALPNT(k))&&(k!=NIL))
				{
					k=VALTOPNT(k);
					vmem_heap[j+i]=vmem_heap[k+HEADER_GC]|1;	// attention, hack
					if (!HEADER_USED(k))
					{
						HEADER_MARK(k);
						vmem_heap[k+HEADER_LIST]=first;
						first=k;
					}
				}
			}
		}
	}
}
void vmemGCfourth()
{
	int32_t pos,newpos,realsize,i;

	pos=newpos=vmem_start;

	while(pos < vmem_heapindex)
	{
		realsize=VSIZE(pos)+HEADER_LENGTH;
		if (HEADER_USED(pos))
		{
			vmem_heap[pos+HEADER_GC]=0;
                        if (newpos!=pos)
                        {
                          if (newpos+realsize<=pos)
                            memcpy(&vmem_heap[newpos],&vmem_heap[pos],realsize<<2);
                          else
                          {
                            consolestr("########GC : BIG MOVE\n");
                            for(i=0;i<realsize;i++) vmem_heap[newpos+i]=vmem_heap[pos+i];
                          }

                          newpos+=realsize;
                          pos+=realsize;
//                        for(i=0;i<realsize;i++) vmem_heap[newpos++]=vmem_heap[pos++];
                        }
                        else newpos=pos=pos+realsize;
		}
		else
		{
			// ## ajouter ici la gestion des types externes : if (HEADER_EXT(pos)) ...
			pos+=realsize;
		}
	}
	vmem_heapindex=newpos;
}

void vmemGC()
{
//  logGC();
#ifdef VREAL
	play_check(1);
#endif
	vmemGCfirst();
#ifdef VREAL
  play_check(1);
#endif
	vmemGCsecond();
#ifdef VREAL
  play_check(1);
#endif
	vmemGCthird();
#ifdef VREAL
  play_check(1);
#endif
	vmemGCfourth();
#ifdef VREAL
  play_check(1);
#endif
	logGC();
//        dump(bytecode,32);
}

int32_t vmemAllocBin(int32_t size,int32_t ext)
{
	int32_t wsize,p;
	wsize=HEADER_LENGTH+((size+4)>>2);

	if (VMEM_LENGTH+vmem_stack-vmem_heapindex-wsize<VMEM_GCTHRESHOLD)
	{
		vmemGC();
		if (VMEM_LENGTH+vmem_stack-vmem_heapindex-wsize<VMEM_GCTHRESHOLD)
		{
                        consolestr("?OM Error\n");
                        vmem_broken=1;
                        sysReboot();
			return -1;
		}
	}
	p=vmem_heapindex;
	vmem_heapindex+=wsize;
	vmem_heap[p]=(size<<8)+((ext&127)<<1)+(TYPE_BINARY);
	vmem_heap[p+HEADER_GC]=0;
	vmem_heap[p+HEADER_LIST]=0;
	vmem_heap[p+wsize-1]=0;
	return p;
}

int32_t vmemAllocString(uint8_t *p,int32_t len)
{
	int32_t i;
	uint8_t *q;
	int32_t iq=vmemAllocBin(len,0);
	if (iq<0) return iq;
	q=VSTARTBIN(iq);
	for(i=0;i<len;i++) q[i]=p[i];
	return iq;
}

int32_t vmemAllocTab(int32_t size,int32_t ext)
{
	int32_t wsize,p;
	wsize=HEADER_LENGTH+size;

	if (VMEM_LENGTH+vmem_stack-vmem_heapindex-wsize<VMEM_GCTHRESHOLD)
	{
		vmemGC();
		if (VMEM_LENGTH+vmem_stack-vmem_heapindex-wsize<VMEM_GCTHRESHOLD)
		{
                        consolestr("?OM Error\n");
                        vmem_broken=1;
                        sysReboot();
			return -1;
		}
	}
	p=vmem_heapindex;
	vmem_heapindex+=wsize;
	size=(size<<2)-1;
	vmem_heap[p]=(size<<8)+((ext&127)<<1)+(TYPE_TAB);
	vmem_heap[p+HEADER_GC]=0;
	vmem_heap[p+HEADER_LIST]=0;
	vmem_heap[p+wsize-1]=0;
	return p;
}

int32_t vmemAllocTabClear(int32_t size,int32_t ext)
{
	int32_t p=vmemAllocTab(size,ext);
	if (p>=0)
	{
		int32_t i;
		for(i=0;i<size;i++)vmem_heap[p+HEADER_LENGTH+i]=NIL;
	}
	return p;
}

int32_t vmemPush(int32_t val)
{
	vmem_top[--vmem_stack]=val;
	if (VMEM_LENGTH+vmem_stack-vmem_heapindex<VMEM_GCTHRESHOLD)
	{
		vmemGC();
		if (VMEM_LENGTH+vmem_stack-vmem_heapindex<VMEM_GCTHRESHOLD)
		{
                        consolestr("?OM Error\n");
                        vmem_broken=1;
                        sysReboot();
			return -1;
		}
	}
	return 0;
}

void vmemStacktotab(int32_t n)
{
	int32_t *q;
	int32_t p=vmemAllocTab(n,0);
	q=VSTART(p);
	while(n>0) q[--n]=VPULL();
	VPUSH(PNTTOVAL(p));
}


void vmemDumpHeap()
{
#ifdef VSIMU
	int32_t i,pos,realsize,n;
#endif
	consolestr("HEAP\n----\n");
#ifdef VSIMU
	pos=vmem_start;
	n=0;
	while(pos < vmem_heapindex)
	{
		realsize=VSIZE(pos)+HEADER_LENGTH;
		printf("%06X : %s %d\n",pos,HEADER_TYPE(pos)?"Tab":"Bin",VSIZE(pos));
		for(i=0;i<realsize;i++) printf("%x ",vmem_heap[pos+i]);
		printf("\n");
		pos+=realsize;
		n++;
	}
#endif
	logGC();
}

void vmemDumpStack()
{
#ifdef VSIMU
	int32_t i,k;
#endif
	consolestr("STACK\n-----\n");
#ifdef VSIMU
	for(i=-1;i>=vmem_stack;i--)
	{
		k=vmem_top[i];
		printf("%d : %6x -> %6x (%d)\n",i,k,k>>1,k>>1);
	}
#endif
}

void vmemDump()
{
	vmemDumpHeap();
	vmemDumpStack();
}

void vmemDumpShort()
{
	logGC();
}
