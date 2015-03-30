#ifndef _DEBUG_H_
#define _DEBUG_H

#include <stdio.h>
#include "uart.h"

extern char dbg_buffer[];

#ifdef DEBUG
#define DBG(x) putst_uart(x)
#else
#define DBG(x)
#endif

#ifdef DEBUG_USB
#define DBG_USB(x) putst_uart(x)
#else
#define DBG_USB(x)
#endif

#ifdef DEBUG_WIFI
#define DBG_WIFI(x) putst_uart(x)
#else
#define DBG_WIFI(x)
#endif

#endif /* _DEBUG_H */
