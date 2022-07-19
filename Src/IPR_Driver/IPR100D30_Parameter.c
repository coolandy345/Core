#include "IPR100D30_Parameter.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "cmsis_os.h"
#include "ADS1247.h"
#include "Constant.h"
#include "Link_Slave_Driver.h"
#include "Link_Master_Driver.h"
#include <math.h>


uint8_t Link_signals=0x01;

Unit_Status_typedef Unit_Status;
uint16_t SYS_Registor[15*4];

void Registor_Update(void){
	
	SYS_Registor[SYS_SR]=(
							Unit_Status.PWR_Status.PWR_INTERLOCK_Indecate<<12	|
							Unit_Status.PWR_Status.PWR_OUTPUT_Indecate<<11		|
							Unit_Status.PWR_Status.PWR_REM_Indecate<<10			|
							Unit_Status.PWR_Status.PWR_REM_Enable<<9			|
							Unit_Status.MCU_Status.MCU_PWR_ENABLE<<8			|
							Unit_Status.PWR_Status.PWR_Error<<7					|
							Unit_Status.MCU_Status.MCU_NO_ERROR<<6				|
							Unit_Status.MCU_Status.SYS_Error<<5					|
							Unit_Status.MCU_Status.MCU_REM_ENABLE<<4			|
							Unit_Status.MCU_Status.MCU_PWR_ENABLE<<3			|
							Unit_Status.User_Status.USER_Start<<2				|
							Unit_Status.MCU_Status.Operate_State);
	
	SYS_Registor[MCU_TEMP]=(uint16_t)((Unit_Status.MCU_Status.MCU_Temperature+100)*100);
	
	SYS_Registor[LINK_SR]=(
	
							Unit_Status.Modbus_Status.MODBUS_ADDRESS<<8	|
							Unit_Status.Link_Status.Link_Mode<<6		|
							Unit_Status.Link_Status.Link_MaxNumber<<4	|
							Unit_Status.Link_Status.Link_Number<<2		|
							Unit_Status.Link_Status.Link_Node);
	
	SYS_Registor[VOLTAGE_H]		=(uint16_t)(Unit_Status.PWR_Status.Voltage);
	SYS_Registor[VOLTAGE_L]		=(uint16_t)(fmod(Unit_Status.PWR_Status.Voltage,10.0)*1000);
	SYS_Registor[CURRENT_H]		=(uint16_t)(Unit_Status.PWR_Status.Current);
	SYS_Registor[CURRENT_L]		=(uint16_t)(fmod(Unit_Status.PWR_Status.Current,10.0)*1000);
	SYS_Registor[POWER_H]		=(uint16_t)(Unit_Status.PWR_Status.Voltage*Unit_Status.PWR_Status.Current);
	SYS_Registor[POWER_L]		=(uint16_t)(fmod(Unit_Status.PWR_Status.Voltage*Unit_Status.PWR_Status.Current,10.0)*1000);
	SYS_Registor[OUTPUT_CMD_H]	=(uint16_t)(Unit_Status.MCU_Status.Output_Current_Cmd);
	SYS_Registor[OUTPUT_CMD_L]	=(uint16_t)(fmod(Unit_Status.MCU_Status.Output_Current_Cmd,10.0)*1000);
	SYS_Registor[USR_CMD_H]		=(uint16_t)(Unit_Status.User_Status.User_Command_Current);
	SYS_Registor[USR_CMD_L]		=(uint16_t)(fmod(Unit_Status.User_Status.User_Command_Current,10.0)*1000);
	SYS_Registor[USR_LMT_H]		=(uint16_t)(Unit_Status.User_Status.User_Limit_Current);
	SYS_Registor[USR_LMT_L]		=(uint16_t)(fmod(Unit_Status.User_Status.User_Limit_Current,10.0)*1000);
	
	
}

void IPR_Init(void){
	uint8_t option_state;
	option_state=	HAL_GPIO_ReadPin(Master_Select_GPIO_Port,Master_Select_Pin)<<5	|
					HAL_GPIO_ReadPin(CCCV_Select_GPIO_Port,CCCV_Select_Pin)<<4		|
					HAL_GPIO_ReadPin(MODBUS_ADD_4_GPIO_Port,MODBUS_ADD_4_Pin)<<3	|
					HAL_GPIO_ReadPin(MODBUS_ADD_3_GPIO_Port,MODBUS_ADD_3_Pin)<<2	|
					HAL_GPIO_ReadPin(MODBUS_ADD_2_GPIO_Port,MODBUS_ADD_2_Pin)<<1	|
					HAL_GPIO_ReadPin(MODBUS_ADD_1_GPIO_Port,MODBUS_ADD_1_Pin)<<0	;
	option_state=~option_state;
	
	Unit_Status.Link_Status.Link_Mode=option_state&(1<<5)? MASTER:SLAVE;		//Master=1  Slave=0
	Unit_Status.Modbus_Status.MODBUS_ADDRESS=0x30 | option_state&0xF;			//Default 0x30  = 48(dec)
	
	if (Unit_Status.Link_Status.Link_Mode==MASTER){
		
		for(int i=0;i<4;i++){
			if (option_state&(1<<i)){
				Unit_Status.Link_Status.Link_MaxNumber=i+1;
				System_Capacity_Set(Unit_Status.Link_Status.Link_MaxNumber);
				Unit_Status.Link_Status.Link_Node=i+1;
				i=4;
			}
		}
		
		Link_Master_Initial();
	
	}else if (Unit_Status.Link_Status.Link_Mode==SLAVE){
		
		for(int i=0;i<4;i++){
			if (option_state&(1<<i)){
				Unit_Status.Link_Status.Link_Node=i+1;
				i=4;
			}
		}
		
		Link_Slave_Initial();
	
	}
	
	
	
	
}


void OPERATE_Process(void){
	if (Unit_Status.MCU_Status.Operate_State==UnitIDLE || 
		Unit_Status.MCU_Status.Operate_State==UnitSTANDBY){
			
		IDLE_Process();
	
	}else if(Unit_Status.MCU_Status.Operate_State==UnitRUN){
			
		RUN_Prosess();
	
	}else{
			
		ERROR_Prosess();
	
	}
}


void State_Process(void){
	Unit_Status.MCU_Status.SYS_Error				= HAL_GPIO_ReadPin(SYSTEM_FAULT_GPIO_Port,SYSTEM_FAULT_Pin);
	Unit_Status.MCU_Status.MCU_NO_ERROR				= HAL_GPIO_ReadPin(MCU_NO_FAULT_GPIO_Port,MCU_NO_FAULT_Pin);
	Unit_Status.MCU_Status.MCU_PWR_ENABLE			= HAL_GPIO_ReadPin(MCU_PWR_ENABLE_GPIO_Port,MCU_PWR_ENABLE_Pin);
	Unit_Status.MCU_Status.MCU_REM_ENABLE			= HAL_GPIO_ReadPin(MCU_PWR_REMOTE_GPIO_Port,MCU_PWR_REMOTE_Pin);
	Unit_Status.PWR_Status.PWR_Error				=!HAL_GPIO_ReadPin(PWR_FAULT_INDICATION_GPIO_Port,PWR_FAULT_INDICATION_Pin);
	Unit_Status.PWR_Status.PWR_REM_Indecate			=!HAL_GPIO_ReadPin(PWR_REMOTE_INDICATION_GPIO_Port,PWR_REMOTE_INDICATION_Pin);
	Unit_Status.PWR_Status.PWR_OUTPUT_Indecate		=!HAL_GPIO_ReadPin(PWR_OUTPUT_ON_INDICATION_GPIO_Port,PWR_OUTPUT_ON_INDICATION_Pin);
	Unit_Status.PWR_Status.PWR_INTERLOCK_Indecate	= HAL_GPIO_ReadPin(PWR_INTERLOCK_INDICATION_GPIO_Port,PWR_INTERLOCK_INDICATION_Pin);
	Unit_Status.User_Status.USER_Start				= HAL_GPIO_ReadPin(USER_ENABLE_GPIO_Port,USER_ENABLE_Pin);
	

	if(!Unit_Status.PWR_Status.PWR_Error){
		
		if(Unit_Status.User_Status.USER_Start){
			
			if(Unit_Status.Link_Status.Link_Mode==MASTER ||
				(Unit_Status.Link_Status.Link_Mode==SLAVE && Unit_Status.Link_Status.Link_Connection)){
			
				Unit_Status.MCU_Status.Operate_State=UnitRUN;	
		
			}else{
				
				Unit_Status.MCU_Status.Operate_State=UnitSTANDBY;	
			
			}
		
		}else{
		
			Unit_Status.MCU_Status.Operate_State=UnitIDLE;

			
		}
	
	}else{
		
		Unit_Status.MCU_Status.Operate_State=UnitERROR;
	
	}

}


void Input_Interface_Process(void){

	if (Unit_Status.Link_Status.Link_Mode==MASTER){

		if(Unit_Status.MCU_Status.Operate_State==UnitRUN){
			
			Unit_Status.MCU_Status.Output_Current_Cmd=Unit_Status.User_Status.User_Command_Current/Unit_Status.Link_Status.Link_Number;
		
		}else{
			
			Unit_Status.MCU_Status.Output_Current_Cmd=0;
		
		}
		
		double data[2*2]={
			0,3275.8,
			250,62258.2};
		
		htim11.Instance->CCR1=find_Approtch(Unit_Status.MCU_Status.Output_Current_Cmd,data,4,0xFFFF,0);  
			
			
	
	}else{
	
		htim11.Instance->CCR1=0;
		
		if (Unit_Status.Link_Status.Link_Connection){
			double data[2*2]={5,0,95,250};
			Unit_Status.MCU_Status.Output_Current_Cmd=find_Approtch(Unit_Status.Link_Status.Link_Duty,data,4,250,0);
		}else{
			Unit_Status.MCU_Status.Output_Current_Cmd=0;
		}
		
		
	}

}


void Link_Manage_Process(void){
	
	if (Unit_Status.Link_Status.Link_Mode==MASTER){
		
		
	
		//Link Check
		int Status_Live_Number=1;
		//Poll Slave Status
		
		for(int i=1;i<Unit_Status.Link_Status.Link_MaxNumber;i++){
			
			//Send Status Respond Request
			
			//HAL_UART_AbortReceive(&huart4);
			Link_TransmitMode();

			if (i==1){
				uint8_t data[]={0x31,0x03,0x00,0x00,0x00,0x0F,0x00,0x3E };
				memmove(Link_Transmit_pkg.BUS_Array,data,8);
				
			}else if  (i==2){
				uint8_t data[]={0x32,0x03,0x00,0x00,0x00,0x0F,0x00,0x0D };
				memmove(Link_Transmit_pkg.BUS_Array,data,8);
				
			}else if (i==3){
				uint8_t data[]={0x33,0x03,0x00,0x00,0x00,0x0F,0x01,0xDC };
				memmove(Link_Transmit_pkg.BUS_Array,data,8);
				
			}
			
			HAL_UART_Transmit_DMA(&huart5,Link_Transmit_pkg.BUS_Array,8);
			HAL_UARTEx_ReceiveToIdle_DMA(&huart5,Link_Receive_pkg.BUS_Array,100);
			if(osSignalWait(Link_signals,2).status==osEventTimeout){	//if slave not repond in 2ms
				
				for(int index=0;index<15;index++){
					SYS_Registor[i*15+index]=0;
				}
					
			}else{
				
				for(int index=0;index<15;index++){
					uint16_t data=Link_Receive_pkg.BUS_Array[3+index*2]<<8 | Link_Receive_pkg.BUS_Array[4+index*2];
					SYS_Registor[i*15+index]=data;
				}
				if((SYS_Registor[i*15]&0x3)==0x3){
					
					Status_Live_Number++;
				
				}
				
			}
			
		
		}
		
		//Set LINK_Number
		Unit_Status.Link_Status.Link_Number=Status_Live_Number;
		
	}
	
}
void Link_TransmitISR(void){
	
	Link_RecevieMode();
	
}

void Link_ReceiveISR(void){
	
	osSignalSet (Link_TaskHandle,Link_signals);
	
}

void RUN_Prosess(void){
	if (!Unit_Status.PWR_Status.PWR_Error){
		
		MCU_PWR_Enable(1);
		MCU_PWR_REM_Enable(1);
		MCU_Fault_Signal_Enable(0);
		
		MCU_PWR_Current_OutputCmdSet(Unit_Status.MCU_Status.Output_Current_Cmd);
		
	
	}else{
		ERROR_Prosess();
	}
	
}
void IDLE_Process(void){
	MCU_PWR_Enable(0);
	MCU_PWR_REM_Enable(1);
	MCU_Fault_Signal_Enable(0);
	
	MCU_PWR_Current_OutputCmdSet(0);
}
void ERROR_Prosess(void){
	MCU_PWR_Enable(0);
	MCU_PWR_REM_Enable(1);
	MCU_Fault_Signal_Enable(1);
	
	MCU_PWR_Current_OutputCmdSet(0);
}



void MCU_PWR_Enable(int enable){
	if (enable){
		HAL_GPIO_WritePin(MCU_PWR_ENABLE_GPIO_Port, MCU_PWR_ENABLE_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(MCU_PWR_ENABLE_GPIO_Port, MCU_PWR_ENABLE_Pin, GPIO_PIN_RESET);
	}
}
void MCU_PWR_REM_Enable(int enable){
	if (enable){
		HAL_GPIO_WritePin(MCU_PWR_REMOTE_GPIO_Port, MCU_PWR_REMOTE_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(MCU_PWR_REMOTE_GPIO_Port, MCU_PWR_REMOTE_Pin, GPIO_PIN_RESET);
	}

}

void MCU_Fault_Signal_Enable(int enable){
	
	if (enable){
		HAL_GPIO_WritePin(MCU_NO_FAULT_GPIO_Port, MCU_NO_FAULT_Pin, GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(MCU_NO_FAULT_GPIO_Port, MCU_NO_FAULT_Pin, GPIO_PIN_SET);
	}
}

void MCU_PWR_Current_OutputCmdSet(float current){
	
	float Cmd_voltage=find_Approtch(current,OutputCmd_to_AnalogCmd_Data,12,9.1,0);
//	float Cmd_voltage=find_Approtch(Unit_Status.MCU_Status.Output_Current_Cmd,OutputCmd_to_AnalogCmd_Data,12,9.1,0); //Delate Test
//	
	

	//Sent to TIM9
	htim9.Instance->CCR2=find_Approtch(Cmd_voltage,PWM_Data,56,0xFFFF,0);

}
void Lost_MasterConnection(void){
	
	Unit_Status.Link_Status.Link_Connection=Lost;
	
}



void BitChange(uint8_t* x,uint8_t* y,uint8_t* n){
	*x = (*x & (~(1 << *n))) | (*y << *n);
}
void BitChange_16(uint16_t* x,uint16_t* y,uint16_t* n){
	*x = (*x & (~(1 << *n))) | (*y << *n);
}
/*
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))
*/



