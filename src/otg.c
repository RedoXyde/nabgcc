/*******************************************************************************
    otg.c
    JOB60842�T���v���v���O���� OTG ����

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev.1.00:�V�K�쐬
*******************************************************************************/
#define DEBUG

#include   "ML674061.h"
#include   "common.h"
#include "otg.h"
#include "uart.h"

/* �^�C�} */
#ifndef TIMER_ON
  #define TIMER_ON(ms)		do{ otg_tmr_ch = auto_timera_set(1000, (ms)); } while(0)
#endif
#ifndef TIMER_OFF
  #define TIMER_OFF()		timera_stop(otg_tmr_ch)
#endif

/* �^�C�}���Ԑݒ� */
#define TA_WAIT_VRISE		100		/* Max.100(ms) */
#define TA_WAIT_BCON		200		/* Min.200(ms) */
#define TA_AIDL_BDIS		250		/* Min.150(ms) */
#define TB_ASE0_BRST		60		/* Min.3.125(ms) */ /* ���Z�b�g���Ԋ܂� */

#define TB_SRP_FAIL			5000	/* Min.5000(ms) Max.30000(ms) */

/* �E�F�C�g���Ԑݒ� */
#define TW_PULLUP           7       /* �����l 85ns    2ms�����オ�莞�ԑO�K�v */
#define TW_PULLDOWN         2       /* �����l 1.58��s DatalinePulling 5�`10ms */
#define TW_VBUS_CHAGE		22		/* �����l 12.2ms  �K�i�l �`22ms(Derived)  */
#define TW_VBUS_DISCHAGE	50		/* �����l 34.8ms  �K�i�l 100ms�ȉ�        */


/*�O���[�o���ϐ�*/
int usbctrl_otg_state = OTG_DISABLE;/* ���݂�OTG�X�e�[�g��ێ����� */
BIT32 usbctrl_otg_status = 0;		/* OTG�X�e�[�g����t���O��ێ����� */
//static int otg_tmr_ch = 0;			/* OTG����Ŏg�p���Ă���^�C�}�ԍ� */
int usbctrl_otg_message = 0; 		/* OTG���b�Z�[�W�ԍ� */

/*�v���g�^�C�v�錾*/
//static void usbctrl_otg_sess_chk(int);

extern UBYTE dummy_buffer[100];

/******************************************************************************/
/*OTG�X�e�[�g����t���O��`*/

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
    Routine Name    �Fusbctrl_otg_get_state
    Form            �Fint usbctrl_otg_get_state(void);
    Parameters      �F
    Return value    �F
    Description     �FOTG�X�e�[�g�ԍ���Ԃ��B
*******************************************************************************/
int usbctrl_otg_get_state(void)
{
	return usbctrl_otg_state;
}

