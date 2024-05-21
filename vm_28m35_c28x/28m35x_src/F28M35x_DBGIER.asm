;//###########################################################################
;// FILE:  F28M35x_DBGIER.asm
;// TITLE: Set the DBGIER register
;// DESCRIPTION:
;//  
;//  Function to set the DBGIER register (for realtime emulation).
;//  Function Prototype: void SetDBGIER(Uint16)
;//  Useage: SetDBGIER(value);
;//  Input Parameters: Uint16 value = value to put in DBGIER register. 
;//  Return Value: none          
;//###########################################################################
;// $TI Release: F28M35x Support Library v220 $ 
;// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $ 
;// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
;//             http://www.ti.com/ ALL RIGHTS RESERVED $
;//###########################################################################
        .global _SetDBGIER
        .text
        
_SetDBGIER:
        MOV     *SP++,AL
        POP     DBGIER
        LRETR
        



