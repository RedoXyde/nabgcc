/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#ifndef __RT2501_IO_H
#define __RT2501_IO_H

unsigned int rt2501_read(PDEVINFO dev, short unsigned int reg);
int rt2501_write(PDEVINFO dev, short unsigned int reg, unsigned int val);
int rt2501_read_eeprom(PDEVINFO dev, short int address, void *buf, int len);
unsigned char rt2501_read_bbp(PDEVINFO dev, unsigned char reg);
int rt2501_write_bbp(PDEVINFO dev, unsigned char reg, unsigned char val);
int rt2501_write_rf(PDEVINFO dev, unsigned int val);

#endif /* __RT2501_IO_H */
