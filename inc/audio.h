#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "ML674061.h"
#include "common.h"

/*******************/
/* VS1003 commands */
/*******************/
#define VS1003_READ		(0x03)
#define VS1003_WRITE		(0x02)

/********************/
/* VS1003 registers */
/********************/
#define VS1003_MODE		(0x00)
#define VS1003_STATUS		(0x01)
#define VS1003_BASS		(0x02)
#define VS1003_CLOCKF		(0x03)
#define VS1003_DECODE_TIME	(0x04)
#define VS1003_AUDATA		(0x05)
#define VS1003_WRAM		(0x06)
#define VS1003_WRAM_ADDR	(0x07)
#define VS1003_HDAT0		(0x08)
#define VS1003_HDAT1		(0x09)
#define VS1003_AIADDR		(0x0A)
#define VS1003_VOLUME		(0x0B)
#define VS1003_AICTRL0		(0x0C)
#define VS1003_AICTRL1		(0x0D)
#define VS1003_AICTRL2		(0x0E)
#define VS1003_AICTRL3		(0x0F)

#define SM_DIFF               0x01
#define SM_SETTOZERO          0x02
#define SM_RESET              0x04
#define SM_OUTOFWAV           0x08
#define SM_PDOWN              0x10
#define SM_TESTS              0x20
#define SM_STREAM             0x40
#define SM_SETTOZERO2         0x80
#define SM_DACT               0x01
#define SM_SDIORD             0x02
#define SM_SDISHARE           0x04
#define SM_SDINEW             0x08
#define SM_ADPCM              0x10
#define SM_ADPCM_HP           0x20
#define SM_LINE_IN            0x40

/*************/
/* Functions */
/*************/
uchar get_adc_value(void);
void init_vlsi(void);
void init_adpcm_encode(ushort sampling_frequency,ushort gain);
void stop_adpcm_encode(void);
void add_riff_header(uchar *data, ushort cmpt_audio_block, ushort sampling_frequency);
void encode_adpcm(uchar *data, ushort cmpt_audio_block, ushort sampling_frequency);
void set_vlsi_volume(uchar volume);
void clear_vlsi_fifo(void);
ulong check_audio_file(void);
ushort check_decode_time(void);
void config_bass(uint config_value);
void sw_reset_vlsi(void);
uchar* stop_decoding(uchar *addr_mem);
void play_audio(uchar *addr_mem, ulong nb_byte_to_play);

void play_start(int trytofeed);
void play_stop();
void play_check(int nocb);
void play_eof();
void rec_start(int sampling_frequency,int gain);
void rec_stop();
void rec_check();

ushort vlsi_read_sci(uchar reg);
void vlsi_write_sci(uchar reg,ushort val);
int vlsi_feed_sdi(uchar* data,int len);
int vlsi_fifo_ready();
void vlsi_ampli(int on);

int push_button_value();


#endif
