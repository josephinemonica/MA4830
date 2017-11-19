HOW TO COMPILE THE PROGRAM
cc -c hardware_input.c
cc -c keyboard_input.c
cc -c switch_input_mode.c
cc -c initialization.c
cc -c generate_wave.c
cc -lm hardware_input.o keyboard_input.o switch_input_mode.o initialization.o generate_wave.o -o main main.c

HOW TO RUN THE PROGRAM
./main t:wave_type A:A_value m:mean_value f:frequency level D:duty_cyctle_value
NOTE: duty cycle only affects for square wave
