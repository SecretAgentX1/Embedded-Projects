/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< counter100.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

void main(){
    SSD_t ssd0 = {SSD_COM_CATHODE,DIO_PORTA,DIO_PORTB,DIO_PIN0};
    SSD_t ssd1 = {SSD_COM_CATHODE,DIO_PORTA,DIO_PORTB,DIO_PIN7};
    SSD_enumInit(&ssd0);
    SSD_enumInit(&ssd1);
    u8 Tens = 0;
    u8 Ones = 0;
    SSD_enumOff(&ssd0);
    SSD_enumOff(&ssd1);
    while(1){
        for(u8 num =0;num<100;num++){
            Tens = num / 10;
            Ones = num % 10;
            for(u8 i = 0;i<100;++i){
                SSD_enumOff(&ssd1);
                SSD_enumDisplayNum(&ssd0,Tens);
                SSD_enumOn(&ssd0);
                _delay_ms(5);
                SSD_enumOff(&ssd0);
                SSD_enumDisplayNum(&ssd1,Ones);
                SSD_enumOn(&ssd1);
                _delay_ms(5);
            }
        }
    }
}

