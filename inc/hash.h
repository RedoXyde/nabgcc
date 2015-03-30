/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _HASH_H_
#define _HASH_H_

void hmac_md5(const unsigned char *key, unsigned int key_len, const unsigned char *data, unsigned int data_len, unsigned char *mac);
void hmac_sha1(const unsigned char *key, unsigned int key_len, const unsigned char *data, unsigned int data_len, unsigned char *mac);

#endif /* _HASH_H_ */
