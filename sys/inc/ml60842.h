/*******************************************************************************
	ml60842.h
	JOB60842�T���v���v���O����
	ML60842���W�X�^��`

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	�X�V����
	Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef __ML60842_H_
#define	__ML60842_H_

#define	REG_BASE_ADDR	0xF0000000
#define MAX_ADDR		0xF0008000

/********************************************************************************/
/* ���ʕ����W�X�^                                                               */
/********************************************************************************/
/*<<<<  �z�X�g�y���t�F�����؂�ւ����W�X�^=====*/
#define HostPeriSel_addr		0x000		/* �z�X�g/�y���t�F�����I�� */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define B_HOST_SEL              0x00        /* HOST�I�� */
#define	B_PERI_SEL				0x01		/* Peripheral�I�� */
#define	B_OPERATION				0x02		/* �������쒆 */
#define	B_HWSW_MODE				0x04		/* MODE�ݒ肠�� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  �`�b�v�R���t�B�O���[�V�������W�X�^=====*/
#define Chip_Config_addr		0x004		/*�`�b�v�R���t�B�O���[�V�������W�X�^*/
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DREQ	 				0x01		/* DREQ�̋ɐ� */
#define	B_DRAK	 				0x02		/* DRAK�̋ɐ� */
#define	B_INTR	 				0x04		/* INTR�̋ɐ� */
#define	B_EXBUFENB 				0x08		/* �O���g�����V�[�o�g�p */
#define	B_TRCV_MODE				0x80		/* �O�t���g�����V�[�o���[�h */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  �G���f�B�A�����W�X�^=====*/
#define Endian_addr     		0x008		/* �G���f�B�A���ݒ背�W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_LITTLEENDIAN 			0x00000000ul	/* ���g���G���f�B�A�� */
#define	B_ENDIAN0 				0x00000001ul	/* �r�b�N�G���f�B�A�� */
#define	B_ENDIAN1 				0x00000100ul	/* �r�b�N�G���f�B�A�� */
#define	B_ENDIAN2 				0x00010000ul	/* �r�b�N�G���f�B�A�� */
#define	B_ENDIAN3 				0x01000000ul	/* �r�b�N�G���f�B�A�� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  OTG���䃌�W�X�^=====*/
#define	OTGCtl_addr	    		0x010		/* OTG���䃌�W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define M_VBUSMODE              0x00000003ul  /* VBUS���䃂�[�h�t�B�[���h MASK */
#define F_VBUSMODE_ROOTHUB      0x00000000ul  /* VBUS���䃂�[�h���[�g�n�u */
#define F_VBUSMODE_DRIVE        0x00000002ul  /* DRVVBUS�r�b�g���䃂�[�h */
#define F_VBUSMODE_PULSE        0x00000003ul  /* CHRG,DISCHRG�r�b�g���䃂�[�h */
#define	B_DRVVBUS    			0x00000004ul 	/* PCONT�[�qL�o�� */
#define	B_CHRGVBUS    			0x00000008ul 	/* VBUS�`���[�WON */
#define	B_DISCHRGVBUS  			0x00000010ul 	/* VBUS�f�B�X�`���[�WON */
#define	B_PDCTLDP      			0x00000020ul 	/* D+�v���_�E������C�l�[�u�� */
#define	B_PDCTLDM      			0x00000040ul 	/* D-�v���_�E������C�l�[�u�� */
#define	B_PUCTLDP      			0x00000080ul 	/* D+�v���A�b�v����C�l�[�u�� */
#define	B_PUCTLDP      			0x00000080ul 	/* D+�v���A�b�v����C�l�[�u�� */
#define	M_SELSV         		0x00000700ul 	/* SELSV MASK */

#define	B_AVBUSVLDENB    		0x00000800ul 	/*A_VBUS_VALID�R���p���[�^�C�l�[�u��*/
#define	B_ABSESSVLDENB    		0x00001000ul 	/*AB_SESS_VALID�R���p���[�^�C�l�[�u��*/
#define	B_USBRCVENB     		0x00002000ul 	/* ���V�[�o���C�l�[�u��*/
#define B_BSE0SRPDETENB         0x00004000ul  /* SE0���o�^�C�}�C�l�[�u�� */
#define	B_SELRV         		0x80000000ul 	/* AVDD=3.3V */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  OTG���荞�݃X�e�[�^�X���W�X�^=====*/
#define	OTGIntStt_addr	   		0x014		/* OTG���荞�݃X�e�[�^�X���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_IDSELCHG     			0x00000001ul 	/* ID�[�q�ω����� */
#define	B_ABSESSVLDCHG			0x00000002ul 	/* AB_SESS_VALID�R���p���[�^�ω�����*/
#define	B_AVBUSVLDCHG			0x00000004ul 	/* A_VBUS_VALID�R���p���[�^�ω����� */
#define	B_USBIFCHG  			0x00008000ul 	/* ��ԕω����� */
#define	B_IDSELST  	    		0x00010000ul 	/* B�f�o�C�X */
#define	B_ABSESSVLDST     		0x00020000ul 	/* VBUS>AB_SESS_VALID */
#define	B_AVBUSVLDST     		0x00040000ul 	/* VBUS>A_VBUS_VALID_LOW */
#define	B_BSE0SRPDETST     		0x04000000ul 	/* ��Ԍ��o */
#define	F_SE0            		0x00000000ul 	/* SE0 */
#define	F_KSTATE           		0x08000000ul 	/* K�X�e�[�g */
#define	F_JSTATE           		0x10000000ul 	/* J�X�e�[�g */
#define	F_SE1           		0x18000000ul 	/* SE1 */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  OTG���荞�݃}�X�N���W�X�^=====*/
#define OTGIntMask_addr	    	0x018	   	/* OTG���荞�݃}�X�N���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_IDSELCHGINT 			0x00000001ul 	/* ID�[�q�ω��C�l�[�u�� */
#define	B_ABSESSVLDCHGINT		0x00000002ul 	/*AB_SESS_VALID�R���p���[�^�ω��C�l�[�u��*/ 
#define	B_AVBUSVLDCHGINT		0x00000004ul 	/* A_VBUS_VALID�R���p���[�^�ω��C�l�[�u��*/
#define	B_USBIFCHGINT  			0x00008000ul 	/* ��ԕω��C�l�[�u�� */
#define	B_BSE0SRPDETSTINT  		0x04000000ul 	/* SE0��Ԍ��o�C�l�[�u�� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/


/*<<<<  ���Z�b�g�N���b�N���䃌�W�X�^=====*/
#define RstClkCtl_addr 	    	0x01C	   	/* ���Z�b�g�N���b�N���䃌�W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_XRUN      			0x00000000ul 	/* ���U��H���� */
#define	B_XSTOP      			0x00000001ul 	/* ���U��H��~ */
#define	B_CLKSTOP      			0x00000002ul 	/* �N���b�N������~ */
#define	B_SLCLKSTOP    			0x00000002ul 	/* �X���[�N���b�N��~ */
#define	B_PRST      			0x00000010ul 	/* �y���t�F�������Z�b�g */
#define	B_HRST      			0x00000020ul 	/* �z�X�g���Z�b�g */
#define	B_CRST      			0x00000040ul 	/* LSI���Z�b�g */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/********************************************************************************/
/* Open Host Control Register                                                   */
/********************************************************************************/
/*<<<<  OHCI����p���W�X�^=====*/
#define HcRevision_addr			0x100		/* ���r�W�������W�X�^ */
  #define RevisonNumber     0x00000010

#define HcControl_addr			0x104		/* �R���g���[�����W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
/* Field Mask */
  #define OHCI_CTRL_CBSR    (3ul << 0)          /* control/bulk service ratio */
  #define OHCI_CTRL_PLE     (1ul << 2)          /* periodic list enable */
  #define OHCI_CTRL_IE      (1ul << 3)          /* isochronous enable */
  #define OHCI_CTRL_CLE     (1ul << 4)          /* control list enable */
  #define OHCI_CTRL_BLE     (1ul << 5)          /* bulk list enable */
  #define OHCI_CTRL_HCFS    (3ul << 6)          /* host controller functional state */
  #define OHCI_CTRL_IR      (1ul << 8)          /* interrupt routing */
  #define OHCI_CTRL_RWC     (1ul << 9)          /* remote wakeup connected */
  #define OHCI_CTRL_RWE     (1ul << 10)         /* remote wakeup enable */
  #define OHCI_USB_RESET    (0ul << 6)
  #define OHCI_USB_RESUME   (1ul << 6)
  #define OHCI_USB_OPER     (2ul << 6)
  #define OHCI_USB_SUSPEND  (3ul << 6)
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcCommandStatus_addr		0x108		/* �R�}���h�X�e�[�^�X���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define OHCI_HCR          (1ul << 0)          /* host controller reset */
  #define OHCI_CLF          (1ul << 1)          /* control list filled */
  #define OHCI_BLF          (1ul << 2)          /* bulk list filled */
  #define OHCI_OCR          (1ul << 3)          /* ownership change request */
  #define OHCI_SOC          (3ul << 16)         /* scheduling overrun count */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcInterruptStatus_addr	0x10C		/* ���荞�݃X�e�[�^�X���W�X�^ */
#define HcInterruptEnable_addr	0x110		/* ���荞�݋����W�X�^ */
#define HcInterruptDisable_addr	0x114		/* ���荞�݋֎~���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define OHCI_INTR_SO      (1ul << 0)          /* scheduling overrun */
  #define OHCI_INTR_WDH     (1ul << 1)          /* writeback of done_head */
  #define OHCI_INTR_SF      (1ul << 2)          /* start frame */
  #define OHCI_INTR_RD      (1ul << 3)          /* resume detect */
  #define OHCI_INTR_UE      (1ul << 4)          /* unrecoverable error */
  #define OHCI_INTR_FNO     (1ul << 5)          /* frame number overflow */
  #define OHCI_INTR_RHSC    (1ul << 6)          /* root hub status change */
  #define OHCI_INTR_OC      (1ul << 30)         /* ownership change */
  #define OHCI_INTR_MIE     (1ul << 31)         /* master interrupt enable */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/



#define HcHCCA_addr			0x118		/* �R�~���j�P�[�V�����G���A�A�h���X���W�X�^ */

#define HcPeriodCurrentED_addr		0x11C		/* �����]���J�����gED���W�X�^ */

#define HcControlHeadED_addr		0x120		/* �R���g���[���]���w�b�hED���W�X�^ */

#define HcControlCurrentED_addr		0x124		/* �R���g���[���]���J�����gED���W�X�^ */

#define HcBulkHeadED_addr		0x128		/* �o���N�]���w�b�hED���W�X�^ */

#define HcBulkCurrentED_addr		0x12C		/* �o���N�]���J�����gED���W�X�^ */

#define HcDoneHead_addr			0x130		/* �]�������w�b�h���W�X�^ */



#define HcFmInterval_addr		0x134		/* �t���[���C���^�[�o�����W�X�^ */

#define HcFmRemaining_addr		0x138		/* �t���[�������C�����W�X�^ */

#define HcFmNumber_addr			0x13C		/* �t���[���i���o���W�X�^ */

#define HcPeriodicStart_addr		0x140		/* �����]���X�^�[�g�w�背�W�X�^ */

#define HcLSThreshold_addr		0x144		/* ���[�X�s�[�h�X���b�V���z�[���h���W�X�^ */



#define HcRhDescriptorA_addr		0x148		/* ���[�g�n�u�f�B�X�N���v�^A���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define RH_A_NDP          0x000000fful          /* number of downstream ports */
  #define RH_A_PSM          0x00000100ul          /* power switching mode */
  #define RH_A_NPS          0x00000100ul          /* no power switching */
  #define RH_A_DT           0x00000200ul          /* device type (mbz) */
  #define RH_A_OCPM         0x00000400ul          /* over current protection mode */
  #define RH_A_NOCP         0x00000800ul          /* no over current protection */
  #define RH_A_POTPGT       0xff000000ul          /* power on to power good time */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcRhDescriptorB_addr		0x14C		/* ���[�g�n�u�f�B�X�N���v�^B���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define RH_B_DR           0x0000fffful          /* device removable flags */
  #define RH_B_PPCM         0xffff0000ul          /* port power control mask */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcRhStatus_addr			0x150		/* ���[�g�n�u�X�e�[�^�X���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define RH_HS_LPS         0x00000001ul          /* local power status */
  #define RH_HS_OCI         0x00000002ul          /* over current indicator */
  #define RH_HS_DRWE        0x00008000ul          /* device remote wakeup enable */
  #define RH_HS_LPSC        0x00010000ul          /* local power status change */
  #define RH_HS_OCIC        0x00020000ul          /* over current indicator change */
  #define RH_HS_CRWE        0x80000000ul          /* clear remote wakeup enable */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcRhPortStatus_addr		0x154		/* ���[�g�n�u�|�[�g1�X�e�[�^�X���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define RH_PS_CCS         0x00000001ul          /* current connect status */
  #define RH_PS_PES         0x00000002ul          /* port enable status */
  #define RH_PS_PSS         0x00000004ul          /* port suspend status */
  #define RH_PS_POCI        0x00000008ul          /* port over current indicator */
  #define RH_PS_PRS         0x00000010ul          /* port reset status */
  #define RH_PS_PPS         0x00000100ul          /* port power status */
  #define RH_PS_LSDA        0x00000200ul          /* low speed device attached */
  #define RH_PS_CSC         0x00010000ul          /* connect status change */
  #define RH_PS_PESC        0x00020000ul          /* port enable status change */
  #define RH_PS_PSSC        0x00040000ul          /* port suspend status change */
  #define RH_PS_OCIC        0x00080000ul          /* over current indicator change */
  #define RH_PS_PRSC        0x00100000ul          /* port reset status change */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/* ����RAM�A�h���X */
#define IntRAMAddr      	(REG_BASE_ADDR+0x1000)
#define IntRAMSize      	(0x1000)


/*<<<<  �z�X�g�R���g���[�����䃌�W�X�^=====*/
#define HostCtl_addr			0x200	/* Host Control ���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMAIRQ_MASK		0x00000001ul  /* �z�X�g�f�[�^�]���}�X�N */
#define	B_OHCIIRQ_MASK		0x00000002ul  /* �z�X�g�R�A���荞�݃}�X�N */
#define	B_DREQMSK   		0x00000008ul  /* PIO�]�� */
#define	B_TRNSTERM   		0x00000080ul  /* �]���I�� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define SttTrnsCnt_addr			0x204		/* Status, RD/WR FIFO �]�������W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMAIRQ    		0x00000001ul  /* �z�X�g�f�[�^�]�����荞�݂��� */
#define	B_OHCIIRQ   		0x00000002ul  /* �z�X�g�R�A���荞�݂��� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HostDataTrnsReq_addr		0x208		/* �z�X�g�f�[�^�]�����N�G�X�g���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMADIR    		0x00000001ul  /* CPU->LSI */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define RamAdr_addr			0x20C		/* ����RAM�A�h���X�ݒ�p���W�X�^ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_IRAMBASEACT  		0x00000001ul  /* �A�N�Z�X���� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define FifoAcc_addr		0x240		/* FIFO�A�N�Z�X���W�X�^ */


/********************************************************************************/
/* �f�o�C�X�R���g���[�������䃌�W�X�^                                           */
/********************************************************************************/
/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.1	fifos */
#define	EP0TXFIFO_addr		0x400		/* EP0 ���MFIFO�f�[�^ LSB */
#define	EP0RXFIFO_addr		0x404		/* EP0 ��MFIFO�f�[�^ LSB */
#define	EP1FIFO_addr		0x410		/* EP1 ���M/��MFIFO�f�[�^ LSB */
#define	EP2FIFO_addr		0x420		/* EP2 ���M/��MFIFO�f�[�^ LSB */
#define	EP3FIFO_addr		0x430		/* EP3 ���M/��MFIFO�f�[�^ LSB */
#define	EP4FIFO_addr		0x440		/* EP4 ���M/��MFIFO�f�[�^ LSB */
#define	EP5FIFO_addr		0x450		/* EP5 ���M/��MFIFO�f�[�^ LSB */

#define	EP0TXFIFOLSB_addr	0x400		/* EP0 ���MFIFO�f�[�^ LSB */
#define	EP0TXFIFOMSB_addr	0x402		/* EP0 ��MFIFO�f�[�^ MSB */
#define	EP0RXFIFOLSB_addr	0x404		/* EP0 ��MFIFO�f�[�^ LSB */
#define	EP0RXFIFOMSB_addr	0x408		/* EP0 ��MFIFO�f�[�^ MSB */
#define	EP1FIFOLSB_addr		0x410		/* EP1 ���M/��MFIFO�f�[�^ LSB */
#define	EP1FIFOMSB_addr		0x41C		/* EP1 ���M/��MFIFO�f�[�^ MSB */
#define	EP2FIFOLSB_addr		0x420		/* EP2 ���M/��MFIFO�f�[�^ LSB */
#define	EP2FIFOMSB_addr		0x42C		/* EP2 ���M/��MFIFO�f�[�^ MSB */
#define	EP3FIFOLSB_addr		0x430		/* EP3 ���M/��MFIFO�f�[�^ LSB */
#define	EP3FIFOMSB_addr		0x43C		/* EP3 ���M/��MFIFO�f�[�^ MSB */
#define	EP4FIFOLSB_addr		0x440		/* EP4 ���M/��MFIFO�f�[�^ LSB */
#define	EP4FIFOMSB_addr		0x44C		/* EP4 ���M/��MFIFO�f�[�^ MSB */
#define	EP5FIFOLSB_addr		0x450		/* EP5 ���M/��MFIFO�f�[�^ LSB */
#define	EP5FIFOMSB_addr		0x45C		/* EP5 ���M/��MFIFO�f�[�^ MSB */


/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.2	Common control and status registers */
#define	DVCADR_addr			0x308		/* �f�o�C�X�A�h���X */
#define	FRAME_addr			0x30C		/* �t���[���ԍ� */

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.3	8-byes setup registers */
#define	SETUP0W_addr			0x300
#define	SETUP1W_addr			0x302
#define	SETUP2W_addr			0x304
#define	SETUP3W_addr			0x306

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.4 Pin function control */

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.5 Interrupt enable control and status */
#define	INTSTAT_addr			0x310
#define	INTENBL_addr			0x314
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_SETUP_RDY_INT			0x0100ul		/* �Z�b�g�A�b�v���f�B���荞�� */
#define	B_EP1PKTRDY_INT			0x0200ul		/* EP1�p�P�b�g���f�B���荞�� */
#define	B_EP2PKTRDY_INT			0x0400ul	/* EP2�p�P�b�g���f�B���荞�� */
#define	B_EP3PKTRDY_INT			0x0800ul		/* EP3�p�P�b�g���f�B���荞�� */
#define	B_EP4PKTRDY_INT			0x1000ul		/* EP4�p�P�b�g���f�B���荞�� */
#define	B_EP5PKTRDY_INT			0x2000ul		/* EP5�p�P�b�g���f�B���荞�� */
#define	B_EP0RXPKTRDY_INT		0x4000ul		/* EP0��M�p�P�b�g���f�B���荞�� */
#define	B_EP0TXPKTRDY_INT		0x8000ul		/* EP0���M�p�P�b�g���f�B���荞�� */
#define	B_SOF_INT				0x0001ul		/* SOF������ */
#define	B_BUS_RESET_INT			0x0002ul		/* USB�o�X���Z�b�g��A�T�[�g������ */
#define	B_BUS_RESET_DES_INT		0x0004ul		/* USB�o�X���Z�b�g��f�A�T�[�g������ */
#define	B_SUSPENDED_STATE_INT	0x0008ul		/* �T�X�y���f�b�h�X�e�[�g���荞�� */
#define	B_AWAKE_INT				0x0010ul		/* �f�o�C�X�A�E�F�C�N�X�e�[�g������ */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define	SYSCON_addr			0x318
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_SOFT_RESET			0x01ul		/* �\�t�g���Z�b�g */
#define	B_PWDWN_MODE			0x02ul		/* �p���[�_�E�����[�h */
#define	B_EP_MODE				0x04ul		/* EP���[�h 0=6EP,1=5EP */
#define	B_PULLUP_CTRL			0x08ul		/* �v���A�b�v���� */
#define	B_REMOTE_WAKEUP			0x10ul		/* �����[�g�E�F�C�N�A�b�v */
#define	B_CLK_CTL				0x80ul		/* �f�o�C�X���̃N���b�N��~ */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.6 DMA settings */
#define	DMA0CON_addr			0x320
#define	DMA1CON_addr			0x324
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMA_ENABLE			0x01ul		/* DMA�C�l�[�u�� */
#define	B_BYTE_COUNT			0x04ul		/* �o�C�g�J�E���g */
#define	F_DMA_EP1				0x00ul		/* EP1��DMA�̑ΏۂƂ��� */
#define	F_DMA_EP2				0x20ul		/* EP2��DMA�̑ΏۂƂ��� */
#define	F_DMA_EP4				0x40ul		/* EP4��DMA�̑ΏۂƂ��� */
#define	F_DMA_EP5				0x60ul		/* EP5��DMA�̑ΏۂƂ��� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/


/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.7 Endpoint controls */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_CONFIG					0x10ul		/* �R���t�B�O���[�V�����r�b�g */
#define B_STALL						0x01ul		/* �X�g�[���r�b�g */
#define	B_DATA_SEQUENCE				0x02ul		/* �f�[�^�V�[�P���X�E�g�O���r�b�g */
#define B_CLR_FIFO					0x04ul		/* FIFO�N���A */
#define B_RECV_PKTRDY				0x01ul		/* ��M�p�P�b�g���f�B */
#define B_TRNS_PKTRDY				0x02ul		/* ���M�p�P�b�g���f�B */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/* 2.7.1 EP0 controls */
#define	EP0CONT_addr			0x378
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	F_CTRL_TRNS				0x00ul		/* �]���^�C�v �R���g���[���]�� */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	EP0PLDCONF_addr		0x330
#define	EP0TXCNT_addr		0x360		/* EP0���M�f�[�^�o�C�g�� */
#define	EP0RXCNTSTAT_addr	0x348
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_EP0_SETUP_RDY			0x04ul		/* �Z�b�g�A�b�v���f�B */
#define	F_SETUP_STAGE			0x00ul		/* �Z�b�g�A�b�v�X�e�[�W */
#define	F_DATA_STAGE			0x10ul		/* �f�[�^�X�e�[�W */
#define	F_STATUS_STAGE			0x20ul		/* �X�e�[�^�X�X�e�[�W */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/* 2.7.2 EP1 controls */
#define	EP1CONT_addr		0x37C
#define	EP1PLDCONF_addr		0x334
#define	EP1RXCNTSTAT_addr	0x34C
#define	EP1TXCNT_addr		0x364		/* EP1���M�f�[�^�o�C�g�� */

/* 2.7.3 EP2 controls */
#define	EP2CONT_addr		0x380
#define	EP2PLDCONF_addr		0x338
#define	EP2RXCNTSTAT_addr	0x350
#define	EP2TXCNT_addr		0x368		/* EP2���M�f�[�^�o�C�g�� */

/* 2.7.4 EP3 controls */
#define	EP3CONT_addr		0x384
#define	EP3PLDCONF_addr		0x33C
#define	EP3RXCNTSTAT_addr	0x354
#define	EP3TXCNT_addr		0x36C		/* EP3���M�f�[�^�o�C�g�� */

/* 2.7.5 EP4 controls */
#define	EP4CONT_addr		0x388
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define ISO_IN_RCVED_STS			0x80ul		/* ���O�t���[����ISO IN����M������ */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	EP4CONF_addr		0x340
#define	EP4PLD_addr			0x340
#define	EP4STAT_addr		0x358
#define	EP4RXCNT_addr		0x358
#define	EP4TXCNT_addr		0x370		/* EP4���M�f�[�^�o�C�g�� */

/* 2.7.6 EP5 controls */
#define	EP5CONT_addr		0x38C
#define	EP5CONF_addr		0x344
#define	EP5PLD_addr			0x344
#define	EP5STAT_addr		0x35C
#define	EP5RXCNT_addr		0x35C
#define	EP5TXCNT_addr		0x374		/* EP5���M�f�[�^�o�C�g�� */

/* 2.7.7 EP4 EP5 ISO controls */
#define	ISOMODE_addr			0x31C

/* 3.	Endpoint serial number definitions

	�e�G���h�|�C���g�ɒʂ��ԍ������܂��B
	���̔ԍ��́A������G���h�|�C���g�A�h���X�Ƃ́A�قȂ�܂��B
	���̔ԍ��̓G���h�|�C���g�\���̂̔z��Y���Ƃ��ėp���܂��B
*/
#define	EP0				0		/* Endpoint 0 �ėp */
#define	EP0RX			0		/* Endpoint 0 ��M�p */
#define	EP1				1		/* Endpoint 1 */
#define	EP2				2		/* Endpoint 2 */
#define	EP3				3		/* Endpoint 3 */
#define	EP4				4		/* Endpoint 4 */
#define	EP5				5		/* Endpoint 5 */
#define	EP0TX			6		/* Endpoint 0 ���M�p */
#define	EP_MAX			6		/* �G���h�|�C���g�ő吔 */


/* 6.	register definitions
	�v���O�����ŗp���郌�W�X�^���`���Ă���
*/
/*<<<<  �z�X�g�y���t�F�����؂�ւ����W�X�^=====*/
#define HostPeriSel     (HostPeriSel_addr + REG_BASE_ADDR)	/* �z�X�g/�y���t�F�����I�� */
/*<<<<  �`�b�v�R���t�B�O���[�V�������W�X�^=====*/
#define Chip_Config     (Chip_Config_addr + REG_BASE_ADDR)	/*�`�b�v�R���t�B�O���[�V�������W�X�^*/
/*<<<<  �G���f�B�A�����W�X�^=====*/
#define Endian          (Endian_addr + REG_BASE_ADDR)	    /* �G���f�B�A���ݒ背�W�X�^ */
/*<<<<  OTG���䃌�W�X�^=====*/
#define	OTGCtl          (OTGCtl_addr + REG_BASE_ADDR)	    /* OTG���䃌�W�X�^ */
/*<<<<  OTG���荞�݃X�e�[�^�X���W�X�^=====*/
#define	OTGIntStt       (OTGIntStt_addr + REG_BASE_ADDR)	/* OTG���荞�݃X�e�[�^�X���W�X�^ */
/*<<<<  OTG���荞�݃}�X�N���W�X�^=====*/
#define OTGIntMask      (OTGIntMask_addr + REG_BASE_ADDR)	/* OTG���荞�݃}�X�N���W�X�^ */
/*<<<<  ���Z�b�g�N���b�N���䃌�W�X�^=====*/
#define RstClkCtl       (RstClkCtl_addr + REG_BASE_ADDR)	/* ���Z�b�g�N���b�N���䃌�W�X�^ */

/********************************************************************************/
/* Open Host Control Register                                                   */
/********************************************************************************/
/*<<<<  OHCI����p���W�X�^=====*/
#define HcRevision	(HcRevision_addr + REG_BASE_ADDR)	/* ���r�W�������W�X�^ */
#define HcControl	(HcControl_addr + REG_BASE_ADDR)	/* �R���g���[�����W�X�^ */
#define HcCommandStatus	(HcCommandStatus_addr + REG_BASE_ADDR)	/* �R�}���h�X�e�[�^�X���W�X�^ */
#define HcInterruptStatus	(HcInterruptStatus_addr + REG_BASE_ADDR)	/* ���荞�݃X�e�[�^�X���W�X�^ */

#define HcInterruptEnable	(HcInterruptEnable_addr + REG_BASE_ADDR)	/* ���荞�݋����W�X�^ */
#define HcInterruptDisable	(HcInterruptDisable_addr + REG_BASE_ADDR)	/* ���荞�݋֎~���W�X�^ */
#define HcHCCA	(HcHCCA_addr + REG_BASE_ADDR)	/* �R�~���j�P�[�V�����G���A�A�h���X���W�X�^ */
#define HcPeriodCurrentED	(HcPeriodCurrentED_addr + REG_BASE_ADDR)	/* �����]���J�����gED���W�X�^ */

#define HcControlHeadED	(HcControlHeadED_addr + REG_BASE_ADDR)	/* �R���g���[���]���w�b�hED���W�X�^ */
#define HcControlCurrentED	(HcControlCurrentED_addr + REG_BASE_ADDR)	/* �R���g���[���]���J�����gED���W�X�^ */
#define HcBulkHeadED	(HcBulkHeadED_addr + REG_BASE_ADDR)	/* �o���N�]���w�b�hED���W�X�^ */
#define HcBulkCurrentED	(HcBulkCurrentED_addr + REG_BASE_ADDR)	/* �o���N�]���J�����gED���W�X�^ */

#define HcDoneHead	(HcDoneHead_addr + REG_BASE_ADDR)	/* �]�������w�b�h���W�X�^ */
#define HcFmInterval	(HcFmInterval_addr + REG_BASE_ADDR)	/* �t���[���C���^�[�o�����W�X�^ */
#define HcFmRemaining	(HcFmRemaining_addr + REG_BASE_ADDR)	/* �t���[�������C�����W�X�^ */
#define HcFmNumber	(HcFmNumber_addr + REG_BASE_ADDR)	/* �t���[���i���o���W�X�^ */

#define HcPeriodicStart	(HcPeriodicStart_addr + REG_BASE_ADDR)	/* �����]���X�^�[�g�w�背�W�X�^ */
#define HcLSThreshold	(HcLSThreshold_addr + REG_BASE_ADDR)	/* ���[�X�s�[�h�X���b�V���z�[���h���W�X�^ */
#define HcRhDescriptorA	(HcRhDescriptorA_addr + REG_BASE_ADDR)	/* ���[�g�n�u�f�B�X�N���v�^A���W�X�^ */
#define HcRhDescriptorB	(HcRhDescriptorB_addr + REG_BASE_ADDR)	/* ���[�g�n�u�f�B�X�N���v�^B���W�X�^ */

#define HcRhStatus	(HcRhStatus_addr + REG_BASE_ADDR)	/* ���[�g�n�u�X�e�[�^�X���W�X�^ */
#define HcRhPortStatus	(HcRhPortStatus_addr + REG_BASE_ADDR)	/* ���[�g�n�u�|�[�g1�X�e�[�^�X���W�X�^ */

/*<<<<  �z�X�g�R���g���[�����䃌�W�X�^=====*/
#define HostCtl	(HostCtl_addr + REG_BASE_ADDR)	/* Host Control ���W�X�^ */
#define SttTrnsCnt	(SttTrnsCnt_addr + REG_BASE_ADDR)	/* Status, RD/WR FIFO �]�������W�X�^ */
#define HostDataTrnsReq	(HostDataTrnsReq_addr + REG_BASE_ADDR)	/* �z�X�g�f�[�^�]�����N�G�X�g���W�X�^ */
#define RamAdr	(RamAdr_addr + REG_BASE_ADDR)	/* ����RAM�A�h���X�ݒ�p���W�X�^ */
#define FifoAcc	(FifoAcc_addr + REG_BASE_ADDR)	/* FIFO�A�N�Z�X���W�X�^ */


/********************************************************************************/
/* �f�o�C�X�R���g���[�������䃌�W�X�^                                           */
/********************************************************************************/
/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.1	fifos */
#define	EP0TXFIFO	(EP0TXFIFO_addr + REG_BASE_ADDR)	/* EP0 ���MFIFO�f�[�^ */
#define	EP0RXFIFO	(EP0RXFIFO_addr + REG_BASE_ADDR)	/* EP0 ��MFIFO�f�[�^ */
#define	EP1FIFO	(EP1FIFO_addr + REG_BASE_ADDR)	/* EP1 ���M/��MFIFO�f�[�^ */
#define	EP2FIFO	(EP2FIFO_addr + REG_BASE_ADDR)	/* EP2 ���M/��MFIFO�f�[�^ */
#define	EP3FIFO	(EP3FIFO_addr + REG_BASE_ADDR)	/* EP3 ���M/��MFIFO�f�[�^ */
#define	EP4FIFO	(EP4FIFO_addr + REG_BASE_ADDR)	/* EP4 ���M/��MFIFO�f�[�^ */
#define	EP5FIFO	(EP5FIFO_addr + REG_BASE_ADDR)	/* EP5 ���M/��MFIFO�f�[�^ */

#define	EP0TXFIFOLSB	(EP0TXFIFOLSB_addr + REG_BASE_ADDR)	/* EP0 ���MFIFO�f�[�^ LSB */
#define	EP0TXFIFOMSB	(EP0TXFIFOMSB_addr + REG_BASE_ADDR)	/* EP0 ��MFIFO�f�[�^ MSB */
#define	EP0RXFIFOLSB	(EP0RXFIFOLSB_addr + REG_BASE_ADDR)	/* EP0 ��MFIFO�f�[�^ LSB */
#define	EP0RXFIFOMSB	(EP0RXFIFOMSB_addr + REG_BASE_ADDR)	/* EP0 ��MFIFO�f�[�^ MSB */
#define	EP1FIFOLSB	(EP1FIFOLSB_addr + REG_BASE_ADDR)	/* EP1 ���M/��MFIFO�f�[�^ LSB */
#define	EP1FIFOMSB	(EP1FIFOMSB_addr + REG_BASE_ADDR)	/* EP1 ���M/��MFIFO�f�[�^ MSB */
#define	EP2FIFOLSB	(EP2FIFOLSB_addr + REG_BASE_ADDR)	/* EP2 ���M/��MFIFO�f�[�^ LSB */
#define	EP2FIFOMSB	(EP2FIFOMSB_addr + REG_BASE_ADDR)	/* EP2 ���M/��MFIFO�f�[�^ MSB */
#define	EP3FIFOLSB	(EP3FIFOLSB_addr + REG_BASE_ADDR)	/* EP3 ���M/��MFIFO�f�[�^ LSB */
#define	EP3FIFOMSB	(EP3FIFOMSB_addr + REG_BASE_ADDR)	/* EP3 ���M/��MFIFO�f�[�^ MSB */
#define	EP4FIFOLSB	(EP4FIFOLSB_addr + REG_BASE_ADDR)	/* EP4 ���M/��MFIFO�f�[�^ LSB */
#define	EP4FIFOMSB	(EP4FIFOMSB_addr + REG_BASE_ADDR)	/* EP4 ���M/��MFIFO�f�[�^ MSB */
#define	EP5FIFOLSB	(EP5FIFOLSB_addr + REG_BASE_ADDR)	/* EP5 ���M/��MFIFO�f�[�^ LSB */
#define	EP5FIFOMSB	(EP5FIFOMSB_addr + REG_BASE_ADDR)	/* EP5 ���M/��MFIFO�f�[�^ MSB */

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.2	Common control and status registers */
#define	DVCADR	(DVCADR_addr + REG_BASE_ADDR)	/* �f�o�C�X�A�h���X */
#define	FRAME	(FRAME_addr + REG_BASE_ADDR)	/* �t���[���ԍ� */

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.3	8-byes setup registers */
#define	SETUP0W		(SETUP0W_addr + REG_BASE_ADDR)
#define	SETUP1W		(SETUP1W_addr + REG_BASE_ADDR)
#define	SETUP2W		(SETUP2W_addr + REG_BASE_ADDR)
#define	SETUP3W		(SETUP3W_addr + REG_BASE_ADDR)

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.4 Pin function control */

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.5 Interrupt enable control and status */
#define	INTSTAT		(INTSTAT_addr + REG_BASE_ADDR)
#define	INTENBL		(INTENBL_addr + REG_BASE_ADDR)

#define	SYSCON		(SYSCON_addr + REG_BASE_ADDR)

/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.6 DMA settings */
#define	DMA0CON		(DMA0CON_addr + REG_BASE_ADDR)
#define	DMA1CON		(DMA1CON_addr + REG_BASE_ADDR)


/*<<<<  �f�o�C�X�R���g���[�����䃌�W�X�^
 2.7 Endpoint controls */

/* 2.7.1 EP0 controls */
#define	EP0CONT			(EP0CONT_addr + REG_BASE_ADDR)
#define	EP0PLDCONF		(EP0PLDCONF_addr + REG_BASE_ADDR)
#define	EP0TXCNT		(EP0TXCNT_addr + REG_BASE_ADDR)
#define	EP0RXCNTSTAT	(EP0RXCNTSTAT_addr + REG_BASE_ADDR)

/* 2.7.2 EP1 controls */
#define	EP1CONT			(EP1CONT_addr + REG_BASE_ADDR)
#define	EP1PLDCONF		(EP1PLDCONF_addr + REG_BASE_ADDR)
#define	EP1RXCNTSTAT	(EP1RXCNTSTAT_addr + REG_BASE_ADDR)
#define	EP1TXCNT		(EP1TXCNT_addr + REG_BASE_ADDR)

/* 2.7.3 EP2 controls */
#define	EP2CONT			(EP2CONT_addr + REG_BASE_ADDR)
#define	EP2PLDCONF		(EP2PLDCONF_addr + REG_BASE_ADDR)
#define	EP2RXCNTSTAT	(EP2RXCNTSTAT_addr + REG_BASE_ADDR)
#define	EP2TXCNT		(EP2TXCNT_addr + REG_BASE_ADDR)

/* 2.7.4 EP3 controls */
#define	EP3CONT			(EP3CONT_addr + REG_BASE_ADDR)
#define	EP3PLDCONF		(EP3PLDCONF_addr + REG_BASE_ADDR)
#define	EP3RXCNTSTAT	(EP3RXCNTSTAT_addr + REG_BASE_ADDR)
#define	EP3TXCNT		(EP3TXCNT_addr + REG_BASE_ADDR)

/* 2.7.5 EP4 controls */
#define	EP4CONT			(EP4CONT_addr + REG_BASE_ADDR)
#define	EP4CONF			(EP4CONF_addr + REG_BASE_ADDR)
#define	EP4PLD			(EP4PLD_addr + REG_BASE_ADDR)
#define	EP4STAT			(EP4STAT_addr + REG_BASE_ADDR)
#define	EP4RXCNT		(EP4RXCNT_addr + REG_BASE_ADDR)
#define	EP4TXCNT		(EP4TXCNT_addr + REG_BASE_ADDR)

/* 2.7.6 EP5 controls */
#define	EP5CONT			(EP5CONT_addr + REG_BASE_ADDR)
#define	EP5CONF			(EP5CONF_addr + REG_BASE_ADDR)
#define	EP5PLD			(EP5PLD_addr + REG_BASE_ADDR)
#define	EP5STAT			(EP5STAT_addr + REG_BASE_ADDR)
#define	EP5RXCNT		(EP5RXCNT_addr + REG_BASE_ADDR)
#define	EP5TXCNT		(EP5TXCNT_addr + REG_BASE_ADDR)

/* 2.7.7 EP4 EP5 ISO controls */
#define	ISOMODE			(ISOMODE_addr + REG_BASE_ADDR)



/********************************************************************************/
#endif /* _ML60842_H_ */

/* End of file */
