#ifndef _CLIENT_CONTEXT_H
#define _CLIENT_CONTEXT_H

#include "Global_Network.h"

class CServer;

class CClientContext :public CObject
{
public:
	enum CLIENT_STAT
	{
		DOING,	//COMPUTING
		DONE,	//FINISH
		DISCON,	//DISCONNECT
		UNKNOWN	//UNKNOWN
	};
public:
	CClientContext(SOCKET s, CServer* pServ);
	virtual ~CClientContext();

public:
	BOOL	AsyncSendData(void);					//SENDING DATA
	void	OnSendCompleted(DWORD dwIOSize);		//FINISH SENDING

	BOOL	AsyncRecvHead( void );					//RECIEVE THE HEADER
	BOOL	AsyncRecvBody(int nLen);				//RECEIVE THE BODY
	void	OnRecvHeadCompleted( DWORD dwIOSize );	//FINISH HEADER COLECTING
	void	OnRecvBodyCompleted( DWORD dwIOSize );	//FINISH BODY COLECTING 
	BOOL	AsyncRecvIOOK(void);					//CLIENT QUIT
	

public:
	IO_OPERATION_DATA	m_iIO;			//IO STRUCT FOR READING
	IO_OPERATION_DATA	m_oIO;			//IO STRUCT FOR WRITTING

	CLIENT_STAT			m_State;         //STAT OF THE CLIENT
	CTime				m_time;			//HEART BEATING TIME
	BOOL				m_bPulse;		//HEARTBEAT

protected:
	SOCKET				m_s;
	CServer*			m_pServer;
};
#endif