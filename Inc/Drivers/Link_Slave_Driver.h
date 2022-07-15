#ifndef __LINK_SLAVE_DRIVER_H
#define __LINK_SLAVE_DRIVER_H

#include "stm32f2xx_hal.h"
#include "cmsis_os.h"

extern void Link_Slave_Initial(void);
extern void Link_Slave_Process(void);
extern TIM_HandleTypeDef htim4;

#endif
