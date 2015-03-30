/*******************************************************************************
	config.h
	JOB60842サンプルプログラム
	環境構成定義ファイル

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	更新履歴
	Mar.31,2003 rev1.00:新規作成
*******************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/* デバッグ用UART・SCI通信速度 */
#define DEBUG_BAUDRATE  	115200

/* 割り込みレベル指定 */
#define IRQ_LV_SIO			7		/*割り込みレベル SIO*/
#define IRQ_LV_TIMERA		6		/*割り込みレベル 汎用タイマー*/
#define	IRQ_LV_EXUSB		5		/*割り込みレベル ML60842 外部3*/

/* 共通インクルードファイル */
#include "ml674000.h"
#include "m674kapi.h"
#include "timer.h"
#include "sio.h"
#include "ml60842.h"

/* USBスタック用データ転送用ワークメモリ */
#define USB_BUFFER 0
#if (USB_BUFFER==0)				/* 外部SRAM 空間 */
  #define USB_BUFFER_ADDRESS	ExtRAM2Base
  #define USB_BUFFER_SIZE 		ExtRAM2Size
#elif (USB_BUFFER==1)			/* 外部DRAM 空間 */
  #define USE_SDRAM
  #define USB_BUFFER_ADDRESS	ExtRAM3Base
  #define USB_BUFFER_SIZE 		ExtRAM3Size
#endif

/***** デバイスデバッグプリント ***********************************************/
#define USBP_DEBUG_PRINT


#endif /* _CONFIG_H_ */
