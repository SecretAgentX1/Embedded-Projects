/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< clickCount.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Created on: Sep 18, 2026
 *  Author: Ali Osama Ismail
 *
 *
 */
#include<util/delay.h>
#include"SSD_interface.h"
#include"BIT_MATH.h"
#include"SSD_interface.h"
#include"SW_interface.h"

void main(){
    SSD_t ssd0 = {SSD_COM_CATHODE,DIO_PORTA,DIO_PORTA,DIO_PIN7};
    SW_Type sw0 = {DIO_PORTB,DIO_PIN7,SW_Int_Pull_UP};
    SSD_enumInit(&ssd0);
    SW_enumInit(&sw0);
    u8 number = 0;
    u8 press = 0;
    SSD_enumOn(&ssd0);
    while(1){
        SSD_enumDisplayNum(&ssd0,number);
        SW_enumGetPressed(&sw0,&press);
        if(press == SW_PRESSED){
            while(press == SW_PRESSED) SW_enumGetPressed(&sw0,&press);
            number = (number+1)%10;
        }
    }
}

