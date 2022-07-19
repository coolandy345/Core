#include "ADS1247.h"
#include "spi.h"
#include "main.h"
#include "Constant.h"

uint8_t 	ADS1247_DRDY_signals=0x01;
uint8_t 	ADS1247_TRAN_signals=0x02;
osMailQId  SPI_MailQueue_ID;

osMailQDef(SPI_MailQueue, 0x20, ADC_pkg_typedef);

osEvent spi_event;
ADC_pkg_typedef* SPI_package;

int ADC_Scan_POS=0;

uint8_t CH0_DATA[4];
uint8_t CH1_DATA[4];
uint8_t CH2_DATA[4];
uint8_t CH3_DATA[4];

uint8_t* CH_DATA[4];

uint32_t ADC_24bit_Value[4];
float ADC_voltage_Value[4];
float ADC_voltage_Value2[4];
float ADC_24bit_Value_Smooth[4];

float ADC_Value[4];


uint8_t SPI_Transmit_GPIO_ADS1247_getting_buffer[]={RREG,16-1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t SPI_Transmit_GPIO_ADS1247_INITSET_buffer[]={WREG|MUX1,0x01,VREFCON1_ON,DOR3_40_SPS};
uint8_t SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[]={WREG|MUX0,0x03,0x08,0x00,VREFCON1_ON,DOR3_40_SPS,WREG|GPIOCFG,0x00,0x08};
uint8_t SPI_Transmit_GPIO_ADS1247_MUXSET_buffer[]={WREG|MUX0,0x00,0x08};
uint8_t SPI_Transmit_GPIO_ADS1247_SELFOCAL_buffer[]={SELFOCAL};
uint8_t SPI_Transmit_GPIO_ADS1247_GPIOSET_buffer[]={WREG|GPIOCFG,0x00,0x08};
uint8_t SPI_Transmit_GPIO_ADS1247_RDATA_buffer[]={0x12,0xFF,0xFF,0xFF};
uint8_t receive_buffer[20];
uint8_t register_buffer[20];
uint8_t* data_buffer;



int init_test=1;
osEvent evt;

void ADS1247_Start_Convert(void);
void _Start_SPI(void);
void _Stop_SPI(void);
void ADS1247_Channel_Set(void);
void ADS1247_Value_Process(void);

/**
  * @brief  ADS1247/8 initialtize and calibrate
  * @note   
  * @param  None
  * @retval None
  */
void ADS1247_Init(void){
	
	CH_DATA[0]=CH0_DATA;
	CH_DATA[1]=CH1_DATA;
	CH_DATA[2]=CH2_DATA;
	CH_DATA[3]=CH3_DATA;
	
	
	HAL_GPIO_WritePin(ADC_Start_GPIO_Port, ADC_Start_Pin, GPIO_PIN_SET);
	evt=osSignalWait(ADS1247_DRDY_signals,osWaitForever );
	_Start_SPI();
	HAL_SPI_TransmitReceive_DMA(&hspi1,SPI_Transmit_GPIO_ADS1247_RDATA_buffer,receive_buffer,4);
	osSignalWait(ADS1247_TRAN_signals,osWaitForever );
	
	ADS1247_Channel_Set();
	
	HAL_SPI_TransmitReceive_DMA(&hspi1,SPI_Transmit_GPIO_ADS1247_INITSET_buffer,receive_buffer,4);
	osSignalWait(ADS1247_TRAN_signals,osWaitForever );
	
	HAL_SPI_TransmitReceive_DMA(&hspi1,SPI_Transmit_GPIO_ADS1247_SELFOCAL_buffer,receive_buffer,1);
	osSignalWait(ADS1247_TRAN_signals,osWaitForever );
	
	_Stop_SPI();
	
	HAL_GPIO_WritePin(ADC_Start_GPIO_Port, ADC_Start_Pin, GPIO_PIN_SET);
}

void _Start_SPI(void){
	HAL_GPIO_WritePin(SPI1_SS_ADC_GPIO_Port, SPI1_SS_ADC_Pin, GPIO_PIN_RESET);
}

void _Stop_SPI(void){
	HAL_GPIO_WritePin(SPI1_SS_ADC_GPIO_Port, SPI1_SS_ADC_Pin, GPIO_PIN_SET);
}

/**
  * @brief  ADS1247/8 process in block mode
  * @note   
  * @param  None
  * @retval None
  */
void ADS1247_Process(void){
 	osSignalWait(ADS1247_DRDY_signals,osWaitForever );
	
	_Start_SPI();
	
	HAL_SPI_TransmitReceive_DMA(&hspi1,SPI_Transmit_GPIO_ADS1247_RDATA_buffer,data_buffer,4);
	osSignalWait(ADS1247_TRAN_signals,osWaitForever );
	
	ADS1247_Value_Process();
	ADS1247_Channel_Set();
	
	
//	HAL_SPI_TransmitReceive_DMA(&hspi1,SPI_Transmit_GPIO_ADS1247_getting_buffer,register_buffer,18);
//	osSignalWait(ADS1247_TRAN_signals,osWaitForever );
	
	
	_Stop_SPI();
	
	HAL_GPIO_WritePin(ADC_Start_GPIO_Port, ADC_Start_Pin, GPIO_PIN_SET);
}

/**
  * @brief  ADS1247/8 process in block mode
  * @note   
  * @param  None
  * @retval None
  */
void ADS1247_Value_Process(void){

	
	uint8_t* Target_Buffer=CH_DATA[ADC_Scan_POS];
	int32_t tmp=	(uint32_t)*(Target_Buffer+1)<<16 | 
					(uint32_t)*(Target_Buffer+2)<<8 | 
					(uint32_t)*(Target_Buffer+3);
	
	if (tmp>0x7FFFFF){
		tmp-=0xFFFFFF;
	}
	
 	ADC_24bit_Value[ADC_Scan_POS]=	tmp;
	
	ADC_voltage_Value[ADC_Scan_POS]=((float)4.096*(float)ADC_24bit_Value[ADC_Scan_POS]/0x7FFFFF)+0.006;
	
	ADC_24bit_Value_Smooth[ADC_Scan_POS]=(float)ADC_24bit_Value[ADC_Scan_POS]*(0.1)+ADC_24bit_Value_Smooth[ADC_Scan_POS]*(0.9);
	
	
	if (ADC_Scan_POS==0){
		ADC_Value[ADC_Scan_POS]=find_Approtch(ADC_24bit_Value[ADC_Scan_POS],CH0_Data,32,10,0);
		Unit_Status.PWR_Status.Current=find_Approtch(ADC_Value[ADC_Scan_POS],Analog_Current_to_RealValue_Data,4,MAX_Unit_Current,MIN_Unit_Current);
		
	}else if(ADC_Scan_POS==1){
		ADC_Value[ADC_Scan_POS]=find_Approtch(ADC_24bit_Value[ADC_Scan_POS],CH1_Data,32,10,0);
		Unit_Status.PWR_Status.Voltage=find_Approtch(ADC_Value[ADC_Scan_POS],Analog_Voltage_to_RealValue_Data,8,MAX_Voltage,MIN_Voltage);
		
	}else if(ADC_Scan_POS==2){
		ADC_Value[ADC_Scan_POS]=find_Approtch(ADC_24bit_Value[ADC_Scan_POS],CH2_Data,32,20,0);
		Unit_Status.User_Status.User_Command=find_Approtch(ADC_Value[ADC_Scan_POS],Analog_4_20_to_RealValue_Data,8,MAX_4_20_Data_Uplimit,MIN_4_20_Data_Downlimit);
		double data[2*2]={0,0,100,Unit_Status.User_Status.User_Limit_Current};
		Unit_Status.User_Status.User_Command_Current=find_Approtch(Unit_Status.User_Status.User_Command,data,4,MAX_Sys_Current,MIN_Sys_Current);
		
	}else if(ADC_Scan_POS==3){
		if(Unit_Status.Link_Status.Link_Mode==MASTER){
			ADC_Value[ADC_Scan_POS]=find_Approtch(ADC_24bit_Value[ADC_Scan_POS],CH3_Data,24,5,0);
			Unit_Status.User_Status.User_Limit=find_Approtch(ADC_Value[ADC_Scan_POS],Analog_Limit_to_RealValue_Data,4,MAX_Limit_Data_Uplimit,MIN_Limit_Data_Downlimit);
			Unit_Status.User_Status.User_Limit_Current=Unit_Status.User_Status.User_Limit*MAX_Sys_Current/100;
			
		}else{
			Unit_Status.User_Status.User_Limit=0;
			Unit_Status.User_Status.User_Limit_Current=0;
		
		}
		
	}
	
		
}

double find_Approtch(double input,double* data_array , int len,float max,float min){
	if (input<0xFFFFFF){
		
		int i=0;
		int compare=0;
		while(compare==0){
			
			if(data_array[i*2]>=input){
				if (i==0){
					double tmp = data_array[1];
					if (tmp>=max){
						return max;
					}else if(tmp<=min){
					
						return min;
					}else{
						return tmp;
					
					}
				}
				compare=1;
			}else{
				i++;
			}
			if (i>=len){
				double tmp = data_array[len-1];
				if (tmp>=max){
					return max;
				}else if(tmp<=min){
				
					return min;
				}else{
					return tmp;
				
				}
			}
		}
		
		double gap=data_array[i*2]-data_array[i*2-2];
		gap=(input-data_array[i*2-2])/gap;
		
		double tmp=((float)data_array[i*2+1]-(float)data_array[i*2-1])*gap;
		tmp+=(float)data_array[i*2-1];
		
		if (tmp>=max){
		
			return max;
		}else if(tmp<=min){
		
			return min;
		}else{
			return tmp;
		
		}
	
	
	}
	
	return 0;
}


/**
  * @brief  ADS1247/8 process in block mode
  * @note   
  * @param  None
  * @retval None
  */
void ADS1247_Channel_Set(void){

	

	if (ADC_Scan_POS==0){
		ADC_Scan_POS=2;
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[2]=0x13; //p2 n3
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[8]=0x08; //l3
	
	}else if(ADC_Scan_POS==1){
		ADC_Scan_POS=3;
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[2]=0x1A; //p3 n2
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[8]=0x04; //l2
	
	}else if(ADC_Scan_POS==2){
		ADC_Scan_POS=1;
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[2]=0x0A; //p1 n2
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[8]=0x04; //l2
	
	}else if(ADC_Scan_POS==3){
		ADC_Scan_POS=0;
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[2]=0x03; //p0 n3
		SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer[8]=0x08; //l3
	
	}
	
	data_buffer=CH_DATA[ADC_Scan_POS];
	
	
	HAL_SPI_TransmitReceive_DMA(&hspi1,SPI_Transmit_GPIO_ADS1247_MUXGPIOSET_buffer,receive_buffer,9);
	osSignalWait(ADS1247_TRAN_signals,osWaitForever );
	
	
}

/**
  * @brief  ADS1247/8 Ready_Callback
  * @note   Call by GPIO interrupt when data ready
  * @param  None
  * @retval None
  */
void ADS1247_Ready_Callback(void){
	
	osSignalSet (ADS1247_TaskHandle,ADS1247_DRDY_signals);
}
/**
  * @brief  ADS1247/8 Ready_Callback
  * @note   Call by GPIO interrupt when data ready
  * @param  None
  * @retval None
  */
void ADS1247_TxRxCpltCallback(void){
	
	osSignalSet (ADS1247_TaskHandle,ADS1247_TRAN_signals);
	
}
/**
  * @brief  ADS1247/8 Start Convert
  * @note   None
  * @param  None
  * @retval None
  */
void ADS1247_Start_Convert(void){

	HAL_GPIO_WritePin(ADC_Start_GPIO_Port, ADC_Start_Pin, GPIO_PIN_SET);
	osDelay(1);
	HAL_GPIO_WritePin(ADC_Start_GPIO_Port, ADC_Start_Pin, GPIO_PIN_RESET);
}
