#define PackHeadLength 4 //��ͷ����
#define PackHead 0x00FE  //��ͷ


#include "global_var.h"




//sci
unsigned int Switchsystem;
unsigned int RCBUF[24];//RS485 ���ջ����� ��ϵͳ��ͨѶЭ���24�����ݣ�
unsigned int ReciveRCOUNT;//RS485 ���ռ����� 0~11
unsigned int RC_DataCount;   //�������ݼ�����
unsigned int TXCOUNT=0;//RS485 ���ͼ�����
unsigned int PSOCOUNT=0;//RS485 ���ͼ�����
unsigned int TXBUF[13];//RS485 ���ͻ�����
unsigned int PSOBUF[PSONumber];//RS485 ���ͻ�����
unsigned int flagRC=0;//�������ݽ�����־λ
unsigned int flagSEND=0;//�������ݱ�־λ
unsigned int PSOSENDF=0;//�������ݱ�־λ
//unsigned int RunCommand_L;
//unsigned int RunCommand_H;
unsigned int RunCommand;
unsigned int cyclecount;
unsigned int datasum;//�����������
unsigned int datasum1;
unsigned int PackLength;     //���ݰ���
unsigned int RC_DataBUF[20];  //�������ݻ�����������վ���-���к�-������-���ݸ�-���ݵ�-У���룩
unsigned int RC_DataCount;   //�������ݼ�����
unsigned int SortNumber;     //վ���
unsigned int SerialNumber;   //SCI���
unsigned int CommandCode;     //SCI������
unsigned int CheckCode;      //У����
unsigned int SendData;       //��������
unsigned int SendDataNumber;     //�������ݸ���
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

