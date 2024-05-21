#ifndef __GOF__
#define __GOF__


#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "message.h"
#include "ipc.h"

//����Ƕ���һ����������#define   �������һ����������extern float
//SCI
#define PackHeadLength 4 //��ͷ����
#define PackHead 0x00FE  //��ͷ
//#define TestIO PORTBbits.RB5  //���ڼ��
//#define CL485 PORTBbits.RB13  //CL485Ϊ1ʱ����ʹ�ܣ�Ϊ0ʱ����ʹ��
#define ParameterNumber 118 //����ͨ�ű�������


#define SortNo 0x01//վ��ţ���������δʹ��
//#define set485 GpioDataRegs.GPASET.bit.GPIO26= 1//����ʹ��
//#define clear485 GpioDataRegs.GPACLEAR.bit.GPIO26= 1 //����ʹ��
#define On_off 81   //���ػ�
#define ConfirmCode  01 //SCIȷ����
//�Զ������SCI��Ӧ��ϵ
#define speed_bldcm 1
#define I_meandc_run 2
#define Iu_adc_run 3
#define Iv_adc_run 4
#define Iw_adc_run 5
#define U_meandc_run 6
#define hallposition 7
//8��9��10��Ϊ������ʾ�ı���
#define overcurrentt 11
#define overloadd 12
#define overvoltagee 13
#define undervoltagee 14
#define tabanfaultt 15
#define hightemcircuitt 16
#define hightemmotorr 17
#define ocfaultt 18
#define faultoccurr 19
#define flagfault_run 20
//////////////////////////////���������в����й̶����������������޸ģ����ɶ�8��9��10������Ŀ��
#define io_alpha 21
#define io_beta  22
#define io_d     23
#define io_q     24
#define uo_alpha 25
#define uo_beta 26
#define uo_d 27
#define uo_q 28

#define U0 311
#define w0 50*2*PI
#define m 0.000005
#define n 0.0001
#define M 500


//////////////////////////////ϣ��ͨ����λ��������ֵ��main����һ��Paramet���������λ����������ֵ��
#define P_0     44//�������й� �޹�����
#define Q_0     45
#define kp_I_p  46//�����ڻ�d��PI����
#define ki_I_p  47//
#define kp_I_n  48//�����ڻ�q��PI����
#define ki_I_n  49
#define kp_u_p  50//��ѹ�⻷d��PI����
#define ki_u_p  51
#define kp_u_n  52//��ѹ�⻷q��PI����
#define ki_u_n  53
#define kp_pcc 54
#define ki_pcc 55
#define reduce_ratio 56
#define current_ref 57
#define stop_moder 58
#define speed_max 59
#define speed_ref 60
#define ref_source 61
#define rotatdircw 62//����ת
#define N_kp 63
#define N_ki 64
#define PI_N_max 65
#define PI_N_min 66
#define I_kp 67
#define I_ki 68
#define PI_I_max 70
#define PI_I_min 71
//����Ƶ��Ϊfk,�򿪹�����Ϊts,TBPRD��Ӧ��ֵ��ʾ�������ڵ�һ�룬switch��ʾ��������ֵ
#define W_kp 72 //
#define W_ki 73
#define PI_W_max 74
#define PI_W_min 75
#define modulation 76
#define predir_num2 77
#define Kw_start 78
#define Iq_ref_startup 79
#define debugmode 80
#define debug_predirORlcom 81
#define slope_delt_n 82
#define slope_delt_t 83
#define Slope_en_sign 84
#define current_ref_limit 85
#define rs_psm 102
#define Ld_psm 103
#define Lq_psm 104
#define flux_psm 105


#define graphNumber 400
#define PSONumber 48


extern unsigned int Switchsystem;
extern unsigned int RCBUF[24];//RS485 ���ջ����� ��ϵͳ��ͨѶЭ���25�����ݣ�
extern unsigned int ReciveRCOUNT;//RS485 ���ռ����� 0~25
extern unsigned int RC_DataCount;   //�������ݼ�����
extern unsigned int TXCOUNT;//RS485 ���ͼ�����
extern unsigned int PSOCOUNT;//RS485 ���ͼ�����
extern unsigned int TXBUF[13];//RS485 ���ͻ�����
extern unsigned int PSOBUF[PSONumber];//RS485 ���ͻ�����
extern unsigned int flagRC;//�������ݽ�����־λ
extern unsigned int flagSEND;//�������ݱ�־λ
extern unsigned int PSOSENDF;//�������ݱ�־λ
extern unsigned int RunCommand_L;
extern unsigned int RunCommand_H;
extern unsigned int RunCommand;
extern unsigned int cyclecount;
extern unsigned int datasum;//�����������
extern unsigned int datasum1;
extern unsigned int PackLength;     //���ݰ���
extern unsigned int RC_DataBUF[20];  //�������ݻ�����������վ���-���к�-������-���ݸ�-���ݵ�-У���룩
extern unsigned int RC_DataCount;   //�������ݼ�����
extern unsigned int SortNumber;     //վ���
extern unsigned int SerialNumber;   //SCI���
extern unsigned int CommandCode;     //SCI������
extern unsigned int CheckCode;      //У����
extern unsigned int SendData;       //��������
extern unsigned int SendDataNumber;     //�������ݸ���
//extern unsigned int Paramet[ParameterNumber];
extern unsigned int PSO_datainit_flag;
extern float Paramet[ParameterNumber];

extern float pso_t[10];
extern int n_pso;


extern unsigned int IPC_send_flag;
extern unsigned int IPC_get_flag;
extern union FLOAT_COM  Data_get;
extern union FLOAT_COMF  FData_send;
extern union FLOAT_COMF  FData_get;
extern union FLOAT_COMF  PSO_send;
extern union FLOAT_COMF  PSO_get;
extern union FLOAT_IPCF  IPC_get;
extern float PSO_g[4];


//IPC


//*****************************************************************************
// Address Definitions
//*****************************************************************************
#define M3_CTOM_PASSMSG   0x2007F7E8            // CTOM MSG RAM offsets for
                                                // passing addresses
#define M3_MTOC_PASSMSG 0x2007FFE8  // MTOC MSG RAM offsets for passing
                                    // addresses
#define M3_S0SARAM_START  0x20008000            // Start of S0 SARAM in M3
                                                // memory map
#define M3_S1SARAM_START  0x2000A000            // Start of S1 SARAM in M3
                                                // memory map
#define usMBuffer_SIZE 100 //IPCͨѶ

extern unsigned short usMBuffer[usMBuffer_SIZE];
extern unsigned short gusMBuffer[usMBuffer_SIZE];
//*****************************************************************************
// At least 1 volatile global tIpcController instance is required when using
// IPC API Drivers.
//*****************************************************************************
extern volatile tIpcController g_sIpcController1;
extern volatile tIpcController g_sIpcController2;

//*****************************************************************************
// Global variable used to track errors
//*****************************************************************************
extern volatile unsigned short ErrorFlag;
extern volatile unsigned short ErrorCount;


#endif
