// ServerTask.cpp: implementation of the CServerTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "ServerTask.h"
#include "Global.h"
#include "DataProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern int  g_nSpectraCount;


CServerTask::CServerTask()
{

}

CServerTask::~CServerTask()
{

}

DWORD CServerTask::Run(void* pParam)
{
	if(global.cs_network.IsOn())
	{
		_server.start();
	};
	return 0;
}

DWORD CServerTask::Stop(void* pParam)
{
	global.cs_network.TurnOff();
	_server.exit();
	this->Exit();
	return 0;
}

void CServerTask::setPort(unsigned int port)
{
	_server.setPort(port);
}