#ifndef __LINK_MASTER_DRIVER_H
#define __LINK_MASTER_DRIVER_H

#include "stm32f2xx_hal.h"
#include "cmsis_os.h"

extern void Link_Master_Initial(void);
extern void Link_Master_Process(void);
extern TIM_HandleTypeDef htim11;

#endif
