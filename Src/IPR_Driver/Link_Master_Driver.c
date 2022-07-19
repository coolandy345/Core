#include "Link_Master_Driver.h"
#include "tim.h"



void Link_Master_Initial(void){

	htim11.Instance->CCR1=0;
	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);
	
	htim9.Instance->CCR2=0;
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);

}


void Link_Master_Process(void){

	
	
	

}