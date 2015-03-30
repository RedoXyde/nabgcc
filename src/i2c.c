#include "ML674061.h"
#include "common.h"
#include "i2c.h"
#include "delay.h"

#include"hcd.h"

int waiti2cmbb()
{
  int nmax=1000000;
  while((get_hvalue(I2CSR)&I2CSR_I2CMBB)&&(nmax>0)) nmax--;
  return nmax;
}

int waiti2cmcf()
{
  int nmax=1000000;
  while((!(get_hvalue(I2CSR)&I2CSR_I2CMCF))&&(nmax>0)) nmax--;
  return nmax;
}

/****************************************************************************/
/*  Initialization of the I2C peripheral                                    */
/*  Function : init_i2c                                                     */
/*      Parameters                                                          */
/*          Input   :   Nothing                                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
void init_i2c(void)
{
  //Set secondary function for PB4 and PB5  => I2C bus : SCL + SDA
  set_wbit(PORTSEL1,0x05000000);

  //I2C peripheral select
  set_hbit(I2CCTL,I2CCTL_I2CMEN);

  //I2C slave address
  put_hvalue(I2CSADR,0x0000);

  //I2C bus speed
  put_hvalue(I2CBC,0x0028);   //100kHz @32MHz
    //I2CBC = (APB_CLK)/( I2C bus speed x 8)

  //I2C control register
  put_hvalue(I2CCTL,0x0080);
    //I2CCS=0
    //enable I2C module
    //selects standard mode 100kHz

}


/****************************************************************************/
/*  Write to an I2C peripheral                                              */
/*  Function : write_i2c                                                    */
/*      Parameters                                                          */
/*          Input   :   Slave address of the I2C peripheral                 */
/*          Input   :   Pointer to the buffer to send                       */
/*          Input   :   number of bytes to send                             */
/*          Output  :   Nothing                                             */
/****************************************************************************/
uint8_t write_i2c(uint8_t addr_i2c, uint8_t *data, uint8_t nb_byte)
{
    __disable_interrupt();

  //Transmitted by master
  set_hbit(I2CCTL,I2CCTL_I2CMTX);
  //Continues clock upon completion
//  clr_hbit(I2CCTL,I2CCTL_I2CCS);
  //wait for I2C bus to be ready
  if (!waiti2cmbb())
  {
  __enable_interrupt();
    return FALSE;
  }

/********************/
/* Send I2C address */
/********************/
  //Write slave address
  put_hvalue(I2CDR,(addr_i2c|I2C_WRITE_INSTR));
  //Start condition
  set_hbit(I2CCTL,I2CCTL_I2CMSTA);
  //Look at arbitration
  if((get_hvalue(I2CSR)&I2CSR_I2CMAL))
  {
    //Clear status
    put_hvalue(I2CSR,0x0000);
  __enable_interrupt();
    return FALSE;
  }
  //wait for transfer to be completed
  if (!waiti2cmcf())
  {
  __enable_interrupt();
    return FALSE;
  }
  //Look at acknowledge
  if((get_hvalue(I2CSR)&I2CSR_I2CRXAK))
  {
    //Stop condition
    clr_hbit(I2CCTL,I2CCTL_I2CMSTA);
    //Clear status
    put_hvalue(I2CSR,0x0000);
  __enable_interrupt();
    return FALSE;
  }

/*****************/
/* Send I2C data */
/*****************/
  //Clear status
  put_hvalue(I2CSR,0x0000);
  while(nb_byte--)
  {
    //Write data
    put_hvalue(I2CDR,*(data++));
    //wait for transfer to be completed
    if (!waiti2cmcf())
    {
    __enable_interrupt();
      return FALSE;
    }
    //Look at acknowledge
    if((get_hvalue(I2CSR)&I2CSR_I2CRXAK))
    {
      //Stop condition
      clr_hbit(I2CCTL,I2CCTL_I2CMSTA);
      //Clear status
      put_hvalue(I2CSR,0x0000);
  __enable_interrupt();
      return FALSE;
    }
    //Clear  completion bit
    clr_hbit(I2CSR,I2CSR_I2CMCF);
  }

/*************/
/* Stop I2C  */
/*************/
  //Clear status
  put_hvalue(I2CSR,0x0000);
  //Stop condition
  clr_hbit(I2CCTL,I2CCTL_I2CMSTA);

  __enable_interrupt();
  return TRUE;
}

/****************************************************************************/
/*  Read from an I2C peripheral                                             */
/*  Function : read_i2c                                                     */
/*      Parameters                                                          */
/*          Input   :   Slave address of the I2C peripheral                 */
/*          Input   :   Pointer to the buffer of reception                  */
/*          Input   :   number of bytes to received                         */
/*          Output  :   Nothing                                             */
/****************************************************************************/
uint8_t read_i2c(uint8_t addr_i2c, uint8_t *data, uint8_t nb_byte)
{
  __disable_interrupt();

  //Transmitted by master
  clr_hbit(I2CCTL,I2CCTL_I2CMTX);
  //Continues clock upon completion
//  clr_hbit(I2CCTL,I2CCTL_I2CCS);
  //wait for I2C bus to be ready
  if (!waiti2cmbb())
  {
  __enable_interrupt();
    return FALSE;
  }

/********************/
/* Send I2C address */
/********************/
  //Write slave address
  put_hvalue(I2CDR,(addr_i2c|I2C_READ_INSTR));
  //Start condition
  set_hbit(I2CCTL,I2CCTL_I2CMSTA);
  //Look at arbitration
  if((get_hvalue(I2CSR)&I2CSR_I2CMAL))
  {
    //Clear status
    put_hvalue(I2CSR,0x0000);
  __enable_interrupt();
    return FALSE;
  }
  //wait for transfer to be completed
    if (!waiti2cmcf())
    {
    __enable_interrupt();
      return FALSE;
    }
  //Look at acknowledge
  if((get_hvalue(I2CSR)&I2CSR_I2CRXAK))
  {
    //Stop condition
    clr_hbit(I2CCTL,I2CCTL_I2CMSTA);
    //Clear status
    put_hvalue(I2CSR,0x0000);
  __enable_interrupt();
    return FALSE;
  }

/********************/
/* Receive I2C data */
/********************/

    do{
      //Clear status
      put_hvalue(I2CSR,0x0000);
      //Check if last byte
      if((nb_byte-1)==0)
        break;
      //wait for transfer to be completed
    if (!waiti2cmcf())
    {
    __enable_interrupt();
      return FALSE;
    }
    //Read data
      *(data++)=get_value(I2CDR);
    }while(nb_byte--);

    //Send no ack
    set_hbit(I2CCTL,I2CCTL_I2CTXAK);
    //wait for transfer to be completed
    if (!waiti2cmcf())
    {
    __enable_interrupt();
      return FALSE;
    }
    //Read data
    *(data++)=get_value(I2CDR);
    //Clear status
    put_hvalue(I2CSR,0x0000);

/*************/
/* Stop I2C  */
/*************/
  //Stop condition
  clr_hbit(I2CCTL,I2CCTL_I2CMSTA);
  clr_hbit(I2CCTL,I2CCTL_I2CTXAK);

  __enable_interrupt();
  return TRUE;
}

