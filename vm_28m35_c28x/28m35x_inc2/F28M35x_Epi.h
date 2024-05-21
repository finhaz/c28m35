//###########################################################################
// FILE:   F28M35x_Epi.h
// TITLE:  F28M35x Device EPI Register Definitions.
//###########################################################################
// $TI Release: F28M35x Support Library v220 $
// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $
// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F28M35x_EPI_H
#define F28M35x_EPI_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// EPI Individual Register Bit Definitions:

struct CFG_BITS {
        Uint32 KEY : 28;                // This field should have value of
                                        //  0x9EDCB4A
        Uint32 rsvd1 : 3;
        Uint32 GRAB : 1;                // Grabs access for Control system
};

union CEPIRTWCFG_REG {
        Uint32 all;
        struct CFG_BITS bit;
};

union CEPIRTWCNT_REG {
        Uint32 all;
};

union CEPIRTWPRD_REG {
        Uint32 all;
};

struct STATUS_BITS {
        Uint32 rsvd1 : 28;
        Uint32 MEMPROTERR : 2;          // status for Memory Protection
        Uint32 RTWTIMEOUT : 2;          // status for RTW time out
};

union CEPISTATUS_REG {
        Uint32 all;
        struct STATUS_BITS bit;
};

struct EPI_REGS {
        union CEPIRTWCFG_REG CEPIRTWCFG;            // Control Reg
        union CEPIRTWCNT_REG CEPIRTWCNT;            // Control Reg
        union CEPIRTWPRD_REG CEPIRTWPRD;            // COntrol Reg
        Uint32 rsvd1;                               // Reserved
        Uint32 rsvd2;                               // Reserved
        union CEPISTATUS_REG CEPISTATUS;            // Control Reg
};

//---------------------------------------------------------------------------
// Epi External References & Function Declarations:
extern volatile struct EPI_REGS EpiRegs;

#ifdef __cplusplus
}
#endif  /* extern "C" */


#endif  // end of F28M35x_EPI_H definition



