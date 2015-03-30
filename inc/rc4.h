/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef _RC4_H
#define _RC4_H_

struct rc4_context {
	unsigned int x;
	unsigned int y;
	unsigned char state[256];
};

void rc4_init(struct rc4_context *rc4, const unsigned char *key, unsigned int length);
unsigned char rc4_byte(struct rc4_context *rc4);
void rc4_cipher(struct rc4_context *rc4, unsigned char *out, 
		const unsigned char *in, unsigned int length);

#endif /* _RC4_H_ */
