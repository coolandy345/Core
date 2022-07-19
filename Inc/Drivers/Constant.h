#ifndef __Constant_H
#define __Constant_H

#define MIN_Unit_Current 0
#define MAX_Unit_Current 250

#define MIN_Voltage 0
#define MAX_Voltage 40

#define MIN_4_20 4
#define MAX_4_20 20
#define Delta_4_20 0.5

#define MIN_Limit 0
#define MAX_Limit 5
#define Delta_Limit 0.1

#define MIN_AnalogIn_Data_Downlimit 0
#define MAX_AnalogIn_Data_Uplimit 10

#define MIN_4_20_Data_Downlimit 0
#define MAX_4_20_Data_Uplimit 100

#define MIN_Limit_Data_Downlimit 0
#define MAX_Limit_Data_Uplimit 100

extern double MIN_Sys_Current ;
extern double MAX_Sys_Current ;

extern double Analog_Current_to_RealValue_Data[2*2];
extern double Analog_Voltage_to_RealValue_Data[2*2];
extern double Analog_4_20_to_RealValue_Data[4*2];
extern double Analog_Limit_to_RealValue_Data[4*2];

extern double OutputCmd_to_AnalogCmd_Data[6*2];

extern double PWM_Data[28*2];

extern double CH0_Data[16*2];
extern double CH1_Data[16*2];
extern double CH2_Data[16*2];
extern double CH3_Data[12*2];

void System_Capacity_Set(int node_number);

#endif
