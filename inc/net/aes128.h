/**
 * @file aes128.h
 * @author RedoX <dev@redox.ws> - 2017
 * @date 2017/02/02
 * @brief RT2501 Wifi/Network driver
 */
#ifndef _AES128_H_
#define _AES128_H_

#include <stdint.h>

/*
 * AES-128, decrypt direction only (what RFC 3394 key unwrap needs; the
 * CCMP data path is done by the RT2573 hardware). Byte-oriented, two
 * 256-byte tables, no encrypt side: flash is the scarce resource here.
 * Wired into eapol.c: message 3/4 and group rekeys unwrap the GTK
 * through aes_key_unwrap + rsn_find_gtk.
 */

struct aes128_dec {
	uint8_t rk[176];  /* 11 round keys of 16 bytes, forward order */
};

/** @brief Expand a 16-byte key into the decryption round keys */
void aes128_dec_init(struct aes128_dec *ctx, const uint8_t key[16]);

/** @brief Decrypt one 16-byte block (FIPS-197 inverse cipher) */
void aes128_dec_block(const struct aes128_dec *ctx,
                      uint8_t out[16], const uint8_t in[16]);

/**
 * @brief RFC 3394 AES Key Wrap: unwrap with a 128-bit KEK
 *
 * @param [in]  kek      16-byte key encryption key (the EAPOL KEK)
 * @param [in]  wrapped  Wrapped key data, 8*(n+1) bytes, n >= 2
 * @param [in]  wlen     Length of wrapped in bytes
 * @param [out] out      Unwrapped key data, 8*n bytes
 * @return 1 if the integrity check value matched, 0 otherwise;
 *         on 0 the contents of out must not be used
 */
int32_t aes_key_unwrap(const uint8_t kek[16], const uint8_t *wrapped,
                       uint32_t wlen, uint8_t *out);

/**
 * @brief Find the GTK inside decrypted WPA2 Key Data (RSN KDE list)
 *
 * Key Data is a sequence of KDEs: type 0xDD, length, OUI 00-0F-AC,
 * data type 1 for the GTK, then a two-byte header (key id in bits 0-1
 * of the first byte) followed by the key itself. Pad KDEs (type 0xDD
 * with length 0) and IEs of other types are skipped.
 *
 * @param [in]  data     Decrypted key data
 * @param [in]  len      Length of data in bytes
 * @param [out] gtk      Receives the group key
 * @param [in]  gtk_max  Capacity of gtk in bytes
 * @param [out] gtk_len  Receives the key length actually found
 * @param [out] key_id   Receives the key index the AP assigned
 * @return 1 if a GTK KDE was found and fits, 0 otherwise
 */
int32_t rsn_find_gtk(const uint8_t *data, uint32_t len,
                     uint8_t *gtk, uint32_t gtk_max,
                     uint32_t *gtk_len, uint8_t *key_id);

#endif /* _aes128_H_ */
