//###########################################################################
// FILE:    F28M35x_Comp.c
// TITLE:   F28M35x Comparator Initialization & Support Functions.
//###########################################################################
// $TI Release: F28M35x Support Library v220 $
// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $
// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28M35x_Device.h"     // F28M35x Headerfile Include File
#include "F28M35x_Examples.h"   // F28M35x Examples Include File

//---------------------------------------------------------------------------
// InitComp:
//---------------------------------------------------------------------------
// This function initializes the Comp to a known state.
void InitComp(void)
{
    // Initialize Comp:

    //tbd...
}

//---------------------------------------------------------------------------
// Example: InitCompGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Comp pins
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.

void InitCompGpio()
{
    InitComp1Gpio();
    InitComp2Gpio();
    InitComp3Gpio();
    InitComp4Gpio();
    InitComp5Gpio();
    InitComp6Gpio();
}

void InitComp1Gpio()
{
    EALLOW;

    GpioG2CtrlRegs.GPEPUD.bit.GPIO129 = 1;      // Disable pull-up for GPIO129
                                                // (CMP1OUT)

/* Configure Comp pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be Comp functional pins.

    GpioG2CtrlRegs.GPEMUX1.bit.GPIO129 = 3;     // Configure GPIO129 for CMP1OUT
                                                // operation

    GpioG2CtrlRegs.AIOMUX1.bit.AIO2 = 2;        // Configure AIO2 for CMP1A
                                                // (analog input) operation
    GpioG2CtrlRegs.AIOMUX1.bit.AIO10 = 2;       // Configure AIO10 for CMP1B
                                                // (analog input) operation

    EDIS;
}

void InitComp2Gpio()
{
    EALLOW;

    GpioG2CtrlRegs.GPEPUD.bit.GPIO131 = 1;      // Disable pull-up for GPIO131
                                                // (CMP2OUT)

/* Configure Comp pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be Comp functional pins.

    GpioG2CtrlRegs.GPEMUX1.bit.GPIO131 = 3;     // Configure GPIO131 for CMP2OUT
                                                // operation

    GpioG2CtrlRegs.AIOMUX1.bit.AIO4 = 2;        // Configure AIO4 for CMP2A
                                                // (analog input) operation
    GpioG2CtrlRegs.AIOMUX1.bit.AIO12 = 2;       // Configure AIO12 for CMP2B
                                                // (analog input) operation

    EDIS;
}

void InitComp3Gpio()
{
    EALLOW;

    GpioG2CtrlRegs.GPEPUD.bit.GPIO132 = 1;      // Disable pull-up for GPIO132
                                                // (CMP3OUT)

/* Configure Comp pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be Comp functional pins.

    GpioG2CtrlRegs.GPEMUX1.bit.GPIO132 = 3;     // Configure GPIO132 for CMP3OUT
                                                // operation

    GpioG2CtrlRegs.AIOMUX1.bit.AIO6 = 2;        // Configure AIO6 for CMP3A
                                                // (analog input) operation
    GpioG2CtrlRegs.AIOMUX1.bit.AIO14 = 2;       // Configure AIO14 for CMP3B
                                                // (analog input) operation

    EDIS;
}

void InitComp4Gpio()
{
    EALLOW;

    GpioG2CtrlRegs.GPEPUD.bit.GPIO133 = 1;      // Disable pull-up for GPIO133
                                                // (CMP4OUT)

/* Configure Comp pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be Comp functional pins.

    GpioG2CtrlRegs.GPEMUX1.bit.GPIO133 = 3;     // Configure GPIO133 for CMP4OUT
                                                // operation

    GpioG2CtrlRegs.AIOMUX2.bit.AIO18 = 2;       // Configure AIO18 for CMP4A
                                                // (analog input) operation
    GpioG2CtrlRegs.AIOMUX2.bit.AIO26 = 2;       // Configure AIO26 for CMP4B
                                                // (analog input) operation

    EDIS;
}

void InitComp5Gpio()
{
    EALLOW;

    GpioG2CtrlRegs.GPEPUD.bit.GPIO135 = 1;      // Disable pull-up for GPIO135
                                                // (CMP5OUT)

/* Configure Comp pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be Comp functional pins.

    GpioG2CtrlRegs.GPEMUX1.bit.GPIO135 = 3;     // Configure GPIO135 for CMP5OUT
                                                // operation

    GpioG2CtrlRegs.AIOMUX2.bit.AIO20 = 2;       // Configure AIO20 for CMP5A
                                                // (analog input) operation
    GpioG2CtrlRegs.AIOMUX2.bit.AIO28 = 2;       // Configure AIO28 for CMP5B
                                                // (analog input) operation

    EDIS;
}

void InitComp6Gpio()
{
    EALLOW;

    GpioG2CtrlRegs.GPEPUD.bit.GPIO130 = 1;      // Disable pull-up for GPIO130
                                                // (CMP6OUT)

/* Configure Comp pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be Comp functional pins.

    GpioG2CtrlRegs.GPEMUX1.bit.GPIO130 = 3;     // Configure GPIO130 for CMP6OUT
                                                // operation

    GpioG2CtrlRegs.AIOMUX2.bit.AIO22 = 2;       // Configure AIO22 for CMP6A
                                                // (analog input) operation
    GpioG2CtrlRegs.AIOMUX2.bit.AIO30 = 2;       // Configure AIO30 for CMP6B
                                                // (analog input) operation

    EDIS;
}




