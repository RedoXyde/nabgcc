/*******************************************************************************
	type.h
	JOB60842サンプルプログラム
	型定義ファイル

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	更新履歴
	Mar.31,2003 rev1.00:新規作成
*******************************************************************************/
#ifndef _TYPEDEF_H_
#define	_TYPEDEF_H_

#ifndef NULL
#define	NULL	0
#endif

#ifndef OK
#define	OK		0
#endif

#ifndef NG
#define	NG		-1
#endif

#ifndef SET
#define	SET		1
#endif

#ifndef RESET
#define	RESET	0
#endif

#define FALSE   0
#define TRUE    1

#define E_OK	OK
#define E_NG	NG


typedef	unsigned char	uchar;
typedef	unsigned short	ushort;
typedef	unsigned long	ulong;
typedef	unsigned long	uint;

#endif /* _TYPEDEF_H_ */
