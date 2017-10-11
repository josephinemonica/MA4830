/**
    MA4830 Minor Assignment
    projectile.c
    Purpose: Compute the trajectory distance of a projectile.
             Parameters include initial velocity, launching angle, and initial height.
             User can choose to vary one of this parameter, and the program will tabulate the trajectory distance

    @author Josephine Monica, Aaron Khonstantine
    @version 1 11/10/17 
*/

#include <stdio.h>
#include <math.h>

#define g 9.81      //Macro for gravitational value
#define pi 3.1415   //Macro for pi

/******************************************function prototypes********************************************/
/**
    Recursively prompt user to enter input mode (0,1,2,3) of the program until valid mode is entered
    
    @param mode_: The user input mode will be stored in this parameter
    @return void
*/
void input_mode(int* mode_);

/**
    Recursively prompt user to enter angle value until valid angle (-pi/2 to pi/2) is entered
    
    @param teta_: The user input angle will be stored in this parameter
    @return void
*/
void input_angle(double* teta_);

/**
    Recursively prompt user to enter velocity value until valid velocity (v>=0) is entered
    
    @param v: The user input velocity will be stored in this parameter
    @return void
*/
void input_velocity(double* v_);

/**
    Recursively prompt user to enter height value until valid height (y>=0) is entered
    
    @param y_: The user input height will be stored in this parameter
    @return void
*/
void input_y(double* y_);

/**
    Recursively prompt user to enter N_ (number of output data points) value 
    until valid N_ (at least 2 data points) is entered
    
    @param N_: The user input N_ will be stored in this parameter
    @return void
*/
void input_N(int* N_);

/**
    Compute and return trajectory distance of projectile 
    launched with initial velocity v_ at angle teta_ and at initial height of y_
    
    @param teta_: launching angle
    @param v_   : initial velocity
    @param y_   : initial height
    @return The computed trajectory distance for given parameters
*/
double compute_d(double teta_, double v_, double y_);

/**********************************************************************************************************/
int main()
{   
    //variables
    int mode;                       //mode of program (vary v / theta/ height)
    double v1,v2,teta1,teta2,y1,y2; 
    int N;                          //Number of data points that the program will output
    
    //auxillary variables
    int i;double step;
    
    while(1)                        //repeat the program until the user chooses to exit
    {
        //ask the user to choose mode (1: vary theta, 2: vary velocity, 3: vary height, or 0 :EXIT the program)
        input_mode(&mode);          
        
        switch (mode)
        {
            //EXIT the program
            case 0:
                return 0;   
            
            //vary theta    
            case 1: 
                //take necessary input parameters
                printf("Enter teta1\n");            //angle range
                input_angle(&teta1);
                printf("Enter teta2\n");
                input_angle(&teta2);
                
                input_N(&N);                        //N
                
                input_velocity(&v1);                //velocity
            
                input_y(&y1);                       //height
            
                //print the overhead of the table
                printf("\nCOMPUTING d for teta= %lf to %lf , v= %lf, y=%lf \n",teta1,teta2,v1,y1);
                printf("----------------------------------------------------\n");
                printf("No\t teta \t\t\t d\n");
                printf("----------------------------------------------------\n");
            
                double teta_min,teta_max;           
                teta_min=fmin(teta1,teta2);
                teta_max=fmax(teta1,teta2);
                step=(teta_max-teta_min)/(N-1);
                
                //compute and print the outputs (N data points for varying theta: teta_min to teta_max)
                for(i=0;i<N;i++)
                {
                    printf("%d\t %lf \t\t %lf\n",i+1,teta_min+i*step,compute_d(teta_min+i*step,v1,y1)); 
                }
                break;
                
            //vary v    
            case 2: 
                //take necessary input parameters
                input_angle(&teta1);                //angle
            
                printf("Enter v1\n");               //velocity range
                input_velocity(&v1);
                printf("Enter v2\n");
                input_velocity(&v2);
            
                input_N(&N);                        //N
            
                input_y(&y1);                       //height
                
                //print the overhead of the table
                printf("\nCOMPUTING d for teta= %lf, v= %lf to %lf , y=%lf \n",teta1,v1,v2,y1);
                printf("----------------------------------------------------\n");
                printf("No\t v \t\t\t d\n");
                printf("----------------------------------------------------\n");
            
                double v_min,v_max;
                v_min=fmin(v1,v2);
                v_max=fmax(v1,v2);
                step=(v_max-v_min)/(N-1);
                
                //compute and print the outputs (N data points for varying v: v_min to v_max)
                for(i=0;i<N;i++)
                {
                    printf("%d\t %lf \t\t %lf\n",i+1,v_min+i*step,compute_d(teta1,v_min+i*step,y1)); 
                }
                break;
                
            //vary y    
            case 3: 
                //take necessary input parameters
                input_angle(&teta1);                //angle
            
                input_velocity(&v1);                //velocity
            
                printf("Enter y1\n");               //initial height range
                input_y(&y1);
                printf("Enter y2\n");
                input_y(&y2);
                
                input_N(&N);                        //N
                
                //print the overhead of the table
                printf("\nCOMPUTING d for teta= %lf, v= %lf , y=%lf to %lf \n",teta1,v1,y1,y2);
                printf("----------------------------------------------------\n");
                printf("No\t y \t\t\t d\n");
                printf("----------------------------------------------------\n");
            
                double y_min,y_max;
                y_min=fmin(y1,y2);
                y_max=fmax(y1,y2);
                step=(y_max-y_min)/(N-1);
                
                //compute and print the outputs (N data points for varying height: y_min to y_max)
                for(i=0;i<N;i++)
                {
                    printf("%d\t %lf \t\t %lf\n",i+1,y_min+i*step,compute_d(teta1,v1,y_min+i*step)); 
                }
                
                break;  
        }
    }            
}
/**********************************************************************************************************/

//ask user to input mode
void input_mode(int* mode_)
{
    
    //input mode
    printf("\n>>Enter your mode selection:\n");
    printf("1 for varying angle\n");
    printf("2 for varying velocity\n");
    printf("3 for varying initial height\n");
    printf("0 to exit the program\n");
    
    int s;  //scanf return value
    s=scanf("%d",mode_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of correct type
    
    if(s==0)    ///re-ask user if input is not of type integer
    {
        printf("ERR: Invalid argument. Input is not an integer.\n");
        input_mode(mode_);              
    } 
    else        //check if input is valid (0,1,2,3)
    {
        switch(*mode_){
            case 1:
                printf("mode 1: Variation in ANGLE from teta1 to teta2\n\n");
                break;
            case 2:
                printf("mode 2: Variation in VELOCITY from v1 to v2\n\n");
                break;
            case 3:
                printf("mode 3: Variation in HEIGHT from y1 to y2\n\n");
                break;
            case 0:
                printf("EXIT the program\n\n");
                break;
            default:    //invalid input
                printf("ERR: Invalid argument. Please enter 0, 1, 2, or 3 \n");
                input_mode(mode_);      //ask the user to reenter mode
        }
    }
}

//ask user to input initial angle
void input_angle(double* teta_)
{
    //teta only from -90degree to 90degree, otherwise different computation
    printf(">>Enter angle (radian) from -pi/2 to pi/2: ");
    
    int s;
    s=scanf("%lf",teta_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)                        ///re-ask user if input is not of type double
    {   
        printf("ERR: Invalid argument. Input is not a double type.\n");
        input_angle(teta_); 
    }
    else if(*teta_>pi/2 || *teta_<-pi/2)    //re-ask user if input is not in valid range (-pi/2 to pi/2)  
    {
        printf("ERR: Invalid argument. Angle must be between -pi/2 and pi/2\n");
        input_angle(teta_);
    }

}

//ask user to input initial velocity
void input_velocity(double* v_)
{   
    //velocity must be at least 0 or positive
    printf(">>Enter positive velocity (m/s): ");
    
    int s;
    s=scanf("%lf",v_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)                //re-ask user if input is not of type double        
    {   
        printf("ERR: Invalid argument. Input is not a double type.\n");
        input_velocity(v_); 
    }
    else if(*v_<0)          //re-ask user if input is not in valid range (>0)
    {
        printf("ERR: Invalid argument. Velocity must be zero or positive\n");
        input_velocity(v_);
    }
}

//ask user to input initial height y
void input_y(double* y_)
{
    //y must be at least 0 or positive
    printf(">>Enter positive initial height (m): ");
    
    int s;
    s=scanf("%lf",y_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)            //re-ask user if input is not of type double
    {
        printf("ERR: Invalid argument. Input is not a double type.\n");
        input_y(y_);    
    }
    else if(*y_<0)      //re-ask user if input is not in valid range (>0)
    {
        printf("ERR: Invalid argument. Initial height must be zero or positive\n");
        input_y(y_);
    }
}

//ask user to input N
void input_N(int* N_)
{
    //input N
    printf("d will be computed N times for different values of parameter in the range\n");
    printf("Note that minimum of N is 2 (to at least include the two boundaries in range) \n");
    printf(">>Enter desired N: ");
    
    int s;  //scanf return value
    s=scanf("%d",N_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of the correct type
    
    if(s==0)    //re-ask user if input is not of type integer
    {
        printf("ERR: Invalid argument. Input is not an integer.\n");
        input_N(N_); 
    }
    else if(*N_<2)  //re-ask user if input is not in valid range (at least 2)
    {
        printf("ERR: Invalid argument. N must be at least 2\n");
        input_N(N_); 
    }   
}

//returns computed trajectory distance
double compute_d(double teta_, double v_, double y_)
{
    /*INSTEAD of (pow(v_,2)*sin(2*teta_)/(2*g)) * (1 + sqrt(1+2*g*y_/(pow(v_,2)*pow(sin(teta_),2))))
    rewrite the formula as follos to avoid edge case division  by 0
    and to allow correct value of for negative angle*/
    return (pow(v_,2)/(2*g)) * (sin(2*teta_) + sqrt( pow(sin(2*teta_),2) + 8*g*y_* pow(cos(teta_),2) /(pow(v_,2))));
}
