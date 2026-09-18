/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< main.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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
    SSD_t ssd0 = {SSD_COM_CATHODE,DIO_PORTA,DIO_PORTA,DIO_PIN7};
    SSD_enumInit(&ssd0);
    u8 number = 0;
    u8 sign = 0;
    SSD_enumOn(&ssd0);
    while(1){
        
        SSD_enumDisplayNum(&ssd0,number);
        _delay_ms(1000);
        if(sign == 0){
            if(number == 9){
                sign = 1;
                number--;
            }
            else number++;
        }else{
            if(number == 0){
                sign = 0;
                number++;
            }
            else number--;  
        }
    }
}

