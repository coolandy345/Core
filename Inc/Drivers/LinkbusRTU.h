#ifndef __LINKBUSRTU_H
#define __LINKBUSRTU_H

#include <string.h>
#include <stdlib.h>
#include "typedef_struct.h"
#include "main.h"

/*--------------Function Table---------------*/
#define Modbus_Function_Multi_Read  	0x03
#define Modbus_Function_Single_write  	0x06
#define Modbus_Function_Multi_write 	0x10

/*----------Modifly to each device-----------*/
#define Device_address 0x77
#define General_address 0xFF

typedef struct
{
	uint8_t 	Slave_Address;
	uint8_t 	Function;
	uint16_t	Register_Address;
	uint16_t 	Data_Length_Word;
	uint16_t 	Data_Length_Byte;
	
	uint8_t 	CRC_Low;
	uint8_t 	CRC_High;
	
	uint8_t		BUS_length;
	uint8_t 	BUS_Array[200];
	uint8_t 	Data_Array[200];
	
	uint8_t 	CRC_verify;
	uint8_t 	Expired;
}Link_RTU_typedef;

extern Link_RTU_typedef Link_Transmit_pkg;
extern Link_RTU_typedef Link_Receive_pkg;

Driver_StatusTypeDef Link_ModbusRTU_analyze(Link_RTU_typedef *Modbus);

extern void Link_Modbus_Respond(Link_RTU_typedef *RxModbus,Link_RTU_typedef *TxModbus);

void Link_Single_write_analyze(Link_RTU_typedef *Modbus);
void Link_multi_read_analyze(Link_RTU_typedef *Modbus);
void Link_multi_write_analyze(Link_RTU_typedef *Modbus);

Driver_StatusTypeDef Link_ModbusRTU_format(Link_RTU_typedef *Modbus);
void Link_Multi_Read_Format(Link_RTU_typedef *Modbus);
void Link_Single_Write_Format(Link_RTU_typedef *Modbus);
void Link_Multi_Write_Format(Link_RTU_typedef *Modbus);

Driver_StatusTypeDef Link_CRC_Check_verify(Link_RTU_typedef *Modbus);
uint16_t Link_Software_16BIT_crc(volatile uint8_t *crc_data,uint8_t length);

void Link_Modbus_init(Link_RTU_typedef *Modbus);
void Link_RecevieMode(void);

void Link_TransmitMode(void);

#endif
