/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "modbusRTU.h"
//#include "Link_Driver.h"
#include "IPR100D30_Parameter.h"
#include "typedef_struct.h"
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern osThreadId ADS1247_TaskHandle;
extern osThreadId ADC_TaskHandle;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern int hard_fault;
extern int test[10];
extern float test_float[10];
extern int UART_errorcounter;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
//#define MASTER

#define Analog_IN_FeedBack_s_Pin GPIO_PIN_3
#define Analog_IN_FeedBack_s_GPIO_Port GPIOC
#define TIM2_CCCV_Control_Pin GPIO_PIN_3
#define TIM2_CCCV_Control_GPIO_Port GPIOA
#define SPI1_SS_ADC_Pin GPIO_PIN_4
#define SPI1_SS_ADC_GPIO_Port GPIOA
#define ADC_Ready_Pin GPIO_PIN_4
#define ADC_Ready_GPIO_Port GPIOC
#define ADC_Ready_EXTI_IRQn EXTI4_IRQn
#define ADC_Start_Pin GPIO_PIN_5
#define ADC_Start_GPIO_Port GPIOC
#define ADC_Reset_Pin GPIO_PIN_0
#define ADC_Reset_GPIO_Port GPIOB
#define MCU_CCCV_SELECT_Pin GPIO_PIN_2
#define MCU_CCCV_SELECT_GPIO_Port GPIOB
#define USER_ENABLE_Pin GPIO_PIN_10
#define USER_ENABLE_GPIO_Port GPIOB
#define SYSTEM_FAULT_Pin GPIO_PIN_11
#define SYSTEM_FAULT_GPIO_Port GPIOB
#define SYSTEM_FAULT_EXTI_IRQn EXTI15_10_IRQn
#define PWR_REMOTE_INDICATION_Pin GPIO_PIN_12
#define PWR_REMOTE_INDICATION_GPIO_Port GPIOB
#define PWR_OUTPUT_ON_INDICATION_Pin GPIO_PIN_13
#define PWR_OUTPUT_ON_INDICATION_GPIO_Port GPIOB
#define MCU_FAULT_Pin GPIO_PIN_14
#define MCU_FAULT_GPIO_Port GPIOB
#define MCU_PWR_ENABLE_Pin GPIO_PIN_15
#define MCU_PWR_ENABLE_GPIO_Port GPIOB
#define PWR_INTERLOCK_Pin GPIO_PIN_6
#define PWR_INTERLOCK_GPIO_Port GPIOC
#define PWR_INTERLOCK_EXTI_IRQn EXTI9_5_IRQn
#define PWR_FAULT_INDICATION_Pin GPIO_PIN_7
#define PWR_FAULT_INDICATION_GPIO_Port GPIOC
#define PWR_FAULT_INDICATION_EXTI_IRQn EXTI9_5_IRQn
#define Master_Select_Pin GPIO_PIN_8
#define Master_Select_GPIO_Port GPIOC
#define CCCV_Select_Pin GPIO_PIN_9
#define CCCV_Select_GPIO_Port GPIOC
#define MODBUS_ADD_1_Pin GPIO_PIN_8
#define MODBUS_ADD_1_GPIO_Port GPIOA
#define MODBUS_ADD_2_Pin GPIO_PIN_9
#define MODBUS_ADD_2_GPIO_Port GPIOA
#define MODBUS_ADD_3_Pin GPIO_PIN_10
#define MODBUS_ADD_3_GPIO_Port GPIOA
#define MODBUS_ADD_4_Pin GPIO_PIN_11
#define MODBUS_ADD_4_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define UART5_EN_Pin GPIO_PIN_11
#define UART5_EN_GPIO_Port GPIOC
#define USART1_EN_Pin GPIO_PIN_4
#define USART1_EN_GPIO_Port GPIOB
#define TIM4_Slave_In_Pin GPIO_PIN_8
#define TIM4_Slave_In_GPIO_Port GPIOB
#define TIM4_Master_Out_Pin GPIO_PIN_9
#define TIM4_Master_Out_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
