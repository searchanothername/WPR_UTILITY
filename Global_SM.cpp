// Global_SM.cpp: implementation of the Global_SM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Global_SM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//FOR SIGNAL GENERATOR
const char OPEN25M[4] = {0xa5,0xa1,0x11,0xaa};
const char CLOSE25M[4]= {0xa5,0xa1,0x00,0xaa};
const char OBLIQUE[4] = {0xa5,0xa2,0x11,0xaa};
const char VERTICAL[4]= {0xa5,0xa2,0x00,0xaa};

char g_sg_command[4] = {0};
unsigned char g_sg_status[4] = {0};

const unsigned char RFD_ALARM_MASK		= 0X10;
const unsigned char STALO_ALARM_MASK	= 0X08;
const unsigned char RFTEST_ALARM_MASK	= 0X04;
const unsigned char S_60M_ALARM_MASK	= 0X02;
const unsigned char S_25M_ALRAM_MASK	= 0X01;


sm_port_config g_sm_port_config;
sm_port_config g_sg_port_config;

communication_config g_communication_config;
control_config  g_ctrl_config;
int g_nCommunicationSel = 0;

SM_STATUS g_sm_status;
SM_STATUS g_sm_temp;

unsigned char g_sm_command[4] = {0x1a,0x00,0x00,0x55}; 
unsigned char g_sm_rss[4]     = {0x1a,0x00,0x00,0x00}; 

class CSM_Port g_sm_port;
class CSM_Port g_sg_port; //FOR FREQ GENERATOR
/*
char HPA_START_MASK[10] = {0xfa,0xf6,0xee,0xde,0xbe,0x7e,//in byte1
							0xfa,0xf6,0xee,0xde};//in byte2
char HPA_SHUT_MASK[10] = {0x06,0x0a,0x12,0x22,0x42,0x82,
							0xc6,0xca,0xd2,0xe2};
							*/

char HPA_START_MASK = 0x40;
char HPA_SHUT_MASK = 0x00;

char DRIVER_A_MASK = 0xbe;
char DRIVER_B_MASK = 0x42;
unsigned int byteinqueue = 0;
BOOL g_bCycleCtrol;
int  g_CommunicationSel;

CString baudrate[3] = {"2400","9600","19200"};
CString portname[6] = {"COM1","COM2","COM3","COM4","COM5","COM6"};
CString parity[3] = {"EVEN","ODD","NONE"};

CFile f_port;

void LoadPortAdaptor(){
	f_port.Open("SM_SIM_PORT_ADAPT.dat",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead);
	f_port.Read(&g_sm_port_config,sizeof(sm_port_config));
    f_port.Read(&g_communication_config,sizeof(communication_config));
    f_port.Read(&g_ctrl_config,sizeof(control_config));
	f_port.Read(&g_sg_port_config,sizeof(sm_port_config));
	f_port.Close();
}

void SavePortAdapor(){
	f_port.Open("SM_SIM_PORT_ADAPT.dat",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	f_port.Write(&g_sm_port_config,sizeof(sm_port_config));
	f_port.Write(&g_communication_config,sizeof(communication_config));
	f_port.Write(&g_ctrl_config,sizeof(control_config));
    f_port.Write(&g_sg_port_config,sizeof(sm_port_config));
	f_port.Close();
}
