/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< serialSSD.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Created on: Sep 18, 2026
 *  Author: Ali Osama Ismail
 *
 *
 */
#include<util/delay.h>
#include"DIO_interface.h"
void main(){
    DIO_enumSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);
    DIO_enumSetPinDirection(DIO_PORTA,DIO_PIN1,DIO_OUTPUT);
    DIO_enumSetPinDirection(DIO_PORTA,DIO_PIN2,DIO_OUTPUT);
    DIO_enumSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW);
    DIO_enumSetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW);
    DIO_enumSetPinValue(DIO_PORTA,DIO_PIN2,DIO_LOW);
    static const u8 SSD_NumberPattern[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
    u8 number = 0;
    while(1){
        for(s8 i = 7 ; i>=0 ; i--){
            u8 tmp = SSD_NumberPattern[number] >> i;
            tmp = tmp & 1;
            DIO_enumSetPinValue(DIO_PORTA,DIO_PIN1,tmp);
            DIO_enumSetPinValue(DIO_PORTA,DIO_PIN0,DIO_HIGH); // CLK PULSE
            DIO_enumSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW);
        }
        DIO_enumSetPinValue(DIO_PORTA,DIO_PIN2,DIO_HIGH); //STORE PULSE
        DIO_enumSetPinValue(DIO_PORTA,DIO_PIN2,DIO_LOW);
        number = number == 9 ? 0 : number+1;
        _delay_ms(1000);
    }
}

