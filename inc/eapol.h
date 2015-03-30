/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _EAPOL_H_
#define _EAPOL_H_

#pragma pack(1)

#include "rt2501usb_internal.h"

#define EAPOL_DTYPE_WPAKEY	0xfe

struct eapol_key_info {
	unsigned char key_mic:1;
	unsigned char secure:1;
	unsigned char error:1;
	unsigned char request:1;
	unsigned char ekd:1;
	unsigned char reserved:3;
	unsigned char key_desc_ver:3;
	unsigned char key_type:1;
	unsigned char key_index:2;
	unsigned char install:1;
	unsigned char key_ack:1;
};

#define EAPOL_RPC_LENGTH	8
#define EAPOL_NONCE_LENGTH	32
#define EAPOL_KEYIV_LENGTH	16
#define EAPOL_KEYRSC_LENGTH	8
#define EAPOL_KEYID_LENGTH	8
#define EAPOL_KEYMIC_LENGTH	16

struct eapol_key_frame {
	unsigned char descriptor_type;
	struct eapol_key_info key_info;
	unsigned char key_length[2];
	unsigned char replay_counter[EAPOL_RPC_LENGTH];
	unsigned char key_nonce[EAPOL_NONCE_LENGTH];
	unsigned char key_iv[EAPOL_KEYIV_LENGTH];
	unsigned char key_rsc[EAPOL_KEYRSC_LENGTH];
	unsigned char key_id[EAPOL_KEYID_LENGTH];
	unsigned char key_mic[EAPOL_KEYMIC_LENGTH];
	unsigned char key_data_length[2];
	unsigned char key_data[];
};

#define EAPOL_VERSION		0x01

#define EAPOL_TYPE_EAP		0x00
#define EAPOL_TYPE_START	0x01
#define EAPOL_TYPE_LOGOFF	0x02
#define EAPOL_TYPE_KEY		0x03
#define EAPOL_TYPE_ASF		0x04

struct eapol_frame {
	unsigned char llc[LLC_LENGTH];
	
	unsigned char protocol_version;
	unsigned char packet_type;
	unsigned char body_length[2];
	
	struct eapol_key_frame key_frame;
};

#define EAPOL_MICK_LENGTH		16
#define EAPOL_EK_LENGTH			16

#define EAPOL_TKIP_EK_LENGTH		16
#define EAPOL_TKIP_RXMICK_LENGTH	8
#define EAPOL_TKIP_TXMICK_LENGTH	8

#define EAPOL_PTK_LENGTH		(EAPOL_MICK_LENGTH+EAPOL_EK_LENGTH+EAPOL_TKIP_EK_LENGTH+EAPOL_TKIP_RXMICK_LENGTH+EAPOL_TKIP_TXMICK_LENGTH)

#define EAPOL_MASTER_KEY_LENGTH		32
#define EAPOL_TSC_LENGTH		6

#pragma pack()

#endif /* _EAPOL_H_ */
