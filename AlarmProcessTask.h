// AlarmProcessTask.h: interface for the AlarmProcessTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMPROCESSTASK_H__288A2BB9_AB3E_4BF3_9410_6FCBF655C385__INCLUDED_)
#define AFX_ALARMPROCESSTASK_H__288A2BB9_AB3E_4BF3_9410_6FCBF655C385__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

class AlarmProcessTask : public CThread  
{
public:
	AlarmProcessTask();
	virtual ~AlarmProcessTask();

};

#endif // !defined(AFX_ALARMPROCESSTASK_H__288A2BB9_AB3E_4BF3_9410_6FCBF655C385__INCLUDED_)
