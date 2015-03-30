/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#include <stdio.h>
#include "ML674061.h"
#include "common.h"
#include "hcd.h"
#include "usbctrl.h"
#include "usbh.h"
#include "ml60842.h"
#include "delay.h"
#include "debug.h"

#include "rt2501usb_hw.h"
#include "rt2501usb_io.h"

unsigned int rt2501_read(PDEVINFO dev, short unsigned int reg)
{
	unsigned int val;
	int ret;

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

int rt2501_write(PDEVINFO dev, short unsigned int reg, unsigned int val)
{
	int ret;

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

int rt2501_read_eeprom(PDEVINFO dev, short int address, void *buf, int len)
{
	int ret;

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

unsigned char rt2501_read_bbp(PDEVINFO dev, unsigned char reg)
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

int rt2501_write_bbp(PDEVINFO dev, unsigned char reg, unsigned char val)
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

int rt2501_write_rf(PDEVINFO dev, unsigned int val)
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
