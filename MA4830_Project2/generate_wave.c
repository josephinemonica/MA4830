/**
    MA4830
    generate_wave.c
    header in generate_wave.h
    Purpose: Implementation of generate_wave.h containing functions & variables needed related for generating wave purpose

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <math.h>
															
#include "initialization.h" //for hardware addresses
#include "generate_wave.h"  //for shared wave parameters (A,D,wave_type,f,avg)

unsigned int i;
unsigned int data;

int N=50;
int t_delay;

/**
    converts frequency level to suitable delay duration required in implementation 
    @param f_level (1,2,3,4,5) Note: level 5 is the highest frequency
    @return delay duration
*/
int f_to_t(int f_level)
{
    switch(f_level)
    {
        case(1):
            return 250;
        case(2):
            return 200;
        case(3):
            return 150;
        case(4):
            return 100;
        case(5):
            return 50;
    }
};

/**
    write sine wave voltage to D/A 0
    
    @param -
    @return void
*/	
void sine_wave()
{
    while(wave_type==1)         //stops if wave_type is not 1 (sine)
    {
        for(i=0;i<N;i++) 
        {
            t_delay=f_to_t(f);
            data=( ( ( sinf((float)(i*2*3.1415/N))*A ) + avg+10)/20.0  * 0xFFFF );
	        out16(DA_CTLREG,0x0923);			// DA Enable, #0, #1, SW 10V bipolar		2/6
   	        out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
            out16(DA_Data,(short) data);  
            delay(t_delay);
																																																	
      	 }
    }
}

/**
    write square wave voltage to D/A 0
    
    @param -
    @return void
*/	
void square_wave()
{
    while(wave_type==2)     //stops if wave_type is not 2 (square)
    {
            t_delay=f_to_t(f);
            data=( (avg+A+10) /20.0  * 0xFFFF );
	        out16(DA_CTLREG,0x0923);			    // DA Enable, #0, #1, SW 10V bipolar		2/6
   	        out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
            out16(DA_Data,(short) data);
            delay((int)N*t_delay*D/100);
            
            data=( (avg-A+10) /20.0  * 0xFFFF );
            out16(DA_CTLREG,0x0923);			    // DA Enable, #0, #1, SW 10V bipolar		2/6
   	        out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
            out16(DA_Data,(short) data);
            delay((int)N*t_delay*(100-D)/100);

    }
}

/**
    write triangular wave voltage to D/A 0
    
    @param -
    @return void
*/	
void triangular_wave()
{
    while(wave_type==3)     //stops if wave_type is not 3 (triangular)
    {
        t_delay=f_to_t(f);

        for(i=0;i<N/2;i++) 
        {
            data=( ( avg-A+ A*4*i/N + 10)/20.0  * 0xFFFF );
	        out16(DA_CTLREG,0x0923);			    // DA Enable, #0, #1, SW 10V bipolar		
   	        out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
            out16(DA_Data,(short) data);
			delay(t_delay);		//micros																								
																																
  	    }
  	    for(i=0;i<N/2;i++) 
        {
            data=( ( avg+A- A*4*i/N + 10)/20.0  * 0xFFFF );
	        out16(DA_CTLREG,0x0923);			    // DA Enable, #0, #1, SW 10V bipolar
   	        out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
            out16(DA_Data,(short) data);
			delay(t_delay);		//micros																								
																																
  	    }
    }
}

/**
    write zero voltage to D/A 0
    
    @param -
    @return void
*/	
void zero_signal()
{
    data=1/2* 0xFFFF;                       //corresponds to 0 voltage signal
	out16(DA_CTLREG,0x0923);			    // DA Enable, #0, #1, SW 10V bipolar		
   	out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
    out16(DA_Data,(short) data);
            
    while(wave_type==0)     //stops if wave_type is not 0 (zero voltage)
    {
	    out16(DA_CTLREG,0x0923);			    // DA Enable, #0, #1, SW 10V bipolar		
   	    out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
        out16(DA_Data,(short) data);																									
    }
}

/**
    function to generate wave at D/A 0
    the wave is generated based on the wave parameters
    
    @param arg
    @return void
*/
void *generate_wave_thread(void *arg)
{   
    while(1)
    {
        switch(wave_type)
        {
            case(1):    //sine
                sine_wave();
                break;
            case(2):    //square
                square_wave();
                break;
            case(3):    //triangular
                triangular_wave();
                break;
            case(0):    //zero voltage
                zero_signal();
                break;
            default:
                printf("invalid wave type error\n");
                break;
        }
    } 
}
