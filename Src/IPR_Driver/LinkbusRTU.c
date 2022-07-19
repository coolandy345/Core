#include "LinkbusRTU.h"
#include "IPR100D30_Parameter.h"
#include "main.h"

Link_RTU_typedef Link_Transmit_pkg;
Link_RTU_typedef Link_Receive_pkg;


Driver_StatusTypeDef Link_ModbusRTU_analyze(Link_RTU_typedef *Modbus){     //
	
	Link_Modbus_init(Modbus);
	
	Modbus->Slave_Address 		= Modbus->BUS_Array[0];
	
	if(Modbus->Slave_Address==Unit_Status.Modbus_Status.MODBUS_ADDRESS | Modbus->Slave_Address==General_address){
		
		Modbus->Function      		= Modbus->BUS_Array[1]; //
		Modbus->Register_Address 	= ((uint16_t)Modbus->BUS_Array[2]<<8|Modbus->BUS_Array[3]);
		
		switch (Modbus->Function){    		//
			
			case Modbus_Function_Multi_Read:
				Link_multi_read_analyze(Modbus);   	//
				break;
			
			case Modbus_Function_Single_write:
				Link_Single_write_analyze(Modbus);   //
				break;
			
			case Modbus_Function_Multi_write:
				Link_multi_write_analyze(Modbus);  	//
				break;
			
			default:
				return Driver_ERROR;
		}
		if(Link_CRC_Check_verify(Modbus)!=Driver_OK){
			return Driver_ERROR;
		}else{
			return Driver_OK;
		}
	}else{
		
		return Driver_ERROR;
	}
}

/**
  * @brief Modbus Device Respond Function
  * @param None
  * @retval None
  */
void Link_Modbus_Respond(Link_RTU_typedef *RxModbus,Link_RTU_typedef *TxModbus){
	
	*TxModbus=*RxModbus;
	
	switch (RxModbus->Function){
			
		case Modbus_Function_Multi_Read:
			
			for(uint8_t len=0;len<RxModbus->Data_Length_Word;len++ ){
				
				TxModbus->Data_Array[2*len]		=	SYS_Registor[RxModbus->Register_Address+len]	>>	8;
				TxModbus->Data_Array[1+2*len]	=	SYS_Registor[RxModbus->Register_Address+len] 	& 	0xFF;
			
			}
			break;
		
		case Modbus_Function_Single_write:
			//check if master is going to write correct address
			if(RxModbus->Register_Address>=SYS_SR && RxModbus->Register_Address<=USR_LMT_L){
				SYS_Registor[RxModbus->Register_Address]	=	(((uint16_t)RxModbus->Data_Array[0]<<8) | (RxModbus->Data_Array[1]&0xFF) );
			}
			
			break;
		
		case Modbus_Function_Multi_write:
			
			for(uint8_t len=0;len<RxModbus->Data_Length_Word;len++ ){
				
				int position=RxModbus->Register_Address+len;
				if(position>=SYS_SR && position<=USR_LMT_L){
					SYS_Registor[position]	=	((uint16_t)RxModbus->Data_Array[2*len]<<8 | RxModbus->Data_Array[1+2*len] );
				}
				
			}
			break;
		
		default:
			break;
	}
	Link_ModbusRTU_format(TxModbus);
}

void Link_multi_read_analyze(Link_RTU_typedef *Modbus){
	
	Modbus->Data_Length_Word = (uint16_t)Modbus->BUS_Array[4]<<8|Modbus->BUS_Array[5];
	Modbus->CRC_Low  = Modbus->BUS_Array[6];
	Modbus->CRC_High = Modbus->BUS_Array[7];
	Modbus->BUS_length = 8;
}

void Link_Single_write_analyze(Link_RTU_typedef *Modbus){
	
	memmove(Modbus->Data_Array,Modbus->BUS_Array+4,2);
	Modbus->Data_Length_Word = 1;
	Modbus->CRC_Low  = Modbus->BUS_Array[6];
	Modbus->CRC_High = Modbus->BUS_Array[7];
	Modbus->BUS_length = 8;
}
void Link_multi_write_analyze(Link_RTU_typedef *Modbus){
	
	Modbus->Data_Length_Word = (uint16_t)Modbus->BUS_Array[4]<<8|Modbus->BUS_Array[5];
	Modbus->Data_Length_Byte = Modbus->BUS_Array[6];
	memmove(Modbus->Data_Array,Modbus->BUS_Array+7,2*Modbus->Data_Length_Word);
	Modbus->CRC_Low  = Modbus->BUS_Array[7+2*Modbus->Data_Length_Word];
	Modbus->CRC_High = Modbus->BUS_Array[8+2*Modbus->Data_Length_Word];
	Modbus->BUS_length = 9+2*Modbus->Data_Length_Word;
}



Driver_StatusTypeDef Link_ModbusRTU_format(Link_RTU_typedef *Modbus){
	
	if( Modbus->Function==0 |Modbus->Data_Length_Word==0 ){
		return Driver_ERROR;
	}
	
	Modbus->BUS_Array[0]  = Device_address;
	Modbus->BUS_Array[1]  = Modbus->Function;

	switch (Modbus->Function){

		case Modbus_Function_Multi_Read:
			Link_Multi_Read_Format(Modbus);
			break;

		case Modbus_Function_Single_write:
			Link_Single_Write_Format(Modbus);
			break;

		case Modbus_Function_Multi_write:
			Link_Multi_Write_Format(Modbus);
			break;

		default:
			return Driver_ERROR;
	}
	return Driver_OK;
}

void Link_Multi_Read_Format(Link_RTU_typedef *Modbus){
	
	Modbus->BUS_Array[2]=Modbus->Data_Length_Word*2;
	memmove(3+Modbus->BUS_Array,Modbus->Data_Array,2*Modbus->Data_Length_Word);
	Modbus->BUS_length=5+2*Modbus->Data_Length_Word;
	uint16_t crc = Software_16BIT_crc(Modbus->BUS_Array,Modbus->BUS_length-2);
	
	Modbus->CRC_Low  	= crc & 0xFF;
	Modbus->CRC_High  	= (crc>>8)  & 0xFF;
	
	Modbus->BUS_Array[3+2*Modbus->Data_Length_Word]  = Modbus->CRC_Low;
	Modbus->BUS_Array[4+2*Modbus->Data_Length_Word]  = Modbus->CRC_High;
  
}

void Link_Single_Write_Format(Link_RTU_typedef *Modbus){
  
	Modbus->BUS_Array[2]=Modbus->Register_Address>>8;
	Modbus->BUS_Array[3]=Modbus->Register_Address&0x00FF;
	memmove(Modbus->BUS_Array+4,Modbus->Data_Array,2);
	Modbus->BUS_length=8;
	uint16_t crc = Software_16BIT_crc(Modbus->BUS_Array,Modbus->BUS_length-2);
	
	Modbus->CRC_Low  		= crc & 0xFF;
	Modbus->CRC_High  	= (crc>>8)  & 0xFF;
	
	Modbus->BUS_Array[6]  = Modbus->CRC_Low;
	Modbus->BUS_Array[7]  = Modbus->CRC_High;
  
}

void Link_Multi_Write_Format(Link_RTU_typedef *Modbus){
	
	Modbus->BUS_Array[2]=Modbus->Register_Address>>8;
	Modbus->BUS_Array[3]=Modbus->Register_Address&0x00FF;
	Modbus->BUS_Array[2]=Modbus->BUS_length>>8;
	Modbus->BUS_Array[3]=Modbus->BUS_length&0x00FF;
	Modbus->BUS_length=8;
	uint16_t crc = Link_Software_16BIT_crc(Modbus->BUS_Array,Modbus->BUS_length-2);
	
	Modbus->CRC_Low  	= crc & 0xFF;
	Modbus->CRC_High  	= (crc>>8)  & 0xFF;
	
	Modbus->BUS_Array[3+2*Modbus->Data_Length_Word]  = Modbus->CRC_Low;
	Modbus->BUS_Array[4+2*Modbus->Data_Length_Word]  = Modbus->CRC_High;
}



Driver_StatusTypeDef Link_CRC_Check_verify(Link_RTU_typedef *Modbus){
	
	uint16_t Slave_crc	= Link_Software_16BIT_crc(Modbus->BUS_Array,Modbus->BUS_length-2);
	
	uint16_t Master_crc	= ((uint16_t)Modbus->CRC_High<<8|Modbus->CRC_Low);
	if(Slave_crc == Master_crc){
		Modbus->CRC_verify = 1;
		return Driver_OK;
	}else{
		Modbus->CRC_verify = 0;
		return Driver_ERROR;
	}
}
uint16_t Link_Software_16BIT_crc(volatile uint8_t *crc_data,uint8_t length){
  
  uint16_t crc = 0xFFFF;
  uint8_t	j;
  uint8_t len=length;
	
  while(len--){
    crc ^= *crc_data++;
    for(j = 0; j < 8; j++){
      if(crc & 1){
        crc=(crc >> 1)^0xA001;
      }else{
        crc = crc >> 1;
      }
    }
  }
  return crc; 
}

void Link_Modbus_init(Link_RTU_typedef *Modbus){
	
	Modbus->Slave_Address=0;
	Modbus->Function=0;
	Modbus->Register_Address=0;
	Modbus->Data_Length_Word=0;
	Modbus->Data_Length_Byte=0;
	Modbus->CRC_Low=0;
	Modbus->CRC_High=0;
	Modbus->CRC_verify=0;
	Modbus->Expired=0;
	Modbus->BUS_length=0;
	memset(&Modbus->Data_Array,0,100);
	//memset(&Modbus->BUS_Array,0,50);
	
}

void Link_RecevieMode(void){
	HAL_GPIO_WritePin(UART5_EN_GPIO_Port,UART5_EN_Pin,GPIO_PIN_RESET);
}

void Link_TransmitMode(void){
	HAL_GPIO_WritePin(UART5_EN_GPIO_Port,UART5_EN_Pin,GPIO_PIN_SET);
	
}
