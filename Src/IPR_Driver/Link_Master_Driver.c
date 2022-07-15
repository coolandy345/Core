#include "Link_Master_Driver.h"
#include "tim.h"
#include "ADS1247.h"

#ifdef MASTER
//Master
float PWM_Data[28*2]={
0,		0,
0.01,	0x0080,
0.02,	0x00F0,
0.03,	0x016D,
0.04,	0x01E0,
0.05,	0x0258,
0.1,	0x04A6,
0.5,	0x1659,
1,		0x2AD0,
1.5,	0x3DA0,
2,		0x4EF8,
2.5,	0x5F08,
3,		0x6DF8,
3.5,	0x7BD8,
4,		0x88D0,
4.5,	0x94EF,
5,		0xA048,
5.5,	0xAAF4,
6,		0xB500,
6.5,	0xBE78,
7,		0xC768,
7.5,	0xCFF0,
8,		0xD7E0,
8.5,	0xDF70,
9,		0xE6C0,
9.5,	0xED80,
10,		0xF420,
10.1,	0xF570,

};

#else
//Slave
float PWM_Data[28*2]={
0,		0,
0.01,	0x0080,
0.02,	0x00F0,
0.03,	0x016D,
0.04,	0x01E0,
0.05,	0x0258,
0.1,	0x04A6,
0.5,	0x166C,
1,		0x2AEE,
1.5,	0x3DCC,
2,		0x4F38,
2.5,	0x5F50,
3,		0x6E46,
3.5,	0x7C2E,
4,		0x892B,
4.5,	0x9551,
5,		0xA0B4,
5.5,	0xAB63,
6,		0xB572,
6.5,	0xBEEB,
7,		0xC7CE,
7.5,	0xD066,
8,		0xD868,
8.5,	0xDFED,
9,		0xE727,
9.5,	0xEE16,
10,		0xF4A1,
10.1,	0xF618,

};
#endif


void Link_Master_Initial(void){


	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);  
	htim11.Instance->CCR1=20000;
	
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);  
	htim9.Instance->CCR2=20000;

}


void Link_Master_Process(void){

	int tmp;
	
	tmp=find_Approtch(test_float[0],PWM_Data,56,0xFFFF,0);
	
	htim9.Instance->CCR2=tmp;

}