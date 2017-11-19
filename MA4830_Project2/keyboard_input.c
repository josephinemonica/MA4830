/**
    MA4830
    keyboard_input.c
    implementation od keyboard_input.h
    Purpose: Library containing functions & variables needed related to get wave_parameter input from keyboard

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//thread and process library
#include <pthread.h>
#include <process.h>

#include "switch_input_mode.h"  //for shared variable input_mode
#include "generate_wave.h"      //for shared wave parameters (A,D,wave_type,f,avg)
//***********************************************************************************************************************************//
int s;  //scanf return value

int mode_;
float A_dummy, avg_dummy;
int f_dummy, D_dummy, wave_type_dummy;

/**
    Recursively prompt user to enter A (amplitude) value until valid A
    
    @param -
    @return void
*/
void input_A()
{
    //input A
    printf("mode 1: Input amplitude: \n");
    
    s=scanf("%f",&A_dummy);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)    //re-ask user if input is not of type float
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid argument. Your input is not of float type.\n");
        printf("*******************************************************\n");
        input_A(); 
    }
    //check if Amplitude is valid
    else if(A_dummy>5 || A_dummy<0)  //specify the invalid range of valid A
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid A\n");//change error message
        printf("A must be between 0 and 5\n");
        printf("*******************************************************\n");
        input_A(); 
    }   
    else    //valid
    {
        A=A_dummy;
    }
}

/**
    Recursively prompt user to enter f (frequency level) value until valid f
    
    @param -
    @return void
*/
void input_f()
{
    //input f
    printf("mode 2: Input frequency: \n");
    
    s=scanf("%d",&f_dummy);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)    //re-ask user if input is not of type int
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid argument. Your input is not of int type.\n");
        printf("*******************************************************\n");
        input_f(); 
    }
    //check if frequency is valid
    else if(f_dummy!=1 && f_dummy!=2 && f_dummy!=3 && f_dummy!=4 && f_dummy!=5)
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid f\n");
        printf("Choose one level of f (1,2,3,4,5)\n");
        printf("*******************************************************\n");
        input_f(); 
    } 
    else    //valid
    {
        f=f_dummy;
    }
}

/**
    Recursively prompt user to enter wave average (avg) value until valid avg
    
    @param -
    @return void
*/
void input_avg()
{
    //input avg
    printf("mode 3: Input average: \n");
    
    s=scanf("%f",&avg_dummy);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)    //re-ask user if input is not of type float
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid argument. Your input is not of float type.\n");
        printf("*******************************************************\n");
        input_avg(); 
    }
    //check if average is valid
    else if(avg_dummy<-5 || avg_dummy>5)  
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid avg\n");
        printf("avg must be between -5 and 5\n");
        printf("*******************************************************\n");
        input_avg(); 
    }   
    else    //valid
    {
        avg=avg_dummy;
    }
}

/**
    Recursively prompt user to enter D (duty cycle) value until valid D
    
    @param -
    @return void
*/
void input_D()
{
    //input D
    printf("mode 4: Input duty cycle: \n");
    
    s=scanf("%d",&D_dummy);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)    //re-ask user if input is not of type int
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid argument. Your input is not of int type.\n");
        printf("*******************************************************\n");
        input_D(); 
    }
    //check if duty cycle is valid
    else if(D_dummy<0 || D_dummy>100) 
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid D\n");
        printf("D must be between 0 and 100\n");
        printf("*******************************************************\n");
        input_D(); 
    }
    else    //valid
    {
        D=D_dummy;
    }
}

/**
    Recursively prompt user to enter wave form (wave_type) value until valid wave_type
    
    @param -
    @return void
*/
void input_wave_type()
{
    //input wave type
    printf("Input wave type (1 for sine, 2 for square, 3 for triangular): \n");// sine(1), square(2), tri(3), 
    
    s=scanf("%d",&wave_type_dummy);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)    //re-ask user if input is not of type int
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid argument. Your input is not of int type.\n");
        printf("*******************************************************\n");
        input_wave_type(); 
    }
    //check if wave type is valid
    else if(wave_type_dummy!=1 && wave_type_dummy!=2 && wave_type_dummy!=3)
    {
        printf("\n*******************************************************\n");
        printf("ERR: Invalid input\n");
        printf("Input 1 for sine wave, 2 for square wave, 3 for triangular wave\n");
        printf("*******************************************************\n");
        input_wave_type(); 
    }   
    else    //valid
    {
        wave_type=wave_type_dummy;
    }
}

/**
    function to get wave parameters from user keyboard input
    
    @param -
    @return void
*/
void keyboard()
{
        printf("\n");
        printf("==================================================================\n");
        printf("A\t\t:%f\n", A);
        printf("avg\t\t:%f\n", avg);
        printf("wave type\t:%d (%s)\n",wave_type,wave_type==1?"sine":(wave_type==2?"square":"triangular"));
        printf("Duty cycle\t:%d\n",D);
        printf("f level\t\t:%d\n",f);
        printf("------------------------------------------------------------------\n");
        printf("0: Terminate program\n");
        printf("1: Change amplitude (A): 0 to 5 \n");
        printf("2: Change frequency level (f): 1, 2, 3, 4, 5\n");
        printf("3: Change average (avg): -5 to 5\n");
        printf("4: Change duty cycle (D): 0 to 100\n");
        printf("5: Change wave type: 1 for sine, 2 for square, 3 for triangular \n");
        printf("Enter selection: \n");
        s=scanf("%d",&mode_);
        while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of correct type
    
        if(s==0)    ///re-ask user if input is not of type integer
        {   
            printf("\n*******************************************************\n");
            printf("ERR: Invalid argument. Input is not an integer.\n");
            printf("*******************************************************\n");
            keyboard();
        } 
        else        //check if input is valid (0,1,2,3,4,5)
        {
            switch(mode_){
                case 1:
                    input_A();
                    break;
                case 2:
                    input_f();
                    break;
                case 3:
                    input_avg();
                    break;
                case 4:
                    input_D();
                    break;
                case 5:
                    input_wave_type();
                    break;
                case 0:
                    raise(SIGINT);
                    //exit program
                    break;
                default:    //invalid input
                    printf("\n*******************************************************\n");
                    printf("ERR: Invalid argument. Please enter 0, 1, 2, 3, 4, or 5 \n");
                    printf("*******************************************************\n");
                    keyboard();      //ask the user to reenter mode
            }
        }
}
/**
    thread to recursively get wave parameters from user keyboard input
    
    @param arg
    @return void
*/
void *keyboard_input_thread(void *arg)
{
     while(input_mode==0)
     {
        keyboard();
     }
}

