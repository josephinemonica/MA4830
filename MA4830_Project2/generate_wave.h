/**
    MA4830
    generate_wave.h
    implementation in generate_wave.c
    Purpose: Library containing functions & variables needed related for generating wave purpose

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/

#ifndef __GENERATE_WAVE_H
#define __GENERATE_WAVE_H

#ifdef __cplusplus
	extern "C" {
#endif

//Wave parameters
int f;      //frequency
float A;    //ampltude
float avg;  //average value of wave voltage
int D;      //duty cycle (only affects square wave)
int wave_type;  //1 sine, 2 square, 3 triangular, 0 zero voltage

/**
    function to generate wave at D/A 0
    the wave is generated based on the wave parameters
    
    @param arg
    @return void
*/
void *generate_wave_thread(void *arg);

#ifdef __cplusplus
	}
#endif

#endif /* __GENERATE_WAVE_H */
