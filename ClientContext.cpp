#include "stdafx.h"
#include "ClientContext.h"
#include "Server.h"
#include "Global_Network.h"

CClientContext::CClientContext(SOCKET s, CServer* pServ)
:m_s(s),
m_State(CClientContext::UNKNOWN),
m_pServer(pServ),
m_bPulse(FALSE)
{
	ZeroMemory(&m_iIO, OVERLAPPEDPLUSLEN);
	ZeroMemory(&m_oIO, OVERLAPPEDPLUSLEN);

}

CClientContext::~CClientContext()
{
	CancelIo((HANDLE)m_s);
	closesocket(m_s);
	m_pServer = NULL;
}

/*
********************************************************
* SEND THE DATA
********************************************************
*/
BOOL CClientContext::AsyncSendData( void )
{
	DWORD	flags = 0;			
	DWORD	sendBytes =0;		
	
	ZeroMemory(&m_oIO, OVERLAPPEDPLUSLEN);
	m_oIO.type = IOWriteData;	

	WSABUF wsaBuf[2];
	m_oIO.hdr.ustype = TYPE_DATA;						
	m_oIO.hdr.usLen = m_pServer->m_DataLen;

	wsaBuf[0].buf = (char*)&m_oIO.hdr;			
	wsaBuf[0].len = HEADELEN;

	wsaBuf[1].buf = m_pServer->m_Data;		
	wsaBuf[1].len = m_pServer->m_DataLen;

	//SENDING
	if (WSASend(m_s, 
				wsaBuf,
				2, 
				&sendBytes, 
				flags,
				&m_oIO.overlapped,
				NULL) == SOCKET_ERROR)
	{
		if(ERROR_IO_PENDING != WSAGetLastError())
		{
			return FALSE;
		}
	}	
	return TRUE;
}

/*
********************************************************
* RECEIVE THE DATA
********************************************************
*/
BOOL CClientContext::AsyncRecvHead( void )
{
	DWORD	flags = 0;		
	DWORD	recvBytes =0;	

	ZeroMemory(&m_iIO, OVERLAPPEDPLUSLEN);
	m_iIO.type = IOReadHead;

	WSABUF wsaBuf;
	wsaBuf.buf = (char*)&m_iIO.hdr;	
	wsaBuf.len = HEADELEN;			
	
	//READING
	if (WSARecv(m_s, 
				&wsaBuf,
				1, 
				&recvBytes, 
				&flags,
				&m_iIO.overlapped,
				NULL) == SOCKET_ERROR)
	{
		if(ERROR_IO_PENDING != WSAGetLastError())
		{
			return FALSE;
		}
	}	
	return TRUE;	
}

/*
********************************************************
* FINISH THE HEADER READING
********************************************************
*/
void CClientContext::OnRecvHeadCompleted( DWORD dwIOSize )
{
	if (TYPE_HEARTBEAT == m_iIO.hdr.ustype)			//PROCESS THE HEARTBEAT
	{	
		m_bPulse = TRUE;					//HEARTBEAT COMMING
		m_time = CTime::GetCurrentTime();	//TIME
		AsyncRecvHead();					//CONTINUE RECEIVING
	}
	else
	{
		AsyncRecvBody(m_iIO.hdr.usLen);
	}
	return;
}

/*
********************************************************
* FINISH THE SENDING 
********************************************************
*/
void CClientContext::OnSendCompleted( DWORD dwIOSize )
{
	return;
}

/*
********************************************************
* EXIT
********************************************************
*/
BOOL CClientContext::AsyncRecvIOOK(void) 
{
	DWORD	flags = 0;	
	DWORD	recvBytes =0;

	ZeroMemory(&m_iIO, OVERLAPPEDPLUSLEN);
	m_iIO.type = IOEXIT;				

	WSABUF wsaBuf;
	wsaBuf.buf = (char*)&m_iIO.hdr;	
	wsaBuf.len = HEADELEN;

	//READING
	if (WSARecv(m_s, 
				&wsaBuf,
				1, 
				&recvBytes, 
				&flags,
				&m_iIO.overlapped,
				NULL) == SOCKET_ERROR)
	{
		if(ERROR_IO_PENDING != WSAGetLastError())
		{
			return FALSE;
		}
	}	
	return TRUE;	
}


/*
********************************************************
* RECEIVING BODY
********************************************************
*/
BOOL CClientContext::AsyncRecvBody(int nLen )
{
	DWORD	flags = 0;			
	DWORD	recvBytes =0;	
	
	ZeroMemory(&m_iIO, OVERLAPPEDPLUSLEN);
	m_iIO.type = IOReadBody;	
	
	WSABUF wsaBuf;	
	wsaBuf.buf = m_iIO.recvBuf;	
	wsaBuf.len = nLen;		

	//READING
	if (WSARecv(m_s, 
				&wsaBuf,
				1, 
				&recvBytes, 
				&flags,
				&m_iIO.overlapped,
				NULL) == SOCKET_ERROR)
	{
		if(ERROR_IO_PENDING != WSAGetLastError())
		{
			return FALSE;
		}
	}	

	return TRUE;	
}

/*
********************************************************
* FINISH THE BODY RECEIVING
********************************************************
*/
void CClientContext::OnRecvBodyCompleted( DWORD dwIOSize )
{
	return;
}
