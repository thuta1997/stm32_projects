/*
 * dcmotor.h
 *
 *  Created on: Sep 18, 2026
 *      Author: Thu Ta
 */

#ifndef INC_DCMOTOR_H_
#define INC_DCMOTOR_H_
#include "main.h"
#include "config.h"
#include "helper.h"
extern TIM_HandleTypeDef htim3;

void set_PWM(DoorNumber door_number,uint16_t speed);
void motor_FW(MotorNumber motor);
void motor_RE(MotorNumber motor);
void motor_Disable(MotorNumber motor);

#endif /* INC_DCMOTOR_H_ */
