//###########################################################################
// FILE:   blinky.c
// TITLE:  blinky example.
//###########################################################################
// $TI Release: F28M35x Support Library v220 $
// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $
// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_nvic.h"
#include "hw_gpio.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "hw_ram.h"
#include "hw_ipc.h"
#include "debug.h"
#include "interrupt.h"
#include "sysctl.h"
#include "gpio.h"
#include "uart.h"
#include "flash.h"
#include "cpu.h"

#include "ram.h"
#include <string.h>
#include "message.h"
#include "global_var.h"

//*****************************************************************************
//
//! \addtogroup master_example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED3.
//
//*****************************************************************************

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern unsigned long RamfuncsLoadStart;
extern unsigned long RamfuncsRunStart;
extern unsigned long RamfuncsLoadSize;
#endif

//*****************************************************************************
// The error routine that is called if the driver library encounters an error.
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}

#endif



//*****************************************************************************
//
// 分配M3与28x内核外设引脚
//*****************************************************************************
int
main(void)
{

    // Define Local  Variables
    unsigned short counter;
    unsigned short *pusMBufferPt;
    unsigned short *pusCBufferPt;
    unsigned long *pulMsgRam;

    // Disable Protection
    HWREG(SYSCTL_MWRALLOW) =  0xA5A5A5A5;

    // Sets up PLL, M3 running at 75MHz and C28 running at 150MHz
    SysCtlClockConfigSet(SYSCTL_USE_PLL | (SYSCTL_SPLLIMULT_M & 0xF) |
                         SYSCTL_SYSDIV_1 | SYSCTL_M3SSDIV_2 |
                         SYSCTL_XCLKDIV_4);

    // Initialize M3toC28 message RAM and Sx SARAM and wait until initialized
    RAMMReqSharedMemAccess(S0_ACCESS, SX_M3MASTER);
    //RAMMReqSharedMemAccess(S1_ACCESS, SX_M3MASTER);

    //
    // Initialize Sx RAM and MtoC MSG RAM Used by Example
    //
    HWREG(RAM_CONFIG_BASE + RAM_O_MSXRTESTINIT1) |= 0x1;
    while((HWREG(RAM_CONFIG_BASE + RAM_O_MSXRINITDONE1)&0x1) != 0x1)
    {
    }

    HWREG(RAM_CONFIG_BASE + RAM_O_MTOCCRTESTINIT1) |= 0x1;
    while((HWREG(RAM_CONFIG_BASE + RAM_O_MTOCRINITDONE)&0x1) != 0x1)
    {
    }

    //  Disable writes to protected registers.
    HWREG(SYSCTL_MWRALLOW) = 0;

    //  Register M3 interrupt handlers
    //IntRegister(INT_CTOMPIC1, CtoMIPC1IntHandler);
    IntRegister(INT_CTOMPIC2, CtoMIPC2IntHandler);


#ifdef _FLASH
// Copy time critical code and Flash setup code to RAM
// This includes the following functions:  InitFlash();
// The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
// symbols are created by the linker. Refer to the device .cmd file.
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
    FlashInit();
#endif

    // Initialize IPC Controllers
    //IPCMInitialize (&g_sIpcController1, IPC_INT1, IPC_INT1);
    IPCMInitialize (&g_sIpcController2, IPC_INT2, IPC_INT2);

    //  Enable processor interrupts.
    IntMasterEnable();

    //  Enable the IPC interrupts.
    //IntEnable(INT_CTOMPIC1);
    IntEnable(INT_CTOMPIC2);

    //pulMsgRam = (void *)M3_MTOC_PASSMSG;



    pulMsgRam = (void *)M3_MTOC_PASSMSG;
    pulMsgRam[2]= (unsigned long)&gusMBuffer[0];


    // Initialize local variables
    pulMsgRam = (void *)M3_CTOM_PASSMSG;

    pusMBufferPt = (void *)M3_S0SARAM_START;
    pusCBufferPt = (void *)(M3_S0SARAM_START + usMBuffer_SIZE);

    ErrorCount = 0;

    for (counter = 0; counter < usMBuffer_SIZE; counter++)
    {
        usMBuffer[counter] = 0;
    }
    for (counter = 0; counter < usMBuffer_SIZE; counter++)
    {
        gusMBuffer[counter] = 0;
    }


    // Spin here until C28 has written variable addresses to pulMsgRam
    while ((HWREG(MTOCIPC_BASE + IPC_O_CTOMIPCSTS) & IPC_CTOMIPCSTS_IPC17) !=
           IPC_CTOMIPCSTS_IPC17)
    {
    }
    HWREG(MTOCIPC_BASE + IPC_O_CTOMIPCACK) = IPC_CTOMIPCACK_IPC17;



    //IPC正常通讯后，才允许C28X获得外设控制


    // Enable clock supply for the peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Give C28 control of GPIO
    //EPWM control
    GPIOPinConfigureCoreSelect(GPIO_PORTA_BASE, GPIO_PIN_0, GPIO_PIN_C_CORE_SELECT);
    GPIOPinConfigureCoreSelect(GPIO_PORTA_BASE, GPIO_PIN_1, GPIO_PIN_C_CORE_SELECT);
    GPIOPinConfigureCoreSelect(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_C_CORE_SELECT);
    GPIOPinConfigureCoreSelect(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_C_CORE_SELECT);
    GPIOPinConfigureCoreSelect(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_C_CORE_SELECT);
    GPIOPinConfigureCoreSelect(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_C_CORE_SELECT);

    //Led show
    GPIOPinConfigureCoreSelect(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_PIN_C_CORE_SELECT);

    // Disable clock supply for the watchdog modules
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG1);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG0);

    // Enable processor interrupts.
    IntMasterEnable();


    // Set GPIO D2 and D3 as UART pins.
    GPIOPinConfigure(GPIO_PD2_U1RX);
    GPIOPinConfigure(GPIO_PD3_U1TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3);

    // Configure the UART for 9600, 8-N-1 operation.
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(SYSTEM_CLOCK_SPEED), 9600,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    // Enable the UART interrupt.
    IntRegister(INT_UART1, UARTIntHandler);
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);



    // Loop forever while the timers run.
    while(1)
    {
        if(IPC_get_flag)
        {
            IPCdata_tran();
            IPC_get_flag=0;
        }
        //数据通讯与处理
         Checkdata();
         SciSend();

         if(IPC_send_flag==1)
         {
             // Data Block Writes
             // Request Memory Access to S0 SARAM for M3
             RAMMReqSharedMemAccess (S0_ACCESS, SX_M3MASTER);
             while ((HWREG(RAM_CONFIG_BASE + RAM_O_MSXMSEL) & S0_ACCESS) != 0)
             {
             }
             // Write a block of data from M3 to S0 shared RAM which is then written to a
             // C28 address.
             for (counter = 0; counter < usMBuffer_SIZE; counter++)
             {
                 pusMBufferPt[counter] = usMBuffer[counter];
             }

             IPCMtoCBlockWrite(&g_sIpcController2, pulMsgRam[2],
                               (unsigned long)pusMBufferPt, usMBuffer_SIZE, IPC_LENGTH_16_BITS,
                               ENABLE_BLOCKING);

             // Give Memory Access to S0 SARAM to C28
             RAMMReqSharedMemAccess (S0_ACCESS, SX_C28MASTER);

             while ((HWREG(RAM_CONFIG_BASE + RAM_O_MSXMSEL) & S0_ACCESS) != S0_ACCESS)
             {
             }

             // Read data back from C28.
             IPCMtoCBlockRead(&g_sIpcController2, pulMsgRam[2],
                              (unsigned long)pusCBufferPt, usMBuffer_SIZE, ENABLE_BLOCKING,
                              IPC_FLAG17);

             // Wait until read data is ready (by checking IPC Response Flag is cleared).
             // Then check for correct data.
             while (HWREG(MTOCIPC_BASE + IPC_O_MTOCIPCFLG) & IPC_MTOCIPCFLG_IPC17)
             {
             }

             for (counter = 0; counter <usMBuffer_SIZE; counter++)
             {
                 if (usMBuffer[counter] != pusCBufferPt[counter])
                 {
                     ErrorFlag = 1;
                 }
                 else
                 {
                     ErrorFlag = 0;
                 }
             }

             if (ErrorFlag == 1)
             {
                 ErrorCount++;
             }

             IPC_send_flag=0;
         }

    }
}


//*****************************************************************************
// The UART interrupt handler.
//*****************************************************************************
void UARTIntHandler(void)
{
    unsigned long ulStatus;

    // Get the interrupt status.
    ulStatus = UARTIntStatus(UART1_BASE, true);


//    //get the char用串口助手给
//    u=UARTCharGet(UART1_BASE);

    SciRecieve();

    // Clear the asserted interrupts.
    UARTIntClear(UART1_BASE, ulStatus);

//    // Loop while there are characters in the receive FIFO.
//    while(UARTCharsAvail(UART1_BASE))
//    {
//        // Read the next character from the UART and write it back to the UART.
//        UARTCharPutNonBlocking(UART1_BASE,
//                               UARTCharGetNonBlocking(UART1_BASE));
//    }
}

//*****************************************************************************
// Send a string to the UART.
//*****************************************************************************
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount)
{
    // Loop while there are more characters to send.
    while(ulCount--)
    {
        // Write the next character to the UART.
        UARTCharPutNonBlocking(UART1_BASE, *pucBuffer++);
    }
}





////*****************************************************************************
//// CtoM IPC INT1 Interrupt Handler -
//// Handles writes into M3 addresses as a result of read commands to the C28.
////*****************************************************************************
//void
//CtoMIPC1IntHandler (void)
//{
//    tIpcMessage sMessage;
//
//    // Continue processing messages as long as MtoC GetBuffer1 is full
//    while (IpcGet(&g_sIpcController1, &sMessage,
//                  DISABLE_BLOCKING) != STATUS_FAIL)
//    {
//        switch (sMessage.ulcommand)
//        {
//        case IPC_DATA_WRITE:
//            IPCCtoMDataWrite(&sMessage);
//            break;
//        case IPC_DATA_READ:
//            IPCCtoMDataRead(&g_sIpcController1, &sMessage, ENABLE_BLOCKING);
//            break;
//        default:
//            ErrorFlag = 1;
//            break;
//        }
//    }
//
//    // Acknowledge IPC INT1 Flag
//    HWREG(MTOCIPC_BASE + IPC_O_CTOMIPCACK) |= IPC_CTOMIPCACK_IPC1;
//}

//*****************************************************************************
// CtoM IPC INT2 Interrupt Handler -
// Should never reach this ISR. This is an optional placeholder for
// g_sIpcController2.
//*****************************************************************************
void
CtoMIPC2IntHandler (void)
{
    // Should never reach here - Placeholder for Debug
    tIpcMessage sMessage;

    // Continue processing messages as long as CtoM GetBuffer2 is full
    while (IpcGet (&g_sIpcController2, &sMessage,
                   DISABLE_BLOCKING)!= STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
        case IPC_SET_BITS_PROTECTED:
            IPCCtoMSetBits_Protected(&sMessage);       // Processes
                                                       // IPCCtoMReqMemAccess()
                                                       // function
            break;
        case IPC_CLEAR_BITS_PROTECTED:
            IPCCtoMClearBits_Protected(&sMessage);     // Processes
                                                       // IPCCtoMReqMemAccess()
                                                       // function
            break;
        case IPC_BLOCK_WRITE:
            IPCCtoMBlockWrite(&sMessage);
            break;
        case IPC_BLOCK_READ:
            IPCCtoMBlockRead(&sMessage);
            break;
        default:
            ErrorFlag = 1;
            break;
        }
    }
    IPC_get_flag=1;
    // Acknowledge IPC INT2 Flag
    HWREG(MTOCIPC_BASE + IPC_O_CTOMIPCACK) |= IPC_CTOMIPCACK_IPC2;
}

void IPCdata_tran(void)
{
    int i=0;

    for(i=0;i<44;i++)
    {
        IPC_get.bit.MEM1=gusMBuffer[2*i];
        IPC_get.bit.MEM2=gusMBuffer[2*i+1];
        Paramet[i]=IPC_get.all;
    }

}
