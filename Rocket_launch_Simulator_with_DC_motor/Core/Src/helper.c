/*
 * helper.c
 *
 *  Created on: Sep 23, 2026
 *      Author: Thu Ta
 */
#include "helper.h"

void door_Open(DoorNumber number, MotorNumber m1, MotorNumber m2, uint16_t speed){
	set_PWM(number,speed);
	motor_FW(m1);
	motor_RE(m2);
	HAL_Delay(5000);
	set_PWM(number,0);
	motor_Disable(m1);
	motor_Disable(m2);
}

void door_Close(DoorNumber number, MotorNumber m1, MotorNumber m2, uint16_t speed){
	set_PWM(number,speed);
	motor_FW(m1);
	motor_RE(m2);
	HAL_Delay(5000);
	set_PWM(number,0);
	motor_Disable(m1);
	motor_Disable(m2);
}

void send_state_uart(char *state)
{
    char buffer[50];
    sprintf(buffer, "%s\r\n", state);

    HAL_UART_Transmit(&huart2,
                      (uint8_t*)buffer,
                      strlen(buffer),
                      100);
}

void send_cmd_uart(char *cmd)
{
    char buffer[50];
    sprintf(buffer, "%s\r\n", cmd);

    HAL_UART_Transmit(&huart1,
                      (uint8_t*)buffer,
                      strlen(buffer),
                      100);
}


