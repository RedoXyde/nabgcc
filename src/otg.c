/*******************************************************************************
    otg.c
    JOB60842サンプルプログラム OTG 制御

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    更新履歴
    Mar.31,2003 rev.1.00:新規作成
*******************************************************************************/
#define DEBUG

#include   "ML674061.h"
#include   "common.h"
#include "otg.h"
#include "uart.h"

/* タイマ */
#ifndef TIMER_ON
  #define TIMER_ON(ms)		do{ otg_tmr_ch = auto_timera_set(1000, (ms)); } while(0)
#endif
#ifndef TIMER_OFF
  #define TIMER_OFF()		timera_stop(otg_tmr_ch)
#endif

/* タイマ時間設定 */
#define TA_WAIT_VRISE		100		/* Max.100(ms) */
#define TA_WAIT_BCON		200		/* Min.200(ms) */
#define TA_AIDL_BDIS		250		/* Min.150(ms) */
#define TB_ASE0_BRST		60		/* Min.3.125(ms) */ /* リセット時間含む */

#define TB_SRP_FAIL			5000	/* Min.5000(ms) Max.30000(ms) */

/* ウェイト時間設定 */
#define TW_PULLUP           7       /* 実測値 85ns    2ms立ち上がり時間前必要 */
#define TW_PULLDOWN         2       /* 実測値 1.58μs DatalinePulling 5～10ms */
#define TW_VBUS_CHAGE		22		/* 実測値 12.2ms  規格値 ～22ms(Derived)  */
#define TW_VBUS_DISCHAGE	50		/* 実測値 34.8ms  規格値 100ms以下        */


/*グローバル変数*/
int usbctrl_otg_state = OTG_DISABLE;/* 現在のOTGステートを保持する */
BIT32 usbctrl_otg_status = 0;		/* OTGステート制御フラグを保持する */
//static int otg_tmr_ch = 0;			/* OTG制御で使用しているタイマ番号 */
int usbctrl_otg_message = 0; 		/* OTGメッセージ番号 */

/*プロトタイプ宣言*/
//static void usbctrl_otg_sess_chk(int);

extern UBYTE dummy_buffer[100];

/******************************************************************************/
/*OTGステート制御フラグ定義*/

#define id					usbctrl_otg_status.bit.b00

#define a_bus_req			usbctrl_otg_status.bit.b02
#define a_suspend_req		usbctrl_otg_status.bit.b03
#define a_bus_drop			usbctrl_otg_status.bit.b04
#define a_srp_det			usbctrl_otg_status.bit.b05
#define a_set_b_hnp_en		usbctrl_otg_status.bit.b06
#define a_host_release		usbctrl_otg_status.bit.b07

#define a_vbus_vld			usbctrl_otg_status.bit.b08
#define a_sess_vld			usbctrl_otg_status.bit.b09
#define b_conn				usbctrl_otg_status.bit.b10
#define b_bus_suspend		usbctrl_otg_status.bit.b11
#define b_bus_resume		usbctrl_otg_status.bit.b12
#define a_wait_vrise_tmout	usbctrl_otg_status.bit.b13
#define a_wait_bcon_tmout	usbctrl_otg_status.bit.b14
#define a_aidl_bdis_tmout	usbctrl_otg_status.bit.b15

#define b_bus_req			usbctrl_otg_status.bit.b16
#define b_hnp_en			usbctrl_otg_status.bit.b20
#define a_hnp_support		usbctrl_otg_status.bit.b21
#define a_alt_hnp_support	usbctrl_otg_status.bit.b22
#define b_srp_fail_tmout	usbctrl_otg_status.bit.b23

#define b_sess_vld			usbctrl_otg_status.bit.b24
#define b_sess_end			usbctrl_otg_status.bit.b25
#define a_conn				usbctrl_otg_status.bit.b26
#define a_bus_suspend		usbctrl_otg_status.bit.b27
#define a_bus_resume		usbctrl_otg_status.bit.b28
#define b_se0_srp			usbctrl_otg_status.bit.b29
#define b_srp_done			usbctrl_otg_status.bit.b30
#define b_ase0_brst_tmout	usbctrl_otg_status.bit.b31

/*******************************************************************************
    Routine Name    ：usbctrl_otg_get_state
    Form            ：int usbctrl_otg_get_state(void);
    Parameters      ：
    Return value    ：
    Description     ：OTGステート番号を返す。
*******************************************************************************/
int usbctrl_otg_get_state(void)
{
	return usbctrl_otg_state;
}

