// DataProcessTask.h: interface for the CDataProcessTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAPROCESSTASK_H__DFB67648_E931_4C99_B865_DFEAB65CA9FD__INCLUDED_)
#define AFX_DATAPROCESSTASK_H__DFB67648_E931_4C99_B865_DFEAB65CA9FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

class CDataProcessTask : public CThread  
{
public:
	CDataProcessTask();
	virtual ~CDataProcessTask();
    DWORD Run(void* pParam);
	DWORD Stop(void* pParam);

public:
    HANDLE hEventDataFinished;
};

#endif // !defined(AFX_DATAPROCESSTASK_H__DFB67648_E931_4C99_B865_DFEAB65CA9FD__INCLUDED_)
