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
#define		BCS1_1		00000000b    // 00 Burnout current source off (default)
#define		BCS1_2      01000000b    // 01 Burnout current source on 0.5 �A
#define		BCS1_3      10000000b    // 10 Burnout current source on 2 �A
#define		BCS1_4      11000000b    // 11 Burnout current source on 10 �A
/* MUX_SP2:0 Positive input channel selection bits */
#define		MUX_SP2_AIN0	 00000000b    // 000 AIN0 (default)
#define		MUX_SP2_AIN1	 00001000b    // 001 AIN1
#define		MUX_SP2_AIN2	 00010000b    // 010 AIN2
#define		MUX_SP2_AIN3	 00011000b    // 011 AIN3
#define		MUX_SP2_AIN4	 00100000b    // 100 AIN4
#define		MUX_SP2_AIN5	 00101000b    // 101 AIN5
#define		MUX_SP2_AIN6	 00110000b    // 110 AIN6
#define		MUX_SP2_AIN7	 00111000b    // 111 AIN7
/* MUX_SN2:0 Positive input channel selection bits */
#define		MUX_SN2_AIN0	 00000000b    // 000 AIN0
#define		MUX_SN2_AIN1	 00000001b    // 001 AIN1 (default)
#define		MUX_SN2_AIN2	 00000010b    // 010 AIN2
#define		MUX_SN2_AIN3	 00000011b    // 011 AIN3
#define		MUX_SN2_AIN4	 00000100b    // 100 AIN4
#define		MUX_SN2_AIN5	 00000101b    // 101 AIN5
#define		MUX_SN2_AIN6	 00000110b    // 110 AIN6
#define		MUX_SN2_AIN7	 00000111b    // 111 AIN7


/* VBIAS - Bias Voltage Register (see p43 - bring together with bitwise OR | */
/*  BIT7  -  BIT6  -  BIT5  -  BIT4  -  BIT3  -  BIT2  -  BIT1  -  BIT0  */
/* VBIAS7 - VBIAS6 - VBIAS5 - VBIAS4 - VBIAS3 - VBIAS2 - VBIAS1 - VBIAS0 */

/* VBIAS These bits apply a bias voltage of midsupply (AVDD + AVSS)/2 to the selected analog input */
#define		VBIAS_RESET	0x00		 // Reset VBIAS Register 
#define		VBIAS_7	 10000000b    // AIN7
#define		VBIAS_6	 01000000b    // AIN6
#define		VBIAS_5	 00100000b    // AIN5
#define		VBIAS_4	 00010000b    // AIN4
#define		VBIAS_3	 00001000b    // AIN3
#define		VBIAS_2	 00000100b    // AIN2
#define		VBIAS_1	 00000010b    // AIN1
#define		VBIAS_0	 00000001b    // AIN0


/* MUX1 - Multiplexer Control Register 1 (see p44 - bring together with bitwise OR | */
/*  BIT7   -   BIT6   -   BIT5   -   BIT4   -   BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* CLKSTAT - VREFCON1 - VREFCON0 - REFSELT1 - REFSELT0 - MUXCAL2 - MUXCAL1 - MUXCAL0 */
#define			MUX1_RESET		0x00      // Reset MUX1 Register 
/* CLKSTAT This bit is read-only and indicates whether the internal or external oscillator is being used
0 = internal, 1 = external */
/* VREFCON1 These bits control the internal voltage reference. These bits allow the reference to be turned on or
off completely, or allow the reference state to follow the state of the device. Note that the internal
reference is required for operation the IDAC functions.*/
#define		VREFCON1_OFF	 00000000b    // Internal reference is always off (default)
#define		VREFCON1_ON		 00100000b    // Internal reference is always on
#define		VREFCON1_PS		 01100000b    // Internal reference is on when a conversion is in progress
/* REFSELT1:0 These bits select the reference input for the ADC  */
#define		REFSELT1_REF0	 00000000b    // REF0 input pair selected (default)
#define		REFSELT1_REF1	 00001000b    // REF1 input pair selected
#define		REFSELT1_ON		 00010000b    // Onboard reference selected
#define		REFSELT1_ON_REF0 00011000b    // Onboard reference selected and internally connected to REF0 input pair
/* MUXCAL2:0 These bits are used to select a system monitor. The MUXCAL selection supercedes selections from registers MUX0 and MUX1  */
#define		MUXCAL2_NORMAL	 00000000b    // Normal operation (default)
#define		MUXCAL2_OFFSET	 00000001b    // Offset measurement
#define		MUXCAL2_GAIN	 00000010b    // Gain measurement
#define		MUXCAL2_TEMP	 00000011b    // Temperature diode
#define		MUXCAL2_REF1	 00000100b    // External REF1 measurement
#define		MUXCAL2_REF0	 00000101b    // External REF0 measurement
#define		MUXCAL2_AVDD	 00000110b    // AVDD measurement
#define		MUXCAL2_DVDD	 00000111b     // DVDD measurement


/* SYS0 - System Control Register 0 (see p45 - bring together with bitwise OR | */
/* BIT7 - BIT6 - BIT5 - BIT4 - BIT3 - BIT2 - BIT1 - BIT0 */
/*  0   - PGA2 - PGA1 - PGA0 - DOR3 - DOR2 - DOR1 - DOR0 */
/* PGA2:0 These bits determine the gain of the PGA  */
#define		PGA2_0		00000000b    // 1 (default)
#define		PGA2_2		00010000b    // 2
#define		PGA2_4		00100000b    // 4
#define		PGA2_8		00110000b    // 8
#define		PGA2_16		01000000b    // 16
#define		PGA2_32		01010000b    // 32
#define		PGA2_64		01100000b    // 64
#define		PGA2_128	01110000b    // 128
/* DOR3:0 These bits select the output data rate of the ADC  */
#define		DOR3_5     00000000b    // 5SPS (default)
#define		DOR3_10    00000001b    // 10SPS 
#define		DOR3_20    00000010b    // 20SPS 
#define		DOR3_40    00000011b    // 40SPS 
#define		DOR3_80    00000100b    // 80SPS 
#define		DOR3_160   00000101b    // 160SPS 
#define		DOR3_320   00000110b    // 320SPS 
#define		DOR3_640   00000111b    // 640SPS 
#define		DOR3_1000  00001000b    // 1000SPS 
#define		DOR3_2000  00001001b    // 2000SPS 


/* IDAC0- IDAC Control Register 0 (see p46 - bring together with bitwise OR | */
/* BIT7 - BIT6 - BIT5 - BIT4 -   BIT3    - BIT2  - BIT1  - BIT0 */
/* ID3  - ID2  - ID1  - ID0  - DRDY MODE - IMAG2 - IMAG1 - IMAG0 */
#define IDAC0_ID	144 
/* DRDY MODE This bits sets the DOUT/DRDY pin functionality  */
#define		DRDY_ONLY    00000000b    // Data out only (default)
#define		DRDY_BOTH    00001000b    // Data out and Data ready functionality
/* IMAG2:0 The ADS1247/8 have two programmable current source DACs that can be used for sensor excitation.
The IMAG bits control the magnitude of the excitation current. The IDACs require the internal reference to be on.  */
#define		IMAG2_OFF    00000000b    // off (default)
#define		IMAG2_50     00000001b    // 50uA
#define		IMAG2_100    00000010b    // 100uA
#define		IMAG2_250    00000011b    // 250uA
#define		IMAG2_500    00000100b    // 500uA
#define		IMAG2_750    00000101b    // 750uA
#define		IMAG2_1000   00000110b    // 1000uA
#define		IMAG2_1500   00000111b    // 1500uA


/* IDAC1- IDAC Control Register 1 (see p47 - bring together with bitwise OR | */
/*  BIT7  -  BIT6  -  BIT5  -  BIT4  - BIT3   -  BIT2  -  BIT1  -  BIT0 */
/* I1DIR3 - I1DIR2 - I1DIR2 - I1DIR0 - I2DIR3 - I2DIR2 - I2DIR1 - I2DIR0 */
/* I1DIR3:0 These bits select the output pin for the first current source DAC  */
#define		I1DIR_AIN0    00000000b    // AIN0
#define		I1DIR_AIN1    00010000b    // AIN1
#define		I1DIR_AIN2    00100000b    // AIN2
#define		I1DIR_AIN3    00110000b    // AIN3
#define		I1DIR_AIN4    01000000b    // AIN4
#define		I1DIR_AIN5    01010000b    // AIN5
#define		I1DIR_AIN6    01100000b    // AIN6
#define		I1DIR_AIN7    01110000b    // AIN7 
#define		I1DIR_IEXT1   10000000b    // IEXT1  
#define		I1DIR_IEXT2   10010000b    // IEXT2
#define		I1DIR_OFF     11000000b    // Disconnected (default)

/* I2DIR3:0 These bits select the output pin for the second current source DAC  */
#define		I2DIR_AIN0    00000000b    // AIN0
#define		I2DIR_AIN1    00000001b    // AIN1
#define		I2DIR_AIN2    00000010b    // AIN2
#define		I2DIR_AIN3    00000011b    // AIN3
#define		I2DIR_AIN4    00000100b    // AIN4
#define		I2DIR_AIN5    00000101b    // AIN5
#define		I2DIR_AIN6    00000110b    // AIN6
#define		I2DIR_AIN7    00000111b    // AIN7 
#define		I2DIR_IEXT1   00001000b    // IEXT1  
#define		I2DIR_IEXT2   00001001b    // IEXT2
#define		I2DIR_OFF     00001100b    // Disconnected (default)

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

typedef struct ADC_pkg_typedef{
	
	uint16_t 					Data_length;
	uint8_t* 					Receive_buffer_ptr;
	uint8_t* 					Transmit_buffer_ptr;
	uint8_t 					Receive_Data_Active;
	uint8_t						CallBack_Enable;
	void                  		(* CallbackFunction)(void);
	
}ADC_pkg_typedef;


extern void ADS1247_Init(void);
extern void ADS1247_Ready_Callback(void);



#endif
