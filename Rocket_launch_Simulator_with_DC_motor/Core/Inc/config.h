/*
 * config.h
 *
 *  Created on: Sep 23, 2026
 *      Author: Thu Ta
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_
#include "main.h"
typedef enum
{
    STATE_IDLE,
	STATE_HOME,

    STATE_DOOR1_OPEN,
    STATE_DOOR2_OPEN,
    STATE_DOOR3_OPEN,
	STATE_DOOR4_OPEN,

	STATE_LAUNCH,

	STATE_DOOR4_CLOSE,
    STATE_DOOR3_CLOSE,
    STATE_DOOR2_CLOSE,
    STATE_DOOR1_CLOSE,

    STATE_COMPLETE,
    STATE_EMERGENCY

}SystemState;

typedef enum
{
    Door1,
    Door2,
	Door3,
	Door4
}DoorNumber;

typedef enum
{
    M1,
    M2,
	M3,
	M4,
	M5,
	M6,
	M7,
	M8
}MotorNumber;

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;

}ProximitySensor;

#endif /* INC_CONFIG_H_ */
