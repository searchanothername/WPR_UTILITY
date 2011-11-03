// StatusMonitorWatch.h: interface for the CStatusMonitorWatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSMONITORWATCH_H__84F70293_EB0E_4354_BA49_631A6183EFD3__INCLUDED_)
#define AFX_STATUSMONITORWATCH_H__84F70293_EB0E_4354_BA49_631A6183EFD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

class CStatusMonitorWatch : public CThread  
{
public:
	CStatusMonitorWatch();
	virtual ~CStatusMonitorWatch();

};

#endif // !defined(AFX_STATUSMONITORWATCH_H__84F70293_EB0E_4354_BA49_631A6183EFD3__INCLUDED_)
