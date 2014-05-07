
// SPIDA antenna driver files for Tmote Sky Nodes

// $Id: spida_sky.c,v 1.2 2009/10/10 20:58:11 eriköström Exp $


#include "dev/hwconf.h"
#include "contiki.h"
#include "spida_sky.h"

static unsigned char u8AntennaState = 0;
/*************************************************************************
	Function: 	spida_init()
	Input: 		-
	Output: 	-

	Description: 	Initializes I/O pins and sets them
			all low (Dampen communication).
*************************************************************************/

HWCONF_PIN(U2_2,3,5); //UART0RX P3.5
HWCONF_PIN(U2_3,6,0); //ADC0 P6.0
HWCONF_PIN(U2_4,3,4); //UART0TX P3.4
HWCONF_PIN(U2_5,6,1); //ADC1 P6.0
HWCONF_PIN(U2_7,6,2); //ADC2 P6.0
HWCONF_PIN(U2_10,6,3); //ADC0 P6.3


void inline spida_init(void) {

	//Hardware setup
	//Defines U2 port pins 2-5, 7 and 10, and makes them I/O pins with direction output.
	//U2 port pin1 is Vcc and pin9 is Gnd, pins 6 and 8 are left undefined and they can not be used
	//as I/O pins because they are connected to the antenna Data and Clk signals. 
	

	U2_2_SELECT_IO();
	U2_2_MAKE_OUTPUT();


	U2_3_SELECT_IO();
	U2_3_MAKE_OUTPUT();


	U2_4_SELECT_IO();
	U2_4_MAKE_OUTPUT();


	U2_5_SELECT_IO();
	U2_5_MAKE_OUTPUT();


	U2_7_SELECT_IO();
	U2_7_MAKE_OUTPUT();


	U2_10_SELECT_IO();
	U2_10_MAKE_OUTPUT();

	U2_2_CLEAR();
	U2_3_CLEAR();
	U2_4_CLEAR();
	U2_5_CLEAR();
	U2_7_CLEAR();
	U2_10_CLEAR();

	u8AntennaState = 0; // All grounded
}



void inline spida_optimized_set_dir(unsigned char u8Direction)
{

	if(u8AntennaState != 0 && u8AntennaState != 7)
	{
		switch(u8AntennaState) {
		case 1:
			U2_10_CLEAR();
		break;	
		case 2:
			U2_7_CLEAR();
		break;	
		case 3:
			U2_5_CLEAR();
		break;	
		case 4:
			U2_3_CLEAR();
		break;	
		case 5:
			U2_2_CLEAR();
		break;	
		case 6:
			U2_4_CLEAR();
		break;
	}


	}
	else if (u8AntennaState == 7)
	{

			U2_2_CLEAR();
			U2_3_CLEAR();
			U2_4_CLEAR();
			U2_5_CLEAR();
			U2_7_CLEAR();
			U2_10_CLEAR();

	}


	switch(u8Direction) {
		case 1:
			U2_10_SET();
		break;	
		case 2:
			U2_7_SET();
		break;	
		case 3:
			U2_5_SET();
		break;	
		case 4:
			U2_3_SET();
		break;	
		case 5:
			U2_2_SET();
		break;	
		case 6:
			U2_4_SET();
		break;
		case 7:
			U2_2_SET();
			U2_3_SET();
			U2_4_SET();
			U2_5_SET();
			U2_7_SET();
			U2_10_SET();
		break;
	}

	u8AntennaState = u8Direction;

}

/*************************************************************************
	Function: 	spida_activate_direction()
	Input: 		integer x; 0 < x < 7
	Output: 	-

	Description: 	Initializes I/O pins and sets the selected
			direction pin high (Enhance communication).
*************************************************************************/

void spida_activate_direction(int direction) {
	//Returns if direction is not 1-6
	if(direction > 6 || direction < 1) return;
	

	U2_2_SELECT_IO();
	U2_2_MAKE_OUTPUT();


	U2_3_SELECT_IO();
	U2_3_MAKE_OUTPUT();


	U2_4_SELECT_IO();
	U2_4_MAKE_OUTPUT();


	U2_5_SELECT_IO();
	U2_5_MAKE_OUTPUT();


	U2_7_SELECT_IO();
	U2_7_MAKE_OUTPUT();


	U2_10_SELECT_IO();
	U2_10_MAKE_OUTPUT();	

	//Sets the U2 pin corresponding to the direction (1-6);
	switch(direction) {
		case 1:
			U2_10_SET();
		break;	
		case 2:
			U2_7_SET();
		break;	
		case 3:
			U2_5_SET();
		break;	
		case 4:
			U2_3_SET();
		break;	
		case 5:
			U2_2_SET();
		break;	
		case 6:
			U2_4_SET();
		break;
	}


}

/*************************************************************************
	Function: 	spida_deactivate_direction()
	Input: 		integer x; 0 < x < 7
	Output: 	-

	Description: 	Initializes I/O pins and sets the selected
			direction pin low (Dampen communication).
*************************************************************************/

void spida_deactivate_direction(int direction) {
	//Returns if direction is not 1-6
	if(direction > 6 || direction < 1) return;


	U2_2_SELECT_IO();
	U2_2_MAKE_OUTPUT();


	U2_3_SELECT_IO();
	U2_3_MAKE_OUTPUT();


	U2_4_SELECT_IO();
	U2_4_MAKE_OUTPUT();


	U2_5_SELECT_IO();
	U2_5_MAKE_OUTPUT();


	U2_7_SELECT_IO();
	U2_7_MAKE_OUTPUT();


	U2_10_SELECT_IO();
	U2_10_MAKE_OUTPUT();

	//Sets the U2 pin corresponding to the direction (1-6)
	switch(direction) {
		case 1:
			U2_10_CLEAR();
		break;	
		case 2:
			U2_7_CLEAR();
		break;	
		case 3:
			U2_5_CLEAR();
		break;	
		case 4:
			U2_3_CLEAR();
		break;	
		case 5:
			U2_2_CLEAR();
		break;	
		case 6:
			U2_4_CLEAR();
		break;	
	}
}

/*************************************************************************
	Function: 	spida_set_dir()
	Input: 		integer x; -1 < x < 8
	Output: 	-

	Description: 	Initializes I/O pins and configures them for
			communication over the selected direction only.
			Direction 0 sets all pins low.
			Direction 7 sets all pins high.
*************************************************************************/

void spida_set_dir(int direction) {
	//Returns if direction is not 0-7
	if(direction > 7 || direction < 0) return;

	//Sets all pins low and only activates the called direction (1-6) or
	//direction (0), (all pins low), or direction (7), (all pins high).
	if(direction != 7) {
		spida_deactivate_direction(1);
		spida_deactivate_direction(2);
		spida_deactivate_direction(3);
		spida_deactivate_direction(4);
		spida_deactivate_direction(5);
		spida_deactivate_direction(6);
	}
	else {  //Direction (7), activates all pins.
		spida_activate_direction(1);
		spida_activate_direction(2);
		spida_activate_direction(3);
		spida_activate_direction(4);
		spida_activate_direction(5);
		spida_activate_direction(6);
	}

	spida_activate_direction(direction);
	u8AntennaState = direction;
}

/*************************************************************************
	Function: 	spida_set_dir()
	Input: 		integer x; -1 < x < 8
	Output: 	-

	Description: 	Initializes I/O pins and configures them for
			communication over the selected direction only.
			Direction 0 sets all pins low.
			Direction 7 sets all pins high.
*************************************************************************/

void spida_dir(int direction1, int direction2, int direction3, int direction4, int direction5, int direction6) {
	if(direction1 > 0)
		spida_activate_direction(1);
	else
		spida_deactivate_direction(1);

	if(direction2 > 0)
		spida_activate_direction(2);
	else
		spida_deactivate_direction(2);

	if(direction3 > 0)
		spida_activate_direction(3);
	else
		spida_deactivate_direction(3);

	if(direction4 > 0)
		spida_activate_direction(4);
	else
		spida_deactivate_direction(4);

	if(direction5 > 0)
		spida_activate_direction(5);
	else
		spida_deactivate_direction(5);

	if(direction6 > 0)
		spida_activate_direction(6);
	else
		spida_deactivate_direction(6);
	
}
/*---------------------------------------------------------------------------*/
