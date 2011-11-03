// StatusMonitorTaskWatch.h: interface for the CStatusMonitorTaskWatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSMONITORTASKWATCH_H__B2DE688E_117E_4DE7_A3E5_50A659D8151A__INCLUDED_)
#define AFX_STATUSMONITORTASKWATCH_H__B2DE688E_117E_4DE7_A3E5_50A659D8151A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

class CStatusMonitorTaskWatch : public CThread  
{
public:
	CStatusMonitorTaskWatch();
	virtual ~CStatusMonitorTaskWatch();

};

#endif // !defined(AFX_STATUSMONITORTASKWATCH_H__B2DE688E_117E_4DE7_A3E5_50A659D8151A__INCLUDED_)
