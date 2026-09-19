/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< switchingLedModes.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Created on: Sep 18, 2026
 *  Author: Ali Osama Ismail
 *
 *
 */
#include<util/delay.h>
#include"BIT_MATH.h"
#include"LED_interface.h"
#include"SW_interface.h"

#define LEDS_NUM 8
#define SW_NUM 5
void main(){

    LED_t led[LEDS_NUM];
    SW_Type sw[SW_NUM];
    u8 SW_value[SW_NUM];
    s8 Last_Value = -1;

    for(u8 i =0;i<LEDS_NUM;++i){
        led[i] = (LED_t){DIO_PORTA,i,LED_ACTIVE_HIGH};
        LED_enumInit(&led[i]);
        LED_enumOff(&led[i]);
        if(i<SW_NUM){
            sw[i] = (SW_Type){DIO_PORTB,i,SW_Int_Pull_UP};
            SW_enumInit(&sw[i]);
        }
    }

    u8 i = 0,  j = 0, flag=0;


    while(1){
        for(u8 i =0 ; i<SW_NUM ; ++i){
            SW_enumGetPressed(&sw[i],&SW_value[i]);
        }
        if(SW_value[0]){ //Snake_Effect
            if(Last_Value != 0){
                i = 1;
            }
            else{
                if(i==0xFF)i=0;
                i<<=1;++i;
            }

            u8 temp = i;
            for(u8 z = 0; z<LEDS_NUM;++z){
                temp = i>>z;
                if(temp%2) LED_enumOn(&led[z]);
                else LED_enumOff(&led[z]);
            }
            Last_Value = 0;
        }
        else if(SW_value[1]){ //Ping-Pong
            if(Last_Value != 1){
                flag = 0;
                i = 1;
            }
            else{
                if(!flag){
                    i<<=1;
                    if(i==0x80){
                        flag=1;
                    }
                }
                else{
                    i>>=1;
                    if(i==0x01){
                        flag=0;
                    }
                }
            }
            u8 temp = i;
            for(u8 z = 0; z<LEDS_NUM;++z){
                temp = i>>z;
                if(temp%2) LED_enumOn(&led[z]);
                else LED_enumOff(&led[z]);
            }
            Last_Value = 1;
        }
        else if(SW_value[2]){ //DivergingLeds
            for(u8 z = 0; z<LEDS_NUM;++z){
                LED_enumOff(&led[z]);
            }
            if(Last_Value != 2){
                i=3,j=4,flag=1;
            }
            else{
                i--;j++;
                if(j==8){
                    i=3,j=4,flag=1;
                }
            }  
            if
            (flag){
                LED_enumOff(&led[0]);
                LED_enumOff(&led[7]);
                flag = 0;
            }
            else{
                LED_enumOff(&led[i+1]);
                LED_enumOff(&led[j-1]);
            }
            LED_enumOn(&led[i]);
            LED_enumOn(&led[j]); 
            
            Last_Value = 2;
        }
        else if(SW_value[3]){ //ConvergingLeds
            for(u8 z = 0; z<LEDS_NUM;++z){
                LED_enumOff(&led[z]);
            }
            if(Last_Value != 3){
                i=0,j=7,flag=1;
            }
            else{
                i++;j--;
                if(i>j){
                    i=0,j=7,flag=1;
                }
            }  
            LED_enumOn(&led[i]);
            LED_enumOn(&led[j]);              
            if(flag){
                LED_enumOff(&led[3]);
                LED_enumOff(&led[4]);
                flag = 0;
            }
            else{
                LED_enumOff(&led[i-1]);
                LED_enumOff(&led[j+1]);
            }

            Last_Value = 3;
        }
        else if(SW_value[4]){ //ConvergingDiverging
            for(u8 z = 0; z<LEDS_NUM;++z){
                LED_enumOff(&led[z]);
            }
            if(Last_Value != 4){
                i=0,j=7,flag=1;
            }
            LED_enumOn(&led[i]);
            LED_enumOn(&led[j]); 
            if(flag){
                if(i!=0){
                    LED_enumOff(&led[i-1]);
                    LED_enumOff(&led[j+1]);
                }
                else{
                    LED_enumOff(&led[i+1]);
                    LED_enumOff(&led[j-1]);
                }
                i++;j--;
                if(i>j){
                    flag =0;i-=2;j+=2;
                }
            }
            else{
                if(j!=7){
                    LED_enumOff(&led[i+1]);
                    LED_enumOff(&led[j-1]);
                }
                else{
                    LED_enumOff(&led[i-1]);
                    LED_enumOff(&led[j+1]);
                }
                i--;j++;
                if(j==8){
                    flag =1;i+=2;j-=2;
                }
            }
            Last_Value = 4;
         
        }
        _delay_ms(250);
    }
}
