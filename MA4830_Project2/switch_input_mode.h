/**
    MA4830
    switch_input_mode.h
    implementation in switch_input_mode.c
    Purpose: Library containing functions & variables needed related to reading switch0
    toggle switch0 to 0 -> input is from keyboard
    toggle switch0 to 1 -> input is from hardware
    it will also read wave parameters either from keyboard or hardware depending on the switch4 state

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/

#ifndef __SWITCH_INPUT_MODE_H
#define __SWITCH_INPUT_MODE_H


#ifdef __cplusplus
	extern "C" {
#endif

//0 = means input is from keyboard; 1= means input is from hardware
//this var is shared between switch_input_mode thread and (keyboard_input, hardware_input)
int input_mode; 

/**
    function to read switch0
    Prompt input from user (either from keyboard or hardware, depending on the state of switch0)
    toggle switch0 to 0 -> input is from keyboard
    toggle switch0 to 1 -> input is from hardware
    
    @param arg
    @return void
*/
void *switch_input_mode_thread(void *arg);

#ifdef __cplusplus
	}
#endif

#endif /* __SWITCH_INPUT_MODE_H */
