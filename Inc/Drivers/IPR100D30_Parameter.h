#ifndef __IPR100D30_Parameter_H
#define __IPR100D30_Parameter_H

#include "stm32f2xx_hal.h"
#include <string.h>

extern uint16_t SYS_Registor[8*16];

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
      USR_CMD,
      USR_LMT
}Registor_Pos;
/**
  * @}
  */

typedef enum {
	Lost,
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

    Link_Mode_typedef     		Link_Mode;
    Link_Connection_typedef   	Link_Connection;
    Operate_State_typedef   	Operate_State;

    float   Voltage,
            Current,
            Power,
            User_Command,
            User_Limit;
    
    int     PWR_Error,
            PWR_Enable,
            PWR_REM_Enable,
            SYS_Error,
            USER_Start,
            MCU_NO_FAULT,
            Link_Slave_Error,
            Link_Master_Error;

    int LINK_Connect,
        LINK_Node,
        LINK_Number;

    int MODBUS_ADDRESS;
    
} Unit_Status_typedef ;

extern Unit_Status_typedef Unit_Status;
  


void SYS_Registor_Init(void);
void SYS_OPERATOR(void);
void sys_shoutdown(void);
extern void Lost_MasterConnection(void);

void BitChange(uint8_t* x,uint8_t* y,uint8_t* n);
void BitChange_16(uint16_t* x,uint16_t* y,uint16_t* n);


#endif
