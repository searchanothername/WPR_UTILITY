// AlarmProcess.h: interface for the AlarmProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMPROCESS_H__6F4A24DA_038B_4904_AAD4_8501348C4D8C__INCLUDED_)
#define AFX_ALARMPROCESS_H__6F4A24DA_038B_4904_AAD4_8501348C4D8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "Global_Advanced.h"
#include <afxtempl.h>

//////////////////////////////////////////////////////////////////////	
//THIS CLASS IS TO STORE ALL THE ALRAMS
//////////////////////////////////////////////////////////////////////
class AlarmTable{
public:
	AlarmTable();
	virtual ~AlarmTable();
    void GetAlarm(int nAlarmClass, const int& nAlramId, CString& AlarmName);
    void ReportAlarm();
public:
    int ALARM_OFFSET[TOTAL_ALARM_CLASS];
	CString   ALARMNAME[TOTAL_ALARNUM];
	bool      ALRAMFLAG[TOTAL_ALARNUM];
    CMap<int, int&, CString, LPCTSTR> alarm_map;
};


//////////////////////////////////////////////////////////////////////	
//THIS CLASS IS TO PROCESS THE ALRAMS 
//////////////////////////////////////////////////////////////////////
class CWPR_UTILITIESDlg;
class AlarmProcess : public CThread  
{
public:
enum SM_REPORT{	PAGE1_ALARM = 0, PAGE1_OK = 1,
				PAGE2_ALARM = 2, PAGE2_OK = 3,
				PAGE3_ALARM = 4, PAGE3_OK = 5,
				PAGE4_ALARM = 6, PAGE4_OK = 7,
				PAGE5_ALARM = 8, PAGE5_OK = 9,
				PAGE6_ALARM = 10, PAGE6_OK = 11,
				PAGE7_ALARM = 12, PAGE7_OK = 13,
				PAGE8_ALARM = 14, PAGE8_OK = 15
				};

public:
	AlarmProcess();
	virtual ~AlarmProcess();
    DWORD Run(void* pParam);
	DWORD Stop(void* pParam);
	void ProcessAlarm();
	void ShowTheAlarmOnTheScreen();
	void ResponseAlarm();
	void SetAlarm(SM_REPORT sm_report, int AlarmId);
	void ShowAlarm();
	void ClearAllAlarm();
	void SetParent(CWPR_UTILITIESDlg* pWindow);

public:
	HANDLE h_eAlarmComming;
    CString str_AlarmClass[TOTAL_ALARM_CLASS*2];
    CWPR_UTILITIESDlg* g_utility;
	SM_REPORT   nCurAlarmId;
	int         nIdOfAlarm;
	AlarmTable  alarmTable;
};


#endif // !defined(AFX_ALARMPROCESS_H__6F4A24DA_038B_4904_AAD4_8501348C4D8C__INCLUDED_)
