// Global_SM.h: interface for the Global_SM class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_SM_H__37575174_0831_4761_83DA_21C125ADA4AA__INCLUDED_)
#define AFX_GLOBAL_SM_H__37575174_0831_4761_83DA_21C125ADA4AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(1)  //SET BOUNDARY FOR STATUS MONITOR
#include "sm_port.h"
#include "Global_SM_NewTx.h"


////////////////////////////////////////////////////////////////
//STATUS MONITOR INTERFACE
////////////////////////////////////////////////////////////////

/*
****************************************
* ENUM FOR SAVING DATA INTO A FILE.
****************************************
*/
enum{
	SAVE_BINARY,	
	SAVE_TEXT,
	SAVE_NONE,

};

/*
***************************************
* PORT CONFIGURATION FOR SM
***************************************
*/
struct sm_port_config{
	char str_portname[10];
	unsigned int baudrate;
    char parity;
	BOOL bInUse;
	unsigned int byte_num; //LIUChen add it 2011/5/30
	BOOL bHRDCheck; //LIUChen add it 2011/6/11
};

/*
***************************************
* PORT CONFIGURATION FOR NETWORK
***************************************
*/
struct communication_config{
	int selection;
	DWORD server_ip;	//Server IP Address
	UINT port;
};

/*
***************************************
* CONFIGURATION FOR MODE CONTROL
***************************************
*/
struct control_config{
	int selection;       //archive mode.
	char str_archive_path[200];
	BOOL b_CycleTest;
	BOOL b_RemoteCtrl;
};

extern CString baudrate[3];
extern CString portname[6];
extern CString parity[3]; 

extern struct sm_port_config g_sm_port_config;
extern struct sm_port_config g_sg_port_config;

extern struct communication_config g_communication_config;
extern struct control_config  g_ctrl_config;
extern SM_STATUS  g_sm_status;
extern SM_STATUS  g_sm_temp;
extern unsigned char g_sm_command[4]; 
extern unsigned char g_sm_rss[4]; 

extern char HPA_START_MASK;
extern char HPA_SHUT_MASK;
extern char DRIVER_A_MASK;
extern char DRIVER_B_MASK;

extern class CSM_Port g_sm_port;
extern class CSM_Port g_sg_port; //FOR FREQ GENERATOR

extern CFile f_port;
extern void LoadPortAdaptor();
extern void SavePortAdapor();
extern BOOL g_bCycleCtrol;
extern int  g_CommunicationSel;

//FOR FREQ GENERATOR
extern const char OPEN25M[4];
extern const char CLOSE25M[4];
extern const char OBLIQUE[4];
extern const char VERTICAL[4];

extern char g_sg_command[4];
extern unsigned char g_sg_status[4];

extern const unsigned char RFD_ALARM_MASK;
extern const unsigned char STALO_ALARM_MASK;
extern const unsigned char RFTEST_ALARM_MASK;
extern const unsigned char S_60M_ALARM_MASK;
extern const unsigned char S_25M_ALRAM_MASK;
#endif // !defined(AFX_GLOBAL_SM_H__37575174_0831_4761_83DA_21C125ADA4AA__INCLUDED_)
