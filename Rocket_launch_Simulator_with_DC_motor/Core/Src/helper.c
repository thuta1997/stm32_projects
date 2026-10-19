/*
 * helper.c
 *
 *  Created on: Sep 23, 2026
 *      Author: Thu Ta
 */
#include "helper.h"
void home_state(){
	door_Close(Door4,M8,M7,35535);
	door_Close(Door3,M6,M5,35535);
	door_Close(Door2,M4,M3,35535);
	door_Close(Door1,M2,M1,35535);
}
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
        	uint8_t sensor1_done = 0;
        	uint8_t sensor2_done = 0;
            while (!sensor1_done || !sensor2_done)
            {
            	if (!sensor1_done && HAL_GPIO_ReadPin(GPIOC, sensor1_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m1);
            		sensor1_done = 1;
        	    }
            	if (!sensor2_done &&HAL_GPIO_ReadPin(GPIOC, sensor2_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m2);
            		sensor2_done = 1;
            	}
            }
            break;

        case Door2:
        	uint8_t sensor3_done = 0;
        	uint8_t sensor4_done = 0;
            while (!sensor3_done || !sensor4_done)
            {
            	if (!sensor3_done && HAL_GPIO_ReadPin(GPIOC, sensor3_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m1);
            		sensor3_done = 1;
        	    }
            	if (!sensor4_done &&HAL_GPIO_ReadPin(GPIOD, sensor4_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m2);
            		sensor4_done = 1;
            	}
            }
            break;

        case Door3:
        	uint8_t sensor5_done = 0;
        	uint8_t sensor6_done = 0;
            while (!sensor5_done || !sensor6_done)
            {
            	if (!sensor5_done && HAL_GPIO_ReadPin(GPIOB, sensor5_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m1);
            		sensor5_done = 1;
        	    }
            	if (!sensor6_done &&HAL_GPIO_ReadPin(GPIOB, sensor6_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m2);
            		sensor6_done = 1;
            	}
            }
            break;

        case Door4:
        	uint8_t sensor7_done = 0;
        	uint8_t sensor8_done = 0;
            while (!sensor7_done || !sensor8_done)
            {
            	if (!sensor7_done && HAL_GPIO_ReadPin(GPIOC, sensor7_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m1);
            		sensor7_done = 1;
        	    }
            	if (!sensor8_done &&HAL_GPIO_ReadPin(GPIOB, sensor8_Pin) == GPIO_PIN_RESET)
            	{
            		motor_Disable(m2);
            		sensor8_done = 1;
            	}
            }
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


