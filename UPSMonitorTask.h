// UPSMonitorTask.h: interface for the CUPSMonitorTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPSMONITORTASK_H__C81F5BD7_D831_4FCA_882D_C1CF9AD31ED3__INCLUDED_)
#define AFX_UPSMONITORTASK_H__C81F5BD7_D831_4FCA_882D_C1CF9AD31ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

class CWPR_UTILITIESDlg;
class CUPSMonitorTask : public CThread  
{
public:
	CUPSMonitorTask();
	virtual ~CUPSMonitorTask();

public:
	DWORD Run(void* pParam);
	DWORD Stop(void* pParam);
	void SetParent(CWPR_UTILITIESDlg* pWindow);
private:
	void Parse();
	CWPR_UTILITIESDlg* g_utility;
};

#endif // !defined(AFX_UPSMONITORTASK_H__C81F5BD7_D831_4FCA_882D_C1CF9AD31ED3__INCLUDED_)
