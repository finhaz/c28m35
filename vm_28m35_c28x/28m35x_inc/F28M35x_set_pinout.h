//###########################################################################
// FILE:   F28M35x_set_pinout.h
// TITLE:  Defines for board specific GPIO setup
//###########################################################################
// $TI Release: F28M35x Support Library v220 $
// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $
// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F28M35x_SET_PINOUT_H
#define F28M35x_SET_PINOUT_H

#ifdef __cplusplus
extern "C" {
#endif

#define LED_0_DIR_REG GpioG1CtrlRegs.GPCDIR.bit.GPIO70
#define LED_0_DAT_REG GpioG1DataRegs.GPCDAT.bit.GPIO70    

#define LED_1_DIR_REG GpioG1CtrlRegs.GPCDIR.bit.GPIO71
#define LED_1_DAT_REG GpioG1DataRegs.GPCDAT.bit.GPIO71    

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F28M35x_DMA_DEFINES_H




