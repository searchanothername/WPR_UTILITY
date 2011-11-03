// TestTask.h: interface for the CTestTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTTASK_H__B9C6C99D_38CD_4E3A_90B3_7F8B996D8557__INCLUDED_)
#define AFX_TESTTASK_H__B9C6C99D_38CD_4E3A_90B3_7F8B996D8557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
///////////////////////////////////////////////////////////////////////
//TEST TASK IS TO CONTROL WHOLE SYSTEM BY DOWNLOADING PARAMETERS TO 
//SPS.AND THE PARAMETERS CAN BE SET BY USER. SOME IMPORTANT PARAMETERS
//ARE STORED AT 'BASIC SETTING'.
//THIS TASK IS NOT A INDEPEND TASK. IT CALL TASK 'DATA PROCESS' TO COMMUNICATE
//WITH SPS.
///////////////////////////////////////////////////////////////////////

#include "Thread.h"
#include "DataProcess.h"
class CWPR_UTILITIESDlg;
class CTestTask : public CThread  
{
public:
	CTestTask();
	virtual ~CTestTask();
    DWORD Run(void* pParam);
	DWORD Stop(void* pParam);
	void SendDataToMainDlg();
	void ProcessBeamCycle();

public:
	CDataProcess dp_task;
	int m_StartBeamNum;
	CWPR_UTILITIESDlg* g_utility;
	void SetParent(CWPR_UTILITIESDlg* pWindow);
};

#endif // !defined(AFX_TESTTASK_H__B9C6C99D_38CD_4E3A_90B3_7F8B996D8557__INCLUDED_)
