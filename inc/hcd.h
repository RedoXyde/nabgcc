/**
 * @file hcd.h
 * @author Oki Electric Industry Co.,Ltd. - 2003 - Initial version
 * @author RedoX <dev@redox.ws> - 2015 - GCC Port, cleanup
 * @date 2015/09/07
 * @brief USB Host
 */
#ifndef _HCD_H_
#define _HCD_H_

#include "ml60842.h"
#include "usbh.h"

/*
 * Host Controller Endpoint Descriptor,
 * refer to Section 4.2, Endpoint Descriptor
 */
typedef struct _HC_ED
{
  volatile uint32_t  Control;         /* dword 0*/
  volatile uint32_t  TailP;           /* physical pointer to HC_TD*/
  volatile uint32_t  HeadP;           /* flags + phys ptr to HC_TD*/
  volatile uint32_t  NextED;          /* phys ptr to HC_ED*/
} HC_ED, *PHC_ED;

#define HcED_FA           0x0000007F  /* */
#define HcED_EN           0x00000780  /* */
#define HcED_DIR          0x00001800  /* */
#define HcED_DIR_OUT      0x00000800  /* */
#define HcED_DIR_IN       0x00001000  /* */
#define HcED_SPEED        0x00002000  /* */
#define HcED_SKIP         0x00004000  /* */
#define HcED_FORMAT       0x00008000  /* */
#define HcED_MPS          0x07FF0000  /* */

#define HcED_HeadP_HALT   0x00000001  /* hardware stopped bit */
#define HcED_HeadP_CARRY  0x00000002  /* hardware toggle carry bit */

#define ED_IDLE           0
#define ED_LINK           1
#define ED_PAUSE          2
#define ED_UNLINK         3

#define MAXIMUM_OVERHEAD  500

/*
 * Host Controller Transfer Descriptor, refer to Section 4.3, Transfer Descriptor
 */
typedef struct _HC_TD
{
  volatile uint32_t  Control;         /* dword 0*/
  volatile void *CBP;                 /* phys ptr to data buffer*/
  volatile uint32_t  NextTD;          /* phys ptr to HC_TD*/
  volatile void *BE;                  /* phys ptr to end of data buffer*/
} HC_TD, *PHC_TD;

#define HcTD_CC           0xF0000000  /* */
#define HcTD_EC           0x0C000000  /* */
#define HcTD_T            0x03000000  /* */
#define HcTD_T_DATA0      0x02000000  /* */
#define HcTD_T_DATA1      0x03000000  /* */
#define HcTD_R            0x00040000  /* */
#define HcTD_DI           0x00E00000  /* */
#define HcTD_DP           0x00180000  /* */
#define HcTD_DP_SETUP     0x00000000  /* */
#define HcTD_DP_IN        0x00100000  /* */
#define HcTD_DP_OUT       0x00080000  /* */

#define CC_NOERROR        0x0      /* 0000 */
#define CC_CRC            0x1      /* 0001 */
#define CC_BITSTUFFING    0x2      /* 0010 */
#define CC_TOGGLEMISMATCH 0x3      /* 0011 */
#define CC_STALL          0x4      /* 0100 */
#define CC_NOTRESPONDING  0x5      /* 0101 */
#define CC_PIDCHECKFAILURE 0x6     /* 0110 */
#define CC_UNEXPECTEDPID  0x7      /* 0111 */
#define CC_DATAOVERRUN    0x8      /* 1000 */
#define CC_DATAUNDERRUN   0x9      /* 1001 */
#define CC_BUFFEROVERRUN  0xC      /* 1100 */
#define CC_BUFFERUNDERRUN 0xD      /* 1101 */
#define CC_NOTACCESSED    0xF      /* 1111 */

#define TD_SETUP          1
#define TD_DATA           2
#define TD_STATUS         3

/*
* HCD Endpoint Descriptor
*/
typedef struct _HCD_ED
{
  HC_ED    HcED;
  uint8_t    type;
  uint8_t    interval;
  uint8_t    flag;
  uint8_t    reserved;
  void    *dev;
  LIST_ENTRY  ed_list;
} HCD_ED, *PHCD_ED;

/*
* HCD Transfer Descriptor
*/
typedef struct _HCD_TD {
  HC_TD   HcTD;
  PURB    urb;
  int32_t index;
  LIST_ENTRY  list;
} HCD_TD, *PHCD_TD;


struct hcca
{
  uint32_t int_table[32]; /* These 32 Dwords are pointers to interrupt EDs */
  uint16_t framenumber;   /* Contains the current frame number.  */
  uint16_t pad1;          /* When the HC updates HccaFrameNumber,
                           *      it sets this word to 0. */
  uint32_t donehead;      /* The Done Queue of completed TD's. */
  uint8_t  reserved[116];
};

struct hcd_info
{
  struct hcca *hcca;      /* address of HCCA */

  int32_t     disabled;   /* status of host controller */
  uint32_t    hc_control; /* copy of the hc control reg */

  LIST_ENTRY  ed_bulk;    /* bulk endpoint list*/
  LIST_ENTRY  ed_control; /* control endpoint list*/

  LIST_ENTRY  ed_pause0;  /* delete endpoint list0*/
  LIST_ENTRY  ed_pause1;  /* delete endpoint list1*/

  int32_t     rh_status;  /* status of root hub */
  void        *rh_device;
};

#define HcdRH_CONNECT     0x01
#define HcdRH_DISCONNECT  0x02
#define HcdRH_SPEED       0x10

extern struct hcd_info hcd_info;

#define disable_ohci_irq() put_wvalue(HostCtl, B_OHCIIRQ_MASK)
#define enable_ohci_irq() put_wvalue(HostCtl, 0)

int8_t hcd_init(void);
void hcd_exit(void);

uint8_t hcd_rh_events(void);

PHCD_ED hcd_create_ed(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, uint8_t);
int8_t hcd_update_ed(PHCD_ED, uint8_t, uint16_t);
void hcd_delete_ed(PHCD_ED);

int8_t hcd_transfer_request(PURB);
int8_t hcd_transfer_cancel(PURB);
int8_t hcd_rh_disconnect(void);

#endif  /* _HCD_H_ */
