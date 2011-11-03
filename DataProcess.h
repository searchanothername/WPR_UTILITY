// DataProcess.h: interface for the CDataProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAPROCESS_H__8EAA6303_BB35_4877_B83A_EC18236A8CBD__INCLUDED_)
#define AFX_DATAPROCESS_H__8EAA6303_BB35_4877_B83A_EC18236A8CBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "Global_CtrlWords.h"
#include "Global.h"
#include "DataHandlor.h"
//#define SIMULATE 

class CWPR_UTILITIESDlg;
class ServerTask;

class CDataProcess : public CThread  
{
	friend void CALLBACK TimeProc(UINT	IDEvent,
					  UINT  uReserved,
					  DWORD dw1,
					  DWORD dw2,
					  DWORD dw3);
	friend class ServerTask;
public:

	CDataProcess();
	virtual ~CDataProcess();
    DWORD Run(void* pParam);
	DWORD Stop(void* pParam);
    void DownLoadCtrlWords(control_word_0_6& g_controlwords);
	void GetOneBeamData();
	void DataProcess();
    void UploadData();
	void TestProcess();
	void OperateProcess();
    void SetParent(CWPR_UTILITIESDlg* pWindow);

public:

	static HANDLE h_eCtrlWordsDownloaded;
	static HANDLE h_eSingleSpectraFinished;
	static HANDLE h_eSingleSpectraSending;
	static HANDLE h_eTotalSpectrasFinished;
    static HANDLE h_eSpectraDataProcessed;
	static HANDLE h_eSpectraDataProcessedResponse;
	static HANDLE h_eBeamDataProcessed;
	static HANDLE h_eBeamDataProcessedResponse;
	static HANDLE h_eInterrupt[2];
	//BOOL   b_CommunicationSel;

	CWPR_UTILITIESDlg* _utility;

};

#endif // !defined(AFX_DATAPROCESS_H__8EAA6303_BB35_4877_B83A_EC18236A8CBD__INCLUDED_)
