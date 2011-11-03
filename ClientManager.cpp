#include "stdafx.h"
#include "Server.h"
#include "ClientManager.h"
#include "ClientContext.h"

CClientManager * CClientManager::m_pClientMgr = NULL;
CClientManager::CClientManager()
{
	m_pClientMgr = NULL; 
}

CClientManager::~CClientManager()
{
	
}

CClientManager * CClientManager::GetClientManager( void )
{
	return (m_pClientMgr == NULL)? m_pClientMgr = new CClientManager:m_pClientMgr;
}

void CClientManager::AddClient( CClientContext *pClient )
{
	
	m_clientList.AddTail(pClient);
}


void CClientManager::DeleteClient( CClientContext *pClient )
{
	m_cs.Lock();
	POSITION pos1 = NULL;
	POSITION pos2 = NULL;
	for (pos1 = m_clientList.GetHeadPosition(); (pos2 = pos1) != NULL;)
	{
		CClientContext *pClientCText = (CClientContext*)m_clientList.GetNext(pos1);
		if (pClient == pClientCText)
		{
			m_clientList.RemoveAt(pos2);
			delete pClientCText;
			pClientCText = NULL;
		}		
	}
	m_cs.Unlock();
}

void CClientManager::DeleteAllClient( void )
{
	m_cs.Lock();

	POSITION pos = NULL;
	for (pos = m_clientList.GetHeadPosition(); pos != NULL;)
	{
		CClientContext *pClient = (CClientContext*)m_clientList.GetNext(pos);
		delete pClient;
		pClient = NULL;
	}
	m_clientList.RemoveAll();
	m_cs.Unlock();
}


void CClientManager::ReleaseManager( void )
{
	if (NULL != m_pClientMgr)
	{
		delete m_pClientMgr;
		m_pClientMgr = NULL;
	}
	
}

void CClientManager::ProcessIO( CClientContext* pClient, 
							   LPOVERLAPPED pOverlapped, DWORD dwIOSize)
{
	PIO_OPERATION_DATA pIO = CONTAINING_RECORD(pOverlapped,	
												IO_OPERATION_DATA,
												overlapped);
	if (NULL != pIO)
	{
		switch(pIO->type)
		{
		case IOReadHead:
			{
				pClient->OnRecvHeadCompleted(dwIOSize);
				break;				
			}
		case IOReadBody:
			{
				pClient->OnRecvBodyCompleted(dwIOSize);
				break;				
			}			
		case IOWriteData:
			{
				pClient->OnSendCompleted(dwIOSize);
				break;
			}
		case IOEXIT:
			{
				DeleteClient(pClient);
				break;
			}
		default:break;
		}		
	}
}