/*******************************************************************************
    otg.h
    JOB60842サンプルプログラム OTG 制御 ヘッダファイル

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    更新履歴
    Mar.31,2003 rev.1.00:新規作成
*******************************************************************************/
#ifndef _OTG_H_
#define _OTG_H_

/* On-The-Go ステート */
#define OTG_DISABLE         0x00
#define OTG_START			0x01

#define OTG_A				0x10
#define OTG_A_IDLE			(OTG_A | 0x1)
#define OTG_A_WAIT_VRISE	(OTG_A | 0x2)
#define OTG_A_WAIT_BCON		(OTG_A | 0x3)
#define OTG_A_HOST			(OTG_A | 0x4)
#define OTG_A_SUSPEND		(OTG_A | 0x5)
#define OTG_A_PERIPHERAL	(OTG_A | 0x6)
#define OTG_A_WAIT_VFALL	(OTG_A | 0x7)
#define OTG_A_VBUS_ERR		(OTG_A | 0x8)

#define OTG_B				0x20
#define OTG_B_IDLE			(OTG_B | 0x1)
#define OTG_B_SRP_INIT		(OTG_B | 0x2)
#define OTG_B_PERIPHERAL	(OTG_B | 0x3)
#define OTG_B_WAIT_ACON		(OTG_B | 0x4)
#define OTG_B_HOST			(OTG_B | 0x5)
#define OTG_B_SRP_PRE		(OTG_B | 0x6)

#define BUS_REQ 				 1
#define DROP_REQ				 2
#define SUSPEND_REQ 			 3
#define HNP_ENABLE_SET			 4
#define HNP_NOT_SUPPORTED 		 5
#define HOST_RELEASE			 6
#define B_HNP_ENABLE_SET		 7
#define A_HNP_SUPPORT_SET		 8
#define A_ALT_HNP_SUPPORT_SET	 9
#define B_CONFIGRATION			10
#define B_UNCONFIGRATION		11
#define CONNECT 				12
#define DISCONNECT				13
#define BUS_SUSPENDED			14
#define BUS_RESUME				15


typedef union {
  int32_t word;
	struct {
		int b00	:1;		int b01	:1;		int b02	:1;		int b03	:1;
		int b04	:1;		int b05	:1;		int b06	:1;		int b07	:1;
		int b08	:1;		int b09	:1;		int b10	:1;		int b11	:1;
		int b12	:1;		int b13	:1;		int b14	:1;		int b15	:1;
		int b16	:1;		int b17	:1;		int b18	:1;		int b19	:1;
		int b20	:1;		int b21	:1;		int b22	:1;		int b23	:1;
		int b24	:1;		int b25	:1;		int b26	:1;		int b27	:1;
		int b28	:1;		int b29	:1;		int b30	:1;		int b31	:1;
	}bit;
}BIT32;

/* プロトタイプ宣言 */
int32_t usbctrl_otg_init(void);
int32_t usbctrl_otg_request(int);
void usbctrl_otg_control(void);
int32_t usbctrl_otg_srp(void);
int32_t usbctrl_otg_message_get(void);
int32_t usbctrl_otg_get_state(void);
void usbctrl_vbus_changed(void);
void usbctrl_id_changed(void);
void usbctrl_se0_det(void);

/* グローバル変数 */
extern int32_t usbctrl_otg_state;

#endif /* _OTG_H_ */
