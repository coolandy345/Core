#include "ADS1247.h"
#include "spi.h"
#include "main.h"

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
double ADC_24bit_Value_Smooth[4];

double ADC_Value[4];


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

#ifdef MASTER
//Master
float CH0_Data[16*2]={
835298.4602763	,0,
839074.3583138	,0.01,
865976.7968854	,0.05,
900293.3313094	,0.1,
1168656.763353	,0.5,
1504745.305361	,1,
2176023.424451	,2,
2847647.634488	,3,	
3519778.097083	,4,
4190922.500637	,5,
4862232.163184	,6,
5532735.795284	,7,
6189482.601365	,8,
6827200.560022	,9,
7449034.599245	,10,
7570721.56754	,10.198
};

float CH1_Data[16*2]={
833353.6845146	,0,
837461.2847583	,0.01,
864340.3053593	,0.05,
898661.0789148	,0.1,
1166942.245877	,0.5,
1502958.172314	,1,
2174064.395306	,2,
2845526.721584	,3,
3517508.019228	,4,
4188499.763665	,5,
4859652.481287	,6,
5530019.611033	,7,
6186760.276947	,8,
6824415.524446	,9,
7446170.1033	,10,
7567852.043985	,10.198
};
float CH2_Data[16*2]={
4186046.036353	,0,
4188379.124374	,0.01,
4196598.352615	,0.05,
4206860.375472	,0.1,
4288957.047590	,0.5,
4597067.601587	,2,
5007982.576511	,4,
5418093.886698	,6,
5824089.146629	,8,
6222943.016404	,10,
6614412.859862	,12,
6999542.731095	,14,
7379299.096538	,16,
7753690.658293	,18,
8123457.293697	,20,
8141827.68632	,20.1
};

float CH3_Data[12*2]={
4186062.069941	,0,
4193324.220882	,0.01, 
4226244.425261	,0.05,
4267386.003597	,0.1,
4596468.606086	,0.5,
5007739.094635	,1,
5825374.313667	,2, 
6616077.372049	,3,
7382226.06547	,4,
7757167.238647	,4.5,
8127318.440111	,5,
8200820.142612	,5.1
};
#else
//Slave
float CH0_Data[16*2]={
834835.3104	,0,
838651.5365001	,0.01,
865988.3887729	,0.05,
899851.1754919	,0.1,
1167802.391043	,0.5,
1503270.029	,1,
2173562.800	,2,
2844172.204	,3,
3515333.85	,4,
4185501.546	,5,
4855777.709	,6,
5526671.308	,7,
6197241.082	,8,
6864757.403	,9,
7515300.974	,10,
7640425.171717	,10.198
};

float CH1_Data[16*2]={
833968.9755	,0,
838094.2587031	,0.01,
865412.945753	,0.05,
899114.8237819	,0.1,
1166692.186255	,0.5,
1501768.895	,1,
2171109.809	,2,
2840763.896	,3,
3510951.174	,4,
4180137.75	,5,
4849479.234	,6,
5519382.882	,7,
6189028.653	,8,
6855642.677	,9,
7505512.165	,10,
7630459.797413	,10.198
};
float CH2_Data[16*2]={
4185693.956	,0,
4188108.042519	,0.01,
4196298.777303	,0.05,
4206548.610138	,0.1,
4288559.647526	,0.5,
4185943.506813	,2,
5006684.461117	,4,
5416912.358893	,6,
5827156.639914	,8,
6237577.440632	,10,
6646787.157955	,12,
7050868.395796	,14,
7446945.865831	,16,
7834946.120052	,18,
8216450.716507	,20,
8235371.628211	,20.1

};

float CH3_Data[12*2]={
4186737.085173	,0,
4193028.378226	,0.01, 
4225917.383282	,0.05,
4266995.309109	,0.1,
4595945.242216	,0.5,
5006881.820397	,1,
5828854.31533	,2, 
6648757.607879	,3,
7450170.140786	,4,
7838702.713094	,4.5,
8220768.676998	,5,
8296610.194078	,5.1
};
#endif

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
	}else if(ADC_Scan_POS==1){
		ADC_Value[ADC_Scan_POS]=find_Approtch(ADC_24bit_Value[ADC_Scan_POS],CH1_Data,32,10,0);
	}else if(ADC_Scan_POS==2){
		ADC_Value[ADC_Scan_POS]=find_Approtch(ADC_24bit_Value[ADC_Scan_POS],CH2_Data,32,20,0);
	}else if(ADC_Scan_POS==3){
		ADC_Value[ADC_Scan_POS]=find_Approtch(ADC_24bit_Value[ADC_Scan_POS],CH3_Data,24,5,0);
	}
		
}

float find_Approtch(float input,float* data_array , int len,float max,float min){
	if (input<0xFFFFFF){
		
		int i=0;
		int compare=0;
		while(compare==0){
			if(data_array[i*2]>=input){
				if (i==0){
					return data_array[1];
				}
				compare=1;
			}else{
				i++;
			}
			if (i>=len){
				return 0;
			}
		}
//		test[0]=i;
		
		float gap=data_array[i*2]-data_array[i*2-2];
//		test_float[0]=gap;
		gap=(input-data_array[i*2-2])/gap;
//		test_float[1]=gap;
		
		float tmp=((float)data_array[i*2+1]-(float)data_array[i*2-1])*gap;
//		test_float[2]=tmp;
		tmp+=(float)data_array[i*2-1];
//		test_float[3]=tmp;
		
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
