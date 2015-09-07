#include "ml674061.h"
#include "common.h"

/* constants */
#define XON     17
#define XOFF    19

// UARTDL = Fclk / (baudrate x 16)
//#define    DLM_BAUD             0x00  //115.2kbps @32.768MHz
//#define    DLL_BAUD             0x12  //115.2kbps @32.768MHz
#define    DLM_BAUD             0x00  //115.2kbps @32MHz
#define    DLL_BAUD             0x11  //115.2kbps @32MHz
//#define    DLM_BAUD             0x00  //57.6kbps @32MHz
//#define    DLL_BAUD             0x23  //57.6kbps @32MHz

/* === setting baud rate value === */
/*     baud  | DLM_BAUD | DLL_BAUD */
/*     1,200 |   0x06   |   0xB7   */
/*     2,400 |   0x03   |   0x5B   */
/*     4,800 |   0x01   |   0xAE   */
/*     9,600 |   0x00   |   0xD7   */
/*    19,200 |   0x00   |   0x6B   */
/*    38,400 |   0x00   |   0x36   */
/*    57,600 |   0x00   |   0x24   */
/*   115,200 |   0x00   |   0x12   */

#define C_CHAR 0x43
#define SOH 0x01
#define STX 0x02
#define EOT 0x04
#define _ACK 0x06
#define NAK 0x15
#define CAN 0x18

/*************/
/* Functions */
/*************/
void    init_uart(void);
void    write_uart(uint8_t *);
void    putch_uart(uint8_t c);
void    putst_uart(uint8_t *str);
void    putint_uart(int32_t v);
void    puthx_uart(int32_t v);
void    putbin_uart(uint8_t *str,int32_t len);


uint32_t xmodem_recv(uint8_t *addr_mem);
void xmodem_send(uint8_t *addr_mem, uint32_t nb_bytes_to_send);
int16_t calcrc(uint8_t *ptr, int16_t count);
