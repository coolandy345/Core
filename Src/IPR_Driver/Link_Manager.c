#include "Link_Manager.h"
#include "gpio.h"

int Master_Slave_Option=0; //Master=1  Slave=0
int Link_Address=0x30; //Default 0x30  = 48(dec)

void Link_Manager_Init(void){

	Master_Slave_Option=option_state&(1<<5)? 1:0; 	//Master=1  Slave=0
	Link_Address=0x30 | option_state&0xF;			//Default 0x30  = 48(dec)
	

}


void Link_Manager_Process(void){




}