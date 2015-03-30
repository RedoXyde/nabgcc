/*******************************************************************************
	ml60842.h
	JOB60842サンプルプログラム
	ML60842レジスタ定義

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	更新履歴
	Mar.31,2003 rev1.00:新規作成
*******************************************************************************/
#ifndef __ML60842_H_
#define	__ML60842_H_

#define	REG_BASE_ADDR	0xF0000000
#define MAX_ADDR		0xF0008000

/********************************************************************************/
/* 共通部レジスタ                                                               */
/********************************************************************************/
/*<<<<  ホストペリフェラル切り替えレジスタ=====*/
#define HostPeriSel_addr		0x000		/* ホスト/ペリフェラル選択 */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define B_HOST_SEL              0x00        /* HOST選択 */
#define	B_PERI_SEL				0x01		/* Peripheral選択 */
#define	B_OPERATION				0x02		/* 内部動作中 */
#define	B_HWSW_MODE				0x04		/* MODE設定あり */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  チップコンフィグレーションレジスタ=====*/
#define Chip_Config_addr		0x004		/*チップコンフィグレーションレジスタ*/
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DREQ	 				0x01		/* DREQの極性 */
#define	B_DRAK	 				0x02		/* DRAKの極性 */
#define	B_INTR	 				0x04		/* INTRの極性 */
#define	B_EXBUFENB 				0x08		/* 外部トランシーバ使用 */
#define	B_TRCV_MODE				0x80		/* 外付けトランシーバモード */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  エンディアンレジスタ=====*/
#define Endian_addr     		0x008		/* エンディアン設定レジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_LITTLEENDIAN 			0x00000000ul	/* リトルエンディアン */
#define	B_ENDIAN0 				0x00000001ul	/* ビックエンディアン */
#define	B_ENDIAN1 				0x00000100ul	/* ビックエンディアン */
#define	B_ENDIAN2 				0x00010000ul	/* ビックエンディアン */
#define	B_ENDIAN3 				0x01000000ul	/* ビックエンディアン */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  OTG制御レジスタ=====*/
#define	OTGCtl_addr	    		0x010		/* OTG制御レジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define M_VBUSMODE              0x00000003ul  /* VBUS制御モードフィールド MASK */
#define F_VBUSMODE_ROOTHUB      0x00000000ul  /* VBUS制御モードルートハブ */
#define F_VBUSMODE_DRIVE        0x00000002ul  /* DRVVBUSビット制御モード */
#define F_VBUSMODE_PULSE        0x00000003ul  /* CHRG,DISCHRGビット制御モード */
#define	B_DRVVBUS    			0x00000004ul 	/* PCONT端子L出力 */
#define	B_CHRGVBUS    			0x00000008ul 	/* VBUSチャージON */
#define	B_DISCHRGVBUS  			0x00000010ul 	/* VBUSディスチャージON */
#define	B_PDCTLDP      			0x00000020ul 	/* D+プルダウン制御イネーブル */
#define	B_PDCTLDM      			0x00000040ul 	/* D-プルダウン制御イネーブル */
#define	B_PUCTLDP      			0x00000080ul 	/* D+プルアップ制御イネーブル */
#define	B_PUCTLDP      			0x00000080ul 	/* D+プルアップ制御イネーブル */
#define	M_SELSV         		0x00000700ul 	/* SELSV MASK */

#define	B_AVBUSVLDENB    		0x00000800ul 	/*A_VBUS_VALIDコンパレータイネーブル*/
#define	B_ABSESSVLDENB    		0x00001000ul 	/*AB_SESS_VALIDコンパレータイネーブル*/
#define	B_USBRCVENB     		0x00002000ul 	/* レシーバ部イネーブル*/
#define B_BSE0SRPDETENB         0x00004000ul  /* SE0検出タイマイネーブル */
#define	B_SELRV         		0x80000000ul 	/* AVDD=3.3V */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  OTG割り込みステータスレジスタ=====*/
#define	OTGIntStt_addr	   		0x014		/* OTG割り込みステータスレジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_IDSELCHG     			0x00000001ul 	/* ID端子変化あり */
#define	B_ABSESSVLDCHG			0x00000002ul 	/* AB_SESS_VALIDコンパレータ変化あり*/
#define	B_AVBUSVLDCHG			0x00000004ul 	/* A_VBUS_VALIDコンパレータ変化あり */
#define	B_USBIFCHG  			0x00008000ul 	/* 状態変化あり */
#define	B_IDSELST  	    		0x00010000ul 	/* Bデバイス */
#define	B_ABSESSVLDST     		0x00020000ul 	/* VBUS>AB_SESS_VALID */
#define	B_AVBUSVLDST     		0x00040000ul 	/* VBUS>A_VBUS_VALID_LOW */
#define	B_BSE0SRPDETST     		0x04000000ul 	/* 状態検出 */
#define	F_SE0            		0x00000000ul 	/* SE0 */
#define	F_KSTATE           		0x08000000ul 	/* Kステート */
#define	F_JSTATE           		0x10000000ul 	/* Jステート */
#define	F_SE1           		0x18000000ul 	/* SE1 */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  OTG割り込みマスクレジスタ=====*/
#define OTGIntMask_addr	    	0x018	   	/* OTG割り込みマスクレジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_IDSELCHGINT 			0x00000001ul 	/* ID端子変化イネーブル */
#define	B_ABSESSVLDCHGINT		0x00000002ul 	/*AB_SESS_VALIDコンパレータ変化イネーブル*/ 
#define	B_AVBUSVLDCHGINT		0x00000004ul 	/* A_VBUS_VALIDコンパレータ変化イネーブル*/
#define	B_USBIFCHGINT  			0x00008000ul 	/* 状態変化イネーブル */
#define	B_BSE0SRPDETSTINT  		0x04000000ul 	/* SE0状態検出イネーブル */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/


/*<<<<  リセットクロック制御レジスタ=====*/
#define RstClkCtl_addr 	    	0x01C	   	/* リセットクロック制御レジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_XRUN      			0x00000000ul 	/* 発振回路動作 */
#define	B_XSTOP      			0x00000001ul 	/* 発振回路停止 */
#define	B_CLKSTOP      			0x00000002ul 	/* クロック供給停止 */
#define	B_SLCLKSTOP    			0x00000002ul 	/* スロークロック停止 */
#define	B_PRST      			0x00000010ul 	/* ペリフェラルリセット */
#define	B_HRST      			0x00000020ul 	/* ホストリセット */
#define	B_CRST      			0x00000040ul 	/* LSIリセット */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/********************************************************************************/
/* Open Host Control Register                                                   */
/********************************************************************************/
/*<<<<  OHCI制御用レジスタ=====*/
#define HcRevision_addr			0x100		/* リビジョンレジスタ */
  #define RevisonNumber     0x00000010

#define HcControl_addr			0x104		/* コントロールレジスタ */
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

#define HcCommandStatus_addr		0x108		/* コマンドステータスレジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define OHCI_HCR          (1ul << 0)          /* host controller reset */
  #define OHCI_CLF          (1ul << 1)          /* control list filled */
  #define OHCI_BLF          (1ul << 2)          /* bulk list filled */
  #define OHCI_OCR          (1ul << 3)          /* ownership change request */
  #define OHCI_SOC          (3ul << 16)         /* scheduling overrun count */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcInterruptStatus_addr	0x10C		/* 割り込みステータスレジスタ */
#define HcInterruptEnable_addr	0x110		/* 割り込み許可レジスタ */
#define HcInterruptDisable_addr	0x114		/* 割り込み禁止レジスタ */
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



#define HcHCCA_addr			0x118		/* コミュニケーションエリアアドレスレジスタ */

#define HcPeriodCurrentED_addr		0x11C		/* 周期転送カレントEDレジスタ */

#define HcControlHeadED_addr		0x120		/* コントロール転送ヘッドEDレジスタ */

#define HcControlCurrentED_addr		0x124		/* コントロール転送カレントEDレジスタ */

#define HcBulkHeadED_addr		0x128		/* バルク転送ヘッドEDレジスタ */

#define HcBulkCurrentED_addr		0x12C		/* バルク転送カレントEDレジスタ */

#define HcDoneHead_addr			0x130		/* 転送完了ヘッドレジスタ */



#define HcFmInterval_addr		0x134		/* フレームインターバルレジスタ */

#define HcFmRemaining_addr		0x138		/* フレームリメインレジスタ */

#define HcFmNumber_addr			0x13C		/* フレームナンバレジスタ */

#define HcPeriodicStart_addr		0x140		/* 周期転送スタート指定レジスタ */

#define HcLSThreshold_addr		0x144		/* ロースピードスレッシュホールドレジスタ */



#define HcRhDescriptorA_addr		0x148		/* ルートハブディスクリプタAレジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define RH_A_NDP          0x000000fful          /* number of downstream ports */
  #define RH_A_PSM          0x00000100ul          /* power switching mode */
  #define RH_A_NPS          0x00000100ul          /* no power switching */
  #define RH_A_DT           0x00000200ul          /* device type (mbz) */
  #define RH_A_OCPM         0x00000400ul          /* over current protection mode */
  #define RH_A_NOCP         0x00000800ul          /* no over current protection */
  #define RH_A_POTPGT       0xff000000ul          /* power on to power good time */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcRhDescriptorB_addr		0x14C		/* ルートハブディスクリプタBレジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define RH_B_DR           0x0000fffful          /* device removable flags */
  #define RH_B_PPCM         0xffff0000ul          /* port power control mask */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcRhStatus_addr			0x150		/* ルートハブステータスレジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
  #define RH_HS_LPS         0x00000001ul          /* local power status */
  #define RH_HS_OCI         0x00000002ul          /* over current indicator */
  #define RH_HS_DRWE        0x00008000ul          /* device remote wakeup enable */
  #define RH_HS_LPSC        0x00010000ul          /* local power status change */
  #define RH_HS_OCIC        0x00020000ul          /* over current indicator change */
  #define RH_HS_CRWE        0x80000000ul          /* clear remote wakeup enable */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HcRhPortStatus_addr		0x154		/* ルートハブポート1ステータスレジスタ */
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

/* 内部RAMアドレス */
#define IntRAMAddr      	(REG_BASE_ADDR+0x1000)
#define IntRAMSize      	(0x1000)


/*<<<<  ホストコントローラ制御レジスタ=====*/
#define HostCtl_addr			0x200	/* Host Control レジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMAIRQ_MASK		0x00000001ul  /* ホストデータ転送マスク */
#define	B_OHCIIRQ_MASK		0x00000002ul  /* ホストコア割り込みマスク */
#define	B_DREQMSK   		0x00000008ul  /* PIO転送 */
#define	B_TRNSTERM   		0x00000080ul  /* 転送終結 */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define SttTrnsCnt_addr			0x204		/* Status, RD/WR FIFO 転送長レジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMAIRQ    		0x00000001ul  /* ホストデータ転送割り込みあり */
#define	B_OHCIIRQ   		0x00000002ul  /* ホストコア割り込みあり */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define HostDataTrnsReq_addr		0x208		/* ホストデータ転送リクエストレジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMADIR    		0x00000001ul  /* CPU->LSI */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define RamAdr_addr			0x20C		/* 内部RAMアドレス設定用レジスタ */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_IRAMBASEACT  		0x00000001ul  /* アクセスあり */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define FifoAcc_addr		0x240		/* FIFOアクセスレジスタ */


/********************************************************************************/
/* デバイスコントローラ部制御レジスタ                                           */
/********************************************************************************/
/*<<<<  デバイスコントローラ制御レジスタ
 2.1	fifos */
#define	EP0TXFIFO_addr		0x400		/* EP0 送信FIFOデータ LSB */
#define	EP0RXFIFO_addr		0x404		/* EP0 受信FIFOデータ LSB */
#define	EP1FIFO_addr		0x410		/* EP1 送信/受信FIFOデータ LSB */
#define	EP2FIFO_addr		0x420		/* EP2 送信/受信FIFOデータ LSB */
#define	EP3FIFO_addr		0x430		/* EP3 送信/受信FIFOデータ LSB */
#define	EP4FIFO_addr		0x440		/* EP4 送信/受信FIFOデータ LSB */
#define	EP5FIFO_addr		0x450		/* EP5 送信/受信FIFOデータ LSB */

#define	EP0TXFIFOLSB_addr	0x400		/* EP0 送信FIFOデータ LSB */
#define	EP0TXFIFOMSB_addr	0x402		/* EP0 受信FIFOデータ MSB */
#define	EP0RXFIFOLSB_addr	0x404		/* EP0 受信FIFOデータ LSB */
#define	EP0RXFIFOMSB_addr	0x408		/* EP0 受信FIFOデータ MSB */
#define	EP1FIFOLSB_addr		0x410		/* EP1 送信/受信FIFOデータ LSB */
#define	EP1FIFOMSB_addr		0x41C		/* EP1 送信/受信FIFOデータ MSB */
#define	EP2FIFOLSB_addr		0x420		/* EP2 送信/受信FIFOデータ LSB */
#define	EP2FIFOMSB_addr		0x42C		/* EP2 送信/受信FIFOデータ MSB */
#define	EP3FIFOLSB_addr		0x430		/* EP3 送信/受信FIFOデータ LSB */
#define	EP3FIFOMSB_addr		0x43C		/* EP3 送信/受信FIFOデータ MSB */
#define	EP4FIFOLSB_addr		0x440		/* EP4 送信/受信FIFOデータ LSB */
#define	EP4FIFOMSB_addr		0x44C		/* EP4 送信/受信FIFOデータ MSB */
#define	EP5FIFOLSB_addr		0x450		/* EP5 送信/受信FIFOデータ LSB */
#define	EP5FIFOMSB_addr		0x45C		/* EP5 送信/受信FIFOデータ MSB */


/*<<<<  デバイスコントローラ制御レジスタ
 2.2	Common control and status registers */
#define	DVCADR_addr			0x308		/* デバイスアドレス */
#define	FRAME_addr			0x30C		/* フレーム番号 */

/*<<<<  デバイスコントローラ制御レジスタ
 2.3	8-byes setup registers */
#define	SETUP0W_addr			0x300
#define	SETUP1W_addr			0x302
#define	SETUP2W_addr			0x304
#define	SETUP3W_addr			0x306

/*<<<<  デバイスコントローラ制御レジスタ
 2.4 Pin function control */

/*<<<<  デバイスコントローラ制御レジスタ
 2.5 Interrupt enable control and status */
#define	INTSTAT_addr			0x310
#define	INTENBL_addr			0x314
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_SETUP_RDY_INT			0x0100ul		/* セットアップレディ割り込み */
#define	B_EP1PKTRDY_INT			0x0200ul		/* EP1パケットレディ割り込み */
#define	B_EP2PKTRDY_INT			0x0400ul	/* EP2パケットレディ割り込み */
#define	B_EP3PKTRDY_INT			0x0800ul		/* EP3パケットレディ割り込み */
#define	B_EP4PKTRDY_INT			0x1000ul		/* EP4パケットレディ割り込み */
#define	B_EP5PKTRDY_INT			0x2000ul		/* EP5パケットレディ割り込み */
#define	B_EP0RXPKTRDY_INT		0x4000ul		/* EP0受信パケットレディ割り込み */
#define	B_EP0TXPKTRDY_INT		0x8000ul		/* EP0送信パケットレディ割り込み */
#define	B_SOF_INT				0x0001ul		/* SOF割込み */
#define	B_BUS_RESET_INT			0x0002ul		/* USBバスリセット･アサート割込み */
#define	B_BUS_RESET_DES_INT		0x0004ul		/* USBバスリセット･デアサート割込み */
#define	B_SUSPENDED_STATE_INT	0x0008ul		/* サスペンデッドステート割り込み */
#define	B_AWAKE_INT				0x0010ul		/* デバイスアウェイクステート割込み */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

#define	SYSCON_addr			0x318
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_SOFT_RESET			0x01ul		/* ソフトリセット */
#define	B_PWDWN_MODE			0x02ul		/* パワーダウンモード */
#define	B_EP_MODE				0x04ul		/* EPモード 0=6EP,1=5EP */
#define	B_PULLUP_CTRL			0x08ul		/* プルアップ制御 */
#define	B_REMOTE_WAKEUP			0x10ul		/* リモートウェイクアップ */
#define	B_CLK_CTL				0x80ul		/* デバイス部のクロック停止 */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/*<<<<  デバイスコントローラ制御レジスタ
 2.6 DMA settings */
#define	DMA0CON_addr			0x320
#define	DMA1CON_addr			0x324
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_DMA_ENABLE			0x01ul		/* DMAイネーブル */
#define	B_BYTE_COUNT			0x04ul		/* バイトカウント */
#define	F_DMA_EP1				0x00ul		/* EP1をDMAの対象とする */
#define	F_DMA_EP2				0x20ul		/* EP2をDMAの対象とする */
#define	F_DMA_EP4				0x40ul		/* EP4をDMAの対象とする */
#define	F_DMA_EP5				0x60ul		/* EP5をDMAの対象とする */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/


/*<<<<  デバイスコントローラ制御レジスタ
 2.7 Endpoint controls */
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_CONFIG					0x10ul		/* コンフィグレーションビット */
#define B_STALL						0x01ul		/* ストールビット */
#define	B_DATA_SEQUENCE				0x02ul		/* データシーケンス・トグルビット */
#define B_CLR_FIFO					0x04ul		/* FIFOクリア */
#define B_RECV_PKTRDY				0x01ul		/* 受信パケットレディ */
#define B_TRNS_PKTRDY				0x02ul		/* 送信パケットレディ */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/* 2.7.1 EP0 controls */
#define	EP0CONT_addr			0x378
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	F_CTRL_TRNS				0x00ul		/* 転送タイプ コントロール転送 */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	EP0PLDCONF_addr		0x330
#define	EP0TXCNT_addr		0x360		/* EP0送信データバイト数 */
#define	EP0RXCNTSTAT_addr	0x348
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	B_EP0_SETUP_RDY			0x04ul		/* セットアップレディ */
#define	F_SETUP_STAGE			0x00ul		/* セットアップステージ */
#define	F_DATA_STAGE			0x10ul		/* データステージ */
#define	F_STATUS_STAGE			0x20ul		/* ステータスステージ */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

/* 2.7.2 EP1 controls */
#define	EP1CONT_addr		0x37C
#define	EP1PLDCONF_addr		0x334
#define	EP1RXCNTSTAT_addr	0x34C
#define	EP1TXCNT_addr		0x364		/* EP1送信データバイト数 */

/* 2.7.3 EP2 controls */
#define	EP2CONT_addr		0x380
#define	EP2PLDCONF_addr		0x338
#define	EP2RXCNTSTAT_addr	0x350
#define	EP2TXCNT_addr		0x368		/* EP2送信データバイト数 */

/* 2.7.4 EP3 controls */
#define	EP3CONT_addr		0x384
#define	EP3PLDCONF_addr		0x33C
#define	EP3RXCNTSTAT_addr	0x354
#define	EP3TXCNT_addr		0x36C		/* EP3送信データバイト数 */

/* 2.7.5 EP4 controls */
#define	EP4CONT_addr		0x388
/*;;;;;;;;;;;;;;;;;;;;;;;Bit Field Definition ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define ISO_IN_RCVED_STS			0x80ul		/* 直前フレームでISO INを受信したか */
/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/
#define	EP4CONF_addr		0x340
#define	EP4PLD_addr			0x340
#define	EP4STAT_addr		0x358
#define	EP4RXCNT_addr		0x358
#define	EP4TXCNT_addr		0x370		/* EP4送信データバイト数 */

/* 2.7.6 EP5 controls */
#define	EP5CONT_addr		0x38C
#define	EP5CONF_addr		0x344
#define	EP5PLD_addr			0x344
#define	EP5STAT_addr		0x35C
#define	EP5RXCNT_addr		0x35C
#define	EP5TXCNT_addr		0x374		/* EP5送信データバイト数 */

/* 2.7.7 EP4 EP5 ISO controls */
#define	ISOMODE_addr			0x31C

/* 3.	Endpoint serial number definitions

	各エンドポイントに通し番号をつけます。
	この番号は、いわゆるエンドポイントアドレスとは、異なります。
	この番号はエンドポイント構造体の配列添字として用います。
*/
#define	EP0				0		/* Endpoint 0 汎用 */
#define	EP0RX			0		/* Endpoint 0 受信用 */
#define	EP1				1		/* Endpoint 1 */
#define	EP2				2		/* Endpoint 2 */
#define	EP3				3		/* Endpoint 3 */
#define	EP4				4		/* Endpoint 4 */
#define	EP5				5		/* Endpoint 5 */
#define	EP0TX			6		/* Endpoint 0 送信用 */
#define	EP_MAX			6		/* エンドポイント最大数 */


/* 6.	register definitions
	プログラムで用いるレジスタを定義している
*/
/*<<<<  ホストペリフェラル切り替えレジスタ=====*/
#define HostPeriSel     (HostPeriSel_addr + REG_BASE_ADDR)	/* ホスト/ペリフェラル選択 */
/*<<<<  チップコンフィグレーションレジスタ=====*/
#define Chip_Config     (Chip_Config_addr + REG_BASE_ADDR)	/*チップコンフィグレーションレジスタ*/
/*<<<<  エンディアンレジスタ=====*/
#define Endian          (Endian_addr + REG_BASE_ADDR)	    /* エンディアン設定レジスタ */
/*<<<<  OTG制御レジスタ=====*/
#define	OTGCtl          (OTGCtl_addr + REG_BASE_ADDR)	    /* OTG制御レジスタ */
/*<<<<  OTG割り込みステータスレジスタ=====*/
#define	OTGIntStt       (OTGIntStt_addr + REG_BASE_ADDR)	/* OTG割り込みステータスレジスタ */
/*<<<<  OTG割り込みマスクレジスタ=====*/
#define OTGIntMask      (OTGIntMask_addr + REG_BASE_ADDR)	/* OTG割り込みマスクレジスタ */
/*<<<<  リセットクロック制御レジスタ=====*/
#define RstClkCtl       (RstClkCtl_addr + REG_BASE_ADDR)	/* リセットクロック制御レジスタ */

/********************************************************************************/
/* Open Host Control Register                                                   */
/********************************************************************************/
/*<<<<  OHCI制御用レジスタ=====*/
#define HcRevision	(HcRevision_addr + REG_BASE_ADDR)	/* リビジョンレジスタ */
#define HcControl	(HcControl_addr + REG_BASE_ADDR)	/* コントロールレジスタ */
#define HcCommandStatus	(HcCommandStatus_addr + REG_BASE_ADDR)	/* コマンドステータスレジスタ */
#define HcInterruptStatus	(HcInterruptStatus_addr + REG_BASE_ADDR)	/* 割り込みステータスレジスタ */

#define HcInterruptEnable	(HcInterruptEnable_addr + REG_BASE_ADDR)	/* 割り込み許可レジスタ */
#define HcInterruptDisable	(HcInterruptDisable_addr + REG_BASE_ADDR)	/* 割り込み禁止レジスタ */
#define HcHCCA	(HcHCCA_addr + REG_BASE_ADDR)	/* コミュニケーションエリアアドレスレジスタ */
#define HcPeriodCurrentED	(HcPeriodCurrentED_addr + REG_BASE_ADDR)	/* 周期転送カレントEDレジスタ */

#define HcControlHeadED	(HcControlHeadED_addr + REG_BASE_ADDR)	/* コントロール転送ヘッドEDレジスタ */
#define HcControlCurrentED	(HcControlCurrentED_addr + REG_BASE_ADDR)	/* コントロール転送カレントEDレジスタ */
#define HcBulkHeadED	(HcBulkHeadED_addr + REG_BASE_ADDR)	/* バルク転送ヘッドEDレジスタ */
#define HcBulkCurrentED	(HcBulkCurrentED_addr + REG_BASE_ADDR)	/* バルク転送カレントEDレジスタ */

#define HcDoneHead	(HcDoneHead_addr + REG_BASE_ADDR)	/* 転送完了ヘッドレジスタ */
#define HcFmInterval	(HcFmInterval_addr + REG_BASE_ADDR)	/* フレームインターバルレジスタ */
#define HcFmRemaining	(HcFmRemaining_addr + REG_BASE_ADDR)	/* フレームリメインレジスタ */
#define HcFmNumber	(HcFmNumber_addr + REG_BASE_ADDR)	/* フレームナンバレジスタ */

#define HcPeriodicStart	(HcPeriodicStart_addr + REG_BASE_ADDR)	/* 周期転送スタート指定レジスタ */
#define HcLSThreshold	(HcLSThreshold_addr + REG_BASE_ADDR)	/* ロースピードスレッシュホールドレジスタ */
#define HcRhDescriptorA	(HcRhDescriptorA_addr + REG_BASE_ADDR)	/* ルートハブディスクリプタAレジスタ */
#define HcRhDescriptorB	(HcRhDescriptorB_addr + REG_BASE_ADDR)	/* ルートハブディスクリプタBレジスタ */

#define HcRhStatus	(HcRhStatus_addr + REG_BASE_ADDR)	/* ルートハブステータスレジスタ */
#define HcRhPortStatus	(HcRhPortStatus_addr + REG_BASE_ADDR)	/* ルートハブポート1ステータスレジスタ */

/*<<<<  ホストコントローラ制御レジスタ=====*/
#define HostCtl	(HostCtl_addr + REG_BASE_ADDR)	/* Host Control レジスタ */
#define SttTrnsCnt	(SttTrnsCnt_addr + REG_BASE_ADDR)	/* Status, RD/WR FIFO 転送長レジスタ */
#define HostDataTrnsReq	(HostDataTrnsReq_addr + REG_BASE_ADDR)	/* ホストデータ転送リクエストレジスタ */
#define RamAdr	(RamAdr_addr + REG_BASE_ADDR)	/* 内部RAMアドレス設定用レジスタ */
#define FifoAcc	(FifoAcc_addr + REG_BASE_ADDR)	/* FIFOアクセスレジスタ */


/********************************************************************************/
/* デバイスコントローラ部制御レジスタ                                           */
/********************************************************************************/
/*<<<<  デバイスコントローラ制御レジスタ
 2.1	fifos */
#define	EP0TXFIFO	(EP0TXFIFO_addr + REG_BASE_ADDR)	/* EP0 送信FIFOデータ */
#define	EP0RXFIFO	(EP0RXFIFO_addr + REG_BASE_ADDR)	/* EP0 受信FIFOデータ */
#define	EP1FIFO	(EP1FIFO_addr + REG_BASE_ADDR)	/* EP1 送信/受信FIFOデータ */
#define	EP2FIFO	(EP2FIFO_addr + REG_BASE_ADDR)	/* EP2 送信/受信FIFOデータ */
#define	EP3FIFO	(EP3FIFO_addr + REG_BASE_ADDR)	/* EP3 送信/受信FIFOデータ */
#define	EP4FIFO	(EP4FIFO_addr + REG_BASE_ADDR)	/* EP4 送信/受信FIFOデータ */
#define	EP5FIFO	(EP5FIFO_addr + REG_BASE_ADDR)	/* EP5 送信/受信FIFOデータ */

#define	EP0TXFIFOLSB	(EP0TXFIFOLSB_addr + REG_BASE_ADDR)	/* EP0 送信FIFOデータ LSB */
#define	EP0TXFIFOMSB	(EP0TXFIFOMSB_addr + REG_BASE_ADDR)	/* EP0 受信FIFOデータ MSB */
#define	EP0RXFIFOLSB	(EP0RXFIFOLSB_addr + REG_BASE_ADDR)	/* EP0 受信FIFOデータ LSB */
#define	EP0RXFIFOMSB	(EP0RXFIFOMSB_addr + REG_BASE_ADDR)	/* EP0 受信FIFOデータ MSB */
#define	EP1FIFOLSB	(EP1FIFOLSB_addr + REG_BASE_ADDR)	/* EP1 送信/受信FIFOデータ LSB */
#define	EP1FIFOMSB	(EP1FIFOMSB_addr + REG_BASE_ADDR)	/* EP1 送信/受信FIFOデータ MSB */
#define	EP2FIFOLSB	(EP2FIFOLSB_addr + REG_BASE_ADDR)	/* EP2 送信/受信FIFOデータ LSB */
#define	EP2FIFOMSB	(EP2FIFOMSB_addr + REG_BASE_ADDR)	/* EP2 送信/受信FIFOデータ MSB */
#define	EP3FIFOLSB	(EP3FIFOLSB_addr + REG_BASE_ADDR)	/* EP3 送信/受信FIFOデータ LSB */
#define	EP3FIFOMSB	(EP3FIFOMSB_addr + REG_BASE_ADDR)	/* EP3 送信/受信FIFOデータ MSB */
#define	EP4FIFOLSB	(EP4FIFOLSB_addr + REG_BASE_ADDR)	/* EP4 送信/受信FIFOデータ LSB */
#define	EP4FIFOMSB	(EP4FIFOMSB_addr + REG_BASE_ADDR)	/* EP4 送信/受信FIFOデータ MSB */
#define	EP5FIFOLSB	(EP5FIFOLSB_addr + REG_BASE_ADDR)	/* EP5 送信/受信FIFOデータ LSB */
#define	EP5FIFOMSB	(EP5FIFOMSB_addr + REG_BASE_ADDR)	/* EP5 送信/受信FIFOデータ MSB */

/*<<<<  デバイスコントローラ制御レジスタ
 2.2	Common control and status registers */
#define	DVCADR	(DVCADR_addr + REG_BASE_ADDR)	/* デバイスアドレス */
#define	FRAME	(FRAME_addr + REG_BASE_ADDR)	/* フレーム番号 */

/*<<<<  デバイスコントローラ制御レジスタ
 2.3	8-byes setup registers */
#define	SETUP0W		(SETUP0W_addr + REG_BASE_ADDR)
#define	SETUP1W		(SETUP1W_addr + REG_BASE_ADDR)
#define	SETUP2W		(SETUP2W_addr + REG_BASE_ADDR)
#define	SETUP3W		(SETUP3W_addr + REG_BASE_ADDR)

/*<<<<  デバイスコントローラ制御レジスタ
 2.4 Pin function control */

/*<<<<  デバイスコントローラ制御レジスタ
 2.5 Interrupt enable control and status */
#define	INTSTAT		(INTSTAT_addr + REG_BASE_ADDR)
#define	INTENBL		(INTENBL_addr + REG_BASE_ADDR)

#define	SYSCON		(SYSCON_addr + REG_BASE_ADDR)

/*<<<<  デバイスコントローラ制御レジスタ
 2.6 DMA settings */
#define	DMA0CON		(DMA0CON_addr + REG_BASE_ADDR)
#define	DMA1CON		(DMA1CON_addr + REG_BASE_ADDR)


/*<<<<  デバイスコントローラ制御レジスタ
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
