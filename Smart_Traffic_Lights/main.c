/*
 * main.c
 *
 *  Created on: Oct 21, 2026
 *      Author: sagentx
 */


#include "LED_interface.h"
#include "DIO_interface.h"
#include "SSD_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "SW_interface.h"

#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"

enum Mode {
	Normal = 0,PS =1
} OperationMode = Normal;
enum Ocur {
	Single = 0,
	Redundant = 1
} OperationRedundancy = Single;

u8 redVal = 0;
u8 yellowVal = 0;
u8 greenVal = 1;

SSD_t SSD0 = {SSD_COM_CATHODE, DIO_PORTC , DIO_PORTC, DIO_PIN7};
LED_t RedLed = {DIO_PORTD,DIO_PIN0,LED_ACTIVE_HIGH};
LED_t YellowLed = {DIO_PORTD,DIO_PIN1,LED_ACTIVE_HIGH};
LED_t GreenLed = {DIO_PORTD,DIO_PIN3,LED_ACTIVE_HIGH};


void ISR_F(){
	OperationRedundancy = OperationMode == PS ? Redundant : Single;
	OperationMode = OperationMode == Normal ? PS : OperationMode;
}

void NormalMode(){
	LED_enumOff       (&RedLed   );
	LED_enumOff       (&YellowLed);
	LED_enumOn        (&GreenLed );
	SSD_enumOn        (&SSD0);
	SSD_enumDisplayNum(&SSD0,0);
}

int main(){
	DIO_enumConnectPullup(DIO_PORTD,DIO_PIN2,DIO_HIGH);

	SSD_enumInit   (&SSD0);
	LED_enumInit   (&RedLed   );
	LED_enumInit   (&YellowLed);
	LED_enumInit   (&GreenLed );


	EXTI_voidSetCallBack(EXTI_LINE0,&ISR_F);
	EXTI_voidInit       ();
	GIE_voidEnable      ();

	u8 LOC_u8LastNormal =0;

	while(1){
		if(OperationMode == Normal){
			if(LOC_u8LastNormal == 0) {
				NormalMode();
				LOC_u8LastNormal = 1;
			}
		}
		else{
			LOC_u8LastNormal = 0;
			if(redVal == 1){
				LED_enumOn   (&RedLed   );
				LED_enumOff  (&YellowLed);
				LED_enumOff  (&GreenLed);
				for(s8 i = 9 ; i>=0; i--){
					SSD_enumDisplayNum(&SSD0,i);
					_delay_ms(1000);
					if(OperationRedundancy == Redundant) {
						i = 10;
						OperationRedundancy = Single;
					}
				}
				redVal = 0;
				greenVal = 1;
				OperationMode = Normal;
			}
			else if(yellowVal){
				LED_enumOn   (&YellowLed);
				LED_enumOff  (&GreenLed);
				for(s8 i = 3 ; i>=0; i--){
					SSD_enumDisplayNum(&SSD0,i);
					_delay_ms(1000);
					if(OperationRedundancy == Redundant) {
						i = 4;
						OperationRedundancy = Single;
					}
				}
				yellowVal = 0;
				redVal = 1;


			}
			else if(greenVal){
				yellowVal = 1;
				greenVal = 0;

			}
			// if red -> count again from 0 to 9
			// else greed -> led yello activated 3 seconds then red 9 seconds
			// else yellow -> led yellow from 0 to 3 then red 9 seconds
		}
	}


	return 0;
}
