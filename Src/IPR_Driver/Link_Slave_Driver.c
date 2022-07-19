#include "Link_Slave_Driver.h"
#include "usart.h"
#include "tim.h"
#include "LinkbusRTU.h"

uint32_t IC_Data[1];

void Link_Slave_Initial(void){
	
	Link_RecevieMode();
	__HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart5,Link_Receive_pkg.BUS_Array,100);
	
	
	HAL_TIM_Base_Start_IT(&htim14);
	
	
	htim9.Instance->CCR2=0;
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	
}


void Link_Slave_Process(void){




}