/*
 * Ralink RT2501 driver for Violet embedded platforms
 * (c) 2006 Sebastien Bourdeauducq
 *
 * RedoX <dev@redox.ws> - 2015 - GCC Port
*/

#include "common.h"
#include "usbh.h"

#include "rt2501usb_hw.h"
#include "rt2501usb_io.h"

uint32_t rt2501_read(PDEVINFO dev, uint16_t reg)
{
	uint32_t val;
	int8_t ret;

	ret = usbh_control_transfer(dev,
				 0,				/* pipe */
				 RT2501_READMULTIMAC,		/* bRequest */
				 USB_TYPE_VENDOR|USB_DIR_IN,	/* bmRequestType */
				 0,				/* wValue */
				 reg,				/* wIndex */
				 sizeof(val),			/* wLength */
				 &val);
	if(ret != sizeof(val)) return 0;
	return val;
}

uint8_t rt2501_write(PDEVINFO dev, uint16_t reg, uint32_t val)
{
	int8_t ret;

	ret = usbh_control_transfer(dev,
				 0,				/* pipe */
				 RT2501_WRITEMULTIMAC,		/* bRequest */
				 USB_TYPE_VENDOR|USB_DIR_OUT,	/* bmRequestType */
				 0,				/* wValue */
				 reg,				/* wIndex */
				 sizeof(val),			/* wLength */
				 &val);
	return (ret == sizeof(val));
}

uint8_t rt2501_read_eeprom(PDEVINFO dev, uint16_t address, void *buf, uint16_t len)
{
	int8_t ret;

	ret = usbh_control_transfer(dev,
				 0,				/* pipe */
				 RT2501_READEEPROM,		/* bRequest */
				 USB_TYPE_VENDOR|USB_DIR_IN,	/* bmRequestType */
				 0,				/* wValue */
				 address,			/* wIndex */
				 len,				/* wLength */
				 buf);
	return (ret == len);
}

uint8_t rt2501_read_bbp(PDEVINFO dev, uint8_t reg)
{
	PHY_CSR3_STRUC csr;

	/* Wait until busy flag clears */
	do {
		csr.word = rt2501_read(dev, RT2501_PHY_CSR3);
	} while(csr.field.Busy);

	/* Write register address */
	csr.word = 0;
	csr.field.fRead = 1;
	csr.field.RegNum = reg;
	csr.field.Busy = 1;
	rt2501_write(dev, RT2501_PHY_CSR3, csr.word);

	/* Wait until busy flag clears, then we have the read value */
	do {
		csr.word = rt2501_read(dev, RT2501_PHY_CSR3);
	} while(csr.field.Busy);

	csr.word = rt2501_read(dev, RT2501_PHY_CSR3);

	return (csr.field.Value);
}

uint8_t rt2501_write_bbp(PDEVINFO dev, uint8_t reg, uint8_t val)
{
	PHY_CSR3_STRUC csr;

	/* Wait until busy flag clears */
	do {
		csr.word = rt2501_read(dev, RT2501_PHY_CSR3);
	} while(csr.field.Busy);

	/* Write address and data */
	csr.word = 0;
	csr.field.RegNum = reg;
	csr.field.Value = val;
	csr.field.Busy = 1;
	if(!rt2501_write(dev, RT2501_PHY_CSR3, csr.word)) return 0;
	return 1;
}

uint8_t rt2501_write_rf(PDEVINFO dev, uint32_t val)
{
	PHY_CSR4_STRUC	csr;

	/* Wait until busy flag clears */
	do {
		csr.word = rt2501_read(dev, RT2501_PHY_CSR4);
	} while(csr.field.Busy);

	/* Write value */
	if(!rt2501_write(dev, RT2501_PHY_CSR4, val)) return 0;

	return 1;
}
