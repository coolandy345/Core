#include "ADS1247.h"
#include "spi.h"
#include "main.h"
//typedef struct {
//  const char                   *name;   ///< name of the event flags
//  uint32_t                 attr_bits;   ///< attribute bits
//  void                      *cb_mem;    ///< memory for control block
//  uint32_t                   cb_size;   ///< size of provided memory for control block
//} osEventFlagsAttr_t;
//osEventFlagsAttr_t SPI_Message_Attr;
uint8_t 	ADC_DRDY_signals=0x01;
osMailQId  SPI_MailQueue_ID;

osMailQDef(SPI_MailQueue, 0x20, ADC_pkg_typedef);

osEvent spi_event;
ADC_pkg_typedef* SPI_package;


uint8_t SPI_Transmit_GPIO_ADS1247_getting_buffer[]={0x20,0x0E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t SPI_Transmit_GPIO_ADS1247_write_buffer[]={0x42,0x01,0x20,0x02};
uint8_t SPI_Transmit_GPIO_ADS1247_read_buffer[]={0x12,0xFF,0xFF,0xFF};
uint8_t receive_buffer[20];
uint8_t receive_buffer2[10];

int init_test=1;

void ADS1247_Start_Convert(void);

/**
  * @brief  ADS1247/8 initialtize and calibrate
  * @note   
  * @param  None
  * @retval None
  */
void ADS1247_Init(void){
	
//	SPI_Message_Attr
	
	
	
	HAL_GPIO_WritePin(ADC_Start_GPIO_Port, ADC_Start_Pin, GPIO_PIN_SET);
//	SPI_MailQueue_ID			= osMailCreate(osMailQ(SPI_MailQueue), NULL);
	
}

/**
  * @brief  ADS1247/8 Ready_Callback
  * @note   Call by GPIO interrupt when data ready
  * @param  None
  * @retval None
  */
void ADS1247_Ready_Callback(void){
	test[2]++;
	test_float[0]=(float)test[2]*10000/(float)test[1];

	HAL_GPIO_WritePin(SPI1_SS_ADC_GPIO_Port, SPI1_SS_ADC_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1,SPI_Transmit_GPIO_ADS1247_read_buffer,receive_buffer2,4,1);
	if (init_test){
		HAL_SPI_TransmitReceive(&hspi1,SPI_Transmit_GPIO_ADS1247_write_buffer,receive_buffer2,4,1);
		init_test=0;
	}
	else{
	HAL_SPI_TransmitReceive(&hspi1,SPI_Transmit_GPIO_ADS1247_getting_buffer,receive_buffer,18,1);
	}
//		
	
	
	
	HAL_GPIO_WritePin(SPI1_SS_ADC_GPIO_Port, SPI1_SS_ADC_Pin, GPIO_PIN_SET);
	
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
