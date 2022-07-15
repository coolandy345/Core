#include "Link_Slave_Driver.h"
#include "time.h"

uint32_t IC_Data[1];

void Link_Slave_Initial(void){

	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_4);
}


void Link_Slave_Process(void){




}