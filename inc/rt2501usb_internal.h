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
extern const uint8_t eapol_llc[LLC_LENGTH];

void rt2501_switch_channel(uint8_t channel);
int32_t rt2501_set_bssid(const uint8_t *bssid);
void rt2501_make_tx_descriptor(
	PTXD_STRUC txd,
	uint8_t CipherAlg,
	uint8_t KeyTable,
	uint8_t KeyIdx,
	uint8_t Ack,
	uint8_t Fragment,
	uint8_t InsTimestamp,
	uint8_t RetryMode,
	uint8_t Ifs,
	uint32_t Rate,
	uint32_t Length,
	uint8_t QueIdx,
	uint8_t PacketId);
int32_t rt2501_tx(void *buffer, uint32_t length);
int32_t rt2501_beacon(void *buffer, uint32_t length);
int32_t rt2501_set_key(uint8_t index, uint8_t *key, uint8_t *txmic, uint8_t *rxmic, uint8_t cipher);
uint16_t rt2501_txtime(uint32_t len, uint8_t rate);

void ieee80211_init(void);
void ieee80211_timer(void);
void ieee80211_input(uint8_t *frame, uint32_t length, int16_t rssi);

void eapol_init(void);
void eapol_input(uint8_t *frame, uint32_t length);

void rt2501buffer_init(void);
void rt2501buffer_free(void);
int32_t rt2501buffer_new(const uint8_t *data, uint32_t length,
                     const uint8_t *source_mac,
                     const uint8_t *dest_mac);

extern uint8_t rt2501_mac[IEEE80211_ADDR_LEN];

extern int32_t ieee80211_mode;

enum {
	IEEE80211_S_IDLE,  /* disconnected, no operation going on */
	IEEE80211_S_SCAN,  /* scanning */
	IEEE80211_S_AUTH,  /* awaiting authentication reply from AP */
	IEEE80211_S_ASSOC, /* awaiting association reply from AP */
	IEEE80211_S_EAPOL, /* awaiting WPA key exchange */
	IEEE80211_S_RUN,   /* connected or master mode */
};

extern int32_t ieee80211_state;
extern uint32_t ieee80211_timeout;

extern uint8_t ieee80211_assoc_mac[];
extern uint8_t ieee80211_assoc_bssid[];
extern uint8_t ieee80211_assoc_ssid[];
extern uint8_t ieee80211_assoc_channel;
extern uint16_t ieee80211_assoc_rateset;

extern uint8_t ieee80211_authmode;
extern uint8_t ieee80211_encryption;
extern uint8_t ieee80211_key[];

struct ieee80211_sta_state {
	int32_t state;
	uint32_t timer;
	uint8_t mac[IEEE80211_ADDR_LEN];
};

typedef enum {
	EAPOL_S_MSG1,  /* awaiting first message */
	EAPOL_S_MSG3,  /* awaiting third message */
	EAPOL_S_GROUP, /* awaiting group key     */
	EAPOL_S_RUN,
} eapol_state_t;

extern eapol_state_t eapol_state;
extern uint8_t ptk_tsc[];

#endif /* _RT2501_INTERNAL_H_ */
