#ifndef _SPI_H_
#define _SPI_H_

#include "ml674061.h"
#include "common.h"

/*************/
/* Functions */
/*************/
void init_spi(void);

void WriteSPI(uint8_t data_out);
uint8_t ReadSPI(void);

void WriteSPI_1(uint8_t data_out);
uint8_t ReadSPI_1(void);

#endif
