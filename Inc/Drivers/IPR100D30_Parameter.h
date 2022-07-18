#ifndef __IPR100D30_Parameter_H
#define __IPR100D30_Parameter_H

#include "stm32f2xx_hal.h"
#include <string.h>


extern uint16_t SYS_Registor[12*16];

/** @defgroup Registor Map
  * @{
  */
typedef enum{
      SYS_SR1=0,
      SYS_SR2,
      LINK_SR,
      VOLTAGE,
      CURRENT,
      POWER,
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
	float   Voltage,
            Current,
            Power;
	
	int     PWR_Error,
            PWR_Enable,
            PWR_REM_Enable;
	
}PWR_Status_typedef;

typedef struct { 
	Link_Mode_typedef  			Link_Mode;
	Link_Connection_typedef   	Link_Connection;
	int LINK_Node,
        LINK_Number,
		LINK_MaxNumber,
		Link_Slave_Error,
		Link_Master_Error;
}Link_Status_typedef;

typedef struct { 
	int MODBUS_ADDRESS;
	
}Modbus_Status_typedef;

typedef struct { 
	float   User_Command,
			User_Command_Current,
            User_Limit;
	int     USER_Start;
	
}User_Status_typedef;

typedef struct { 

    Operate_State_typedef   	Operate_State;
	PWR_Status_typedef			PWR_Status;
	Link_Status_typedef			Link_Status;
	Modbus_Status_typedef		Modbus_Status;
	User_Status_typedef			User_Status;
	
    int     SYS_Error;
	float	MCU_Temp;
	float	Output_Current_Cmd;

} Unit_Status_typedef ;

extern Unit_Status_typedef Unit_Status;
  

extern void IPR_Init(void);
void OPERATE_Process(void);
void State_Process(void);
void IDLE_Process(void);
void RUN_Prosess(void);
void ERROR_Prosess(void);
void Input_Interface_Process(void);
void Link_Manage_Process(void);




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
