#include "IPR100D30_Parameter.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"
#include "ADS1247.h"
#include "Constant.h"




Unit_Status_typedef Unit_Status;
uint16_t SYS_Registor[12*16];

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
}


void OPERATE_Process(void){
	if (Unit_Status.Operate_State==UnitIDLE || 
		Unit_Status.Operate_State==UnitSTANDBY){
			
		IDLE_Process();
	
	}else if(Unit_Status.Operate_State==UnitRUN){
			
		RUN_Prosess();
	
	}else{
			
		ERROR_Prosess();
	
	}
}


void State_Process(void){

	if(!Unit_Status.PWR_Status.PWR_Error){
		
		if(!Unit_Status.User_Status.USER_Start){
			
			if(Unit_Status.Link_Status.Link_Mode==MASTER ||
				(Unit_Status.Link_Status.Link_Mode==SLAVE && Unit_Status.Link_Status.Link_Connection)){
			
				Unit_Status.Operate_State=UnitRUN;	
		
			}else{
				
				Unit_Status.Operate_State=UnitSTANDBY;	
			
			}
		
		}else{
		
			Unit_Status.Operate_State=UnitIDLE;
			
		}
	
	}else{
	
		Unit_Status.Operate_State=UnitERROR;
	
	}

}


void Input_Interface_Process(void){

	if (Unit_Status.Link_Status.Link_Mode==MASTER){
		
		Unit_Status.Output_Current_Cmd=Unit_Status.User_Status.User_Command_Current/Unit_Status.Link_Status.LINK_Number;
		
		float data[2*2]={0,655.35,250,64879.65};
		htim11.Instance->CCR1=find_Approtch(Unit_Status.Output_Current_Cmd,data,4,0xFFFF,0);
	
	}else{
	
		htim11.Instance->CCR1=0;
		
		if (Unit_Status.Link_Status.Link_Connection){
			float data[2*2]={1,0,99,250};
			Unit_Status.Output_Current_Cmd=find_Approtch(duty,data,4,250,0);
		}else{
			Unit_Status.Output_Current_Cmd=0;
		}
		
		
	}

}


void Link_Manage_Process(void){
	
	if (Unit_Status.Link_Status.Link_Mode==MASTER){
	
		//Link Check
		int Status_Live_Number=0;
		//Poll Slave Status
		for(int i=0;i<Unit_Status.Link_Status.LINK_MaxNumber;i++){
			
			int timeout=0;
			
			//Send Status Respond Request
			
			//if Get
			if (!Status_Live_Number){
				Status_Live_Number++;
			}else{
				
			}
		
		}
		
		//Set LINK_MaxNumber
		Unit_Status.Link_Status.LINK_Number=Status_Live_Number;
		
	}
	
}

void RUN_Prosess(void){
	if (!Unit_Status.PWR_Status.PWR_Error){
		
		MCU_PWR_Enable(1);
		MCU_PWR_REM_Enable(1);
		MCU_Fault_Signal_Enable(0);
		
		MCU_PWR_Current_OutputCmdSet(Unit_Status.Output_Current_Cmd);
		
	
	}else{
		IDLE_Process();
	}
	
}
void IDLE_Process(void){
	MCU_PWR_Enable(0);
	MCU_PWR_REM_Enable(0);
	MCU_Fault_Signal_Enable(0);
	
	MCU_PWR_Current_OutputCmdSet(0);
}
void ERROR_Prosess(void){
	MCU_PWR_Enable(0);
	MCU_PWR_REM_Enable(0);
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
		HAL_GPIO_WritePin(MCU_PWR_REM_GPIO_Port, MCU_PWR_REM_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(MCU_PWR_REM_GPIO_Port, MCU_PWR_REM_Pin, GPIO_PIN_RESET);
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
	
	float Cmd_voltage=find_Approtch(current,OutputCmd_to_AnalogCmd_Data,8,MAX_Current_Uplimit+0.1,MIN_Current_Downlimit-0.1);

	//Sent to TIM9
	htim9.Instance->CCR2=find_Approtch(Cmd_voltage,PWM_Data,56,0xFFFF,0);

}
void Lost_MasterConnection(void){
	
//	Master_ConnectionStatus=0;
//	PFC_Status.MasterConnection=Lost;
//	sys_shoutdown();
}

void sys_powerup(void){

//	SET_BIT(SYS_Registor[CONTRL],CONTRL_PFC_SWON);

}



void sys_shoutdown(void){
	
//	CLEAR_BIT(SYS_Registor[CONTRL],CONTRL_PFC_SWON);

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



