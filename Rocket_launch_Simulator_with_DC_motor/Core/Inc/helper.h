/*
 * helper.h
 *
 *  Created on: Sep 23, 2026
 *      Author: Thu Ta
 */

#ifndef INC_HELPER_H_
#define INC_HELPER_H_

#include "main.h"
#include "dcmotor.h"
#include "config.h"

extern volatile uint8_t auto_mode;
extern volatile uint8_t emergency_mode;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void door_Open(DoorNumber number, MotorNumber m1, MotorNumber m2, uint16_t speed);
void door_Close(DoorNumber number, MotorNumber m1, MotorNumber m2, uint16_t speed);
void send_state_uart(char *state);
void send_cmd_uart(char *cmd);
void home_state(void);
#endif /* INC_HELPER_H_ */
