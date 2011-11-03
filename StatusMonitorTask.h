// StatusMonitorTask.h: interface for the CStatusMonitorTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSMONITORTASK_H__084D4832_D56E_4B19_A637_C86281775C4A__INCLUDED_)
#define AFX_STATUSMONITORTASK_H__084D4832_D56E_4B19_A637_C86281775C4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
//STATUS MONITOR TASK IS TO CONTROL STATUS MONITOR.
//IT ACQUIRE THE STATUS OF OUR SYSTEM AND SEND COMMAND TO THE HARDWARE TO 
//CONTROL 10 HPA OF TX.
//YOU CAN START OR STOP IT AT ANY TIME. AND YOU ALSO CAN MONITOR THE STATUS
//AT THE ALEXANDRA'S TOP PLATFORM. TOTALLY 62 BYTES RECEIVED FROM SERIAL 
//PORT WILL BE LISTED. BY CLICK MENU ITEM 'STATUS MONITOR' YOU WILL SEE
//ALL STATUS OF OUR SYSTEM.
//////////////////////////////////////////////////////////////////////


#include "Thread.h"
#include "AlarmProcess.h"
#include "Global.h"

#define MAX_MESSAGE_SIZE 100+1
class CWPR_UTILITIESDlg;

class CStatusMonitorTask : public CThread  
{
public:
	CStatusMonitorTask();
	virtual ~CStatusMonitorTask();
public:
    DWORD Run(void* pParam);
	DWORD Stop(void* pParam);
	void SendDataToMainDlg();
	void SendDataToBITEX();  //LIUChen add it 2011/5/17
	void SearchStatus(void* ps);
	CWPR_UTILITIESDlg* g_utility;
	void SetParent(CWPR_UTILITIESDlg* pWindow);
	void TurnOnHPAForEachBeam(const int nCurrentBeam);
	void SetSingleHPA(const int HPANUM, const BOOL bOpen);
	void MakeHPAParamForEachBeam();
	STATUS_EVL checkSingleBit(STATUS_ITEM_INFO&_status_info, unsigned char Byte, unsigned char Bit);
    STATUS_EVL checkDualByte(STATUS_ITEM_INFO&_status_info, unsigned char hByte, unsigned char lByte);
    STATUS_EVL checkMultiBit(STATUS_ITEM_INFO&_status_info, unsigned char Byte, unsigned char hBit, unsigned char lBit); 

private:
	void Scale();
	void CheckVal(float val, int id);
	void CheckStat(bool bError,int level,CString strInfo);

	unsigned char* _bytes;
	HANDLE h_bite;
	int _integer;
	int _decimal;
	STATUS_ITEM_INFO_BIN _status_info_send;
};


#endif // !defined(AFX_STATUSMONITORTASK_H__084D4832_D56E_4B19_A637_C86281775C4A__INCLUDED_)
