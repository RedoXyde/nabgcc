/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _RT2501_H_
#define _RT2501_H_

#include "rt2501usb_hw.h"
#include "ieee80211.h"

extern const unsigned char ieee80211_broadcast_address[IEEE80211_ADDR_LEN];
extern const unsigned char ieee80211_null_address[IEEE80211_ADDR_LEN];

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
	char ssid[IEEE80211_SSID_MAXLEN+1];
	unsigned char mac[IEEE80211_ADDR_LEN];
	unsigned char bssid[IEEE80211_ADDR_LEN];
	short int rssi;
	unsigned char channel;
	unsigned short int rateset;
	unsigned char encryption;
};

typedef void (*rt2501_scan_callback)(struct rt2501_scan_result *, void *);

struct rt2501buffer {
	struct rt2501buffer *next;			/* driver internal use             */
	unsigned int length;				/* length of the data              */
	unsigned char source_mac[IEEE80211_ADDR_LEN];	/* MAC address of the source       */
	unsigned char dest_mac[IEEE80211_ADDR_LEN];	/* MAC address of the destination  */
	unsigned char data[];				/* ethernet frame, starting at LLC */
};

int rt2501_driver_install(void);
int rt2501_state(void);
int rt2501_rssi_average(void);
/* 100ms (approx.) timer. Must not be called in interrupt context. */
void rt2501_timer(void);
/* Must not be called in interrupt context */
void rt2501_setmode(int mode, const char *ssid, unsigned char channel);
/* Must not be called in interrupt context */
void rt2501_scan(const char *ssid, rt2501_scan_callback callback, void *userparam);
/* Must not be called in interrupt context */
void rt2501_auth(const char *ssid, const unsigned char *mac,
		 const unsigned char *bssid, unsigned char channel,
		 unsigned short int rateset,
		 unsigned char authmode,
		 unsigned char encryption,
		 const unsigned char *key);
/* Must not be called in interrupt context */
struct rt2501buffer *rt2501_receive(void);
/* Must not be called in interrupt context if mayblock=1 */
int rt2501_send(const unsigned char *frame, unsigned int length, const unsigned char *dest_mac,
		int lowrate, int mayblock);

#endif /* _RT2501_H_ */
