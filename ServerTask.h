// ServerTask.h: interface for the CServerTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERTASK_H__39524181_77C5_44B4_BBBF_745CBE51082F__INCLUDED_)
#define AFX_SERVERTASK_H__39524181_77C5_44B4_BBBF_745CBE51082F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "Server.h"

class CServerTask : public CThread  
{
public:
	CServerTask();
	virtual ~CServerTask();
	
public:
	DWORD Run(void* pParam);
	DWORD Stop(void* pParam);
    void setPort(unsigned int port);

private:
	CServer _server;
};

#endif // !defined(AFX_SERVERTASK_H__39524181_77C5_44B4_BBBF_745CBE51082F__INCLUDED_)
