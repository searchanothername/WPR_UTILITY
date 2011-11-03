// AlarmProcess.cpp: implementation of the AlarmProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "AlarmProcess.h"
#include "WPR_UTILITIESDlg.h"
#include "AlarmShowDlg.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

AlarmTable::AlarmTable()
{

	//INITIALIZE THE MAP OF ALARMS.
	//INSERT THE MESSAGE INTO THIS MAP.
	ALARM_OFFSET[0] = G_KPA_MOD1_FAIL;
    ALARM_OFFSET[1] = G_KPA_DRIVER_ASSEMA_FAIL;
	ALARM_OFFSET[2] = G_KPA_MOD1_DEGRAADED;
	ALARM_OFFSET[3] = G_KPA_PWR_P40V1_FAIL;
	ALARM_OFFSET[4] = G_KANTENNA_FORWARD_POWER_DEGRADED;
	ALARM_OFFSET[5] = G_KPOWER_AMP_DRIVER_OUTPUT_POWER_ZERO;
	ALARM_OFFSET[6] = G_KNOISE_BIN_EXCEEDED_LIMITS;
	ALARM_OFFSET[7] = G_KNO_ALARM;

	alarm_map.InitHashTable(TOTAL_ALARNUM);
	memcpy(ALRAMFLAG,bDefaultAlarmTable,sizeof(bool)*TOTAL_ALARNUM);

	for(int i=0; i<TOTAL_ALARNUM; i++)
         alarm_map.SetAt(i,alram_string_status[i]);
	
}

AlarmTable:: ~AlarmTable()
{
}

void AlarmTable::GetAlarm(int nAlarmClass, 
					 const int& nAlramId, 
					 CString& AlarmName)
{
	return;
}


void AlarmTable::ReportAlarm()
{
	return;
}

//////////////////////////////////////////////////////////////////////
//Class AlramProcess Construction/Destruction
//////////////////////////////////////////////////////////////////////
AlarmProcess::AlarmProcess()
{
	//SET THE ALARM ARRAY
	str_AlarmClass[ 0] = "STATUS 1 ALARM";
	str_AlarmClass[ 2] = "STATUS 2 ALARM";
	str_AlarmClass[ 4] = "STATUS 3 ALARM";
	str_AlarmClass[ 6] = "STATUS 4 ALARM";
	str_AlarmClass[ 8] = "STATUS 5 ALARM";
	str_AlarmClass[10] = "STATUS 6 ALARM";
	str_AlarmClass[12] = "STATUS 7 ALARM";
	str_AlarmClass[14] = "STATUS 8 ALARM";
	
	str_AlarmClass[ 1] = "STATUS 1 OK";
	str_AlarmClass[ 3] = "STATUS 2 OK";
	str_AlarmClass[ 5] = "STATUS 3 OK";
	str_AlarmClass[ 7] = "STATUS 4 OK";
	str_AlarmClass[ 9] = "STATUS 5 OK";
	str_AlarmClass[11] = "STATUS 6 OK";
	str_AlarmClass[13] = "STATUS 7 OK";
	str_AlarmClass[15] = "STATUS 8 OK";

    h_eAlarmComming = CreateEvent(NULL,FALSE,FALSE,NULL);
	nCurAlarmId = PAGE1_OK;//INITIALIZE
}

AlarmProcess::~AlarmProcess()
{
	if(h_eAlarmComming)
		CloseHandle(h_eAlarmComming);
	this->Exit();
}

void AlarmProcess::SetParent(CWPR_UTILITIESDlg* pWindow)
{
	g_utility = pWindow;
}

DWORD AlarmProcess::Run(void* pParam){

	ClearAllAlarm();
    while(global.cs_alarmprocess.IsOn()){	
		 WaitForSingleObject(h_eAlarmComming,INFINITE);
         ProcessAlarm();
	};
	return 1;
}

DWORD AlarmProcess::Stop(void* pParam){
	global.cs_alarmprocess.TurnOff();
	this->Exit();
	return 1;
}
//////////////////////////////////////////////////////////////////////
//PROCESS THE ALARM
//////////////////////////////////////////////////////////////////////
void AlarmProcess::ProcessAlarm(){
	//FIRST TELL ME THE ALARM HAPPENED
	ShowTheAlarmOnTheScreen();
	ResponseAlarm();
}

//////////////////////////////////////////////////////////////////////
//CLEAR ALL THE ALARMS.
//////////////////////////////////////////////////////////////////////
void AlarmProcess::ClearAllAlarm()
{
	for(int i=0; i<TOTAL_ALARM_CLASS; i++){
		g_utility->m_Alarm.DeleteString(i);
		g_utility->m_Alarm.InsertString(i,str_AlarmClass[PAGE1_OK+i*2]);
	}
	memcpy(alarmTable.ALRAMFLAG,bDefaultAlarmTable,sizeof(bool)*TOTAL_ALARNUM);
}

//////////////////////////////////////////////////////////////////////
//SHOW THE GROUP OF ALARM ON THE SCREEN. AND YOU WILL SEE THE DETIAL IN
//THE DIALOG OF PERFORMANCE.
//////////////////////////////////////////////////////////////////////
void AlarmProcess::ShowTheAlarmOnTheScreen()
{
	switch(nCurAlarmId){
		
	case PAGE1_ALARM:
		g_utility->m_Alarm.DeleteString(0);
		g_utility->m_Alarm.InsertString(0,str_AlarmClass[PAGE1_ALARM]);
		break;
		
	case PAGE1_OK:
		g_utility->m_Alarm.DeleteString(0);
		g_utility->m_Alarm.InsertString(0,str_AlarmClass[PAGE1_OK]);
		break;
		
	case PAGE2_ALARM:
        g_utility->m_Alarm.DeleteString(1);
		g_utility->m_Alarm.InsertString(1,str_AlarmClass[PAGE2_ALARM]);
		break;
		
	case PAGE2_OK:
		g_utility->m_Alarm.DeleteString(1);
		g_utility->m_Alarm.InsertString(1,str_AlarmClass[PAGE2_OK]);
		break;
		
	case PAGE3_ALARM:
		g_utility->m_Alarm.DeleteString(2);
		g_utility->m_Alarm.InsertString(2,str_AlarmClass[PAGE3_ALARM]);
		break;
		
	case PAGE3_OK:
		g_utility->m_Alarm.DeleteString(2);
		g_utility->m_Alarm.InsertString(2,str_AlarmClass[PAGE3_OK]);
		break;
		
	case PAGE4_ALARM:
		g_utility->m_Alarm.DeleteString(3);
		g_utility->m_Alarm.InsertString(3,str_AlarmClass[PAGE4_ALARM]);
		break;
		
	case PAGE4_OK:
		g_utility->m_Alarm.DeleteString(3);
		g_utility->m_Alarm.InsertString(3,str_AlarmClass[PAGE4_OK]);
		break;
		
	case PAGE5_ALARM:
        g_utility->m_Alarm.DeleteString(4);
		g_utility->m_Alarm.InsertString(4,str_AlarmClass[PAGE5_ALARM]);
		break;
		
	case PAGE5_OK:
		g_utility->m_Alarm.DeleteString(4);
		g_utility->m_Alarm.InsertString(4,str_AlarmClass[PAGE5_OK]);
		break;
		
	case PAGE6_ALARM:
		g_utility->m_Alarm.DeleteString(5);
		g_utility->m_Alarm.InsertString(5,str_AlarmClass[PAGE6_ALARM]);
		break;
		
	case PAGE6_OK:
		g_utility->m_Alarm.DeleteString(5);
		g_utility->m_Alarm.InsertString(5,str_AlarmClass[PAGE6_OK]);
		break;

	case PAGE7_ALARM:
		g_utility->m_Alarm.DeleteString(6);
		g_utility->m_Alarm.InsertString(6,str_AlarmClass[PAGE7_ALARM]);
		break;
		
	case PAGE7_OK:
		g_utility->m_Alarm.DeleteString(6);
		g_utility->m_Alarm.InsertString(6,str_AlarmClass[PAGE7_OK]);
		break;

	case PAGE8_ALARM:
		g_utility->m_Alarm.DeleteString(7);
		g_utility->m_Alarm.InsertString(7,str_AlarmClass[PAGE8_ALARM]);
		break;
		
	case PAGE8_OK:
		g_utility->m_Alarm.DeleteString(7);
		g_utility->m_Alarm.InsertString(7,str_AlarmClass[PAGE8_ALARM]);
		break;
	};
}

//////////////////////////////////////////////////////////////////////
//WHEN THE ALARM HAPPENED , WE NEED TO DO SOME WORK. 
//////////////////////////////////////////////////////////////////////
void AlarmProcess::ResponseAlarm()
{
    
    if(!bSeriousTable[nIdOfAlarm]){
		//DEAL THE NORMAL ALARM. USUALLY I JUST REPORT THEM
		//IF YOU WANT TO DO SOMETHING ELSE . YOU CAN WRITE CODE
		//HERE.
		//switch(nIdOfAlarm){
		//		
		//}
	}
	else{
		//THEN DEAL THE SPECTIAL ALARM
		switch(nIdOfAlarm)
		{	
		case G_KBEAM_OUT_OF_TIME:
		case G_KCUT_OUT_OF_TIME:
		case G_KDATA_PROCESSOR_TIMEOUT:
			//g_utility->testtask.Stop(NULL);
			//AfxMessageBox("DATA PROCESSOR TIME OUT.SO TASK IS STOP.");
			break;
			
		case G_KSM_COMND_TIMEOUT:
			//TRY IT AGAIN THEN GIVE A MESSAGE BOX
			//g_utility->smtask.Stop(NULL);
			break;		
		case G_KRADAR_IS_INOPERATIVE:
			//g_utility->testtask.Stop(NULL);
			break;
			
		case G_KGENERATE_PRODUCT_TIMEOUT:
			
			break;
			
		case G_KWAIT_FOR_INTR_TIMEOUT:
			//g_utility->testtask.Stop(NULL);
			break;
			
		default:
			
			break;
		}
	}
    return;
}
//////////////////////////////////////////////////////////////////////
//SET ALARM AND SET FALG INTO THE ALARM TABLE
//////////////////////////////////////////////////////////////////////
void AlarmProcess::SetAlarm(SM_REPORT sm_report, int AlarmId){
	if(global_advance.alarmsetting.nLevel[AlarmId]){
		//IF NEED TO REPORT IT . SET BY ADAPTORS.
		alarmTable.ALRAMFLAG[AlarmId] = true;
		nCurAlarmId = sm_report;
		nIdOfAlarm = AlarmId;
		SetEvent(h_eAlarmComming);
	}
	return;
}

//////////////////////////////////////////////////////////////////////
//SHOW THE ALARM
//////////////////////////////////////////////////////////////////////
void AlarmProcess::ShowAlarm()
{
	//nAlarmCount = 0;
    CAlarmShowDlg dlg;
	BOOL bFoundAlarm = FALSE;
	int nAlarmCount = 0;

	for(int i=0; i<TOTAL_ALARNUM; i++){
		if(alarmTable.ALRAMFLAG[i]){
			CString str_Alarm;		
			alarmTable.alarm_map.Lookup(i, str_Alarm);
			BOOL b_serious = (global_advance.alarmsetting.nLevel[i]==LEVEL_HIGH) | bSeriousTable[i];
			dlg.AddAlarm(nAlarmCount,b_serious,i,str_Alarm);
			bFoundAlarm = TRUE;
			++nAlarmCount;
		}
	}
	if(bFoundAlarm){
		dlg.DoModal();
	}
}