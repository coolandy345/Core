#ifndef __MODBUSRTU_H
#define __MODBUSRTU_H

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
	uint8_t 	BUS_Array[100];
	uint8_t 	Data_Array[100];
	
	uint8_t 	CRC_verify;
	uint8_t 	Expired;
}modbus_RTU_typedef;

extern modbus_RTU_typedef Modbus_Transmit_pkg;
extern modbus_RTU_typedef Modbus_Receive_pkg;

Driver_StatusTypeDef ModbusRTU_analyze(modbus_RTU_typedef *Modbus);

extern void Modbus_Respond(modbus_RTU_typedef *RxModbus,modbus_RTU_typedef *TxModbus);

void Single_write_analyze(modbus_RTU_typedef *Modbus);
void multi_read_analyze(modbus_RTU_typedef *Modbus);
void multi_write_analyze(modbus_RTU_typedef *Modbus);

Driver_StatusTypeDef ModbusRTU_format(modbus_RTU_typedef *Modbus);
void Multi_Read_Format(modbus_RTU_typedef *Modbus);
void Single_Write_Format(modbus_RTU_typedef *Modbus);
void Multi_Write_Format(modbus_RTU_typedef *Modbus);

Driver_StatusTypeDef CRC_Check_verify(modbus_RTU_typedef *Modbus);
uint16_t Software_16BIT_crc(volatile uint8_t *crc_data,uint8_t length);

void Modbus_init(modbus_RTU_typedef *Modbus);
void RS485_Driver_RecevieMode(void);

void RS485_Driver_TransmitMode(void);

#endif
