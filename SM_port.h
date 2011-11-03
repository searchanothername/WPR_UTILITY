#ifndef _SM_PORT_H
#define _SM_PORT_H

#include "afxmt.h"
#include "process.h"

UINT  readcomm(LPVOID lpParam);
UINT  writecomm(LPVOID lpParam);
UINT  writecomm_rss(LPVOID lpParam);

//FOR NEW FREQ GENERATOR
UINT  writecomm_sg(LPVOID lpParam);
UINT  read_alarm_of_signalgenerator(LPVOID lpParam);

//FOR UPS CONTROL
UINT writecomm_ups(LPVOID lpParam);
UINT read_ups_status(LPVOID lpParam);

#define RxBuffer	4096
#define TxBuffer	4096
#define ReadInterval	2
#define ReadTotal		55
#define WriteMulti		2
#define WriteTotal		4

class CSM_Port
{
	friend UINT writecomm(LPVOID lpParam);
    friend UINT writecomm_rss(LPVOID lpParam);
	friend UINT writecomm_sg(LPVOID lpParam);
    friend UINT read_alarm_of_signalgenerator(LPVOID lpParam);
	friend UINT writecomm_ups(LPVOID lpParam);
	friend UINT read_ups_status(LPVOID lpParam);

public:
	CSM_Port(char* str_com,unsigned int baudrate,char parity, unsigned int bytenum ):
	      com_name(str_com),
		  m_baudrate(baudrate),
		  m_parity(parity),
		  b_IsConfig(FALSE),
		  m_nByteNum(bytenum){}

	CSM_Port():com_name("COM1"),b_IsConfig(FALSE){}

	~CSM_Port(){closecomm();}

	int configcomm(char* str_com,unsigned int baudrate,char parity,unsigned int bytenum)
	{
		DCB dcb;
		CString str; 
        COMMTIMEOUTS TimeOuts;
		BOOL fSuccess;
		
		TimeOuts.ReadIntervalTimeout=ReadInterval; 
		TimeOuts.ReadTotalTimeoutMultiplier=0; 
		TimeOuts.ReadTotalTimeoutConstant=ReadTotal; 
	
		m_hCom = CreateFile(str_com,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if(m_hCom==INVALID_HANDLE_VALUE)
		{
			str.Format("Can't open %s",str_com);
			AfxMessageBox(str);
			b_IsConfig = FALSE;
			return 0;
		}
		//for com handle is very important so I use ASSERT
		//ASSERT(m_hCom!=INVALID_HANDLE_VALUE);

		fSuccess = SetupComm(m_hCom,RxBuffer,TxBuffer);
		GetCommState(m_hCom,&dcb);
		dcb.BaudRate = baudrate;
		dcb.ByteSize = 8;
		switch (parity%3)
		{
		case 0:
			dcb.Parity = EVENPARITY;
			break;
		case 1:
			dcb.Parity = ODDPARITY;
			break;
		case 2:
			dcb.Parity = NOPARITY;
			break;
		default:
			break;
		}
		//(parity == 1)?ODDPARITY:EVENPARITY;
		
		dcb.StopBits = ONESTOPBIT;
		SetCommState(m_hCom,&dcb);
		
		fSuccess = EscapeCommFunction(m_hCom,CLRDTR);
		fSuccess = EscapeCommFunction(m_hCom,CLRRTS);
		fSuccess = SetCommMask(m_hCom, 
			EV_ERR | EV_CTS | EV_DSR |EV_RXCHAR | EV_TXEMPTY);
		fSuccess = GetCommTimeouts(m_hCom, &TimeOuts);

		TimeOuts.ReadIntervalTimeout = ReadInterval;
		TimeOuts.ReadTotalTimeoutMultiplier = 0;
		TimeOuts.ReadTotalTimeoutConstant = ReadTotal;
		TimeOuts.WriteTotalTimeoutMultiplier = WriteMulti;
		TimeOuts.WriteTotalTimeoutConstant = WriteTotal;
		
		// Set the read and write timeout intervals 
		fSuccess = SetCommTimeouts(m_hCom, &TimeOuts);
		fSuccess = PurgeComm(m_hCom,PURGE_TXABORT | PURGE_RXABORT |
			PURGE_TXCLEAR | PURGE_RXCLEAR );

		if(fSuccess)
		   b_IsConfig = TRUE;

		m_nByteNum = bytenum;

		return 1;
	}

	int closecomm()
	{
		b_IsConfig = FALSE;
		if(m_hCom)
			CloseHandle(m_hCom);
		return 0;
	}

	BOOL isconfiged(){return b_IsConfig;}

private:
	char* com_name;
	HANDLE m_hCom;
	BOOL b_IsOpen;
	BOOL b_IsConfig;
	CMutex sMutex;
	unsigned int m_baudrate;
	char m_parity;
	unsigned int m_nByteNum;

};

#endif