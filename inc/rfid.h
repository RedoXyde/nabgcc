#ifndef _RFID_H_
#define _RFID_H_

#include "ML674061.h"
#include "common.h"
#include "rfid.h"

/********************/
/* SPECIFIC DEFINES */
/********************/
#define CRX14_PARAMETER_REGISTER      0x00
#define CRX14_IO_FRAME_REGISTER       0x01
#define CRX14_AUTHENTICATE_REGISTER   0x02
#define CRX14_SLOT_MARKER_REGISTER    0x03

#define SR176_CHIP_ID      0x00
#define SRI4K_CHIP_ID      0x00
#define SRIX4K_CHIP_ID     0x00
#define SRIX512_CHIP_ID    0x00

struct _tag_rfid
{
  uchar CHIP_ID;
  uchar UID[8];
};

/*************/
/* Functions */
/*************/
uchar init_rfid(void);
uchar close_rfid(void);
uchar initiate_rfid(void);
uchar slot_marker_rfid(void);
uchar select_tag_rfid(uchar chip_id);
uchar read_frame_rfid(uchar *data, uchar nb_bytes);
uchar completion_rfid(void);
uchar get_uid_rfid(void);
uchar check_rfid_devices(struct _tag_rfid *p_tag_rfid);
void write_eeprom_rfid(uchar chip_id, uchar num_block, uchar *data, uchar num_bytes);
void read_eeprom_rfid(uchar chip_id, uchar num_block, uchar *data, uchar num_bytes);

char* get_rfid_first_device();

#endif
