#include "ML674061.h"
#include "common.h"
#include "audio.h"
#include "spi.h"
#include "delay.h"
#include "inarm.h"
#include "led.h"
#include "uart.h"


#if (PCB_RELEASE == LLC2_3) || (PCB_RELEASE == LLC2_4c)

#ifdef SINUS_TEST                    //SDI tests allowed
#define VS1003_MODE_VALUE_L (SM_TESTS)
#else
#define VS1003_MODE_VALUE_L (0x00)
#endif
#define VS1003_MODE_VALUE_H (SM_SDISHARE | SM_SDINEW) //VS1002 native SPI mode active

#elif PCB_RELEASE == LLC2_2

#ifdef SINUS_TEST                    //SDI tests allowed
#define VS1003_MODE_VALUE_L (SM_TESTS | SM_DIFF)
#else
#define VS1003_MODE_VALUE_L (SM_DIFF)
#endif
#define VS1003_MODE_VALUE_H (SM_SDINEW) //VS1002 native SPI mode active

#endif

/****************************************************************************/
/*  Analog to digital conversion of channel #2                              */
/*  Function : get_adc_value                                                */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   return of the ADC result of channel #2 in 8bits     */
/****************************************************************************/
uchar get_adc_value(void)
{
  ushort adc_result;
  //Start ADC for channel #2
  set_hbit(ADCON1, ADCON1_STS | ADCON1_CH2);
  //Wait for the ADC to be done
  while(get_hvalue(ADCON1) & ADCON1_STS);
  //Return the ADC in a 8bits result
  adc_result=get_hvalue(ADR2);
  return (uchar)(adc_result>>2);
}

ushort vlsi_read_sci(uchar reg)
{
    ushort received_short;
    while( !(INT_AUDIO_READ & INT_AUDIO_BIT) ) CLR_WDT;
    CS_AUDIO_SCI_CLEAR;
    WriteSPI(VS1003_READ);
    WriteSPI(reg);
  //Clear reception buffer
    while( get_wvalue(SPSR0) & SPSR0_RFD ) get_value(SPDRR0);
    received_short = ReadSPI()<<8;
    received_short += ReadSPI();
    CS_AUDIO_SCI_SET;
    return received_short;
}

void vlsi_write_sci(uchar reg,ushort val)
{
  while( !(INT_AUDIO_READ & INT_AUDIO_BIT) ) CLR_WDT;
  CS_AUDIO_SCI_CLEAR;
  WriteSPI(VS1003_WRITE);
  WriteSPI(reg);
  WriteSPI(val>>8);
  WriteSPI(val);
  CS_AUDIO_SCI_SET;
}

int vlsi_feed_sdi(uchar* data,int len)
{
  int i=0;
  CS_AUDIO_SDI_CLEAR;
  while((i<len)&&(INT_AUDIO_READ & INT_AUDIO_BIT)) WriteSPI(data[i++]);
  CS_AUDIO_SDI_SET;
  return i;
}

int vlsi_fifo_ready()
{
  if (INT_AUDIO_READ & INT_AUDIO_BIT) return 1;
  return 0;
}

void vlsi_ampli(int on)
{
  if (on)
  {
    TURN_ON_AUDIO_AMPLIFIER;
  }
  else
  {
    TURN_OFF_AUDIO_AMPLIFIER;
  }
}

#define patchwma_len 10
const int patchwma_data[patchwma_len]=
{
0x0207800e,0x02062801,0x02063f80,0x02060006,0x020653d7,
0x020784fe,0x02062000,0x02060000,0x02063f05,0x0206c024
};

void patchwma()
{
  for(int i=0;i<patchwma_len;i++)
  {
    int k=patchwma_data[i];
    vlsi_write_sci(k>>16,k);
  }
}
/****************************************************************************/
/*  Init VLSI peripheral                                                    */
/*  Function : init_vlsi                                                    */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void init_vlsi(void)
{
  //Set SPI0 to low speed before initialising PLL of VS1003 => 2.11MHz max
  //SPI0 baudrate = APB_CLK/16 => 2MHz @ 32MHz
  clr_wbit(SPCR0,SPCR0_SPE);
  put_wvalue(SPBRR0,0x00000008);
  set_wbit(SPCR0,SPCR0_SPE);

  //Set VS1003
  RST_AUDIO_CLEAR;
  DelayMs(1);
  RST_AUDIO_SET;
  DelayMs(1);

//Update CLKI of VS 1003 from 12.688MHz to 12.688MHZ x 4 = 49.152MHz
//So SCI write and SDI can be up to 49.152MHz/4 = 12.288MHZ
//So SCI read can be up to 49.152MHz/6 = 8.192MHZ

//  vlsi_write_sci(VS1003_CLOCKF,0xc430);
  vlsi_write_sci(VS1003_CLOCKF,0xc000);

  //Set SPI0 to low speed before initialising PLL of VS1003 => 8.458MHz max
  //SPI0 baudrate = APB_CLK/4 => 8MHz @ 32MHz
  clr_wbit(SPCR0,SPCR0_SPE);
  put_wvalue(SPBRR0,0x00000002);
  set_wbit(SPCR0,SPCR0_SPE);

//Config MODE
  vlsi_write_sci(VS1003_MODE,(VS1003_MODE_VALUE_H<<8)|VS1003_MODE_VALUE_L | SM_RESET);

//Config VOLUME
  vlsi_write_sci(VS1003_VOLUME,0xffff);

  patchwma();
}

/****************************************************************************/
/*  Set configuration for adpcm encoding                                    */
/*  Function : init_adpcm_encode                                            */
/*      Parameters                                                          */
/*          Input   :   sampling frequency in Hz on 16bits, up to 48kHz     */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void init_adpcm_encode(ushort sampling_frequency,ushort gain)
{
  ushort config_frequency;

//Sampling frequency up to 48kHz
//XTALI id 12.288MHz x 4 = 49.152MHz and /256 => 192000
  config_frequency=(ushort)(192000/sampling_frequency);

//Config Sampling frequency
  vlsi_write_sci(VS1003_AICTRL0,config_frequency);

//Config Automatic Gain Control
  vlsi_write_sci(VS1003_AICTRL1,gain);

//Config MODE
  vlsi_write_sci(VS1003_MODE,((VS1003_MODE_VALUE_H | SM_ADPCM_HP | SM_ADPCM)<<8)|VS1003_MODE_VALUE_L | SM_RESET);
}

/****************************************************************************/
/*  Close adpcm mode                                                        */
/*  Function : stop_adpcm_encode                                            */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void stop_adpcm_encode(void)
{
//Config MODE
  vlsi_write_sci(VS1003_MODE,((VS1003_MODE_VALUE_H)<<8)|VS1003_MODE_VALUE_L | SM_RESET);
}



/****************************************************************************/
/*  Set output volume of the VLSI                                           */
/*  Function : set_vlsi_volume                                              */
/*      Parameters                                                          */
/*          Input   :   volume on 8bits ; the maximum is 0x00               */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void set_vlsi_volume(uchar volume)
{
//Config VOLUME
  vlsi_write_sci(VS1003_VOLUME,(volume<<8)|volume);
  if (volume>=0x7f)TURN_OFF_AUDIO_AMPLIFIER;
  else TURN_ON_AUDIO_AMPLIFIER;

}


int audioPlayFetch(char* dst,int ask);
char* audioRecFeed_begin(int size);
void audioRecFeed_end();

uchar play_state=0;

uchar rec_state=0;

void rec_start(int sampling_frequency,int gain)
{
  if (play_state) return;
  putst_uart("rec_start\n");
  clear_vlsi_fifo();
  TURN_OFF_AUDIO_AMPLIFIER;
  init_adpcm_encode(sampling_frequency,gain);
  rec_state=1;
}

void rec_stop()
{
  if (!rec_state) return;
  putst_uart("rec_stop\n");
  stop_adpcm_encode();
  TURN_OFF_AUDIO_AMPLIFIER;
  clear_vlsi_fifo();
  rec_state=0;
}

void rec_check()
{
  short received_short;
  if (!rec_state) return;
  //each audio block is 256bytes long, but the buffer fill information is
  //in 16bits word information
//putst_uart("r");
  received_short=vlsi_read_sci(VS1003_HDAT1);

  //putint_uart(received_short);

      received_short&=0xff80;
      if (received_short)
      {
        short val;
        char* dst=audioRecFeed_begin(received_short<<1);
        if (dst)
          while(received_short--)
          {
            val=vlsi_read_sci(VS1003_HDAT0);
            *(dst++)=val>>8;
            *(dst++)=val;
          }
        audioRecFeed_end();
      }
}

int valtrytofeed=2048;

void play_start(int trytofeed)
{
  if (rec_state) return;
  putst_uart("play_start\n");
  clear_vlsi_fifo();
  patchwma();

  if (trytofeed<=0) trytofeed=1024;
  valtrytofeed=trytofeed;
  TURN_ON_AUDIO_AMPLIFIER;
  play_state=1;
}

void play_stop()
{
  if (!play_state) return;
  putst_uart("play_stop\n");
  TURN_OFF_AUDIO_AMPLIFIER;
  clear_vlsi_fifo();
  play_state=0;
}

#include"hcd.h"
int audioPlayTryFeed(int ask);
int audioPlayFetchByte();

void play_check(int nocb)
{
  int empty=0;
  int nb=0;

  if (!play_state) return;
//putst_uart("<");

 if ( !(INT_AUDIO_READ & INT_AUDIO_BIT) ) return;  // buffer occupé

if (!nocb) nocb=1-audioPlayTryFeed(valtrytofeed);

disable_ohci_irq();

  // au moins 32 octets dispos

  while((INT_AUDIO_READ & INT_AUDIO_BIT)&& (!empty))
  {
    CLR_WDT;
    int val=audioPlayFetchByte();
    if ((val<0)&&(nb+nb>=valtrytofeed)&&(!nocb))
    {
      nocb=1-audioPlayTryFeed(valtrytofeed);
      audioPlayTryFeed(valtrytofeed);
      val=audioPlayFetchByte();
    }
    if (val>=0)
    {
      nb++;
  CS_AUDIO_SDI_CLEAR;
      WriteSPI(val);
  CS_AUDIO_SDI_SET;
    }
    else
    {
      empty=1;
      if (play_state==2) play_state=0;
    }
  }
//  putst_uart(":");  putint_uart(nb);
enable_ohci_irq();

}

void play_eof()
{
  if (play_state==1) play_state=2;
}

/****************************************************************************/
/*  Clear the VLSI input FIFO to be ready for a new file to be played       */
/*  Function : clear_vlsi_fifo                                              */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void clear_vlsi_fifo(void)
{
  putst_uart("clear_vlsi_fifo\n");
//Config MODE
  vlsi_write_sci(VS1003_MODE,(VS1003_MODE_VALUE_H<<8)|VS1003_MODE_VALUE_L | SM_RESET);
//  vlsi_write_sci(VS1003_MODE,0x0805);
}


/****************************************************************************/
/*  Software reset of VS1003                                                */
/*  Function : sw_reset_vlsi                                                */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void sw_reset_vlsi(void)
{
//Config MODE
  vlsi_write_sci(VS1003_MODE,(VS1003_MODE_VALUE_H<<8)|VS1003_MODE_VALUE_L | SM_RESET);
}

/****************************************************************************/
/*  Check the audio file specs which is played                              */
/*  Function : check_audio_file                                             */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   return of HDAT1 and HDAT0                           */
/****************************************************************************/
ulong check_audio_file(void)
{
  ulong file_state=0x00000000;

  file_state=vlsi_read_sci(VS1003_HDAT1)<<16;
  file_state|=vlsi_read_sci(VS1003_HDAT0)&0xffff;

  return file_state;
}

/****************************************************************************/
/*  Check the number of seconds of data decoded                             */
/*  Function : check_decode_time                                            */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   return the number of seconds decoded                */
/****************************************************************************/
ushort check_decode_time(void)
{
  return vlsi_read_sci(VS1003_DECODE_TIME);
}


