#ifndef _CLIENT_MANAGER_H
#define _CLIENT_MANAGER_H

class CClientContext;

class CClientManager : public CObject  
{
public:
	virtual ~CClientManager();
public:
	static CClientManager *GetClientManager(void);	
	static void ReleaseManager(void);				

	void	ProcessIO(CClientContext* pClient,		
			LPOVERLAPPED pOverlapped, DWORD dwIOSize);
	void	AddClient(CClientContext *pClient);	
	void	DeleteClient(CClientContext *pClient);	
	void	DeleteAllClient(void);				

	
public:
	CObList	m_clientList;						
private:
	CClientManager();
	CClientManager(const CClientManager& other);
	CClientManager& operator = (CClientManager &other);
	static CClientManager *m_pClientMgr;
	CCriticalSection m_cs;					
};
#endif