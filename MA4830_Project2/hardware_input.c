/**
    MA4830
    hardware_input.c
    header in hardware_input.h
    Purpose: Implementation of hardware_input.c 
    Library containing functions & variables needed related for reading and set wave parameter 

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//thread and process library
#include <pthread.h>
#include <process.h>

#include "initialization.h"
#include "switch_input_mode.h"  //for shared variable input_mode
#include "generate_wave.h"      //for shared wave parameters (A,D,wave_type,f,avg)

uint16_t readpotentiometer1;
uint16_t readpotentiometer2;

/**
    function to convert raw reading of digital output into reading of switch 2 and 3
    
    @param arg
    @return reading of switch 2 and 3 (2 bit: 4 levels : 0,1,2,or3)
*/
int switch_waveform(uint16_t switch_wave)
{
    return (switch_wave>>2)-60; //shift 2, offset by 60 because the switches (1111switch1 switch2 **)
}

/**
    function to read potentiometer 1 and 2
    
    @param -
    @return void
*/
void read_potentiometer()
{
 	//start ADC
 	out16(AD_DATA,0);
 	while(!(in16(MUXCHAN)&0x4000));
 	readpotentiometer1 = in16(AD_DATA); //read potentiometer 1
 	out16(AD_DATA,0);
 	while(!(in16(MUXCHAN)&0x4000));
 	readpotentiometer2 = in16(AD_DATA); //read potentiometer 2
 }

/**
    function to write to LED as visualization according to switch states
    
    @param -
    @return void
*/
void update_LED()
{
    out8(DIO_PORTB,dio_switch); // visualize the four switch states to four LEDs
}

/**
    function to read and set wave parameter from hardware (potentiometers and switches)
    
    @param arg
    @return void
*/
void *hardware_input_thread(void *arg)
{
    printf("\n==================================================================\n");   
    printf("Change parameters from hardware: \n");
    printf("potentiometer 1 for A, potentiometer 2 for average, toggle switch 1 and 2 to change wave type\n");
    printf("------------------------------------------------------------------\n");
    printf("WAVE \t \t A \t avg \t f level \t Duty Cycle\n");
    printf("------------------------------------------------------------------\n");
    while(input_mode==1)
    {
        update_LED();   //visualize the four switch states to the four LEDs
        
        //Read from potentiometer 1 and 2
        read_potentiometer();

        //Convert potentiometer readings to amplitude and average and update the variables
        //maximum potentiometer reading= 32768
        A = readpotentiometer1*1.0/32768 * 5;           //map 0 to 32768 --> 0 to 5 volt   
        avg = readpotentiometer2*1.0/32768 * 10 - 5;    //map 0 to 32768 --> -5 to 5 volt 
        
        //Read from waveform switches : Done in switch_input_mode thread
        //convert switch readings to wave type and update the wave_type variable
        wave_type = switch_waveform(dio_switch);

        //print the wave parameters    
        printf("%d (%s) \t %.2f \t %.2f \t %d \t\t %d \n", wave_type,wave_type==1?"sine":(wave_type==2?"square":(wave_type==3?"triangular":"zero")),A,avg,f,D);
        
        delay(1000);   
    }
}

