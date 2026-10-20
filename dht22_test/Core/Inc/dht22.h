/*
 * dht22.h
 *
 *  Created on: Oct 20, 2026
 *      Author: Thu Ta
 */

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;

typedef struct
{
    float temperature;   // Celsius
    float humidity;      // Relative humidity (%)
} DHT22_Data_t;

typedef enum
{
    DHT22_OK = 0,
    DHT22_ERROR_TIMEOUT,
    DHT22_ERROR_CHECKSUM,
    DHT22_ERROR_ARGUMENT,
    DHT22_ERROR_TIMER
} DHT22_Status_t;

/*
 * Initialize TIM2 as a 1 MHz free-running counter.
 * Call after HAL_Init() and SystemClock_Config().
 */
DHT22_Status_t DHT22_Init(TIM_HandleTypeDef *htim);

/*
 * Read temperature and humidity.
 * GPIOx and GPIO_Pin identify the sensor DATA pin.
 * Do not call faster than once every 2 seconds.
 */
DHT22_Status_t DHT22_Read(
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin,
    DHT22_Data_t *data
);

#endif /* INC_DHT22_H_ */
