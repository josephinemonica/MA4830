/**
    MA4830
    keyboard_input.h
    implementation in keyboard_input.c
    Purpose: Library containing functions & variables needed related to get wave_parameter input from keyboard

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/

#ifndef __KEYBOARD_INPUT_H
#define __KEYBOARD_INPUT_H


#ifdef __cplusplus
	extern "C" {
#endif

/**
    thread function to get wave_parameter input from keyboard
    
    @param arg
    @return void
*/
void *keyboard_input_thread(void *arg);

#ifdef __cplusplus
	}
#endif

#endif /* __KEYBOARD_INPUT_H */
