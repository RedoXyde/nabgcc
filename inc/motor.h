#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "ML674061.h"
#include "common.h"

/*************/
/* Functions */
/*************/
void init_pwm(void);
void run_motor(uchar number, uchar speed, uchar rotation);
void stop_motor(uchar number);
ushort get_motor_position(uchar number);

#endif
