#ifndef ADS1247_h
#define ADS1247_h

#include "main.h"

/* For information to the register and settings see manual page (p..) */


/* ADS1248 Register (see p42 for Register Map) */

#define		MUX0     0x00 //Multiplexer Control Register 0
#define		VBIAS 	  0X01 //Bias Voltage Register
#define		MUX1     0x02 //Multiplexer Control REgister 1
#define		SYS0	  0x03 //System Control Register 0
#define		OFC0	  0X04 //Offset Calibration Coefficient Register 0
#define		OFC1	  0x05 //Offset Calibration Coefficient Register 1
#define		OFC2	  0x06 //Offset Calibration Coefficient Register 2
#define		FSC0 	  0x07 //Full scale Callibration Coefficient Register 0
#define		FSC1	  0x08 //Full scale Callibration Coefficient Register 1
#define		FSC2	  0x09 //Full scale Callibration Coefficient REgister 2
#define		IDAC0	  0x0A //IDAC Control Register 0
#define		IDAC1	  0x0B //IDAC Control Register 1
#define		GPIOCFG  0x0C //GPIO Configuration Register
#define		GPIODIR  0x0D //GPIODirection REgister
#define		GPIODAT  0x0E //GPIO Data Register


/* MUX0 - Multiplexer Control Register 0 (see p43 - bring together with bitwise OR | */
/* BIT7 - BIT6 -  BIT5   -  BIT4   -  BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* BCS1 - BCS0 - MUX_SP2 - MUX_SP1 - MUX_SP0 - MUX_SN2 - MUX_SN1 - MUXSN0 */
#define MUX0_RESET 0x01      // Reset MUX0 Register 
/* BCS1:0 These bits select the magnitude of the sensor detect current source */
#define		BCS1_1		0b00000000  // 00 Burnout current source off (default)
#define		BCS1_2      0b01000000  // 01 Burnout current source on 0.5 uA
#define		BCS1_3      0b10000000  // 10 Burnout current source on 2 uA
#define		BCS1_4      0b11000000  // 11 Burnout current source on 10 uA
/* MUX_SP2:0 Positive input channel selection bits */
#define		MUX_SP2_AIN0	 0b00000000  // 000 AIN0 (default)
#define		MUX_SP2_AIN1	 0b00001000  // 001 AIN1
#define		MUX_SP2_AIN2	 0b00010000  // 010 AIN2
#define		MUX_SP2_AIN3	 0b00011000  // 011 AIN3
#define		MUX_SP2_AIN4	 0b00100000  // 100 AIN4
#define		MUX_SP2_AIN5	 0b00101000  // 101 AIN5
#define		MUX_SP2_AIN6	 0b00110000  // 110 AIN6
#define		MUX_SP2_AIN7	 0b00111000  // 111 AIN7
/* MUX_SN2:0 Negative input channel selection bits */
#define		MUX_SN2_AIN0	 0b00000000  // 000 AIN0
#define		MUX_SN2_AIN1	 0b00000001  // 001 AIN1 (default)
#define		MUX_SN2_AIN2	 0b00000010  // 010 AIN2
#define		MUX_SN2_AIN3	 0b00000011  // 011 AIN3
#define		MUX_SN2_AIN4	 0b00000100  // 100 AIN4
#define		MUX_SN2_AIN5	 0b00000101  // 101 AIN5
#define		MUX_SN2_AIN6	 0b00000110  // 110 AIN6
#define		MUX_SN2_AIN7	 0b00000111  // 111 AIN7


/* VBIAS - Bias Voltage Register (see p43 - bring together with bitwise OR | */
/*  BIT7  -  BIT6  -  BIT5  -  BIT4  -  BIT3  -  BIT2  -  BIT1  -  BIT0  */
/* VBIAS7 - VBIAS6 - VBIAS5 - VBIAS4 - VBIAS3 - VBIAS2 - VBIAS1 - VBIAS0 */

/* VBIAS These bits apply a bias voltage of midsupply (AVDD + AVSS)/2 to the selected analog input */
#define		VBIAS_RESET	0x00		 // Reset VBIAS Register 
#define		VBIAS_7	 0b10000000  // AIN7
#define		VBIAS_6	 0b01000000  // AIN6
#define		VBIAS_5	 0b00100000  // AIN5
#define		VBIAS_4	 0b00010000  // AIN4
#define		VBIAS_3	 0b00001000  // AIN3
#define		VBIAS_2	 0b00000100  // AIN2
#define		VBIAS_1	 0b00000010  // AIN1
#define		VBIAS_0	 0b00000001  // AIN0


/* MUX1 - Multiplexer Control Register 1 (see p44 - bring together with bitwise OR | */
/*  BIT7   -   BIT6   -   BIT5   -   BIT4   -   BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* CLKSTAT - VREFCON1 - VREFCON0 - REFSELT1 - REFSELT0 - MUXCAL2 - MUXCAL1 - MUXCAL0 */
#define			MUX1_RESET		0x00      // Reset MUX1 Register 
/* CLKSTAT This bit is read-only and indicates whether the internal or external oscillator is being used
0 = internal, 1 = external */
/* VREFCON1 These bits control the internal voltage reference. These bits allow the reference to be turned on or
off completely, or allow the reference state to follow the state of the device. Note that the internal
reference is required for operation the IDAC functions.*/
#define		VREFCON1_OFF	 0b00000000  // Internal reference is always off (default)
#define		VREFCON1_ON		 0b00100000  // Internal reference is always on
#define		VREFCON1_PS		 0b01100000  // Internal reference is on when a conversion is in progress
/* REFSELT1:0 These bits select the reference input for the ADC  */
#define		REFSELT1_REF0	 0b00000000  // REF0 input pair selected (default)
#define		REFSELT1_REF1	 0b00001000  // REF1 input pair selected
#define		REFSELT1_ON		 0b00010000  // Onboard reference selected
#define		REFSELT1_ON_REF0 0b00011000  // Onboard reference selected and internally connected to REF0 input pair
/* MUXCAL2:0 These bits are used to select a system monitor. The MUXCAL selection supercedes selections from registers MUX0 and MUX1  */
#define		MUXCAL2_NORMAL	 0b00000000  // Normal operation (default)
#define		MUXCAL2_OFFSET	 0b00000001  // Offset measurement
#define		MUXCAL2_GAIN	 0b00000010  // Gain measurement
#define		MUXCAL2_TEMP	 0b00000011  // Temperature diode
#define		MUXCAL2_REF1	 0b00000100  // External REF1 measurement
#define		MUXCAL2_REF0	 0b00000101  // External REF0 measurement
#define		MUXCAL2_AVDD	 0b00000110  // AVDD measurement
#define		MUXCAL2_DVDD	 0b00000111   // DVDD measurement


/* SYS0 - System Control Register 0 (see p45 - bring together with bitwise OR | */
/* BIT7 - BIT6 - BIT5 - BIT4 - BIT3 - BIT2 - BIT1 - BIT0 */
/*  0   - PGA2 - PGA1 - PGA0 - DOR3 - DOR2 - DOR1 - DOR0 */
/* PGA2:0 These bits determine the gain of the PGA  */
#define		PGA2_0		0b00000000  // 1 (default)
#define		PGA2_2		0b00010000  // 2
#define		PGA2_4		0b00100000  // 4
#define		PGA2_8		0b00110000  // 8
#define		PGA2_16		0b01000000  // 16
#define		PGA2_32		0b01010000  // 32
#define		PGA2_64		0b01100000  // 64
#define		PGA2_128	0b01110000  // 128
/* DOR3:0 These bits select the output data rate of the ADC  */
#define		DOR3_5_SPS     0b00000000  // 5SPS (default)
#define		DOR3_10_SPS    0b00000001  // 10SPS 
#define		DOR3_20_SPS    0b00000010  // 20SPS 
#define		DOR3_40_SPS    0b00000011  // 40SPS 
#define		DOR3_80_SPS    0b00000100  // 80SPS 
#define		DOR3_160_SPS   0b00000101  // 160SPS 
#define		DOR3_320_SPS   0b00000110  // 320SPS 
#define		DOR3_640_SPS   0b00000111  // 640SPS 
#define		DOR3_1000_SPS  0b00001000  // 1000SPS 
#define		DOR3_2000_SPS  0b00001001  // 2000SPS 


/* IDAC0- IDAC Control Register 0 (see p46 - bring together with bitwise OR | */
/* BIT7 - BIT6 - BIT5 - BIT4 -   BIT3    - BIT2  - BIT1  - BIT0 */
/* ID3  - ID2  - ID1  - ID0  - DRDMODE - IMAG2 - IMAG1 - IMAG0 */
#define IDAC0_ID	144 
/* DRDMODE This bits sets the DOUT/DRDpin functionality  */
#define		DRDY_ONL   0b00000000  // Data out only (default)
#define		DRDY_BOTH    0b00001000  // Data out and Data ready functionality
/* IMAG2:0 The ADS1247/8 have two programmable current source DACs that can be used for sensor excitation.
The IMAG bits control the magnitude of the excitation current. The IDACs require the internal reference to be on.  */
#define		IMAG2_OFF    0b00000000  // off (default)
#define		IMAG2_50     0b00000001  // 50uA
#define		IMAG2_100    0b00000010  // 100uA
#define		IMAG2_250    0b00000011  // 250uA
#define		IMAG2_500    0b00000100  // 500uA
#define		IMAG2_750    0b00000101  // 750uA
#define		IMAG2_1000   0b00000110  // 1000uA
#define		IMAG2_1500   0b00000111  // 1500uA


/* IDAC1- IDAC Control Register 1 (see p47 - bring together with bitwise OR | */
/*  BIT7  -  BIT6  -  BIT5  -  BIT4  - BIT3   -  BIT2  -  BIT1  -  BIT0 */
/* I1DIR3 - I1DIR2 - I1DIR2 - I1DIR0 - I2DIR3 - I2DIR2 - I2DIR1 - I2DIR0 */
/* I1DIR3:0 These bits select the output pin for the first current source DAC  */
#define		I1DIR_AIN0    0b00000000  // AIN0
#define		I1DIR_AIN1    0b00010000  // AIN1
#define		I1DIR_AIN2    0b00100000  // AIN2
#define		I1DIR_AIN3    0b00110000  // AIN3
#define		I1DIR_AIN4    0b01000000  // AIN4
#define		I1DIR_AIN5    0b01010000  // AIN5
#define		I1DIR_AIN6    0b01100000  // AIN6
#define		I1DIR_AIN7    0b01110000  // AIN7 
#define		I1DIR_IEXT1   0b10000000  // IEXT1  
#define		I1DIR_IEXT2   0b10010000  // IEXT2
#define		I1DIR_OFF     0b11000000  // Disconnected (default)

/* I2DIR3:0 These bits select the output pin for the second current source DAC  */
#define		I2DIR_AIN0    0b00000000  // AIN0
#define		I2DIR_AIN1    0b00000001  // AIN1
#define		I2DIR_AIN2    0b00000010  // AIN2
#define		I2DIR_AIN3    0b00000011  // AIN3
#define		I2DIR_AIN4    0b00000100  // AIN4
#define		I2DIR_AIN5    0b00000101  // AIN5
#define		I2DIR_AIN6    0b00000110  // AIN6
#define		I2DIR_AIN7    0b00000111  // AIN7 
#define		I2DIR_IEXT1   0b00001000  // IEXT1  
#define		I2DIR_IEXT2   0b00001001  // IEXT2
#define		I2DIR_OFF     0b00001100  // Disconnected (default)

/* GPIOCFG (see p48 - bring together with bitwise OR | */
/* ... To be continued .. */



/* SPI COMMAND DEFINITIONS (p49) */
/*SYSTEM CONTROL */
#define		WAKEUP		0x00 	//Exit Sleep Mode
#define 	SLEEP 		0x01	//Enter Sleep Mode
#define 	SYNC 		0x04	//Synchornize the A/D Conversion
#define 	_RESET		0x06	//Reset To Power UP values
#define 	NOP			0xFF	//NO Operation
/*DATA READ*/
#define		RDATA		0x12	//Read data once
#define 	RDATAC		0x14	//Read data continously
#define 	SDATAC 		0x16	//Stop reading data continously
/*READ REGISTER */
#define 	RREG		0x20	//Read From Register
#define 	WREG 		0x40	//Write To Register
/*Calibration */
#define 	SYSOCAL		0x60	//System Offset Calibration
#define 	SYSGCAL		0x61	//System Gain Calibration
#define 	SELFOCAL	0x62	//Self Offset Calibration

typedef enum{
      ADC_Current=0, 
      ADC_Voltage,
      ADC_4_20,
      ADC_Limit
	
}ADC_Pos_typedef;

typedef struct ADC_pkg_typedef{
	
	uint16_t 					Data_length;
	uint8_t* 					Receive_buffer_ptr;
	uint8_t* 					Transmit_buffer_ptr;
	uint8_t 					Receive_Data_Active;
	uint8_t						CallBack_Enable;
	void                  		(* CallbackFunction)(void);
	
}ADC_pkg_typedef;

extern float ADC_Value[4];
extern uint8_t 	ADC_DRDY_signals;
extern void ADS1247_Init(void);
extern void ADS1247_Process(void);
extern void ADS1247_Ready_Callback(void);
extern void ADS1247_TxRxCpltCallback(void);
extern float find_Approtch(float input,float* data_array , int len,float max,float min);



#endif
