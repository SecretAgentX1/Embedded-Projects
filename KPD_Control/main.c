/*
 * main.c
 *
 *  Created on: Oct 6, 2026
 *      Author: sagentx
 */

#include "KPD_interface.h"
#include "CLCD_interface.h"
#include "LED_interface.h"
#include "DIO_interface.h"
#include <util/delay.h>


int main(){
	CLCD_t clcd0 = {DIO_PORTC,DIO_PIN0,DIO_PORTC,DIO_PIN1,DIO_PORTC,DIO_PIN2,DIO_PORTD};
	CLCD_voidInit(&clcd0);
	KPD_voidInit();

	LED_t leds[8];
	for(u8 i = 0 ; i < 8;++i){
		leds[i] = (LED_t){DIO_PORTA,DIO_PIN0 + i,LED_ACTIVE_HIGH};
		LED_enumInit(leds+i);
		LED_enumOff(leds+i);
	}
	u8 LOC_u8Data;
	u8 LOC_u8LastPowered = 0;
	while(1){
		LOC_u8Data = KPD_u8GetPressed();
		if(LOC_u8Data == NOTPRESSED || LOC_u8Data <= '0' || LOC_u8Data >= '9') continue;
		if(LOC_u8LastPowered != 0)LED_enumOff(leds+LOC_u8LastPowered-1);
		LOC_u8LastPowered = LOC_u8Data - '0';
		LED_enumOn(leds+LOC_u8LastPowered-1);
		CLCD_voidSendCommand(&clcd0,_Clcd_Clear);
		CLCD_voidSendData(&clcd0,LOC_u8Data);
	}


	return 0;
}
