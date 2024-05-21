//###########################################################################
// FILE:   F28M35x_ECap.c
// TITLE:  F28M35x eCAP Initialization & Support Functions.
//###########################################################################
// $TI Release: F28M35x Support Library v220 $
// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $
// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28M35x_Device.h"     // F28M35x Headerfile Include File
#include "F28M35x_Examples.h"   // F28M35x Examples Include File

//---------------------------------------------------------------------------
// InitECap:
//---------------------------------------------------------------------------
// This function initializes the eCAP(s) to a known state.
void InitECap(void)
{
    // Initialize eCAP1/2/3/4/5/6

    //tbd...

}

//---------------------------------------------------------------------------
// Example: InitECapGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ECAP pins
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
// Caution:
// For each eCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation.
// Comment out other unwanted lines.

void InitECapGpio()
{

    InitECap1Gpio();
    InitECap2Gpio();
    InitECap3Gpio();
    InitECap4Gpio();
    InitECap5Gpio();
    InitECap6Gpio();
}

void InitECap1Gpio(void)
{
    EALLOW;

/* Enable internal pull-up for the selected pins */

// Pull-up enable should be set in the
// GPIO_O_PUR register in the M3 code.

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;    // Synch to SYSCLKOUT GPIO5 (CAP1)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;   // Synch to SYSCLKOUT GPIO24 (CAP1)
//  GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 0;   // Synch to SYSCLKOUT GPIO34 (CAP1)

/* Configure eCAP-1 pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be eCAP1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;     // Configure GPIO5 as CAP1
//  GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;    // Configure GPIO24 as CAP1
//  GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 1;    // Configure GPIO34 as CAP1

// Configure GPIO MUX TRIP Inputs
    GpioTripRegs.GPTRIP7SEL.bit.GPTRIP7SEL = 5;     // Configure GPIO5 as CAP1
//  GpioTripRegs.GPTRIP7SEL.bit.GPTRIP7SEL = 24;    // Configure GPIO24 as CAP1
//  GpioTripRegs.GPTRIP7SEL.bit.GPTRIP7SEL = 34;    // Configure GPIO34 as CAP1

    EDIS;
}

void InitECap2Gpio(void)
{
    EALLOW;

/* Enable internal pull-up for the selected pins */

// Pull-up enable should be set in the
// GPIO_O_PUR register in the M3 code.

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;        // Synch to SYSCLKOUT GPIO7
// (CAP2)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;       // Synch to SYSCLKOUT GPIO25
// (CAP2)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO37 = 0;       // Synch to SYSCLKOUT GPIO37
                                                // (CAP2)

/* Configure eCAP-2 pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be eCAP2 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 3;     // Configure GPIO7 as CAP2
//    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;    // Configure GPIO25 as CAP2
    GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 1;    // Configure GPIO37 as CAP2

// Configure GPIO MUX TRIP Inputs
//    GpioTripRegs.GPTRIP8SEL.bit.GPTRIP8SEL = 7;    // Configure GPIO7 as CAP1
//    GpioTripRegs.GPTRIP8SEL.bit.GPTRIP8SEL = 25; // Configure GPIO25 as CAP1
    GpioTripRegs.GPTRIP8SEL.bit.GPTRIP8SEL = 37; // Configure GPIO37 as CAP1

    EDIS;
}

void InitECap3Gpio(void)
{
    EALLOW;

/* Enable internal pull-up for the selected pins */

// Pull-up enable should be set in the
// GPIO_O_PUR register in the M3 code.

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;    // Synch to SYSCLKOUT GPIO9 (CAP3)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;   // Synch to SYSCLKOUT GPIO26 (CAP3)

/* Configure eCAP-3 pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be eCAP3 functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;     // Configure GPIO9 as CAP3
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as CAP3

// Configure GPIO MUX TRIP Inputs
//    GpioTripRegs.GPTRIP9SEL.bit.GPTRIP9SEL = 9;    // Configure GPIO9 as CAP1
    GpioTripRegs.GPTRIP9SEL.bit.GPTRIP9SEL = 26; // Configure GPIO26 as CAP1

    EDIS;
}

void InitECap4Gpio(void)
{
    EALLOW;

/* Enable internal pull-up for the selected pins */

// Pull-up enable should be set in the
// GPIO_O_PUR register in the M3 code.

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0;    // Synch to SYSCLKOUT GPIO11
// (CAP4)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0;    // Synch to SYSCLKOUT GPIO27 (CAP4)

/* Configure eCAP-4 pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be eCAP4 functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;     // Configure GPIO11 as CAP4
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;     // Configure GPIO27 as CAP4

// Configure GPIO MUX TRIP Inputs
//  GpioTripRegs.GPTRIP10SEL.bit.GPTRIP10SEL = 11;    // Configure GPIO11 as
// CAP1
    GpioTripRegs.GPTRIP10SEL.bit.GPTRIP10SEL = 27;   // Configure GPIO27 as CAP1

    EDIS;
}

void InitECap5Gpio(void)
{
    EALLOW;

/* Enable internal pull-up for the selected pins */

// Pull-up enable should be set in the
// GPIO_O_PUR register in the M3 code.

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 0;    // Synch to SYSCLKOUT GPIO3 (CAP5)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = 0;   // Synch to SYSCLKOUT GPIO48 (CAP5)

/* Configure eCAP-5 pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be eCAP5 functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 2;     // Configure GPIO3 as CAP5
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 1;    // Configure GPIO48 as CAP5

// Configure GPIO MUX TRIP Inputs
//    GpioTripRegs.GPTRIP11SEL.bit.GPTRIP11SEL = 3;    // Configure GPIO3 as
// CAP1
    GpioTripRegs.GPTRIP11SEL.bit.GPTRIP11SEL = 48;   // Configure GPIO48 as CAP1

    EDIS;
}

void InitECap6Gpio(void)
{
    EALLOW;

/* Enable internal pull-up for the selected pins */

// Pull-up enable should be set in the
// GPIO_O_PUR register in the M3 code.

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 0;    // Synch to SYSCLKOUT GPIO1 (CAP6)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO49 = 0;   // Synch to SYSCLKOUT GPIO49 (CAP6)

/* Configure eCAP-6 pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be eCAP6 functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 2;     // Configure GPIO1 as CAP6
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 1;    // Configure GPIO49 as CAP6

// Configure GPIO MUX TRIP Inputs
//    GpioTripRegs.GPTRIP12SEL.bit.GPTRIP12SEL = 1;    // Configure GPIO1 as
// CAP1
    GpioTripRegs.GPTRIP12SEL.bit.GPTRIP12SEL = 49;   // Configure GPIO49 as CAP1

    EDIS;
}




