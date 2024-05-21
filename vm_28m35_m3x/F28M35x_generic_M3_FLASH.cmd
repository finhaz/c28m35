/*
//###########################################################################
// FILE:    F28M35x_generic_M3_FLASH.cmd
// TITLE:   Linker Command File for F28M35x examples that run out of FLASH
//###########################################################################
// $TI Release: F28M35x Support Library v220 $
// $Release Date: Tue Sep 26 15:35:11 CDT 2017 $
// $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
*/

--retain=g_pfnVectors

/* The following command line options are set as part of the CCS project.    */
/* If you are building using the command line, or for some reason want to    */
/* define them here, you can uncomment and modify these lines as needed.     */
/* If you are using CCS for building, it is probably better to make any such */
/* modifications in your CCS project and leave this file alone.              */
/*                                                                           */
/* --heap_size=0                                                             */
/* --stack_size=256                                                          */
/* --library=rtsv7M3_T_le_eabi.lib                                           */


/* The following options allow the user to program Z1 and Z2 DCSM security   */
/* values, include CSM PSWD, ECSL PSWD, GRABSECT, GRABRAM, and FLASH EXEONLY */
/* The driverlib/dcsm_z1_secvalues.s and driverlib/dcsm_z2_secvalues.s files */
/* must be included in the Flash project for the below 2 lines to take       */
/* effect.                                                                   */
--retain=dcsm_z1_secvalues.obj(.z1secvalues,.z1_csm_rsvd)
--retain=dcsm_z2_secvalues.obj(.z2secvalues,.z2_csm_rsvd)

/* System memory map */

MEMORY
{
/* FLASH */
    CSM_ECSL_Z1     : origin = 0x00200000, length = 0x0024
    CSM_RSVD_Z1     : origin = 0x00200024, length = 0x000C
    RESETISR (RX)   : origin = 0x00200030, length = 0x0008   /* Reset ISR is mapped to boot to Flash location */
    INTVECS (RX)    : origin = 0x00200200, length = 0x01B0
    FLASH1 (RX)     : origin = 0x00200400, length = 0x1FC00
    FLASH2 (RX)     : origin = 0x00260000, length = 0x1FF00
    CSM_RSVD_Z2     : origin = 0x0027FF00, length = 0x00DC
    CSM_ECSL_Z2     : origin = 0x0027FFDC, length = 0x0024
/* RAM */
    C0 (RWX)        : origin = 0x20000000, length = 0x2000
    C1 (RWX)        : origin = 0x20002000, length = 0x2000
    BOOT_RSVD (RX)  : origin = 0x20004000, length = 0x0900
    C2 (RWX)        : origin = 0x20004900, length = 0x1700
    C3 (RWX)        : origin = 0x20006000, length = 0x2000
/* Message RAM */
    CTOMRAM (RX)    : origin = 0x2007F000, length = 0x0800
    MTOCRAM (RWX)   : origin = 0x2007F800, length = 0x0800
	
	OTPSECLOCK       : origin = 0x00680800, length = 0x0004
    OTP_Reserved1    : origin = 0x00680804, length = 0x0004
    OTP_Reserved2    : origin = 0x00680808, length = 0x0004
    OTP_Z2_FLASH_START_ADDR             : origin = 0x0068080C, length = 0x0004
    OTP_EMACID       : origin = 0x00680810, length = 0x0008
    OTP_Reserved3    : origin = 0x00680818, length = 0x0004
    CUSTOMER_OTP_MAIN_OSC_CLK_FREQ      : origin = 0x0068081C, length = 0x0004
    OTP_Reserved4    : origin = 0x00680820, length = 0x0004
    OTP_BOOT_MODE_GPIO_CONFIGURE        : origin = 0x00680824, length = 0x0004
    OTP_Reserved5    : origin = 0x00680828, length = 0x0004
    OTP_ENTRY_POINT  : origin = 0x0068082C, length = 0x0004
    OTP_Reserved6    : origin = 0x00680830, length = 0x0010
}

/* Section allocation in memory */

SECTIONS
{
    .intvecs:   > INTVECS, ALIGN(8)
    .resetisr:  > RESETISR, ALIGN(8)
    .text   :   >> FLASH1 | FLASH2, crc_table(AppCrc, algorithm=CRC32_PRIME), ALIGN(8)
    .const  :   >> FLASH1 | FLASH2, crc_table(AppCrc, algorithm=CRC32_PRIME), ALIGN(8)
    .cinit  :   >  FLASH1 | FLASH2, crc_table(AppCrc, algorithm=CRC32_PRIME), ALIGN(8)
    .pinit  :   >> FLASH1 | FLASH2, crc_table(AppCrc, algorithm=CRC32_PRIME), ALIGN(8)

    .vtable :   >  C0 | C1 | C2 | C3
    .data   :   >  C2 | C3
    .bss    :   >> C2 | C3
    .sysmem :   >  C0 | C1 | C2 | C3
    .stack  :   >  C2 | C3
    
    .TI.crctab : > FLASH2, ALIGN(8)
    
    .z1secvalues  :   >  CSM_ECSL_Z1, ALIGN(8)
    .z1_csm_rsvd  :   >  CSM_RSVD_Z1
    .z2secvalues  :   >  CSM_ECSL_Z2
    .z2_csm_rsvd  :   >  CSM_RSVD_Z2, ALIGN(8)
                     
#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} LOAD = FLASH1 | FLASH2,
                           RUN = C0 | C1 | C2 | C3,
                           LOAD_START(RamfuncsLoadStart),
                           LOAD_SIZE(RamfuncsLoadSize),
                           LOAD_END(RamfuncsLoadEnd),
                           RUN_START(RamfuncsRunStart),
                           RUN_SIZE(RamfuncsRunSize),
                           RUN_END(RamfuncsRunEnd),
                           crc_table(AppCrc, algorithm=CRC32_PRIME),
                           PAGE = 0, ALIGN(8)
   #else
     ramfuncs            : LOAD = FLASH1 | FLASH2,
                           RUN = C0 | C1 | C2 | C3,
                           LOAD_START(RamfuncsLoadStart),
                           LOAD_SIZE(RamfuncsLoadSize),
                           LOAD_END(RamfuncsLoadEnd),
                           RUN_START(RamfuncsRunStart),
                           RUN_SIZE(RamfuncsRunSize),
                           RUN_END(RamfuncsRunEnd),
                           crc_table(AppCrc, algorithm=CRC32_PRIME),
                           PAGE = 0, ALIGN(8)   
   #endif
#endif
    
    GROUP : > MTOCRAM
    {
        PUTBUFFER  
        PUTWRITEIDX
        GETREADIDX  
    }

     GROUP : > CTOMRAM 
    {
        GETBUFFER : TYPE = DSECT
        GETWRITEIDX : TYPE = DSECT
        PUTREADIDX : TYPE = DSECT
    }    
}






