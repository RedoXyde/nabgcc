#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "ml674061.h"
#include "common.h"

/*************/
/* Functions */
/*************/
void init_pwm(void);
void run_motor(uint8_t number, uint8_t speed, uint8_t rotation);
void stop_motor(uint8_t number);
uint16_t get_motor_position(uint8_t number);

#endif
