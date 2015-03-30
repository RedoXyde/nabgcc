/*******************************************************************************
	usbp_api.h
	JOB60842サンプルプログラム
	API関数定義

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	更新履歴
	Mar.31,2003 rev1.00:新規作成
*******************************************************************************/
#ifndef _USBP_API_H_
#define	_USBP_API_H_

#include "usbp.h"

int usbp_init(Device_Desc	*device_desc);
int usbp_tx_data(uchar *buf, uchar ep, uint size);
int usbp_rx_data(uchar *buf, uchar ep, uint size);
int usbp_set_trans_callback(uchar ep, void (*func)(uchar *, uint));
int usbp_busreset_assert_callback(void *func(void));
int usbp_busreset_deassert_callback(void *func(void));
int usbp_int_enable(uchar);
int usbp_int_disable(uchar);
int usbp_remote_wakeup(void);
signed char usbp_cfg_status(Config_Desc **);
signed char usbp_alt_status(bInterfaceNumber);
int usbp_exit(void);
void usbp_main(void);

int usbp_set_callback_set_interface (void (*func)( uchar, uchar ));


#define usbperi_interrupt	usbp_interrupt
#define usbperi_exit	usbp_exit

/******************************************************************************/
#endif /*_USBP_API_H_*/

/* End of file */
