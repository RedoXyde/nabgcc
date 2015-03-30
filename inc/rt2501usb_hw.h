/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _RT2501_HW_H_
#define _RT2501_HW_H_

#pragma pack(1)

/* Sitecom dongle */
#define RT2501_VENDORID1		0x0df6
#define RT2501_PRODUCTID1		0x9712

/* MSI module */
#define RT2501_VENDORID2		0x148f
#define RT2501_PRODUCTID2		0x2573

/* MSI module, strange version */
#define RT2501_VENDORID3		0x0db0
#define RT2501_PRODUCTID3		0x6877


#define RT2501_READMULTIMAC		0x03
#define RT2501_WRITEMULTIMAC		0x06
#define RT2501_READEEPROM		0x09

/* 8051 firmware image */
#define RT2501_FIRMWARE_IMAGE_BASE     0x800
#define RT2501_MAX_FIRMWARE_IMAGE_SIZE 2048

#define RT2501_RFIC_5226		1
#define RT2501_RFIC_2528		2
#define RT2501_RFIC_5225		3
#define RT2501_RFIC_2527		4

#define RT2501_SOFTWARE_DIVERSITY	0
#define RT2501_ANTENNA_A		1
#define RT2501_ANTENNA_B		2
#define RT2501_HARDWARE_DIVERSITY	3

#define	RT2501_RATE_1			0
#define	RT2501_RATE_2			1
#define	RT2501_RATE_5_5			2
#define	RT2501_RATE_11			3
/* OFDM rates */
#define RT2501_RATE_6			4
#define RT2501_RATE_9			5
#define RT2501_RATE_12			6
#define RT2501_RATE_18			7
#define RT2501_RATE_24			8
#define RT2501_RATE_36			9
#define RT2501_RATE_48			10
#define RT2501_RATE_54			11

/*
   On-chip BEACON frame space - base address 0x2400
*/
#define RT2501_HW_BEACON_BASE0         0x2400
#define RT2501_HW_BEACON_BASE1         0x2500
#define RT2501_HW_BEACON_BASE2         0x2600
#define RT2501_HW_BEACON_BASE3         0x2700

/*
   Security key table memory, base address = 0x1000
*/
#define RT2501_SHARED_KEY_TABLE_BASE       0x1000 /* 32-byte * 16-entry = 512-byte */
#define RT2501_PAIRWISE_KEY_TABLE_BASE     0x1200 /* 32-byte * 64-entry = 2048-byte */
#define RT2501_PAIRWISE_TA_TABLE_BASE      0x1a00 /* 8-byte * 64-entry = 512-byte */

/*
   MAC Control Registers - base address 0x3000
*/
#define RT2501_MAC_CSR0            0x3000
#define RT2501_MAC_CSR1            0x3004
#define RT2501_MAC_CSR2            0x3008
#define RT2501_MAC_CSR3            0x300c
#define RT2501_MAC_CSR4            0x3010
#define RT2501_MAC_CSR5            0x3014
#define RT2501_MAC_CSR6            0x3018
#define RT2501_MAC_CSR7            0x301c
#define RT2501_MAC_CSR8            0x3020  /* SIFS/EIFS */
#define RT2501_MAC_CSR9            0x3024
#define RT2501_MAC_CSR10           0x3028  /* power state configuration */
#define RT2501_MAC_CSR11           0x302c  /* Power state transition time */
#define RT2501_MAC_CSR12           0x3030  /* power state */
#define RT2501_MAC_CSR13           0x3034  /* GPIO */
#define RT2501_MAC_CSR14           0x3038  /* LED control */
#define RT2501_MAC_CSR15           0x303c  /* NAV control */


#define	RT2501_NUM_EEPROM_BBP_PARMS		19
#define	RT2501_NUM_EEPROM_TX_G_PARMS		7
#define	RT2501_NUM_EEPROM_BBP_TUNING_PARMS	7

#define RT2501_EEPROM_VERSION_OFFSET       	0x2
#define	RT2501_EEPROM_MAC_ADDRESS_BASE_OFFSET	0x4
#define	RT2501_EEPROM_BBP_BASE_OFFSET		0x20
#define	RT2501_EEPROM_G_TX_PWR_OFFSET		0x46
#define	RT2501_EEPROM_FREQ_OFFSET		0x5e
#define RT2501_EEPROM_LED_OFFSET		0x60
#define RT2501_EEPROM_A_TX_PWR_OFFSET      	0x62
#define	RT2501_EEPROM_TSSI_REF_OFFSET		0x4A
#define	RT2501_EEPROM_TSSI_DELTA_OFFSET		0x1A
#define	RT2501_EEPROM_MAC_STATUS_OFFSET		0x7E
#define	RT2501_EEPROM_RSSI_BG_OFFSET		0x9a
#define	RT2501_EEPROM_RSSI_A_OFFSET		0x9c
#define	RT2501_EEPROM_BG_TSSI_CALIBRAION	0x54
#define	RT2501_EEPROM_A_TSSI_CALIBRAION		0x90
#define RT2501_EEPROM_TXPOWER_DELTA_OFFSET 	0x9e

/*
   TXRX control registers - base address 0x3000
*/
#define RT2501_TXRX_CSR0           0x3040
#define RT2501_TXRX_CSR1           0x3044
#define RT2501_TXRX_CSR2           0x3048
#define RT2501_TXRX_CSR3           0x304c
#define RT2501_TXRX_CSR4           0x3050
#define RT2501_TXRX_CSR5           0x3054
#define RT2501_TXRX_CSR6           0x3058  /* ACK/CTS payload consumed time */
#define RT2501_TXRX_CSR7           0x305c  /* ACK/CTS payload consumed time */
#define RT2501_TXRX_CSR8           0x3060  /* ACK/CTS payload consumed time */
#define RT2501_TXRX_CSR9           0x3064  /* BEACON SYNC */
#define RT2501_TXRX_CSR10          0x3068  /* BEACON alignment */
#define RT2501_TXRX_CSR11          0x306c  /* AES mask */
#define RT2501_TXRX_CSR12          0x3070  /* TSF low 32 */
#define RT2501_TXRX_CSR13          0x3074  /* TSF high 32 */
#define RT2501_TXRX_CSR14          0x3078  /* TBTT timer */
#define RT2501_TXRX_CSR15          0x307c  /* TKIP MIC priority byte "AND" mask */

/*
   PHY control registers - base address 0x3000
*/
#define RT2501_PHY_CSR0            0x3080  /* RF/PS control */
#define RT2501_PHY_CSR1            0x3084
#define RT2501_PHY_CSR2            0x3088  /* pre-TX BBP control */
#define RT2501_PHY_CSR3            0x308c  /* BBP access */
#define RT2501_PHY_CSR4            0x3090  /* RF serial control */
#define RT2501_PHY_CSR5            0x3094  /* RX to TX signal switch timing control */
#define RT2501_PHY_CSR6            0x3098  /* TX to RX signal timing control */
#define RT2501_PHY_CSR7            0x309c  /* TX DAC switching timing control */

/*
   Security control register - base address 0x3000
*/
#define RT2501_SEC_CSR0            0x30a0  /* shared key table control */
#define RT2501_SEC_CSR1            0x30a4  /* shared key table security mode */
#define RT2501_SEC_CSR2            0x30a8  /* pairwise key table valid bitmap 0 */
#define RT2501_SEC_CSR3            0x30ac  /* pairwise key table valid bitmap 1 */
#define RT2501_SEC_CSR4            0x30b0  /* pairwise key table lookup control */
#define RT2501_SEC_CSR5            0x30b4  /* shared key table security mode */

/*
   STA control registers - base address 0x3000
*/
#define STA_CSR0            0x30c0  /* CRC/PLCP error counter */
#define STA_CSR1            0x30c4  /* Long/False-CCA error counter */
#define STA_CSR2            0x30c8  /* RX FIFO overflow counter */
#define STA_CSR3            0x30cc  /* TX Beacon counter */
#define STA_CSR4            0x30d0  /* TX Retry (1) Counters */
#define STA_CSR5            0x30d4  /* TX Retry (2) Counters */

/*
   QOS control registers - base address 0x3000
*/
#define QOS_CSR0            0x30e0  /* TXOP holder MAC address 0 */
#define QOS_CSR1            0x30e4  /* TXOP holder MAC address 1 */
#define QOS_CSR2            0x30e8  /* TXOP holder timeout register */
#define QOS_CSR3            0x30ec  /* RX QOS-CFPOLL MAC address 0 */
#define QOS_CSR4            0x30f0  /* RX QOS-CFPOLL MAC address 1 */
#define QOS_CSR5            0x30f4  /* "QosControl" field of the RX QOS-CFPOLL */

/*
   WMM Scheduler Register
*/

#define RT2501_AIFSN_CSR               	0x0400
#define RT2501_CWMIN_CSR		0x0404
#define RT2501_CWMAX_CSR           	0x0408
#define RT2501_AC_TXOP_CSR0        	0x040c
#define RT2501_AC_TXOP_CSR1        	0x0410

/*
   BBP & RF definitions
*/

#define	RT2501_BBP_R0			   0
#define	RT2501_BBP_R1			   1
#define	RT2501_BBP_R2          		   2
#define RT2501_BBP_R3                      3
#define RT2501_BBP_R4                      4
#define RT2501_BBP_R5                      5
#define RT2501_BBP_R6                      6
#define	RT2501_BBP_R14			   14
#define RT2501_BBP_R16                     16
#define RT2501_BBP_R17                     17
#define RT2501_BBP_R18                     18
#define RT2501_BBP_R21                     21
#define RT2501_BBP_R22                     22
#define RT2501_BBP_R32                     32
#define RT2501_BBP_R62                     62
#define RT2501_BBP_R64                     64
#define RT2501_BBP_R66                     66
#define RT2501_BBP_R70                     70
#define RT2501_BBP_R77                     77
#define RT2501_BBP_R82                     82
#define RT2501_BBP_R83                     83
#define RT2501_BBP_R84                     84
#define RT2501_BBP_R94                     94

#define BBPR94_DEFAULT                     0x06

#define RT2501_MICS_OFFSET		   16
#define RT2501_KEY_ENTRY_SIZE              32

typedef	union	_MAC_CSR2_STRUC	{
	struct	{
		UCHAR		Byte0;
		UCHAR		Byte1;
		UCHAR		Byte2;
		UCHAR		Byte3;
	}	field;
	ULONG			word;
}	MAC_CSR2_STRUC, *PMAC_CSR2_STRUC;

typedef	union	_MAC_CSR3_STRUC	{
	struct	{
		UCHAR		Byte4;
		UCHAR		Byte5;
		UCHAR		U2MeMask;
		UCHAR		Rsvd1;
	}	field;
	ULONG			word;
}	MAC_CSR3_STRUC, *PMAC_CSR3_STRUC;

typedef	union	_MAC_CSR4_STRUC	{
	struct	{
		UCHAR		Byte0;		// BSSID byte 0
		UCHAR		Byte1;		// BSSID byte 1
		UCHAR		Byte2;		// BSSID byte 2
		UCHAR		Byte3;		// BSSID byte 3
	}	field;
	ULONG			word;
}	MAC_CSR4_STRUC, *PMAC_CSR4_STRUC;

typedef	union	_MAC_CSR5_STRUC	{
	struct	{
		UCHAR		Byte4;		 // BSSID byte 4
		UCHAR		Byte5;		 // BSSID byte 5
		USHORT      BssIdMask:2; // 11: one BSSID, 00: 4 BSSID, 10 or 01: 2 BSSID
		USHORT		Rsvd:14;
	}	field;
	ULONG			word;
}	MAC_CSR5_STRUC, *PMAC_CSR5_STRUC;

typedef	union	_MAC_CSR12_STRUC	{
	struct	{
		ULONG		CurrentPowerState:1; /* 0:sleep, 1:awake */
		ULONG       PutToSleep:1;
		ULONG       ForceWakeup:1;/* ForceWake has higher privilege than PutToSleep when both set */
		ULONG		BbpRfStatus:1; /* 0: not ready, 1:ready */
		ULONG		:28;
	}	field;
	ULONG			word;
}	MAC_CSR12_STRUC, *PMAC_CSR12_STRUC;

typedef	union	_TXRX_CSR9_STRUC	{
	struct	{
		ULONG       BeaconInterval:16; /* in unit of 1/16 TU */
		ULONG		bTsfTicking:1; /* Enable TSF auto counting */
		ULONG		TsfSyncMode:2; /* Enable TSF sync, 00: disable, 01: infra mode, 10: ad-hoc mode */
		ULONG       bTBTTEnable:1;
		ULONG		bBeaconGen:1; /* Enable beacon generator */
		ULONG       :3;
		ULONG		TxTimestampCompensate:8;
	}	field;
	ULONG			word;
}	TXRX_CSR9_STRUC, *PTXRX_CSR9_STRUC;

typedef	union	_PHY_CSR3_STRUC	{
	struct	{
		ULONG		Value:8; /* Register value to program into BBP */
		ULONG		RegNum:7; /* Selected BBP register */
		ULONG		fRead:1; /* 0: Write BBP, 1: Read BBP */
		ULONG		Busy:1; /* 1: ASIC is busy doing BBP programming. */
		ULONG		:15;
	}	field;
	ULONG			word;
}	PHY_CSR3_STRUC, *PPHY_CSR3_STRUC;

typedef	union	_PHY_CSR4_STRUC	{
	struct	{
		ULONG		RFRegValue:24; /* Register value (include register id) serial out to RF/IF chip. */
		ULONG		NumberOfBits:5; /* Number of bits used in RFRegValue (I:20, RFMD:22) */
		ULONG		IFSelect:1; /* 1: select IF to program, 0: select RF to program */
		ULONG		PLL_LD:1; /* RF PLL_LD status */
		ULONG		Busy:1; /* 1: ASIC is busy executing RF programming. */
	}	field;
	ULONG			word;
}	PHY_CSR4_STRUC, *PPHY_CSR4_STRUC;

/*
   E2PROM data layout
*/

typedef	union	_EEPROM_ANTENNA_STRUC	{
	struct	{
		USHORT		NumOfAntenna:2;
		USHORT		TxDefaultAntenna:2; /* default of antenna, 0: diversity, 1:antenna-A, 2:antenna-B reserved (default = 0) */
		USHORT		RxDefaultAntenna:2; /* default of antenna, 0: diversity, 1:antenna-A, 2:antenna-B reserved (default = 0) */
		USHORT		FrameType:1; /* 0: DPDT , 1: SPDT , noted this bit is valid for g only.	*/
		USHORT		Rsv:2;
		USHORT      DynamicTxAgcControl:1;
		USHORT		HardwareRadioControl:1;	/* 1: Hardware controlled radio enabled, Read GPIO0 required. */
		USHORT      RfIcType:5;
	}	field;
	USHORT			word;
}	EEPROM_ANTENNA_STRUC, *PEEPROM_ANTENNA_STRUC;

typedef	union	_EEPROM_NIC_CINFIG2_STRUC	{
	struct	{
		USHORT		Rsv1:4;
		USHORT		ExternalLNA:1;
		USHORT      Rsv2:11;
	}	field;
	USHORT			word;
}	EEPROM_NIC_CONFIG2_STRUC, *PEEPROM_NIC_CONFIG2_STRUC;

typedef	union	_EEPROM_TX_PWR_STRUC	{
	struct	{
		UCHAR	Byte0; /* Low Byte */
		UCHAR	Byte1; /* High Byte */
	}	field;
	USHORT	word;
}	EEPROM_TX_PWR_STRUC, *PEEPROM_TX_PWR_STRUC;

typedef	union	_EEPROM_VERSION_STRUC	{
	struct	{
		UCHAR	FaeReleaseNumber; /* Low Byte */
		UCHAR	Version; /* High Byte */
	}	field;
	USHORT	word;
}	EEPROM_VERSION_STRUC, *PEEPROM_VERSION_STRUC;

typedef	union	_EEPROM_LED_STRUC	{
	struct	{
		USHORT	PolarityRDY_G:1;
		USHORT	PolarityRDY_A:1;
		USHORT	PolarityACT:1;
		USHORT	PolarityGPIO_0:1;
		USHORT	PolarityGPIO_1:1;
		USHORT	PolarityGPIO_2:1;
		USHORT	PolarityGPIO_3:1;
		USHORT	PolarityGPIO_4:1;
		USHORT	LedMode:5;
		USHORT	Rsvd:3;
	}	field;
	USHORT	word;
}	EEPROM_LED_STRUC, *PEEPROM_LED_STRUC;

typedef	union	_EEPROM_TXPOWER_DELTA_STRUC	{
	struct	{
		UCHAR	DeltaValue:6; /* Tx Power delta value (MAX=4) */
		UCHAR	Type:1; /* 1: plus the delta value, 0: minus the delta value */
		UCHAR	TxPowerEnable:1;
	}	field;
	UCHAR	value;
}	EEPROM_TXPOWER_DELTA_STRUC, *PEEPROM_TXPOWER_DELTA_STRUC;

/* calibrate every 4s */
#define RT2501_CAL_PERIOD 40

/* RX/TX Descriptor */

typedef	struct	_RXD_STRUC	{
	/* Word	0 */
	ULONG	Owner:1; /* 1: owned by ASIC, 0: owned by HOST driver */
	ULONG	Drop:1;	 /* 1: drop without receiving to HOST */
	ULONG	U2M:1; /* 1: this RX frame is unicast to me */
	ULONG	Mcast:1; /* 1: this is a multicast frame */
	ULONG	Bcast:1; /* 1: this is a broadcast frame */
	ULONG	MyBss:1; /* 1: this frame belongs to the same BSSID */
	ULONG	Crc:1; /* 1: CRC error */
	ULONG	Ofdm:1; /* 1: this frame is received in OFDM rate */
	ULONG	CipherErr:2; /* 0: decryption okay, 1:ICV error, 2:MIC error, 3:KEY not valid */
	ULONG	KeyIndex:6; /* decryption key actually used */
	ULONG	DataByteCnt:12;
	ULONG	Rsv:1;
	ULONG	CipherAlg:3;

	/* Word 1 */
	ULONG	PlcpSignal:8; /* RX raw data rate reported by BBP */
	ULONG	PlcpRssi:8; /* RSSI reported by BBP */
	ULONG	Rsv0:8;
	ULONG	FrameOffset:7;
	ULONG	Rsv1:1;

	/* Word	2 */
	ULONG	Iv; /* received IV if originally encrypted; for replay attack checking */

	/* Word 3 */
	ULONG	Eiv; /* received EIV if originally encrypted; for replay attack checking */

	/* Word 4 */
	ULONG	Rsv2;

	/* Word	5 */
	ULONG	Rsv3; /* BufPhyAddr */
} RXD_STRUC, *PRXD_STRUC;

#define RT2501_CIPHER_NONE		0
#define RT2501_CIPHER_WEP64		1
#define RT2501_CIPHER_WEP128		2
#define RT2501_CIPHER_TKIP		3
#define RT2501_CIPHER_AES		4
#define RT2501_CIPHER_CKIP64		5
#define RT2501_CIPHER_CKIP128		6
#define RT2501_CIPHER_TKIP_NO_MIC	7

typedef	struct	_TXD_STRUC {
	/* Word 0 */
	ULONG	Burst:1; /* 1: Contiguously used current End Point, eg, Fragment packet should turn on. */
	ULONG	Drop:1; /* 0: skip this frame, 1:valid frame inside */
	ULONG	MoreFrag:1; /* 1: More fragment following this frame */
	ULONG	ACK:1; /* 1: ACK is required */
	ULONG	Timestamp:1; /* 1: MAC auto overwrite current TSF into frame body */
	ULONG	Ofdm:1; /* 1: TX using OFDM rates */
	ULONG	IFS:1; /* 1: require a BACKOFF before this frame, 0:SIFS before this frame */
	ULONG	RetryMd:1;

	ULONG	TkipMic:1; /* 1: ASIC is responsible for appending TKIP MIC if TKIP is in use */
	ULONG	KeyTable:1; /* 1: use per-client pairwise KEY table, 0: shared KEY table */
	/*
	   Key index (0~31) to the pairwise KEY table; or
	   0~3 to shared KEY table 0 (BSS0). STA always use BSS0
	   4~7 to shared KEY table 1 (BSS1)
	   8~11 to shared KEY table 2 (BSS2)
	   12~15 to shared KEY table 3 (BSS3)
	*/
	ULONG	KeyIndex:6;

	ULONG	DataByteCnt:12;
	ULONG	Burst2:1; /* same as "Burst" */
	ULONG	CipherAlg:3;

	/* Word 1 */
	ULONG	HostQId:4; /* EDCA/HCCA queue ID */
	ULONG	Aifsn:4;
	ULONG	Cwmin:4;
	ULONG	Cwmax:4;
	ULONG	IvOffset:6;
	ULONG	:6;
	ULONG	HwSeq:1; /* MAC auto replace the 12-bit frame sequence # */
	ULONG	BufCount:3; /* number of buffers in this TXD */

	/* Word 2 */
	ULONG	PlcpSignal:8;
	ULONG	PlcpService:8;
	ULONG	PlcpLengthLow:8;
	ULONG	PlcpLengthHigh:8;

	/* Word 3 */
	ULONG	Iv;

	/* Word 4 */
	ULONG	Eiv;

	/* Word 5 */
	ULONG	FrameOffset:8; /* frame start offset inside ASIC TXFIFO (after TXINFO field) */
	ULONG	PktId:8; /* driver assigned packet ID to categorize TXResult in TxDoneInterrupt */
	ULONG	BbpTxPower:8;
	ULONG	bWaitingDmaDoneInt:1; /* pure s/w flag. 1:TXD been filled with data and waiting for TxDoneISR for housekeeping */
	ULONG	Reserved:7;
} TXD_STRUC, *PTXD_STRUC;

#pragma pack()

#endif /* _RT2501_HW_H_ */
