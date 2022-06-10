#ifndef __IPR100D30_Parameter_H
#define __IPR100D30_Parameter_H

#include "stm32f2xx_hal.h"
#include <string.h>

/** @defgroup Registor Map
  * @{
  */
#define SYSSTATUS			0x0001		// 	System Status Registor
#define CONTRL				0x0002		//	Control Registor
#define HV_VOLTAGE			0x0003		//	HV Output Voltage Analog Registor
#define AC_VOLTAGE_RMS		0x0004		//	AC Input Voltage RMS Analog Registor
#define AC_CURRENT_RMS		0x0005		//	AC Input Current RMS Analog Registor
#define AC_CURRENT			0x0006		//	AC Input Current REF Analog Registor
#define PHASE_A_CURRENT		0x0007		//	Phase A Current Analog Registor
#define PHASE_B_CURRENT		0x0008		//	Phase B Current Analog Registor
#define PHASE_C_CURRENT		0x0009		//	Phase C Current Analog Registor

#define TEMP_BridgeDiode	0x000A		//	Temperature 1 Analog Registor
#define TEMP_MOSFET			0x000B		//	Temperature 2 Analog Registor
#define TEMP_MCU			0x000C		//	Temperature 2 Analog Registor

#define PFC_ON_COIL			0x000D		//	PFC_ON 				Coil
#define PFC_OFF_COIL		0x000E		//	PFC_OFF 			Coil
#define ERR_RST_COIL		0x000F		//	Error_Reset 		Coil
#define CONNECT_POLL_COIL	0x0010		//	Connection_Check 	Coil

#define ERROR_CODE_BACKUP	0x0011		// 	Backup System Status Registor



/*
	float 	HV_Voltage;
	float 	AC_Voltage_RMS;
	float 	AC_Current_RMS;
	float 	AC_Current;
	float 	Phase_A_Current;
	float 	Phase_B_Current;
	float 	Phase_C_Current;
	float 	Temp_BridgeDiode;
	float 	Temp_Mosfet;
	float 	Temp_MCU;
*/

/**
  * @}
  */

/** @defgroup Registor SYSSTATUS
  * @{
  */

#define SYSSTATUS_PFC_ON_Pos          	(0U)                                     
#define SYSSTATUS_PFC_ON_Msk          	(0x1UL << SYSSTATUS_PFC_ON_Pos)            /*!< 0x00000001 */
#define SYSSTATUS_PFC_ON              	SYSSTATUS_PFC_ON_Msk                       /*!< Power ON */

#define SYSSTATUS_PFC_ErrLatch_Pos    	(1U)                                     
#define SYSSTATUS_PFC_ErrLatch_Msk    	(0x1UL << SYSSTATUS_PFC_ErrLatch_Pos)      /*!< 0x00000001 */
#define SYSSTATUS_PFC_ErrLatch        	SYSSTATUS_PFC_ErrLatch_Msk                 /*!< Error Latch */	



#define SYSSTATUS_OCP_Pos              (8U)                                     
#define SYSSTATUS_OCP_Msk              (0x1UL << SYSSTATUS_OCP_Pos)              	/*!< 0x00000001 */
#define SYSSTATUS_OCP                  SYSSTATUS_OCP_Msk                         	/*!< Over Current */

#define SYSSTATUS_OVP_Pos              (9U)                                     
#define SYSSTATUS_OVP_Msk              (0x1UL << SYSSTATUS_OVP_Pos)              	/*!< 0x00000001 */
#define SYSSTATUS_OVP                  SYSSTATUS_OVP_Msk                         	/*!< Over Voltage */

#define SYSSTATUS_OTP1_Pos             (10U)                                     
#define SYSSTATUS_OTP1_Msk             (0x1UL << SYSSTATUS_OTP1_Pos)              /*!< 0x00000001 */
#define SYSSTATUS_OTP1                 SYSSTATUS_OTP1_Msk                         /*!< Over Temperature 1 */

#define SYSSTATUS_UTP1_Pos             (11U)                                     
#define SYSSTATUS_UTP1_Msk             (0x1UL << SYSSTATUS_UTP1_Pos)              /*!< 0x00000001 */
#define SYSSTATUS_UTP1                 SYSSTATUS_UTP1_Msk                         /*!< Temperature Burnout1 */

#define SYSSTATUS_OTP2_Pos             (12U)                                     
#define SYSSTATUS_OTP2_Msk             (0x1UL << SYSSTATUS_OTP2_Pos)              /*!< 0x00000001 */
#define SYSSTATUS_OTP2                 SYSSTATUS_OTP2_Msk                         /*!< Over Temperature 2 */

#define SYSSTATUS_UTP2_Pos             (13U)                                     
#define SYSSTATUS_UTP2_Msk             (0x1UL << SYSSTATUS_UTP2_Pos)              /*!< 0x00000001 */
#define SYSSTATUS_UTP2                 SYSSTATUS_UTP2_Msk                         /*!< Temperature Burnout2 */

#define SYSSTATUS_UVLO_Pos             (14U)                                     
#define SYSSTATUS_UVLO_Msk             (0x1UL << SYSSTATUS_UVLO_Pos)              /*!< 0x00000001 */
#define SYSSTATUS_UVLO                 SYSSTATUS_UVLO_Msk                         /*!< Low HV input voltage */

#define SYSSTATUS_OVLO_Pos             (15U)                                     
#define SYSSTATUS_OVLO_Msk             (0x1UL << SYSSTATUS_OVLO_Pos)              /*!< 0x00000001 */
#define SYSSTATUS_OVLO                 SYSSTATUS_OVLO_Msk                         /*!< High HV input voltage */
/**
  * @}
  */


/** @defgroup Registor CONTRL
  * @{
  */
#define CONTRL_PFC_SWON_Pos           	(0U)
#define CONTRL_PFC_SWON_Msk           	(0x1UL << CONTRL_PFC_SWON_Pos)        /*!< 0x00000001 */
#define CONTRL_PFC_SWON               	CONTRL_PFC_SWON_Msk                   /*!< Power software ON */

#define CONTRL_PFC_ErrRST_Pos     		(1U)
#define CONTRL_PFC_ErrRST_Msk     		(0x1UL << CONTRL_PFC_ErrRST_Pos)      /*!< 0x00000001 */
#define CONTRL_PFC_ErrRST         		CONTRL_PFC_ErrRST_Msk                 /*!< Error Reset */

#define CONTRL_PFC_SWAP_Pos     		(2U)
#define CONTRL_PFC_SWAP_Msk     		(0x1UL << CONTRL_PFC_SWAP_Pos)        /*!< 0x00000001 */
#define CONTRL_PFC_SWAP         		CONTRL_PFC_SWAP_Msk                 /*!< Error Reset */
/**
  * @}
  */

/** @defgroup ADC_Parameter
  * @{
  */
#define REF_VOLTAGE 3  
/**
  * @}
  */

typedef struct Power_typedef{
	
	uint8_t 	OverVoltage;
	uint8_t 	UnderVoltage;
	
}Power_typedef;


typedef struct PFC_Error_typedef{
	
	uint8_t 	Error;
	uint8_t 	Error_OCP;
	uint8_t 	Error_OVP;
	uint8_t 	Error_OTP1;
	uint8_t 	Error_UTP1;
	uint8_t 	Error_OTP2;
	uint8_t 	Error_UTP2;
	uint8_t 	Error_UVLO;
	uint8_t 	Error_OVLO;
	
}PFC_Error_typedef;

typedef enum {
	none,
	Active,
} PFC_ErrorRST_typedef;

typedef enum {
	Lost,
	Connected,
} Master_Connection_typedef;

typedef enum {
	Shut_Down,
	Start_UP,
} PFC_Startup_typedef;

typedef enum {
	Software_OFF,
	Software_ON_Ready,
} PFC_SW_ON_typedef;

typedef struct PFC_Status_typedef{
	
	Master_Connection_typedef MasterConnection;
	PFC_Startup_typedef PFC_ON;
	PFC_SW_ON_typedef PFC_SWON;
	PFC_ErrorRST_typedef Error_Reset;
	int Swap;
	
	float 	HV_Voltage;
	float 	AC_Voltage_RMS;
	float 	AC_Current_RMS;
	float 	AC_Current;
	float 	Phase_A_Current;
	float 	Phase_B_Current;
	float 	Phase_C_Current;
	float 	Temp_BridgeDiode;
	float 	Temp_Mosfet;
	float 	Temp_MCU;
	
	PFC_Error_typedef	Error_Status;
	
}PFC_Status_typedef;  
  
extern PFC_Status_typedef PFC_Status;
extern float ACin;
extern float Vout;
extern float Iout;
extern float Temp_BridgeDiode;
extern float Temp_MOSFET;

extern uint8_t GPIO_InputData[3];

extern uint16_t SYS_Registor[18];
extern uint8_t PFC_SWON,PFC_ErrRST;


extern uint8_t Master_ConnectionStatus;
extern uint8_t Err_OCP,Err_OVP,Err_OTP1,Err_OTP2,Err_UTP1,Err_UTP2,Err_UVLO,Err_OVLO,Err_15V_P_OVP,Err_15V_P_UVP,Err_5V_P_OVP,Err_5V_P_UVP,PFC_ON,Err_Latch;



void SYS_Registor_Init(void);
void SYS_OPERATOR(void);
void sys_shoutdown(void);
extern void Lost_MasterConnection(void);

void BitChange(uint8_t* x,uint8_t* y,uint8_t* n);
void BitChange_16(uint16_t* x,uint16_t* y,uint16_t* n);


#endif
