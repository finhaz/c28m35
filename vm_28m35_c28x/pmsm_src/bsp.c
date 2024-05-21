/*
 *     bsp.c
 *
 *     ������ص�����������ʼ�����ú����ڴ��ļ���д
 *
 *
 */
#include "F28M35x_Device.h"     // F28M35x Headerfile Include File
#include "F28M35x_Examples.h"   // F28M35x Examples Include File


void InitBoardGpio(void)
{

    // Initialize GPIOs
    //
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
    GpioDataRegs.GPADAT.bit.GPIO14 = 0;

    EDIS;

    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();

    //InitSciGpio();

}


void ConfigureADC(void)
{

	InitAdc1();  // For this example, init the ADC

    // Configure ADC
    EALLOW;

    Adc1Regs.ADCCTL2.bit.ADCNONOVERLAP = 1;     // Set ADC to non-overlap mode

    Adc1Regs.ADCCTL1.bit.INTPULSEPOS   = 1;     // EOC trips after conversion result is latched
    Adc1Regs.INTSEL1N2.bit.INT1E       = 1;     // Enabled ADCINT1
    Adc1Regs.INTSEL1N2.bit.INT1CONT    = 0;     // Disable ADCINT1 Continuous mode
    Adc1Regs.INTSEL1N2.bit.INT1SEL     = 1;     // setup EOC1 to trigger ADCINT1

    // Select ADC input channels
    Adc1Regs.ADCSOC0CTL.bit.CHSEL      = 0;     // set SOC0 channel select to ADC1A0
    Adc1Regs.ADCSOC1CTL.bit.CHSEL      = 2;     // set SOC1 channel select to ADC1A2
    Adc1Regs.ADCSOC2CTL.bit.CHSEL      = 3;     // set SOC2 channel select to ADC1A3
    Adc1Regs.ADCSOC3CTL.bit.CHSEL      = 4;     // set SOC3 channel select to ADC1A4
    Adc1Regs.ADCSOC4CTL.bit.CHSEL      = 6;     // set SOC4 channel select to ADC1A6
    Adc1Regs.ADCSOC5CTL.bit.CHSEL      = 7;     // set SOC5 channel select to ADC1A7
    Adc1Regs.ADCSOC6CTL.bit.CHSEL      = 8;     // set SOC6 channel select to ADC1B0
    Adc1Regs.ADCSOC7CTL.bit.CHSEL      = 11;    // set SOC7 channel select to ADC1B3
    Adc1Regs.ADCSOC8CTL.bit.CHSEL      = 12;    // set SOC8 channel select to ADC1B4
    Adc1Regs.ADCSOC9CTL.bit.CHSEL      = 15;    // set SOC9 channel select to ADC1B7


    // Selecing triggers for SOCs
    AnalogSysctrlRegs.TRIG5SEL.all     = 5;     // Assigning EPWM1SOCA to TRIGGER 5 of analog subsystem
    //AnalogSysctrlRegs.TRIG6SEL.all     = 6;     // Assigning EPWM1SOCB to TRIGGER 6 of analog subsystem

    //Assign ADCTRIG5 �C ADC Trigger 5to SOC0 TRIGSEL

    Adc1Regs.ADCSOC0CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC0 TRIGSEL
    Adc1Regs.ADCSOC1CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC1 TRIGSEL
    Adc1Regs.ADCSOC2CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC2 TRIGSEL
    Adc1Regs.ADCSOC3CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC3 TRIGSEL
    Adc1Regs.ADCSOC4CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC4 TRIGSEL
    Adc1Regs.ADCSOC5CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC5 TRIGSEL
    Adc1Regs.ADCSOC6CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC6 TRIGSEL
    Adc1Regs.ADCSOC7CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC7 TRIGSEL
    Adc1Regs.ADCSOC8CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC8 TRIGSEL
    Adc1Regs.ADCSOC9CTL.bit.TRIGSEL    = 9;     // Assign EPWM1SOCA to SOC9 TRIGSEL



    // Set S/H window of 7 ADC clock cycles
    Adc1Regs.ADCSOC0CTL.bit.ACQPS      = 6;     // S/H = ACQPS + 1
    Adc1Regs.ADCSOC1CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC2CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC3CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC4CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC5CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC6CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC7CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC8CTL.bit.ACQPS      = 6;
    Adc1Regs.ADCSOC9CTL.bit.ACQPS      = 6;

    EDIS;




}


void ConfigureEPwm(void)
{
    //EPWM1-3 DRIVE

    //Note that the default/2 divider for ePWMs and EMIFs
    //EPWMCLK=SYSCLKOUT=150MHZ
    //ePWMģ��ʱ������  // TBCLK = EPWMCLK/(HSPCLKDIV*CLKDIV)
    //PWM����=15000��TBCLK����100us
//    Uint16 Prd=7500;
    //5K
    Uint16 Prd=15000;
    //Uint16 Prd_da=7500;
    // Initialize EPwm1/2/3/4/5/6/7
    //�������ó���------------->>>>>>>>>>>>>
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    //EPWM Moudle 1 ����
    //TB
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm1Regs.TBCTL.bit.CLKDIV=0;
    EPwm1Regs.TBPRD=Prd;
    EPwm1Regs.TBPHS.half.TBPHS=0;//����λ�Ĵ���ֵ����
    EPwm1Regs.TBCTR=0x0000;
    EPwm1Regs.TBCTL.bit.CTRMODE=TB_COUNT_UPDOWN;//����ģʽ
    EPwm1Regs.TBCTL.bit.PHSEN=TB_DISABLE;//��ֹ��λװ��
    EPwm1Regs.TBCTL.bit.PRDLD=TB_SHADOW;//��CTR=0ʱ����ӳ��Ĵ����е�����װ�ص���ǰ�Ĵ���
    EPwm1Regs.TBCTL.bit.SYNCOSEL=TB_CTR_ZERO;//CTR=0ʱ����ͬ���ź�
    //CC
    EPwm1Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;//CMPA�Ĵ��������� ӳ��ģʽ
    EPwm1Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;//CMPB�Ĵ��������� ӳ��ģʽ
    EPwm1Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    EPwm1Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    //AQ
    EPwm1Regs.AQCTLA.bit.CAU=AQ_SET;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵ���������ʹEPWM1AΪ�ߵ�ƽ
    EPwm1Regs.AQCTLA.bit.CAD=AQ_CLEAR;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵݼ�������ʹEPWM1AΪ�͵�ƽ

     //DB
    EPwm1Regs.AQCSFRC.all = 0x0005 ;//���ǿ��PWM���Ϊ��,2017/12/26
    //EPwm1Regs.DBCTL.bit.OUT_MODE=DB_FULL_ENABLE;//ʹ�������ؼ��½�����ʱ�ź�
    EPwm1Regs.DBCTL.bit.IN_MODE=DBA_ALL;//Ĭ��EPWM1A��Ϊ�����ؼ��½�����ʱ���ź�Դ
    EPwm1Regs.DBCTL.bit.POLSEL=DB_ACTV_HIC;//AHC\EPWM1B��ת����
    EPwm1Regs.DBFED=200;//�½�����ʱFED=200��TBCLK
    EPwm1Regs.DBRED=200;//��������ʱRED=200��TBCLK

    //�¼���������ADC
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;         // ʹ��SOCAת��������
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;//������Ϊ0ʱ����ת��
    EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST; // Generate pulse on 1st event

    //EPwm1Regs.CMPA.bit.CMPA  = 100;   // Set compare A value
    //EPwm1Regs.TBCTL.bit.CTRMODE=0;

    //EPWM Moudle 2 ����
    //TB
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm2Regs.TBCTL.bit.CLKDIV=0;
    EPwm2Regs.TBPRD=Prd;
    EPwm2Regs.TBPHS.half.TBPHS=0;//����λ�Ĵ���ֵ����
    EPwm2Regs.TBCTR=0x0000;
    EPwm2Regs.TBCTL.bit.CTRMODE=TB_COUNT_UPDOWN;//����ģʽ
    EPwm2Regs.TBCTL.bit.PHSEN=TB_DISABLE;//��ֹ��λװ��
    EPwm2Regs.TBCTL.bit.PRDLD=TB_SHADOW;//��CTR=0ʱ����ӳ��Ĵ����е�����װ�ص���ǰ�Ĵ���
    EPwm2Regs.TBCTL.bit.SYNCOSEL=TB_CTR_ZERO;//CTR=0ʱ����ͬ���ź�
    //CC
    EPwm2Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;//CMPA�Ĵ��������� ӳ��ģʽ
    EPwm2Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;//CMPB�Ĵ��������� ӳ��ģʽ
    EPwm2Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    EPwm2Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    //AQ
    EPwm2Regs.AQCTLA.bit.CAU=AQ_SET;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵ���������ʹEPWM1AΪ�ߵ�ƽ
    EPwm2Regs.AQCTLA.bit.CAD=AQ_CLEAR;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵݼ�������ʹEPWM1AΪ�͵�ƽ

     //DB
    EPwm2Regs.AQCSFRC.all = 0x0005 ;//���ǿ��PWM���Ϊ��,2017/12/26
    //EPwm1Regs.DBCTL.bit.OUT_MODE=DB_FULL_ENABLE;//ʹ�������ؼ��½�����ʱ�ź�
    EPwm2Regs.DBCTL.bit.IN_MODE=DBA_ALL;//Ĭ��EPWM1A��Ϊ�����ؼ��½�����ʱ���ź�Դ
    EPwm2Regs.DBCTL.bit.POLSEL=DB_ACTV_HIC;//AHC\EPWM1B��ת����
    EPwm2Regs.DBFED=200;//�½�����ʱFED=200��TBCLK
    EPwm2Regs.DBRED=200;//��������ʱRED=200��TBCLK

    //EPWM Moudle 3 ����
    //TB
    EPwm3Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm3Regs.TBCTL.bit.CLKDIV=0;
    EPwm3Regs.TBPRD=Prd;
    EPwm3Regs.TBPHS.half.TBPHS=0;//����λ�Ĵ���ֵ����
    EPwm3Regs.TBCTR=0x0000;
    EPwm3Regs.TBCTL.bit.CTRMODE=TB_COUNT_UPDOWN;//����ģʽ
    EPwm3Regs.TBCTL.bit.PHSEN=TB_DISABLE;//��ֹ��λװ��
    EPwm3Regs.TBCTL.bit.PRDLD=TB_SHADOW;//��CTR=0ʱ����ӳ��Ĵ����е�����װ�ص���ǰ�Ĵ���
    EPwm3Regs.TBCTL.bit.SYNCOSEL=TB_CTR_ZERO;//CTR=0ʱ����ͬ���ź�
    //CC
    EPwm3Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;//CMPA�Ĵ��������� ӳ��ģʽ
    EPwm3Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;//CMPB�Ĵ��������� ӳ��ģʽ
    EPwm3Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    EPwm3Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    //AQ
    EPwm3Regs.AQCTLA.bit.CAU=AQ_SET;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵ���������ʹEPWMAΪ�ߵ�ƽ
    EPwm3Regs.AQCTLA.bit.CAD=AQ_CLEAR;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵݼ�������ʹEPWMAΪ�͵�ƽ

     //DB
    EPwm3Regs.AQCSFRC.all = 0x0005 ;//���ǿ��PWM���Ϊ��,2017/12/26
    //EPwm3Regs.DBCTL.bit.OUT_MODE=DB_FULL_ENABLE;//ʹ�������ؼ��½�����ʱ�ź�
    EPwm3Regs.DBCTL.bit.IN_MODE=DBA_ALL;//Ĭ��EPWMA��Ϊ�����ؼ��½�����ʱ���ź�Դ
    EPwm3Regs.DBCTL.bit.POLSEL=DB_ACTV_HIC;//AHC\EPWM1B��ת����
    EPwm3Regs.DBFED=200;//�½�����ʱFED=200��TBCLK
    EPwm3Regs.DBRED=200;//��������ʱRED=200��TBCLK


    //TBD
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}



//#define CPU_FREQ           150E6
//#define LSPCLK_FREQ     CPU_FREQ/4
//#define SCI_FREQ        9600
//#define SCI_PRD         ((LSPCLK_FREQ/(SCI_FREQ*8))-1)
//BRR =SCI_PRD;

//
//void ConfigureSci(void)
//{
//    EALLOW;
//    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK= 1;
//    //SciaRegs.SCIFFTX.all=0xE040;
//    //SciaRegs.SCIFFRX.all=0x2044;
//    //SciaRegs.SCIFFCT.all=0x0;
//
//    SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
//                                   // No parity,8 char bits,
//                                   // async mode, idle-line protocol
//    SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
//                                   // Disable RX ERR, SLEEP, TXWAKE
//    SciaRegs.SCICTL2.all =0x0003;
//    SciaRegs.SCICTL2.bit.TXINTENA =1;
//    SciaRegs.SCICTL2.bit.RXBKINTENA =1;
//
//    SciaRegs.SCIHBAUD=0x0001;  // 9600 baud @LSPCLK = 37.5MHz
//                                         //(150 MHz SYSCLK).
//    SciaRegs.SCILBAUD =0x00E7;
//
//    SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
//    EDIS;
//
//}

//�ⲿ�жϣ����й�������
void ConfigureXint(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO25=0;
    GpioCtrlRegs.GPADIR.bit.GPIO25=0;
    //�����½��ش���XINT����Ҫ����������������·������������Բ����ڲ�����
    //GpioCtrlRegs.GPAPUD.bit.GPIO25=0;
    GpioTripRegs.GPTRIP4SEL.bit.GPTRIP4SEL=25;//XINT1=gpio25
    EDIS;
// Configure XINT1 Falling edge interrupt
    XIntruptRegs.XINT1CR.bit.POLARITY=0;
// Enable XINT1
    XIntruptRegs.XINT1CR.bit.ENABLE=1;

}


