/**
    MA4830
    hardware_input.h
    implementation in hardware_input.c
    Purpose: Library containing functions & variables needed related for reading and set wave parameter 
    from hardware (potentiometers and switches)

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/

#ifndef __HARDWARE_INPUT_H
#define __HARDWARE_INPUT_H

#ifdef __cplusplus
	extern "C" {
#endif

/**
    function to read and set wave parameter from hardware (potentiometers and switches)
    
    @param arg
    @return void
*/
void *hardware_input_thread(void *arg);

#ifdef __cplusplus
	}
#endif

#endif /* __HARDWARE_INPUT_H */
