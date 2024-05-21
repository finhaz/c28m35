/*
 *     main.c
 *
 *     Created on: 2019-8-7
 *     Author: naiyangui,fin,Summer��
 *     �˳���Ϊ�˲���PSO��ͨѶ
 *     ��xyy�ĳ�������������˶�ʱ����10���������Ĺ���
 *     ���ճ����������ж�PSO��Ӧ�ĳ���
 *     SCI���ֳ�������˼��Ż�
 *	     ��ֲ����28m35
 */

#include "DSP28x_Project.h"     // DSP28x Headerfile
//#include "F28M35x_Ipc_drivers.h"

//#ifdef _FLASH
//#pragma CODE_SECTION(adca1_interrupt_isr,"ramfuncs");//ָ��ĳ������ram������ramfuncs
//#endif


//_iq a,b,c;

/**
 * main.c
 */
void main(void)
{

// Define Local  Variables
    Uint32 *pulMsgRam;
    Uint16 counter;

    Uint16 *pusCBufferPt = (void *)C28_S0SARAM_START;
    Uint16 *pusMBufferPt = (void *)(C28_S0SARAM_START + usMBuffer_SIZE);

    InitSysCtrl();

#ifdef _FLASH
// Copy time critical code and Flash setup code to RAM
// This includes the following functions:  InitFlash();
// The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
// symbols are created by the linker. Refer to the device .cmd file.
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
    InitFlash();
#endif


    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    InitBoardGpio();
    ConfigureEPwm();
    ConfigureADC();
    //ConfigureXint();
    Initparameter();

    EALLOW;
    //PieVectTable.SCIRXINTA = &scirxintab_isr;//SCI�ж��ӳ����ַ
    PieVectTable.ADCINT1=&adca1_interrupt_isr;//��׽�ж��ӳ����ַ
    PieVectTable.XINT1=&xint1_isr;//�ⲿ�ж�2018/1/3
    //PieVectTable.MTOCIPC_INT1 = &MtoCIPC1IntHandler;
    PieVectTable.MTOCIPC_INT2 = &MtoCIPC2IntHandler;
    EDIS;

    // Step 4. Initialize the Device Peripherals:
    //IPCCInitialize (&g_sIpcController1, IPC_INT1, IPC_INT1);
    IPCCInitialize (&g_sIpcController2, IPC_INT2, IPC_INT2);

    //ʹ��CPU�ж�
    //IER |=M_INT9;//SCI�ж�     ��CPU�ж�1~9(���뿪�Ŷ�Ӧ��CPU���жϿ�)
    IER |=M_INT1;//cputime and adc and�ⲿ�ж�
    IER |= M_INT11;
    //ʹ��PIE�ж�
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;//ʹ��Adcint1���ж�
    //PieCtrlRegs.PIEIER9.bit.INTx1 = 1;//ʹ��Sci�����ж�
    //PieCtrlRegs.PIEIER1.bit.INTx4 = 1;//ʹ���ⲿ�ж�

    // Enable MTOCIPC INTn in the PIE: Group 11 interrupts
    //PieCtrlRegs.PIEIER11.bit.INTx1 = 1; // MTOCIPC INT1
    PieCtrlRegs.PIEIER11.bit.INTx2 = 1; // MTOCIPC INT2


    //��ȫ���ж�
    EINT;//ʹ��ȫ���жϣ����жϣ���CPU���ģ�
    ERTM;//ʹ��ʵʱ�жϣ�CPU���ģ�

    // Initialize all variables.
    ErrorFlag = 0;
    wErrorFlag = 0;
    for (counter = 0; counter < usMBuffer_SIZE; counter++)
    {
        usMBuffer[counter] = 0;
    }
    for (counter = 0; counter < usMBuffer_SIZE; counter++)
    {
        usCBuffer[counter] = 0;
    }
    // Point array to address in CTOM MSGRAM for passing variable locations
    pulMsgRam = (void *)C28_CTOM_PASSMSG;

    // Write addresses of variables where words should be written to pulMsgRam
    // array.
    pulMsgRam[2] = (unsigned long)&usMBuffer[0];


    pulMsgRam = (void *)C28_MTOC_PASSMSG;

    // Flag to M3 that the variables are ready in MSG RAM with CTOM IPC Flag 17
    CtoMIpcRegs.CTOMIPCSET.bit.IPC17 = 1;


    ///////////////////////////////////////��ʼ������
    while(1)
    {

        if(IPC_get_flag)
        {
            IPCdata_tran();
            IPC_get_flag=0;
        }

        n_coop++;
        if(n_coop==30000)
        {
            int i=0;
            for(i=0;i<44;i++)
            {
                IPC_send.all=Paramet[i];
                usCBuffer[2*i]=IPC_send.bit.MEM1;
                usCBuffer[2*i+1]=IPC_send.bit.MEM2;
            }
            ipc_to_pso_flag=1;
            n_coop=0;
        }


        Paramet[0]=Ua;//ֵ����λ��
        Paramet[1]=Ub;
        Paramet[2]=Uc;
        Paramet[3]=P;
        Paramet[4]=Q;
        Paramet[5]=w;
        Paramet[6]=theta_fan;
///////////////////////////////////////////////////////////��λ���·�����
        P0=Paramet[P_0];
        Q0=Paramet[Q_0];
        kp_current_dqp=Paramet[kp_I_p];
        ki_current_dqp=Paramet[ki_I_p];
        kp_current_dqn=Paramet[kp_I_n];
        ki_current_dqn=Paramet[ki_I_n];
        kp_voltage_dqp=Paramet[kp_u_p];
        ki_voltage_dqp=Paramet[ki_u_p];
        kp_voltage_dqn=Paramet[kp_u_n];
        ki_voltage_dqn=Paramet[ki_u_n];
        max_current=Paramet[PI_I_max];
        kp_pcc_degree=Paramet[kp_pcc];
        ki_pcc_degree=Paramet[ki_pcc];
        min_current=-max_current;


///////////////////////////////////////////////////////////
        //�Ƿ�ͣ��
        if( FlagRegs.flagsystem.bit.sysonoff == 0)//ͣ��
        {
            SYSTEMoff();
        }
        else
        {
            if(N_stage2==0)
            {
                PWMopen();
            }
            else
            {
                PWMoff();//����PWM
            }
        }


        if(ipc_to_pso_flag)
        {
        // Data Block Writes
            // Request Memory Access to S0 SARAM for C28 (Invokes
            // IPCCtoMSetBits_Protected() function)
            IPCCtoMReqMemAccess (&g_sIpcController2, S0_ACCESS, IPC_SX_C28MASTER,
                                 ENABLE_BLOCKING);
            while ((RAMRegs.CSxMSEL.all & S0_ACCESS) != S0_ACCESS)
            {
            }

            // Write a block of data from C28 to S0 shared RAM which is then written to
            // an M3 address.
            for (counter = 0; counter < usMBuffer_SIZE; counter++)
            {
                pusCBufferPt[counter] = usCBuffer[counter];
            }

            IPCCtoMBlockWrite(&g_sIpcController2, pulMsgRam[2], (Uint32)pusCBufferPt,
                              usMBuffer_SIZE, IPC_LENGTH_16_BITS,
                              ENABLE_BLOCKING);

            // Return Memory Access to S0 SARAM to M3 (Invokes
            // IPCCtoMSetBits_Protected() function)
            IPCCtoMReqMemAccess (&g_sIpcController2, S0_ACCESS, IPC_SX_M3MASTER,
                                 ENABLE_BLOCKING);
            while ((RAMRegs.CSxMSEL.all & S0_ACCESS) != 0)
            {
            }


            // Read data back from M3.
            IPCCtoMBlockRead(&g_sIpcController2, pulMsgRam[2], (Uint32)pusMBufferPt,
                             usMBuffer_SIZE, ENABLE_BLOCKING,
                             IPC_FLAG17);

            // Wait until read data is ready (by checking IPC Response Flag is cleared).
            // Then check for correct data.
            while (CtoMIpcRegs.CTOMIPCFLG.bit.IPC17)
            {
            }

            for (counter = 0; counter <usMBuffer_SIZE; counter++)
            {
                if (usCBuffer[counter] != pusMBufferPt[counter])
                {
                    wErrorFlag = 1;
                }
                else
                {
                    wErrorFlag = 0;
                }
            }

            if (wErrorFlag == 1)
            {
                wErrorCount++;
            }
            ipc_to_pso_flag=0;
        }




        // Flag an Error if an Invalid Command has been received.
        //
        if (ErrorFlag == 1)
        {
            Error();
        }

    }

}

////SCI�����жϷ����ӳ���
//interrupt void scirxintab_isr(void)
//{
//    //�жϳ��򲿷�
//    //SciRecieve();
//    //���жϱ�־λ
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;//��PIEACK�Ĵ����ĵھ�λд1�������PIE�ھ�λ���ж�����
//    EINT;
//}

//�ⲿ�ж�
interrupt void xint1_isr(void)
{

    //���жϱ�־λ
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


interrupt void adca1_interrupt_isr(void)
{
	GpioDataRegs.GPADAT.bit.GPIO14 = 1;
    Adcread();//�����ӳ���
    Adcdeal();

    //�Ƿ�У�����
     if(FlagRegs.flagsystem.bit.AC0CheckFinished==1)//����У���Ѿ����
     {
         //����
  //       FastFaultTest();//������ѹ���ٹ��ϼ��
         //ͣ���ж�
  //       if (FlagRegs.flagsystem.bit.faultoccur ==1) //�����ϣ���ͣ��������ͣ�������ȼ�����
  //       {
  //         Switchsystem = 0;//��ʾ���ش򿪣���Ҫͣ��
  //         SYSTEMoff();//�ػ�
  //       }
          FlagRegs.flagsystem.bit.sysonoff=Switchsystem;//��λ����ͣ������(��λ����Switchsystem����SCI�����д����)����
          //�Ƿ�ͣ��
          if(FlagRegs.flagsystem.bit.sysonoff==1)////������
          {

          //---------------------������-----------------------------------
          /////////////��������
  //        	theta_fan=0;
          //------------------------------------��е�������任
          I_conversion.As=Adcget.Ia;
          I_conversion.Bs=Adcget.Ib;
          I_conversion.Cs=Adcget.Ic;
          I_conversion.Angle=theta_fan;
          abc_dq0p(&I_conversion);
          Idp=I_conversion.Ds;
          Iqp=I_conversion.Qs;
          I_conversion.Angle=-theta_fan;
          abc_dq0n(&I_conversion);
          Idn=I_conversion.Ds;
          Iqn=I_conversion.Qs;


          //------------------------------------������˿ڵ�ѹ
          U_conversion.As=Adcget.Ua;
          U_conversion.Bs=Adcget.Ub;
          U_conversion.Cs=Adcget.Uc;
          U_conversion.Angle=theta_fan;
          abc_dq0p(&U_conversion);
          Udp=U_conversion.Ds;
          Uqp=U_conversion.Qs;
          U_conversion.Angle=-theta_fan;
          abc_dq0n(&U_conversion);
          Udn=U_conversion.Ds;
          Uqn=U_conversion.Qs;

  //        //--------------------------------------PCC����
  //        Io_conversion.As=Adcget.Ioa;
  //        Io_conversion.Bs=Adcget.Iob;
  //        Io_conversion.Cs=Adcget.Ioc;
  //        Io_conversion.Angle=theta_fan;
  //        abc_dq0p(&Io_conversion);

          //--------------------------------------PCC��ѹ
          Uo_conversion.As=Adcget.Uoa;
          Uo_conversion.Bs=Adcget.Uob;
          Uo_conversion.Cs=Adcget.Uoc;
          Uo_conversion.Angle=theta_fan;
          abc_dq0p(&Uo_conversion);
          Uodp=Uo_conversion.Ds;
          Uoqp=Uo_conversion.Qs;
          Uo_conversion.Angle=-theta_fan;
          abc_dq0n(&Uo_conversion);
          Uodn=Uo_conversion.Ds;
          Uoqn=Uo_conversion.Qs;

          droop();
          neiwaihuan();


          //---------------------SPWM����------------------------------------

          //////////////����������
  //        Ua=311;
  //        Ub=-311/2;
  //        Uc=-311/2;
  //        Uout_conversion.As=0;
  //        Uout_conversion.Bs=0;
  //        Uout_conversion.Cs=0;
  //        Uoutn_conversion.As=0;
  //        Uoutn_conversion.Bs=0;
  //        Uoutn_conversion.Cs=0;
          /////////////
  //        Ua=311*cos(theta_fan)+Uout_conversion.As;
  //        Ub=311*cos(theta_fan-TWObyTHREE*PI)+Uout_conversion.Bs;
  //        Uc=311*cos(theta_fan+TWObyTHREE*PI)+Uout_conversion.Cs;
          Ua=311*cos(theta_fan)+Uout_conversion.As+Uoutn_conversion.As;
          Ub=311*cos(theta_fan-TWObyTHREE*PI)+Uout_conversion.Bs+Uoutn_conversion.Bs;
          Uc=311*cos(theta_fan+TWObyTHREE*PI)+Uout_conversion.Cs+Uoutn_conversion.Cs;
  //-----------------------------------------
          a_graph[n_graph]=Ua;
          b_graph[n_graph]=Ub;
          c_graph[n_graph]=Uc;
  //        a_graph[n_graph]=theta_fan;
          n_graph++;
          if(n_graph==graphNumber)
          {

          	n_graph=0;
          }

          //
          if(Ua>M)//M
          {
              Ua=M;
          }
          if(Ua<-M)
          {
              Ua=-M;
          }
          //
          if(Ub>M)
          {
              Ub=M;
          }

          if(Ub<-M)
          {
              Ub=-M;
          }
          //
          if(Uc>M)
          {
              Uc=M;
          }

          if(Uc<-M)
          {
              Uc=-M;
          }
          m_sin_a=Ua/500;
          m_sin_b=Ub/500;
          m_sin_c=Uc/500;

  //        Tcmpa=3750*(1-m_sin_a);
  //        Tcmpb=3750*(1-m_sin_b);
  //        Tcmpc=3750*(1-m_sin_c);
          //T/4

          //5kHz
          Tcmpa=7500*(1-m_sin_a);
          Tcmpb=7500*(1-m_sin_b);
          Tcmpc=7500*(1-m_sin_c);


          EPwm1Regs.CMPA.half.CMPA=Tcmpa;
          EPwm2Regs.CMPA.half.CMPA=Tcmpb;
          EPwm3Regs.CMPA.half.CMPA=Tcmpc;

//		if(n_count1==vn_comp)
//		{
//			n_pso++;
//			if(n_pso==200)
//			{
//				n_pso=0;
//				PSOSENDF=1;
//				PSOsend(pso_t);
//			}
//		}

	  }
	  else
	  {
		  SYSTEMoff();//�ػ�
	  }

    }

	Adc1Regs.ADCINTFLGCLR.bit.ADCINT1 = 1;  //Clear ADCINT1 flag reinitialize
	                                            // for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    GpioDataRegs.GPADAT.bit.GPIO14 = 0;
}



void IPCdata_tran(void)
{
    PackLength=usMBuffer[0];
    SerialNumber=usMBuffer[1];
    CommandCode=usMBuffer[2];

    if(PackLength==5&&CommandCode==0xB1)//�����Ƿ����5-�жϿ��ػ�����
    {
        Data_get.bit.MEM1=usMBuffer[3];
        Data_get.bit.MEM2=usMBuffer[4];
        Switchsystem=Data_get.all;
    }
    if(PackLength==7)//�����Ƿ����7//�����������Ǵӻ�����ʾ�����������޸���Ҫ���Ƕ�Ӧ�Ĵӻ�
    {
        FData_get.bit.MEM1=usMBuffer[3];
        FData_get.bit.MEM2=usMBuffer[4];
        FData_get.bit.MEM3=usMBuffer[5];
        FData_get.bit.MEM4=usMBuffer[6];
        Paramet[SerialNumber]=FData_get.all;
    }

}




//*****************************************************************************
// Function to Indicate an Error has Occurred (Invalid Command Received).
//*****************************************************************************
void
Error(void)
{
    // An error has occurred (invalid command received). Loop forever.
    for (;;)
    {
    }
}


////*****************************************************************************
//// MtoC INT1 Interrupt Handler - Handles Data Word Reads/Writes
////*****************************************************************************
//__interrupt void
//MtoCIPC1IntHandler (void)
//{
//    tIpcMessage sMessage;
//
//    // Continue processing messages as long as MtoC GetBuffer1 is full
//    while (IpcGet (&g_sIpcController1, &sMessage,
//                   DISABLE_BLOCKING)!= STATUS_FAIL)
//    {
//        switch (sMessage.ulcommand)
//        {
////        case IPC_SET_BITS:
////            IPCMtoCSetBits(&sMessage);
////            break;
////        case IPC_CLEAR_BITS:
////            IPCMtoCClearBits(&sMessage);
////            break;
//        case IPC_DATA_WRITE:
//            IPCMtoCDataWrite(&sMessage);
//            break;
//        case IPC_DATA_READ:
//            IPCMtoCDataRead(&g_sIpcController1, &sMessage, ENABLE_BLOCKING);
//            break;
////        case IPC_FUNC_CALL:
////            IPCMtoCFunctionCall(&sMessage);
////            break;
//        default:
//            ErrorFlag = 1;
//            break;
//        }
//    }
//
//    // Acknowledge IPC INT1 Flag and PIE to receive more interrupts from group
//    // 11
//    CtoMIpcRegs.MTOCIPCACK.bit.IPC1 = 1;
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
//}

//*****************************************************************************
// MtoC INT2 Interrupt Handler - Handles Data Block Reads/Writes
//*****************************************************************************
__interrupt void
MtoCIPC2IntHandler (void)
{
    tIpcMessage sMessage;

    // Continue processing messages as long as MtoC GetBuffer2 is full
    while (IpcGet (&g_sIpcController2, &sMessage,
                   DISABLE_BLOCKING)!= STATUS_FAIL)
    {
        switch (sMessage.ulcommand)
        {
        case IPC_BLOCK_WRITE:
            IPCMtoCBlockWrite(&sMessage);
            break;
        case IPC_BLOCK_READ:
            IPCMtoCBlockRead(&sMessage);
            break;
        default:
            ErrorFlag = 1;
            break;
        }
    }
    IPC_get_flag=1;
    // Acknowledge IPC INT2 Flag and PIE to receive more interrupts from group
    // 11
    CtoMIpcRegs.MTOCIPCACK.bit.IPC2 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
}
