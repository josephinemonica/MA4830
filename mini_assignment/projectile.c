#include <stdio.h>
#include <math.h>

#define g 9.81      //Macro for gravitational value
#define pi 3.1415   //Macro for pi

//function prototypes
void input_mode(int* mode_);
void input_angle(double* teta_);
void input_velocity(double* v_);
void input_y(double* y_);
void input_N(int* N_);
double compute_d(double teta_, double v_, double y_);

int main()
{   
    //variables
    int mode;
    double v1,v2,teta1,teta2,y1,y2;
    int N;
    
    //auxillary variables
    int i;double step;
    
    while(1)    //repeat the program until the user chooses to exit
    {
        //ask the user to choose mode (vary teta, velocity, height, or EXIT the program)
        input_mode(&mode);
        
        switch (mode)
        {
            //EXIT the program
            case 0:
                return 0;   
            
            //vary teta    
            case 1: 
                //take necessary input parameters
                printf("Enter teta1\n");
                input_angle(&teta1);
                printf("Enter teta2\n");
                input_angle(&teta2);
                
                input_N(&N);
                
                input_velocity(&v1);
            
                input_y(&y1);
            
                //print the overhead of the table
                printf("\nCOMPUTING d for teta= %lf to %lf , v= %lf, y=%lf \n",teta1,teta2,v1,y1);
                printf("----------------------------------------------------\n");
                printf("No\t teta \t\t\t d\n");
                printf("----------------------------------------------------\n");
            
                double teta_min,teta_max;
                teta_min=fmin(teta1,teta2);
                teta_max=fmax(teta1,teta2);
                step=(teta_max-teta_min)/(N-1);
                
                //compute and print the outputs
                for(i=0;i<N;i++)
                {
                    printf("%d\t %lf \t\t %lf\n",i+1,teta_min+i*step,compute_d(teta_min+i*step,v1,y1)); 
                }
                break;
                
            //vary v    
            case 2: 
                //take necessary input parameters
                input_angle(&teta1);
            
                printf("Enter v1\n");
                input_velocity(&v1);
                printf("Enter v2\n");
                input_velocity(&v2);
            
                input_N(&N);
            
                input_y(&y1);
                
                //print the overhead of the table
                printf("\nCOMPUTING d for teta= %lf, v= %lf to %lf , y=%lf \n",teta1,v1,v2,y1);
                printf("----------------------------------------------------\n");
                printf("No\t v \t\t\t d\n");
                printf("----------------------------------------------------\n");
            
                double v_min,v_max;
                v_min=fmin(v1,v2);
                v_max=fmax(v1,v2);
                step=(v_max-v_min)/(N-1);
                
                //compute and print the outputs
                for(i=0;i<N;i++)
                {
                    printf("%d\t %lf \t\t %lf\n",i+1,v_min+i*step,compute_d(teta1,v_min+i*step,y1)); 
                }
                break;
                
            //vary y    
            case 3: 
                //take necessary input parameters
                input_angle(&teta1);
            
                input_velocity(&v1);
            
                printf("Enter y1\n");
                input_y(&y1);
                printf("Enter y2\n");
                input_y(&y2);
                input_N(&N);
                
                //print the overhead of the table
                printf("\nCOMPUTING d for teta= %lf, v= %lf , y=%lf to %lf \n",teta1,v1,y1,y2);
                printf("----------------------------------------------------\n");
                printf("No\t y \t\t\t d\n");
                printf("----------------------------------------------------\n");
            
                double y_min,y_max;
                y_min=fmin(y1,y2);
                y_max=fmax(y1,y2);
                step=(y_max-y_min)/(N-1);
                
                //compute and print the outputs
                for(i=0;i<N;i++)
                {
                    printf("%d\t %lf \t\t %lf\n",i+1,y_min+i*step,compute_d(teta1,v1,y_min+i*step)); 
                }
                
                break;  
        }
    }            
}

//recursively (until valid input) ask user to input mode
void input_mode(int* mode_)
{
    
    //input mode
    printf("\nEnter your mode selection:\n");
    printf("1 for varying angle\n");
    printf("2 for varying velocity\n");
    printf("3 for varying initial height\n");
    printf("0 to exit the program\n");
    
    int s;  //scanf return value
    s=scanf("%d",mode_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of correct type
    
    //check if input is not integer
    if(s==0)
    {
        printf("ERR: Invalid argument. Input is not an integer.\n");
        input_mode(mode_);                //ask the user to reenter mode
    } 
    else
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
            default:
                printf("ERR: Invalid argument. Please enter 0, 1, 2, or 3 \n");
                input_mode(mode_);                   //ask the user to reenter mode
        }
    }
}

void input_N(int* N_)
{
    //input N
    printf("d will be computed N times for different values of parameter in the range\n");
    printf("Note that minimum of N is 2 (to at least include the two boundaries in range) \n");
    printf("Enter desired N: ");
    
    int s;  //scanf return value
    s=scanf("%d",N_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of correct type
    
    //check if input is not integer
    if(s==0)
    {
        printf("ERR: Invalid argument. Input is not an integer.\n");
        input_N(N_);                //ask the user to reenter mode
    }
    else if(*N_<2)
    {
        printf("ERR: Invalid argument. N must be at least 2\n");
        input_N(N_);
    }
}

double compute_d(double teta_, double v_, double y_)
{
   //Computation of d
   
    //return (pow(v_,2)*sin(2*teta_)/(2*g)) * (1 + sqrt(1+2*g*y_/(pow(v_,2)*pow(sin(teta_),2))));
    //to avoid edge case (division  by 0) when teta=0:
    return (pow(v_,2)/(2*g)) * (sin(2*teta_) + sqrt( pow(sin(2*teta_),2) + 8*g*y_* pow(cos(teta_),2) /(pow(v_,2))));
}

void input_angle(double* teta_)
{
    //teta only from -90degree to 90degree, otherwise different computation
    printf("Enter angle (radian) from -pi/2 to pi/2: ");
    
    int s;
    s=scanf("%lf",teta_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of correct type
    
    if(s==0)
    {   
        printf("ERR: Invalid argument. Input is not a double type.\n");
        input_angle(teta_); //ask the user to reenter angle
    }
    else if(*teta_>pi/2 || *teta_<-pi/2)
    {
        printf("ERR: Invalid argument. Angle must be between -pi/2 and pi/2\n");
        input_angle(teta_);
    }

}

void input_velocity(double* v_)
{   
    //velocity must be at least 0 or positive
    printf("Enter positive velocity (m/s): ");
    
    int s;
    s=scanf("%lf",v_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of correct type
    
    if(s==0)
    {   
        printf("ERR: Invalid argument. Input is not a double type.\n");
        input_velocity(v_); //ask the user to reenter avelocity
    }
    else if(*v_<0)
    {
        printf("ERR: Invalid argument. Velocity must be zero or positive\n");
        input_velocity(v_);
    }
}

void input_y(double* y_)
{
    //y must be at least 0 or positive
    printf("Enter positive initial height (m): ");
    
    int s;
    s=scanf("%lf",y_);
    while ((getchar()) != '\n');    //flush the scanf buffer. This is especially useful when the argument is not of correct type
    
    if(s==0)
    {
        printf("ERR: Invalid argument. Input is not a double type.\n");
        input_y(y_); //ask the user to reenter avelocity
    }
    else if(*y_<0)
    {
        printf("ERR: Invalid argument. Initial height must be zero or positive\n");
        input_y(y_);
    }
}
