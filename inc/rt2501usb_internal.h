/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _RT2501_INTERNAL_H_
#define _RT2501_INTERNAL_H_

#include "usbh.h"
#include "rt2501usb_hw.h"
#include "ieee80211.h"

extern PDEVINFO rt2501_dev;

#define RT2501_MAX_NUM_OF_CHANNELS 14
#define RT2501_USB_PACKET_SIZE     64
#define RT2501_MAX_FRAME_SIZE      2048

#define RT2501_MAX_ASSOCIATED_STA  5

#define	RT2501_RATEMASK_1		(1<<0)
#define	RT2501_RATEMASK_2		(1<<1)
#define	RT2501_RATEMASK_5_5		(1<<2)
#define	RT2501_RATEMASK_11		(1<<3)
/* OFDM rates */
#define RT2501_RATEMASK_6		(1<<4)
#define RT2501_RATEMASK_9		(1<<5)
#define RT2501_RATEMASK_12		(1<<6)
#define RT2501_RATEMASK_18		(1<<7)
#define RT2501_RATEMASK_24		(1<<8)
#define RT2501_RATEMASK_36		(1<<9)
#define RT2501_RATEMASK_48		(1<<10)
#define RT2501_RATEMASK_54		(1<<11)

#define	IEEE80211_RATEMASK_1		(1<<0)
#define	IEEE80211_RATEMASK_2		(1<<1)
#define	IEEE80211_RATEMASK_5_5		(1<<2)
#define IEEE80211_RATEMASK_6		(1<<3)
#define IEEE80211_RATEMASK_9		(1<<4)
#define	IEEE80211_RATEMASK_11		(1<<5)
#define IEEE80211_RATEMASK_12		(1<<6)
#define IEEE80211_RATEMASK_18		(1<<7)
#define IEEE80211_RATEMASK_24		(1<<8)
#define IEEE80211_RATEMASK_36		(1<<9)
#define IEEE80211_RATEMASK_48		(1<<10)
#define IEEE80211_RATEMASK_54		(1<<11)
#define IEEE80211_RATEMASK_HIGHEST	IEEE80211_RATEMASK_54

#define RT2501_RSSI_SAMPLES		15

#define LLC_LENGTH			8
extern const unsigned char eapol_llc[LLC_LENGTH];

void rt2501_switch_channel(unsigned char channel);
int rt2501_set_bssid(const unsigned char *bssid);
void rt2501_make_tx_descriptor(
	PTXD_STRUC txd,
	unsigned char CipherAlg,
	unsigned char KeyTable,
	unsigned char KeyIdx,
	char Ack,
	char Fragment,
	char InsTimestamp,
	unsigned char RetryMode,
	unsigned char Ifs,
	unsigned int Rate,
	unsigned int Length,
	unsigned char QueIdx,
	unsigned char PacketId);
int rt2501_tx(void *buffer, unsigned int length);
int rt2501_beacon(void *buffer, unsigned int length);
int rt2501_set_key(unsigned char index, unsigned char *key, unsigned char *txmic, unsigned char *rxmic, unsigned char cipher);
unsigned short int rt2501_txtime(unsigned int len, unsigned char rate);

void ieee80211_init(void);
void ieee80211_timer(void);
void ieee80211_input(char *frame, unsigned int length, short int rssi);

void eapol_init(void);
void eapol_input(unsigned char *frame, unsigned int length);

void rt2501buffer_init(void);
void rt2501buffer_free(void);
int rt2501buffer_new(const char *data, unsigned int length,
                     const unsigned char *source_mac,
		     const unsigned char *dest_mac);

extern unsigned char rt2501_mac[IEEE80211_ADDR_LEN];

extern int ieee80211_mode;

enum {
	IEEE80211_S_IDLE,  /* disconnected, no operation going on */
	IEEE80211_S_SCAN,  /* scanning */
	IEEE80211_S_AUTH,  /* awaiting authentication reply from AP */
	IEEE80211_S_ASSOC, /* awaiting association reply from AP */
	IEEE80211_S_EAPOL, /* awaiting WPA key exchange */
	IEEE80211_S_RUN,   /* connected or master mode */
};

extern int ieee80211_state;
extern unsigned int ieee80211_timeout;

extern unsigned char ieee80211_assoc_mac[];
extern unsigned char ieee80211_assoc_bssid[];
extern char ieee80211_assoc_ssid[];
extern unsigned char ieee80211_assoc_channel;
extern unsigned short int ieee80211_assoc_rateset;

extern unsigned char ieee80211_authmode;
extern unsigned char ieee80211_encryption;
extern unsigned char ieee80211_key[];

struct ieee80211_sta_state {
	int state;
	unsigned int timer;
	unsigned char mac[IEEE80211_ADDR_LEN];
};

enum {
	EAPOL_S_MSG1,  /* awaiting first message */
	EAPOL_S_MSG3,  /* awaiting third message */
	EAPOL_S_GROUP, /* awaiting group key     */
	EAPOL_S_RUN,
};

extern int eapol_state;
extern unsigned char ptk_tsc[];

#endif /* _RT2501_INTERNAL_H_ */
