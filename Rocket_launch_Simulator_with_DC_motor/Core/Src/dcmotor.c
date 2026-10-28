/*
 * dcmotor.c
 *
 *  Created on: Sep 18, 2026
 *      Author: Thu Ta
 */
#include "dcmotor.h"
void set_PWM(DoorNumber door_number,uint16_t speed){
	switch (door_number)
	{
	  case Door1:
		  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,speed);
		  break;
	  case Door2:
		  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,speed);
		  break;
	  case Door3:
		  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,speed);
		  break;
	  case Door4:
		  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,speed);
		  break;
	  default:
		  break;
	}
}
void motor_FW(MotorNumber motor){
	 switch (motor)
	    {
	        case M1:
	            HAL_GPIO_WritePin(m1F_GPIO_Port, m1F_Pin, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(m1R_GPIO_Port, m1R_Pin, GPIO_PIN_RESET);
	            break;
	        case M2:
	            HAL_GPIO_WritePin(m2F_GPIO_Port, m2F_Pin, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(m2R_GPIO_Port, m2R_Pin, GPIO_PIN_RESET);
	            break;
	        case M3:
	            HAL_GPIO_WritePin(m3F_GPIO_Port, m3F_Pin, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(m3R_GPIO_Port, m3R_Pin, GPIO_PIN_RESET);
	            break;
	        case M4:
	        	HAL_GPIO_WritePin(m4F_GPIO_Port, m4F_Pin, GPIO_PIN_SET);
	        	HAL_GPIO_WritePin(m4R_GPIO_Port, m4R_Pin, GPIO_PIN_RESET);
	        	break;
	        case M5:
	        	HAL_GPIO_WritePin(m5F_GPIO_Port, m5F_Pin, GPIO_PIN_SET);
	        	HAL_GPIO_WritePin(m5R_GPIO_Port, m5R_Pin, GPIO_PIN_RESET);
	        	break;
	        case M6:
	        	HAL_GPIO_WritePin(m6F_GPIO_Port, m6F_Pin, GPIO_PIN_SET);
	        	HAL_GPIO_WritePin(m6R_GPIO_Port, m6R_Pin, GPIO_PIN_RESET);
	            break;
	        case M7:
	        	HAL_GPIO_WritePin(m7F_GPIO_Port, m7F_Pin, GPIO_PIN_SET);
	        	HAL_GPIO_WritePin(m7R_GPIO_Port, m7R_Pin, GPIO_PIN_RESET);
	            break;
	        case M8:
	        	HAL_GPIO_WritePin(m8F_GPIO_Port, m8F_Pin, GPIO_PIN_SET);
	        	HAL_GPIO_WritePin(m8R_GPIO_Port, m8R_Pin, GPIO_PIN_RESET);
	        	break;
	        default:
	        	break;
	    }
}

void motor_RE(MotorNumber motor){
	 switch (motor)
	    {
	        case M1:
	            HAL_GPIO_WritePin(m1F_GPIO_Port, m1F_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(m1R_GPIO_Port, m1R_Pin, GPIO_PIN_SET);
	            break;
	        case M2:
	            HAL_GPIO_WritePin(m2F_GPIO_Port, m2F_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(m2R_GPIO_Port, m2R_Pin, GPIO_PIN_SET);
	            break;
	        case M3:
	            HAL_GPIO_WritePin(m3F_GPIO_Port, m3F_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(m3R_GPIO_Port, m3R_Pin, GPIO_PIN_SET);
	            break;
	        case M4:
	        	HAL_GPIO_WritePin(m4F_GPIO_Port, m4F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m4R_GPIO_Port, m4R_Pin, GPIO_PIN_SET);
	        	break;
	        case M5:
	        	HAL_GPIO_WritePin(m5F_GPIO_Port, m5F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m5R_GPIO_Port, m5R_Pin, GPIO_PIN_SET);
	        	break;
	        case M6:
	        	HAL_GPIO_WritePin(m6F_GPIO_Port, m6F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m6R_GPIO_Port, m6R_Pin, GPIO_PIN_SET);
	            break;
	        case M7:
	        	HAL_GPIO_WritePin(m7F_GPIO_Port, m7F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m7R_GPIO_Port, m7R_Pin, GPIO_PIN_SET);
	            break;
	        case M8:
	        	HAL_GPIO_WritePin(m8F_GPIO_Port, m8F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m8R_GPIO_Port, m8R_Pin, GPIO_PIN_SET);
	        	break;
	        default:
	        	break;
	    }
}

void motor_Disable(MotorNumber motor){
	 switch (motor)
	    {
	        case M1:
	            HAL_GPIO_WritePin(m1F_GPIO_Port, m1F_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(m1R_GPIO_Port, m1R_Pin, GPIO_PIN_RESET);
	            break;
	        case M2:
	            HAL_GPIO_WritePin(m2F_GPIO_Port, m2F_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(m2R_GPIO_Port, m2R_Pin, GPIO_PIN_RESET);
	            break;
	        case M3:
	            HAL_GPIO_WritePin(m3F_GPIO_Port, m3F_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(m3R_GPIO_Port, m3R_Pin, GPIO_PIN_RESET);
	            break;
	        case M4:
	        	HAL_GPIO_WritePin(m4F_GPIO_Port, m4F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m4R_GPIO_Port, m4R_Pin, GPIO_PIN_RESET);
	        	break;
	        case M5:
	        	HAL_GPIO_WritePin(m5F_GPIO_Port, m5F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m5R_GPIO_Port, m5R_Pin, GPIO_PIN_RESET);
	        	break;
	        case M6:
	        	HAL_GPIO_WritePin(m6F_GPIO_Port, m6F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m6R_GPIO_Port, m6R_Pin, GPIO_PIN_RESET);
	            break;
	        case M7:
	        	HAL_GPIO_WritePin(m7F_GPIO_Port, m7F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m7R_GPIO_Port, m7R_Pin, GPIO_PIN_RESET);
	            break;
	        case M8:
	        	HAL_GPIO_WritePin(m8F_GPIO_Port, m8F_Pin, GPIO_PIN_RESET);
	        	HAL_GPIO_WritePin(m8R_GPIO_Port, m8R_Pin, GPIO_PIN_RESET);
	        	break;
	        default:
	        	break;
	    }
}
