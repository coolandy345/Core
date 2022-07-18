#ifndef __Constant_H
#define __Constant_H

#define MIN_Current 0
#define MAX_Current 250

#define MIN_Voltage 0
#define MAX_Voltage 250

#define MIN_4_20 4
#define MAX_4_20 20

#define MIN_Limit 0
#define MAX_Limit 5

#define MIN_Current_Downlimit 0.5
#define MAX_Current_Uplimit 9

#define MIN_AnalogIn_Data_Downlimit 0
#define MAX_AnalogIn_Data_Uplimit 10

#define MIN_4_20_Data_Downlimit 0
#define MAX_4_20_Data_Uplimit 100

#define MIN_Limit_Data_Downlimit MIN_Current
#define MAX_Limit_Data_Uplimit MAX_Current


float Analog_Current_to_RealValue_Data[2*2];
float Analog_Voltage_to_RealValue_Data[2*2];
float Analog_4_20_to_RealValue_Data[4*2];
float Analog_Limit_to_RealValue_Data[4*2];


float OutputCmd_to_AnalogCmd_Data[4*2];

float PWM_Data[28*2];

float CH0_Data[16*2];
float CH1_Data[16*2];
float CH2_Data[16*2];
float CH3_Data[12*2];

#endif
