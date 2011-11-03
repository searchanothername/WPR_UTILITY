// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Thread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD WINAPI ThreadFunction(LPVOID lpParam){
	CThread* pThread = (CThread*) lpParam;
	DWORD result = pThread->Run(pThread->m_pParam);
	return result; 
}

CThread::CThread(){
	m_bStarted = FALSE;
}
CThread:: ~CThread(){
	Exit();
}
	
int CThread::Start(void* pParam){
	if(!m_bStarted){
		//if thread is running now. don't create it again.
		m_pParam = pParam;
		m_hThread = CreateThread(NULL,0,ThreadFunction,this,0,&m_nThreadID);

		if(m_hThread == NULL)
			CloseHandle(m_hThread);
		m_bStarted = TRUE;
	}
	return m_bStarted;
}

void CThread::Exit(){

	if(m_bStarted){
		if(m_hThread){
			TerminateThread(m_hThread,m_nThreadID);
			CloseHandle(m_hThread);
		}
		m_bStarted = FALSE;
	}

	//if(m_bStarted){
	//	DWORD dwExitCode = STILL_ACTIVE;
	//	BOOL  bStat = TRUE;
	//	while((dwExitCode == STILL_ACTIVE) && bStat)
	//		bStat =  GetExitCodeThread(m_hThread, &dwExitCode);
	//}


}

HANDLE CThread::GetThreadHandle(){
	return m_hThread;
}
DWORD CThread::GetThreadID(){
	return m_nThreadID;
}

static DWORD GetCurrentThreadID(){
	return GetCurrentThreadId();
}
