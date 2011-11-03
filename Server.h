#ifndef _SERVER_H
#define _SERVER_H

#include "Global_Network.h"
#include "stdafx.h"

class CServer
{
public:
	CServer();
	virtual ~CServer();

public:
	static	DWORD WINAPI acceptThread(void *pParam);
	static	DWORD WINAPI serviceThread(void *pParam);

	void exit();
	void start();
	void setPort(unsigned int port){m_nPort = port;}

public:
	char			m_Data[DATA_BUFFER_SIZE];	
	u_short			m_DataLen;					
	
private:
	BOOL			m_bRunning;	
	HANDLE			m_hCompPort;				
	SOCKET			m_sListen;		
	HANDLE			m_hThread[MAX_SUBTHREAD_SIZE];	
	int				m_nThreadNum;					
	HANDLE			m_hEvent;
    u_short			m_usDataLength;
	unsigned int	m_nPort;
};
#endif