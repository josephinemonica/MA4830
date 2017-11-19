/**
    MA4830
    switch_input_mode.c
    implementation of switch_input_mode.h
    Purpose: Library containing functions & variables needed related to reading switch0
    toggle switch0 to 0 -> input is from keyboard
    toggle switch0 to 1 -> input is from hardware
    
    it will also read wave parameters either from keyboard or hardware depending on the switch0 state
    
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
#include <pthread.h>
#include <process.h>
#include "initialization.h"
#include "keyboard_input.h"
#include "hardware_input.h"
#include "switch_input_mode.h"

//thread ID
pthread_t keyboard_input_thread_ID;
pthread_t hardware_input_thread_ID;

/**
    function to convert raw reading of digital output into reading of switch0
    
    @param arg
    @return reading of switch0 (either 0 or 1)
*/
int switch0_value(int switch_value)
{
	return switch_value%2;
}

/**
    function to read switch0
    Prompt input from user (either from keyboard or hardware, depending on the state of switch0)
    toggle switch0 to 0 -> input is from keyboard
    toggle switch0 to 1 -> input is from hardware
    
    @param arg
    @return void
*/
void *switch_input_mode_thread(void *arg)
{
    //initialize variables
	dio_switch = in8(DIO_PORTA);
	switch0=switch0_value(dio_switch);
    switch0_prev=switch0;
    input_mode=switch0;
    if(input_mode==0)
    {
        pthread_create( &keyboard_input_thread_ID, NULL, &keyboard_input_thread, NULL );   //keyboard_input_thread
    }
    else if(input_mode==1)
    {
        pthread_create( NULL, NULL, &hardware_input_thread, NULL );   //hardware_input_thread
    }
    
    while(1)
    {
		
       //read SWITCH
		dio_switch = in8(DIO_PORTA);
		switch0=switch0_value(dio_switch);
		out8(DIO_PORTB,dio_switch); //update LED light

		if (switch0!=switch0_prev)
        {
            //DEBOUNCING
			delay(1);
			//read SWITCH0 again
			dio_switch = in8(DIO_PORTA);
			if(switch0_value(dio_switch)==switch0)
			{
				//change detected from 0 to 1
            	if(switch0==0)	//0=keyboard input
            	{
            	    
               		//input from keyboard
               		input_mode=0;
                	
                	delay(1000);
                	
					//kill hardware_input thread, spawn keyboard_input thread

					pthread_create(&keyboard_input_thread_ID, NULL, &keyboard_input_thread, NULL );   //keyboard_input_thread
					
           		}
				//change detected from 1 to 0
           		else if(switch0==1)	//1=hardware input
           		{
               	    //input from hardware
               	    input_mode=1;
               	    
               	    delay(1000);
               	    
				    //keyboard_input thread terminates itself, spawn hardware_input thread
				    pthread_cancel(keyboard_input_thread_ID);
				    pthread_create( &hardware_input_thread_ID, NULL, &hardware_input_thread, NULL );   //hardware_input_thread
           		}
            //update switch0_prev 
            switch0_prev = switch0;
 
			}     
        }
    }
}

