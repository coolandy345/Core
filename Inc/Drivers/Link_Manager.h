#ifndef __LINK_MANAGER_H
#define __LINK_MANAGER_H

#include "stm32f2xx_hal.h"
#include "cmsis_os.h"





extern int Master_Slave_Option; //Master=1  Slave=0
extern int Link_Address; //Default 0x30  = 48(dec)
extern void Link_Manager_Init(void);
extern void Link_Manager_Process(void);




#endif
