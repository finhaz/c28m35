#define PackHeadLength 4 //包头长度
#define PackHead 0x00FE  //包头


#include "global_var.h"




//sci
unsigned int Switchsystem;
unsigned int RCBUF[24];//RS485 接收缓存器 （系统级通讯协议的24个数据）
unsigned int ReciveRCOUNT;//RS485 接收计数器 0~11
unsigned int RC_DataCount;   //接收数据计数器
unsigned int TXCOUNT=0;//RS485 发送计数器
unsigned int PSOCOUNT=0;//RS485 发送计数器
unsigned int TXBUF[13];//RS485 发送缓存器
unsigned int PSOBUF[PSONumber];//RS485 发送缓存器
unsigned int flagRC=0;//接收数据结束标志位
unsigned int flagSEND=0;//发送数据标志位
unsigned int PSOSENDF=0;//发送数据标志位
//unsigned int RunCommand_L;
//unsigned int RunCommand_H;
unsigned int RunCommand;
unsigned int cyclecount;
unsigned int datasum;//发送数据求和
unsigned int datasum1;
unsigned int PackLength;     //数据包长
unsigned int RC_DataBUF[20];  //接收数据缓存器（包括站点号-序列号-命令码-数据高-数据低-校验码）
unsigned int RC_DataCount;   //接收数据计数器
unsigned int SortNumber;     //站点号
unsigned int SerialNumber;   //SCI序号
unsigned int CommandCode;     //SCI命令码
unsigned int CheckCode;      //校验码
unsigned int SendData;       //发送数据
unsigned int SendDataNumber;     //发送数据个数
//unsigned int Paramet[ParameterNumber];
unsigned int PSO_datainit_flag;
float Paramet[ParameterNumber];
unsigned short usMBuffer[usMBuffer_SIZE];
unsigned short gusMBuffer[usMBuffer_SIZE];
float pso_t[10];
int n_pso=0;

unsigned int IPC_send_flag=0;
unsigned int IPC_get_flag=0;
union FLOAT_COM  Data_get;
union FLOAT_COMF  FData_send;
union FLOAT_COMF  FData_get;
union FLOAT_COMF  PSO_send;
union FLOAT_COMF  PSO_get;
union FLOAT_IPCF  IPC_get;

float PSO_g[4]={0,0,0,0};

//IPC
//*****************************************************************************
// At least 1 volatile global tIpcController instance is required when using
// IPC API Drivers.
//*****************************************************************************
volatile tIpcController g_sIpcController1;
volatile tIpcController g_sIpcController2;

//*****************************************************************************
// Global variable used to track errors
//*****************************************************************************
volatile unsigned short ErrorFlag;
volatile unsigned short ErrorCount;

