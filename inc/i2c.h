#ifndef _I2C_H_
#define _I2C_H_

#include "ML674061.h"
#include "common.h"

/***************/
/* I2C address */
/***************/
#define CRX14_ADDR		0xA0

/********************/
/* SPECIFIC DEFINES */
/********************/
#define I2C_WRITE_INSTR		0x00
#define I2C_READ_INSTR		0x01

#define CRX14_PARAMETER_REGISTER      0x00
#define CRX14_IO_FRAME_REGISTER       0x01
#define CRX14_AUTHENTICATE_REGISTER   0x02
#define CRX14_SLOT_MARKER_REGISTER    0x03

/*************/
/* Functions */
/*************/
void init_i2c(void);
uchar write_i2c(uchar addr_i2c, uchar *data, uchar nb_byte);
uchar read_i2c(uchar addr_i2c, uchar *data, uchar nb_byte);

#endif
