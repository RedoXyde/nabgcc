#ifndef _MEM_H_
#define _MEM_H_

#include "ML674061.h"
#include "common.h"

//#define SRAM_BASE   (0xD0000000)    /* base address of external SRAM */
#define SRAM_BASE   (0xD0010000)    /* base address of external SRAM */

/* Memory shared between ARM and USB chips */
/* The allocator is set up in hcd.c, not here */
#define COMRAM 0

/* Memory on the ARM chip */
#define EXTRAM 1
#define EXTRAM_ADDR 0xD0008000
#define EXTRAM_SIZE 0x7FFF


void setup_ext_sram_rom(void);
void setup_malloc(void);
void read_uc_flash(uint address, uchar *data, uint nb_byte);
__ramfunc void init_uc_flash(void);
__ramfunc void write_uc_flash(uint address, uchar *data, uint nb_byte, uchar *temp);
__ramfunc void flash_uc(uchar *data, int nb_byte, uchar *temp);
void reset_uc(void);

#endif
