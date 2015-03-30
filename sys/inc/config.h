/*******************************************************************************
	config.h
	JOB60842�T���v���v���O����
	���\����`�t�@�C��

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	�X�V����
	Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/* �f�o�b�O�pUART�ESCI�ʐM���x */
#define DEBUG_BAUDRATE  	115200

/* ���荞�݃��x���w�� */
#define IRQ_LV_SIO			7		/*���荞�݃��x�� SIO*/
#define IRQ_LV_TIMERA		6		/*���荞�݃��x�� �ėp�^�C�}�[*/
#define	IRQ_LV_EXUSB		5		/*���荞�݃��x�� ML60842 �O��3*/

/* ���ʃC���N���[�h�t�@�C�� */
#include "ml674000.h"
#include "m674kapi.h"
#include "timer.h"
#include "sio.h"
#include "ml60842.h"

/* USB�X�^�b�N�p�f�[�^�]���p���[�N������ */
#define USB_BUFFER 0
#if (USB_BUFFER==0)				/* �O��SRAM ��� */
  #define USB_BUFFER_ADDRESS	ExtRAM2Base
  #define USB_BUFFER_SIZE 		ExtRAM2Size
#elif (USB_BUFFER==1)			/* �O��DRAM ��� */
  #define USE_SDRAM
  #define USB_BUFFER_ADDRESS	ExtRAM3Base
  #define USB_BUFFER_SIZE 		ExtRAM3Size
#endif

/***** �f�o�C�X�f�o�b�O�v�����g ***********************************************/
#define USBP_DEBUG_PRINT


#endif /* _CONFIG_H_ */
