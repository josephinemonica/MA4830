/**
    MA4830
    main.c
    Purpose: Generate wave on D/A 0
             Various parameters include wave form, amplitude, average, frequency level, duty cycle(only for square wave)
             User can set the parameter from : command line argument, tweaking potentiometers and switches from hardware board, keyboard input

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <process.h>
#include <pthread.h>
#include <stdlib.h>
#include "initialization.h"
#include "switch_input_mode.h"
#include "generate_wave.h"  //for shared wave parameters (A,D,wave_type,f,avg)

//variables for parsing command line arguments
int j;
char colon=':';
char argument;
char* argument_value;
//variable for file logging
FILE *fp;
//variables for finding the duration that the program runs
struct timespec start,stop;
double period;

/*--------------------------------------function prototypes-----------------------------------------------*/

/**
    function to handle SIGINT signal (ctrl+c):
    write exit message & duration that the program has run to log.txt, clear terminal screen, print exit message,
    stops the program
    
    @param signum: signal number
    @return void
*/
void signal_handler( int signum) 
{
    
    //get the time when the program stops
    if(clock_gettime(CLOCK_REALTIME,&stop)==-1)
    { 
        printf("clock gettime stop error");
    }
    
    //compute duration that program has run
    period=(double)(stop.tv_sec-start.tv_sec)+ (double)(stop.tv_nsec- start.tv_nsec)/1000000000;
    
    ///create/open log.txt for logging & log exit message and duration that the program has run
    fp = fopen("log.txt","a");
    fprintf(fp,"Ending program \n");
    fprintf(fp,"Program runs for %lf seconds \n\n",period);
    fclose(fp);
    
    pci_detach_device(hdl);
    
    system("/usr/bin/clear");                           //clear screen
    printf("_________________________     \n");         //exit message
    printf("( GOOD BYE)                  \n");
    printf(" -------------------------    \n");
    printf("        o   ^__^\n");
    printf("         o  (oo)\\_______      \n");
    printf("            (__)\\       )\\/\\  \n");
    printf("              ||----w |       \n");
    printf("              ||     ||       \n");
    printf( "\n--------EXIT THE PROGRAM-------\n" );
    exit(EXIT_SUCCESS);                                 //exit the program
}

/*------------------------------------------------------------------------------------------------------------*/
int main(int argc, char * argv[])
{
    //attach signal_handler to catch SIGINT
    signal(SIGINT, signal_handler);
    
    //Set Default Values of wave parameters
    f=1;            //frequency mode level
    A=2.0;          //ampltude
    avg=0;          //average
    D=50;           //duty cycle for square wave
    wave_type=1;    //sine
    
    /*****************************parse command line argument(s)**********************************/
    // ./main t:wave_type A:A_value m:mean_value f:frequency level D:duty_cyctle_value
    for(j=1;j<argc;j++)
    {
        //find colon
        if(argv[j][1]!=colon)   //invalid argument: colon not found at second character
        {
            printf("ERROR: Invalid command line argument\n");
            printf("Command line argument should be as:\n");
            printf("./main t:wave_type A:A_value m:mean_value f:frequency mode choose one level(1, 2, 3, 4, 5) D:duty_cyctle_value\n");
            printf("*******************************************************\n");
            return 0;   //invalid, exit program
        }
        
        //get the argument ( A or avg or f or D or wave type)
        argument=argv[j][0];
        
        //get the VALUE of the argument
        argument_value=&(argv[j][2]);
        switch (argument)
        {
            case('A'):
                if(sscanf(argument_value,"%f",&A)!=1)   //parse A value and check whether it is of correct data type
                {
                    printf("\n*******************************************************\n");
                    printf("ERROR: A must be FLOAT\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                }
                else if(A>5 || A<0)                     //check if Amplitude is in valid range (0 to 5)
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: Invalid A\n");
                    printf("A must be between 0 and 5\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                }  
                break;
               
            case('m'):                                  //parse average/mean value and check whether it is of correct data type
                if(sscanf(argument_value,"%f",&avg)!=1)
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: mean must be FLOAT\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                } 
                else if(avg<-5 || avg>5)                //check if average is in valid range (-5 to 5)
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: Invalid avg\n");
                    printf("avg must be between -5 and 5\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                }    
                break;
                
            case('f'):                                  //parse f level value and check whether it is of correct data type
                if(sscanf(argument_value,"%d",&f)!=1)
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: frequency must be INT\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                }
                else if(f!=1 && f!=2 && f!=3 && f!=4 && f!=5)   //check if frequency is valid (level 1,2,3,4,5)
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: Invalid f\n");
                    printf("Choose one level of f (1,2,3,4,5)\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                } 
                break;
                
            case('D'):
                if(sscanf(argument_value,"%d",&D)!=1)   //parse D value and check whether it is of correct data type
                {
                    printf("\n*******************************************************\n");
                    printf("ERROR: Duty cycle must be INT\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                }
                else if(D<0 || D>100)                           //check if duty cycle is in valid range(0 to 100)
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: Invalid D\n");
                    printf("D must be between 0 and 100\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                } 
                break;
                
            case('t'):  
                if(sscanf(argument_value,"%d",&wave_type)!=1)   //parse wave type and check whether it is of correct data type
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: wave type must be INT (0,1,2,3)\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                }
            else if(wave_type!=1 && wave_type!=2 && wave_type!=3 && wave_type!=0)   //check if wave type value is valid
                {
                    printf("\n*******************************************************\n");
                    printf("ERR: Invalid input\n");
                    printf("Input 1 for sine wave, 2 for square wave, 3 for triangular wave, 0 for zero signal (no wave)\n");
                    printf("*******************************************************\n");
                    return 0;   //invalid, exit program
                }  
                break;
                
            default:    //invalid
                printf("\n*******************************************************\n");
                printf("ERR: Invalid command line argument\n");
                printf("Command line argument should be as:\n");
                printf("./main t:wave_type A:A_value m:mean_value f:frequency level D:duty_cyctle_value\n");
                printf("*******************************************************\n");
                return 0;   //invalid, exit program
                break;
        }
    }
    /*******************************************************************************************/
   
    initialization();   //initialize hardware
    initialize_DIO();   //initialize Digital Input Output
    Initialize_ADC();   //initialize ADC
    
    //get the time when the program starts
    if(clock_gettime(CLOCK_REALTIME,&start)==-1)
    { 
        printf("clock gettime start error");
    } 
    
    //create/open log.txt for logging & write starting message
    fp = fopen("log.txt","a");
    fprintf(fp,"Starting program\n");
    fclose(fp);
    
    //create switch_input_mode_thread -> it will create either thread for keyboard_input or hardware_input
    //depending on the switch state
    pthread_create( NULL, NULL, &switch_input_mode_thread, NULL );
    //create generate_wave_thread   
    pthread_create( NULL, NULL, &generate_wave_thread, NULL );   
           
 	while(1)
 	{}
  	
  	printf("\n\nExit Program\n");
    pci_detach_device(hdl);
    
    return 0;
}


