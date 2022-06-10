#include "IPR100D30_Parameter.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"


PFC_Status_typedef PFC_Status;
int emergency_occur=0;
uint8_t PFC_SWON,PFC_ErrRST;

uint16_t SYS_Registor[18];
uint8_t GPIO_InputData[3];

uint8_t Master_ConnectionStatus;
uint8_t Err_OCP,Err_OVP,Err_OTP1,Err_OTP2,Err_UTP1,Err_UTP2,Err_UVLO,Err_OVLO,Err_15V_P_OVP,Err_15V_P_UVP,Err_5V_P_OVP,Err_5V_P_UVP,PFC_ON,Err_Latch;
float ACin=0;
float Vout=0;
float Iout=0;
float Temp_BridgeDiode=0;
float Temp_MOSFET=0;

int ERROR_IN_RESET=0;

void sys_powerup(void);


void SYS_Registor_Init(void){
	
	PFC_SWON		=	0;
	PFC_ErrRST		=	0;
	memset(SYS_Registor,0x0000,13);
//	HAL_TIM_Base_Start_IT(&Conn_Check_htim17);
	
	sys_shoutdown();
}

void SYS_OPERATOR(void){
	
	if(!emergency_occur){
		
		
		/*  Power On Check */
		
		if(SYS_Registor[PFC_ON_COIL]){
			
			if( !Err_Latch && 	!ERROR_IN_RESET	){			//Only ON with NO error and not in Reset
				sys_powerup();
			}else{
				
				sys_shoutdown();
			}
			
			SYS_Registor[PFC_ON_COIL]=0;
			
			
			
		}
		
		/*  Power Off Check */
		
		if(SYS_Registor[PFC_OFF_COIL]){
			
			sys_shoutdown();
			SYS_Registor[PFC_OFF_COIL]=0;
		}
		
		
		/*  Error Reset */
		if(SYS_Registor[ERR_RST_COIL]){	
			
			if(Err_Latch){		//if err is exist
				
				//turn off first
				sys_shoutdown();
				
				ERROR_IN_RESET=1;
				SET_BIT(SYS_Registor[CONTRL],CONTRL_PFC_ErrRST);
				
				osDelay(10);
//				HAL_Delay(10);
				
				CLEAR_BIT(SYS_Registor[CONTRL],CONTRL_PFC_ErrRST);
				
				ERROR_IN_RESET=0;
				
			}
			SYS_Registor[ERR_RST_COIL]=0;
			SYS_Registor[ERROR_CODE_BACKUP]=0;
		}
		
		
		
	}else{
		
		sys_shoutdown();
		
	}
}

void Lost_MasterConnection(void){
	
	Master_ConnectionStatus=0;
	PFC_Status.MasterConnection=Lost;
	sys_shoutdown();
}

void sys_powerup(void){

	SET_BIT(SYS_Registor[CONTRL],CONTRL_PFC_SWON);

}



void sys_shoutdown(void){
	
	CLEAR_BIT(SYS_Registor[CONTRL],CONTRL_PFC_SWON);

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



