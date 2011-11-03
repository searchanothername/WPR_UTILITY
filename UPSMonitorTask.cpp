// UPSMonitorTask.cpp: implementation of the CUPSMonitorTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "UPSMonitorTask.h"
#include "Global_SM.h"
#include "Global.h"
#include "A44_sm_handler.h"
#include "WPR_UTILITIESDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUPSMonitorTask::CUPSMonitorTask()
{

}

CUPSMonitorTask::~CUPSMonitorTask()
{

}

void CUPSMonitorTask::SetParent(CWPR_UTILITIESDlg* pWindow)
{
	g_utility = pWindow;
}

DWORD CUPSMonitorTask::Run(void* pParam)
{
	if(g_sg_port_config.bInUse)
	{
		g_sg_port.configcomm( g_sg_port_config.str_portname,
			g_sg_port_config.baudrate,
			g_sg_port_config.parity,
			g_sg_port_config.byte_num); 
		if(!g_sg_port.isconfiged()){
			AfxMessageBox("UPS Port config fail");
			return 0;
		}
	}

	while(global.cs_ups.IsOn())
	{
		UINT ups_retcd = 0;
		a422_ups_command("RSS",ups_retcd);
		Parse();
		Sleep(500);
	};
	return 1;
}

DWORD CUPSMonitorTask::Stop(void* pParam)
{
	global.cs_ups.TurnOff();
	if(g_sg_port.isconfiged()){
		g_sg_port.closecomm();
		return 0;
	}
	this->Exit();
	return 1;
}

void CUPSMonitorTask::Parse()
{
	char status_string[8];
		sscanf(g_ups_status.s,"(%f %f %f %f %f %f %f %s",\
			&g_ups_data.ups_I_P_voltage,
			&g_ups_data.ups_I_P_fault_voltage,
			&g_ups_data.ups_O_P_voltage,
			&g_ups_data.ups_O_P_load,
			&g_ups_data.ups_I_P_frquence,
			&g_ups_data.ups_Battery_voltage,
			&g_ups_data.ups_Temperature,
			status_string);

	//Send to the main frame.
	CString str_ups;
	str_ups.Format("%s", g_ups_status.s);
	g_utility->m_str_ups_status = str_ups;
	//::PostMessage(g_utility->m_hWnd,WM_MYSHOW,0,0); 


	g_ups_data.ups_status.status._utility_faild= status_string[0]-'0';
	g_ups_data.ups_status.status._battery_low = status_string[1]-'0';
	g_ups_data.ups_status.status._bypass_boot_active = status_string[2] -'0';
	g_ups_data.ups_status.status._failed = status_string[3] -'0';
	g_ups_data.ups_status.status._standby = status_string[4] - '0';
	g_ups_data.ups_status.status._test_in_progress = status_string[5] - '0';
	g_ups_data.ups_status.status._shut_down_active = status_string[6] - '0';
	g_ups_data.ups_status.status._received = status_string[7] - '0';
	return;
}
