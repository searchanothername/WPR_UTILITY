// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__80634621_5D45_4135_BDD8_1BEFBB4BDEF5__INCLUDED_)
#define AFX_THREAD_H__80634621_5D45_4135_BDD8_1BEFBB4BDEF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
DESCRIPTION:
	CREATE A THREAD CLASS TO MANAGE THE THREADS IN OUR PROGRAM.
	BUT I'D NOT LIKE TO USE THE VERSION OF MFC DIRECTLY.
LIUCHEN 2008/1/3
*/
class CThread  
{
    friend DWORD WINAPI ThreadFunction(LPVOID lpParam);
public:
	CThread();
	virtual ~CThread();
	
	BOOL Start(void* pParam = NULL);
	void Exit();
	DWORD GetThreadID();
	HANDLE GetThreadHandle();
	static DWORD GetCurrentThreadID();
	BOOL IsStarted(){return m_bStarted;}

protected:
	virtual DWORD Run(void* pParam){return 0;}
    virtual DWORD Stop(void* pParam){return 0;}
private:
	HANDLE m_hThread;
	DWORD m_nThreadID;
	BOOL m_bStarted;
	void* m_pParam;
};

#endif // !defined(AFX_THREAD_H__80634621_5D45_4135_BDD8_1BEFBB4BDEF5__INCLUDED_)
