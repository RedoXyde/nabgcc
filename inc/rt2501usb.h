/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _RT2501_H_
#define _RT2501_H_

#include "rt2501usb_hw.h"
#include "ieee80211.h"

extern const uint8_t ieee80211_broadcast_address[IEEE80211_ADDR_LEN];
extern const uint8_t ieee80211_null_address[IEEE80211_ADDR_LEN];

enum {
	IEEE80211_M_MANAGED,
	IEEE80211_M_MASTER,
};

enum {
	IEEE80211_CRYPT_NONE,
	IEEE80211_CRYPT_WEP64,
	IEEE80211_CRYPT_WEP128,
	IEEE80211_CRYPT_WPA,
	IEEE80211_CRYPT_WPA_UNSUPPORTED,
};

enum {
	IEEE80211_AUTH_OPEN,
	IEEE80211_AUTH_SHARED,
};

enum {
	RT2501_S_BROKEN,
	RT2501_S_IDLE,
	RT2501_S_SCAN,
	RT2501_S_CONNECTING,
	RT2501_S_CONNECTED,
	RT2501_S_MASTER,
};

struct rt2501_scan_result {
	uint8_t ssid[IEEE80211_SSID_MAXLEN+1];
	uint8_t mac[IEEE80211_ADDR_LEN];
	uint8_t bssid[IEEE80211_ADDR_LEN];
	int16_t rssi;
	uint8_t channel;
	uint16_t rateset;
	uint8_t encryption;
};

typedef void (*rt2501_scan_callback)(struct rt2501_scan_result *, void *);

struct rt2501buffer {
	struct rt2501buffer *next;			/* driver internal use             */
	uint32_t length;				/* length of the data              */
	uint8_t source_mac[IEEE80211_ADDR_LEN];	/* MAC address of the source       */
	uint8_t dest_mac[IEEE80211_ADDR_LEN];	/* MAC address of the destination  */
	uint8_t data[];				/* ethernet frame, starting at LLC */
};

int32_t rt2501_driver_install(void);
int32_t rt2501_state(void);
int32_t rt2501_rssi_average(void);
/* 100ms (approx.) timer. Must not be called in interrupt context. */
void rt2501_timer(void);
/* Must not be called in interrupt context */
void rt2501_setmode(int32_t mode, const uint8_t *ssid, uint8_t channel);
/* Must not be called in interrupt context */
void rt2501_scan(const uint8_t *ssid, rt2501_scan_callback callback, void *userparam);
/* Must not be called in interrupt context */
void rt2501_auth(const uint8_t *ssid, const uint8_t *mac,
		 const uint8_t *bssid, uint8_t channel,
		 uint16_t rateset,
		 uint8_t authmode,
		 uint8_t encryption,
		 const uint8_t *key);
/* Must not be called in interrupt context */
struct rt2501buffer *rt2501_receive(void);
/* Must not be called in interrupt context if mayblock=1 */
int32_t rt2501_send(const uint8_t *frame, uint32_t length, const uint8_t *dest_mac,
		int32_t lowrate, int32_t mayblock);

#endif /* _RT2501_H_ */
