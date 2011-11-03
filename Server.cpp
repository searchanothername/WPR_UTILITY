#include "StdAfx.h"
#include "server.h"
#include "ClientContext.h"
#include "ClientManager.h"

CServer::CServer()
:m_sListen(INVALID_SOCKET),	
m_hCompPort(NULL),		
m_bRunning(FALSE),			
m_nThreadNum(0),
m_usDataLength(0)				
{
	ZeroMemory(m_hThread, MAX_SUBTHREAD_SIZE);
}

CServer::~CServer()
{
	exit();
}

DWORD WINAPI CServer::acceptThread(void *pParam)
{
	CServer	*pServ= (CServer*)pParam;	
	HANDLE	hComPort = pServ->m_hCompPort;	
	SOCKET	sListen = pServ->m_sListen;	
	SOCKET	sAccept = INVALID_SOCKET;
	while(pServ->m_bRunning)
	{
		DWORD dwRet;
		dwRet = WSAWaitForMultipleEvents(1,		
										&pServ->m_hEvent,
										FALSE,
										100,
										FALSE);		
		if(!pServ->m_bRunning)				
			break;
		
		if (dwRet == WSA_WAIT_TIMEOUT)	
			continue;
		
		WSANETWORKEVENTS events;					
		int nRet = WSAEnumNetworkEvents(pServ->m_sListen,
										pServ->m_hEvent,
										&events);		
		if (nRet == SOCKET_ERROR)
		{
			AfxMessageBox(_T("WSAEnumNetworkEvents() failed"));
			break;
		}

		if ( events.lNetworkEvents & FD_ACCEPT)	
		{
			if ( events.iErrorCode[FD_ACCEPT_BIT] == 0 && pServ->m_bRunning)
			{
				
				SOCKADDR_IN servAddr;
				int	serAddrLen = sizeof(servAddr);	   
				if ((sAccept = WSAAccept(sListen, 
										(SOCKADDR*)&servAddr,
										&serAddrLen,
										NULL, 
										0)) == SOCKET_ERROR)
				{
					AfxMessageBox(_T("WSAAccept() failed"));
					break;
				}
			
				CClientContext *pClient = new CClientContext(sAccept,pServ);				
				
				if (CreateIoCompletionPort((HANDLE)sAccept,	
											hComPort,
											(DWORD) pClient,
											0) == NULL)
				{
					return -1;
				}
	
				CClientManager *pClientMgr = CClientManager::GetClientManager();
				pClientMgr->AddClient(pClient);
				
				if(!pClient->AsyncRecvHead())
				{
					pClientMgr->DeleteClient(pClient);
				}				
			}
		}		
	}

	CClientManager *pClientMgr = CClientManager::GetClientManager();
	pClientMgr->DeleteAllClient();
	pClientMgr->ReleaseManager();

	return 0;
}

//SERVE THE CLIENT
DWORD WINAPI CServer::serviceThread(void *pParam)
{

	CServer	*pServ = (CServer*)pParam;	
	DWORD			dwIoSize;	
	CClientContext	*pClient;	
	LPOVERLAPPED	lpOverlapped;	
	bool			bExit = FALSE;
	while (!bExit)
	{
		dwIoSize = -1;
		lpOverlapped = NULL;
		pClient = NULL;
		
		BOOL bIORet = GetQueuedCompletionStatus(pServ->m_hCompPort,
												&dwIoSize,
												(LPDWORD) &pClient,
												&lpOverlapped,
												INFINITE);
		if (FALSE == bIORet && NULL != pClient)
		{	
			if (CClientContext::DOING == pClient->m_State)
			{
				pClient->m_State = CClientContext::DISCON;
			}
			CClientManager *pClientMgr = CClientManager::GetClientManager();
			pClientMgr->DeleteClient(pClient);				
		}

		if(bIORet && lpOverlapped && pClient) 
		{				
			CClientManager *pClientMgr = CClientManager::GetClientManager();
			pClientMgr->ProcessIO(pClient, lpOverlapped, dwIoSize);				
		}	
	
		if(pClient == NULL && lpOverlapped ==NULL && (pServ->m_bRunning==0))
		{
			bExit = TRUE;
		}		
	}
	return 0;
}


void CServer::start()
{
	int	reVal;				

	//INITIALIZE THE SOCKET
	WSADATA wsaData;	
	if ((reVal = WSAStartup(0x0202, &wsaData)) != 0)
	{
		AfxMessageBox(_T("Initialize the socket dll failed!"));
		return ;
	}
	
	//CREATE SOCKET 
	if ((m_sListen = WSASocket(AF_INET,
								SOCK_STREAM,
								0,
								NULL, 
								0,
								WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Create socket failed!"));
		WSACleanup();
		return ;
	} 

	//BIND THE SOCKET
	SOCKADDR_IN	servAddr;//SERVER ADDRESS
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(m_nPort);	
	if (bind(m_sListen, (SOCKADDR*)&servAddr, sizeof(servAddr)) 
											== SOCKET_ERROR)
	{
		AfxMessageBox(_T("Bind the socket failed!"));
		closesocket(m_sListen);
		WSACleanup();
		return ;
	}
	
	//LISTENING
	if(listen(m_sListen, SOMAXCONN) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("Listen the socket failed!"));
		closesocket(m_sListen);
		WSACleanup();
		return ;
	}
	
	m_bRunning = TRUE;	//RUN THE SERVER
	
	//CREATE EVENT FOR CLIENT COMMING
	m_hEvent = WSACreateEvent();
	if ( m_hEvent == WSA_INVALID_EVENT )
	{	
		closesocket(m_sListen);
		WSACleanup();
		return ;
	}
	
	//REGISTER THE FD_ACCEPT EVENT
	int nRet = WSAEventSelect(m_sListen,
								m_hEvent,
								FD_ACCEPT);	
	if ( nRet == SOCKET_ERROR )
	{
		AfxMessageBox(_T("Record the network event failed!"));
		closesocket(m_sListen);
		WSACleanup();
		return ;
	}
	
	// CREATE IOCP
	if ((m_hCompPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		AfxMessageBox(_T("Create IOCP failed!"));
		WSACloseEvent(m_hEvent);
		closesocket(m_sListen);
		WSACleanup();
		return ;
	}
	
	//CREATE THEREAD FOR HANDLING THE REQUEST OF CLIENT.
	DWORD dwThreadID;
	m_hThread[0] = CreateThread(NULL, 
								0,
								acceptThread,
								this, 
								0,  
								&dwThreadID);
	if (NULL == m_hThread[0])
	{
		AfxMessageBox(_T("Create client thread failed!"));
		WSACloseEvent(m_hEvent);
		closesocket(m_sListen);
		WSACleanup();
		return;
	}
	m_nThreadNum = 1;
	
	// GET THE NUMBER OF CPU
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	
	// CREATE SERVICE FOR CLIENT
	for(int i = 0; i < SystemInfo.dwNumberOfProcessors * 2; i++)
	{
		if ((m_hThread[m_nThreadNum++] = CreateThread(NULL, 
														0,
														serviceThread,
														this,
														0, 
														&dwThreadID)) == NULL)
		{
			AfxMessageBox(_T("Create server thread failed!"));
			WSACloseEvent(m_hEvent);
			closesocket(m_sListen);
			WSACleanup();
			return ;
		}
		
	}

	::WaitForMultipleObjects(m_nThreadNum, m_hThread, TRUE, INFINITE);
	return;
}

void CServer::exit()
{
	if (TRUE == m_bRunning)
	{
		m_bRunning = FALSE;
		for (int i = 0; i < m_nThreadNum ; i++)
		{
			CloseHandle(m_hThread[i]);
			if (i < m_nThreadNum -1)
			{
				//SEND THE QUIT MESSAGE
				PostQueuedCompletionStatus(m_hCompPort, 0, (DWORD) NULL, NULL);	
			}
		}
		//WAIT THE SUB THREAD FINISHED
		::WaitForMultipleObjects(m_nThreadNum, m_hThread, TRUE, INFINITE);


		closesocket(m_sListen);		//CLOSE THE LISTENING
		WSACloseEvent(m_hEvent);	
		WSACleanup();			
		CloseHandle(m_hCompPort);	
	}
	return;
}
