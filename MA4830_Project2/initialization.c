/**
    MA4830
    initialization.c
    implementation of initialization.h
    Purpose: Library containing functions & variables(base address, registers, etc)
     needed to initialize PCI hardware

    @author Josephine Monica, Aaron Khonstantine
    @version 1 last update 17/11/17 
*/
#include "initialization.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <math.h>

/**
    function to read switch0
    Initialize PCI hardware
    
    @param -
    @return void
*/
void initialization()
{
    printf("__        __   _\n");                          
    printf("\\ \\      / /__| | ___ ___  _ __ ___   ___ \n");
    printf(" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ \n");
    printf("  \\ V  V /  __/ | (_| (_) | | | | | |  __/\n");
    printf("   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|\n");
    printf("\n");

    memset(&info,0,sizeof(info));
    if(pci_attach(0)<0) {
        perror("pci_attach");
        exit(EXIT_FAILURE);
    }
    
	/* Vendor and Device ID */
    info.VendorId=0x1307;
    info.DeviceId=0x01;

    if ((hdl=pci_attach_device(0, PCI_SHARE|PCI_INIT_ALL, 0, &info))==0) {
        perror("pci_attach_device");
        exit(EXIT_FAILURE);
    }
  	// Determine assigned BADRn IO addresses for PCI-DAS1602
    for(i=0;i<5;i++) {
        badr[i]=PCI_IO_ADDR(info.CpuBaseAddress[i]);
    }

    for(i=0;i<5;i++) {  // expect CpuBaseAddress to be the same as iobase for PC
        iobase[i]=mmap_device_io(0x0f,badr[i]);
    }
	// Modify thread control privity
    if(ThreadCtl(_NTO_TCTL_IO,0)==-1) {
        perror("Thread Control");
        exit(1);
    }
}

/**
    function to initialize DIO
    
    @param -
    @return void
*/
void initialize_DIO()
{
	out8(DIO_CTLREG,0x90);		//set portA (switch) as Digital input, portB (LED) as Digital output
}

/**
    function to initialize ADC
    
    @param -
    @return void
*/
void Initialize_ADC()
{
 	out16(TRIGGER,0x2081);  //set trigger control
 	out16(AUTOCAL,0x007f);  //set calibration register
 	out16(AD_FIFOCLR,0);    //clear ADC FIFO
 	out16(MUXCHAN,0x0C10);  //select the channel
}
