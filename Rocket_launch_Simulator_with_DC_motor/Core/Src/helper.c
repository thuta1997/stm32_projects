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
    set_PWM(number, speed);
    motor_FW(m1);
    motor_RE(m2);

    switch(number){
        case Door1:
            while(HAL_GPIO_ReadPin(GPIOC, sensor1_Pin) != GPIO_PIN_RESET);
            break;

        case Door2:
            while(HAL_GPIO_ReadPin(GPIOC, sensor2_Pin) != GPIO_PIN_RESET);
            break;

        case Door3:
            while(HAL_GPIO_ReadPin(GPIOC, sensor3_Pin) != GPIO_PIN_RESET);
            break;

        case Door4:
            // Crucial Change: Reading from GPIOD instead of GPIOC
            while(HAL_GPIO_ReadPin(GPIOD, sensor4_Pin) != GPIO_PIN_RESET);
            break;

        default:
            // Turn off motors if an invalid door number is passed
            set_PWM(number, 0);
            motor_Disable(m1);
            motor_Disable(m2);
            return;
    }

    // Centralized motor shutdown for valid cases
    set_PWM(number, 0);
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


