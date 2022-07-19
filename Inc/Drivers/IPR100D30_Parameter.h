#ifndef __IPR100D30_Parameter_H
#define __IPR100D30_Parameter_H

#include "stm32f2xx_hal.h"
#include <string.h>
#include "cmsis_os.h"


extern uint16_t SYS_Registor[15*4];

/** @defgroup Registor Map
  * @{
  */
typedef enum{
      SYS_SR=0,
      MCU_TEMP,
      LINK_SR,
      VOLTAGE_H,
      VOLTAGE_L,
      CURRENT_H,
      CURRENT_L,
      POWER_H,
      POWER_L,
	  OUTPUT_CMD_H,
	  OUTPUT_CMD_L,
      USR_CMD_H,
      USR_CMD_L,
      USR_LMT_H,
      USR_LMT_L,
}Registor_Pos;
/**
  * @}
  */

typedef enum {
	Lost=0,
	Connected,
} Link_Connection_typedef;

typedef enum{
      UnitERROR=0, 
      UnitIDLE, 
      UnitSTANDBY,
      UnitRUN
} Operate_State_typedef;

typedef enum{
      MASTER=0,
      SLAVE
}Link_Mode_typedef;

typedef struct { 
	double  Voltage,
			Current,
            Power,
			Voltage_Feedback;
	
	uint8_t PWR_Error,
            PWR_REM_Enable,
            PWR_REM_Indecate,
			PWR_OUTPUT_Indecate,
			PWR_INTERLOCK_Indecate;
	
}PWR_Status_typedef;

typedef struct { 
	Link_Mode_typedef  			Link_Mode;
	Link_Connection_typedef   	Link_Connection;
	
	uint8_t Link_Node,
			Link_Number,
			Link_MaxNumber;
	
	double  Link_Duty;
	
}Link_Status_typedef;

typedef struct { 
	uint8_t MODBUS_ADDRESS;
	
}Modbus_Status_typedef;

typedef struct { 
	double  User_Command,
			User_Command_Current,
            User_Limit,
			User_Limit_Current;
	uint8_t USER_Start;
	
}User_Status_typedef;

typedef struct { 
	Operate_State_typedef   	Operate_State;
	uint8_t SYS_Error,
			MCU_NO_ERROR,
			MCU_PWR_ENABLE,
			MCU_REM_ENABLE;
	float	MCU_Temperature;
	float	MCU_Reference;
	double	Output_Current_Cmd;
	
}MCU_Status_typedef;

typedef struct { 

    
	PWR_Status_typedef			PWR_Status;
	Link_Status_typedef			Link_Status;
	Modbus_Status_typedef		Modbus_Status;
	User_Status_typedef			User_Status;
	MCU_Status_typedef			MCU_Status;
    
	
	
	
	
	
	

} Unit_Status_typedef ;

extern osThreadId Link_TaskHandle;

extern Unit_Status_typedef Unit_Status;
  
void Registor_Update(void);
void IPR_Init(void);
void OPERATE_Process(void);
void State_Process(void);
void IDLE_Process(void);
void RUN_Prosess(void);
void ERROR_Prosess(void);
void Input_Interface_Process(void);
void Link_Manage_Process(void);


void Link_TransmitISR(void);
void Link_ReceiveISR(void);


void MCU_PWR_Enable(int enable);
void MCU_PWR_REM_Enable(int enable);
void MCU_Fault_Signal_Enable(int enable);
void MCU_PWR_Current_OutputCmdSet(float current);




void SYS_OPERATOR(void);
void sys_shoutdown(void);
extern void Lost_MasterConnection(void);

void BitChange(uint8_t* x,uint8_t* y,uint8_t* n);
void BitChange_16(uint16_t* x,uint16_t* y,uint16_t* n);


#endif
