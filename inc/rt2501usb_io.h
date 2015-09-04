/*
 * Ralink RT2501 driver for Violet embedded platforms
 * (c) 2006 Sebastien Bourdeauducq
 *
 * RedoX <dev@redox.ws> - 2015 - GCC port
*/

#ifndef __RT2501_IO_H
#define __RT2501_IO_H

uint32_t rt2501_read(PDEVINFO dev, uint16_t reg);
uint8_t rt2501_write(PDEVINFO dev, uint16_t reg, uint32_t val);
uint8_t rt2501_read_eeprom(PDEVINFO dev, uint16_t address, void *buf, uint16_t len);
uint8_t rt2501_read_bbp(PDEVINFO dev, uint8_t reg);
uint8_t rt2501_write_bbp(PDEVINFO dev, uint8_t reg, uint8_t val);
uint8_t rt2501_write_rf(PDEVINFO dev, uint32_t val);

#endif /* __RT2501_IO_H */
