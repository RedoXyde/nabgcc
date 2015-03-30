/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _HASH_H_
#define _HASH_H_

void hmac_md5(const uint8_t *key, uint32_t key_len, const uint8_t *data, uint32_t data_len, uint8_t *mac);
void hmac_sha1(const uint8_t *key, uint32_t key_len, const uint8_t *data, uint32_t data_len, uint8_t *mac);

#endif /* _HASH_H_ */
