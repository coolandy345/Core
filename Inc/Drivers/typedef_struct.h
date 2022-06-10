#ifndef __TYPEDEF_STRUCT_H
#define __TYPEDEF_STRUCT_H

#include "stm32f2xx_hal.h"

typedef enum {
  Driver_OK       = (uint8_t)0x00U,
  Driver_ERROR    = (uint8_t)0x01U,
  Driver_BUSY     = (uint8_t)0x02U,
  Driver_TIMEOUT  = (uint8_t)0x03U
} Driver_StatusTypeDef;

#define IS_REG_SETBIT(REG, BIT_MASK)   ((REG & BIT_MASK)==BIT_MASK)

#endif
