// VLISP Virtual Machine - 2006 - by Sylvain Huet
// Lowcost IS Powerfull

#include"vmem.h"
#include"vloader.h"

uint8_t *bc_tabfun;
int32_t bc_nbfun;
int32_t sys_start;
int32_t global_start;

int32_t loaderGetByte(uint8_t *src)
{
	int32_t i;
	i=(src[0]&255);
	return i;
}
int32_t loaderGetShort(uint8_t *src)
{
	int32_t i;
	i=((src[1]&255)<<8)+(src[0]&255);
	return i;
}
int32_t loaderGetInt(uint8_t *src)
{
	int32_t i;
	i=((src[3]&255)<<24)+((src[2]&255)<<16)+((src[1]&255)<<8)+(src[0]&255);
	return i;
}

uint8_t *loaderInitRec(uint8_t *src)
{
	int32_t l,i;

	l=loaderGetInt(src);
	src+=4;
	if (l==-1)
	{
		//		printf("nil\n",l>>1);
		VPUSH(NIL);
	}
	else if (l&1)
	{
		l>>=1;
		if (l&1)
		{
			l>>=1;
			//			printf("tuple %d\n",l);
			for(i=0;i<l;i++) src=loaderInitRec(src);
			VMKTAB(l);
		}
		else
		{
			l>>=1;
			//			printf("string taille %d\n",l);
			VPUSH(PNTTOVAL(VMALLOCSTR(src,l)));
			src+=l;
		}
	}
	else
	{
		//		printf("int int32_t %d\n",l>>1);
		VPUSH(l);
	}
	return src;
}

int32_t loaderSizeBC(uint8_t *src)
{
	int32_t n,b;
	n=loaderGetInt(src);
	src+=n;
	b=loaderGetInt(src);
	src+=4+b;
	n+=4+b;
	n+=2+(loaderGetShort(src)<<2);
	return n;
}

int32_t loaderInit(uint8_t *src)
{
	int32_t n,nw,i;
	uint8_t* src0;
	uint8_t* dst;

	n=loaderSizeBC(src);
	dst=(uint8_t*)vmem_heap;
	for(i=0;i<n;i++) dst[i]=src[i];
	nw=(n+3)>>2;
	vmemInit(nw);

	src=(uint8_t*)vmem_heap;

	sys_start=vmem_stack-1;
	for(i=0;i<SYS_NB;i++) VPUSH(NIL);

	src0=src;
	n=loaderGetInt(src);
	src+=4;
	global_start=vmem_stack-1;
	while(((int32_t)(src-src0))<n) src=loaderInitRec(src);

	n=loaderGetInt(src);
	src+=4;

	bc_tabfun=&bytecode[n+2];
	bc_nbfun=loaderGetShort(src+n);
	n+=2+(bc_nbfun<<2);
	for(i=0;i<n;i++) bytecode[i]=src[i];
	vmemSetstart((n+3)>>2);

	return 0;
}

int32_t loaderFunstart(int32_t funnumber)
{
	return loaderGetInt(bc_tabfun+(funnumber<<2));
}

