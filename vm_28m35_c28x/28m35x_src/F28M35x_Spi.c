//###########################################################################
// FILE:   F28M35x_Spi.c
// TITLE:  F28M35x SPI Initialization & Support Functions.
//###########################################################################
// $TI Release: F28M35x Support Library v220 $
// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $
// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28M35x_Device.h"     // F28M35x Headerfile Include File
#include "F28M35x_Examples.h"   // F28M35x Examples Include File

// Calculate BRR: 7-bit baud rate register value
// SPI CLK freq = 500 kHz
// LSPCLK freq  = CPU freq / 4  (by default)
// BRR          = (LSPCLK freq / SPI CLK freq) - 1
#if CPU_FRQ_150MHZ
#define SPI_BRR        ((150E6 / 4) / 500E3) - 1
#endif

#if CPU_FRQ_100MHZ
#define SPI_BRR        ((100E6 / 4) / 500E3) - 1
#endif

#if CPU_FRQ_75MHZ
#define SPI_BRR        ((75E6 / 4) / 500E3) - 1
#endif

#if CPU_FRQ_60MHZ
#define SPI_BRR        ((60E6 / 4) / 500E3) - 1
#endif

//---------------------------------------------------------------------------
// InitSPI:
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
void InitSpi(void)
{
    // Initialize SPI-A

    // Set reset low before configuration changes
    // Clock polarity (0 == rising, 1 == falling)
    // 16-bit character
    // Enable loop-back
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
    SpiaRegs.SPICCR.bit.SPICHAR = (16-1);
    SpiaRegs.SPICCR.bit.SPILBK = 1;

    // Enable master (0 == slave, 1 == master)
    // Enable transmission (Talk)
    // Clock phase (0 == normal, 1 == delayed)
    // SPI interrupts are disabled
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
    SpiaRegs.SPICTL.bit.TALK = 1;
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;

    // Set the baud rate
    SpiaRegs.SPIBRR = SPI_BRR;

    // Set FREE bit
    // Halting on a breakpoint will not halt the SPI
    SpiaRegs.SPIPRI.bit.FREE = 1;

    // Release the SPI from reset
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;
}

//---------------------------------------------------------------------------
// Example: InitSpiGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SPI pins
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
// Caution:
// For each SPI peripheral
// Only one GPIO pin should be enabled for SPISOMO operation.
// Only one GPIO pin should be enabled for SPISOMI operation.
// Only one GPIO pin should be enabled for SPICLKA operation.
// Only one GPIO pin should be enabled for SPISTEA operation.
// Comment out other unwanted lines.

void InitSpiGpio()
{

    InitSpiaGpio();
}

void InitSpiaGpio()
{

    EALLOW;

/* Enable internal pull-up for the selected pins */

// Pull-up enable should be set in the
// GPIO_O_PUR register in the M3 code.

/* Set qualification for selected pins to asynch only */

// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

//    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3; // Asynch input GPIO16 (SPISIMOA)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input GPIO17 (SPISOMIA)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO18 (SPICLKA)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO19 (SPISTEA)

/* Configure SPI-A pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

//    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1; // Configure GPIO54 as SPISIMOA
//    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; // Configure GPIO55 as SPISOMIA
//    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
//    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA

    EDIS;
}




