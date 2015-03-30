#ifndef _SPI_H_
#define _SPI_H_

#include "ML674061.h"
#include "common.h"

/*************/
/* Functions */
/*************/
void init_spi(void);

void WriteSPI(UBYTE data_out);
UBYTE ReadSPI(void);

void WriteSPI_1(UBYTE data_out);
UBYTE ReadSPI_1(void);

#endif
