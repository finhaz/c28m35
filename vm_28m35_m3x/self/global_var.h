#ifndef __GOF__
#define __GOF__


#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "message.h"
#include "ipc.h"

//如果是定义一个常数就用#define   如果定义一个变量就用extern float
//SCI
#define PackHeadLength 4 //包头长度
#define PackHead 0x00FE  //包头
//#define TestIO PORTBbits.RB5  //用于检测
//#define CL485 PORTBbits.RB13  //CL485为1时发送使能，为0时接收使能
#define ParameterNumber 118 //定义通信变量个数


#define SortNo 0x01//站点号，本程序中未使用
//#define set485 GpioDataRegs.GPASET.bit.GPIO26= 1//发送使能
//#define clear485 GpioDataRegs.GPACLEAR.bit.GPIO26= 1 //接收使能
#define On_off 81   //开关机
#define ConfirmCode  01 //SCI确认码
//自定义变量SCI对应关系
#define speed_bldcm 1
#define I_meandc_run 2
#define Iu_adc_run 3
#define Iv_adc_run 4
#define Iw_adc_run 5
#define U_meandc_run 6
#define hallposition 7
//8、9、10作为采样显示的保留
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
//////////////////////////////以上是运行参数中固定参数，基本不可修改，仅可对8、9、10增加项目。
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


//////////////////////////////希望通过上位机给定的值在main里有一段Paramet的语句是上位机给变量赋值的
#define P_0     44//给定的有功 无功功率
#define Q_0     45
#define kp_I_p  46//电流内环d轴PI参数
#define ki_I_p  47//
#define kp_I_n  48//电流内环q轴PI参数
#define ki_I_n  49
#define kp_u_p  50//电压外环d轴PI参数
#define ki_u_p  51
#define kp_u_n  52//电压外环q轴PI参数
#define ki_u_n  53
#define kp_pcc 54
#define ki_pcc 55
#define reduce_ratio 56
#define current_ref 57
#define stop_moder 58
#define speed_max 59
#define speed_ref 60
#define ref_source 61
#define rotatdircw 62//正反转
#define N_kp 63
#define N_ki 64
#define PI_N_max 65
#define PI_N_min 66
#define I_kp 67
#define I_ki 68
#define PI_I_max 70
#define PI_I_min 71
//开关频率为fk,则开关周期为ts,TBPRD对应的值表示开关周期的一半，switch表示开关周期值
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
extern unsigned int RCBUF[24];//RS485 接收缓存器 （系统级通讯协议的25个数据）
extern unsigned int ReciveRCOUNT;//RS485 接收计数器 0~25
extern unsigned int RC_DataCount;   //接收数据计数器
extern unsigned int TXCOUNT;//RS485 发送计数器
extern unsigned int PSOCOUNT;//RS485 发送计数器
extern unsigned int TXBUF[13];//RS485 发送缓存器
extern unsigned int PSOBUF[PSONumber];//RS485 发送缓存器
extern unsigned int flagRC;//接收数据结束标志位
extern unsigned int flagSEND;//发送数据标志位
extern unsigned int PSOSENDF;//发送数据标志位
extern unsigned int RunCommand_L;
extern unsigned int RunCommand_H;
extern unsigned int RunCommand;
extern unsigned int cyclecount;
extern unsigned int datasum;//发送数据求和
extern unsigned int datasum1;
extern unsigned int PackLength;     //数据包长
extern unsigned int RC_DataBUF[20];  //接收数据缓存器（包括站点号-序列号-命令码-数据高-数据低-校验码）
extern unsigned int RC_DataCount;   //接收数据计数器
extern unsigned int SortNumber;     //站点号
extern unsigned int SerialNumber;   //SCI序号
extern unsigned int CommandCode;     //SCI命令码
extern unsigned int CheckCode;      //校验码
extern unsigned int SendData;       //发送数据
extern unsigned int SendDataNumber;     //发送数据个数
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
#define usMBuffer_SIZE 100 //IPC通讯

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
