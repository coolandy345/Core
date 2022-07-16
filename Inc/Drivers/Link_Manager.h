#ifndef __LINK_MANAGER_H
#define __LINK_MANAGER_H

#include "stm32f2xx_hal.h"
#include "cmsis_os.h"



uint16_t MODBUS_REGISTER[8*16+10];
/** @defgroup Registor Map
  * @{
  */
enum Registor_Pos
{
      SYS_SR1=1,
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






extern int Master_Slave_Option; //Master=1  Slave=0
extern int Link_Address; //Default 0x30  = 48(dec)
extern void Link_Manager_Init(void);
extern void Link_Manager_Process(void);

enum Connect_State{
    disconnect=0,
    connect,
}Connect_State;

enum Operate_State
{
      ERROR=0, 
      IDLE, 
      STANDBY, 
      RUN
} Operate_State;

enum Link_Status
{
      MASTER=0, 
      SLAVE
}Link_Status;



extern struct Unit_Status { 

    Link_Status     link_Status;
    Operate_State   operate_State;
    Connect_State   connect_State;

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
            MCU_NO_FAULT;

    int LINK_Connect,
        LINK_Node,
        LINK_Number;

    int MODBUS_ADDRESS;
    


} Unit_Status ;


#define wdefew


#endif
