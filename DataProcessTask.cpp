// DataProcessTask.cpp: implementation of the CDataProcessTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "DataProcessTask.h"
#include "time.h"
#include "mmsystem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "Global.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//FIRST I WANT TO USE A TIMER TO SIMULATE THE WHOLE DATA PROCESS
typedef struct userinfo{
	int info;
}USERINFO;
void CALLBACK timer_simulate_intr(UINT	IDEvent,
								  UINT uReserved,
								  CDataProcessTask* p_dptask,
							      DWORD dwReserved1,
								  DWORD dwReserved2);
UINT IDEvent;
CDataProcessTask::CDataProcessTask()
{
	hEventDataFinished = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CDataProcessTask::~CDataProcessTask()
{
     this->Stop(NULL);
}

DWORD CDataProcessTask::Run(void* pParam){
	//I use a timer to simulate the data acquire.
	IDEvent = timeSetEvent(2000,
				 1, //resolution in millionsecond
				(LPTIMECALLBACK)timer_simulate_intr,
				(DWORD)(this), //the pointer to ANTENNA(3)
				TIME_PERIODIC); 

	while(global.cs[DP_TASK_ID].IsOn()){
		WaitForSingleObject(hEventDataFinished,2000);
        
	    global.flg[DP_TASK_ID].Up();//FINISH A BEAM SHOULD NOTE THE MAIN TASK
	};

	return 1;
}

DWORD CDataProcessTask::Stop(void* pParam){
	if(hEventDataFinished)
		CloseHandle(hEventDataFinished);
    timeKillEvent(IDEvent);
	return 1;
}


/////////////////////////////////////////////////////////////
//FIRST I WANT TO USE A TIMER TO SIMULATE THE WHOLE DATA PROCESS
void CALLBACK timer_simulate_intr(UINT	IDEvent,
								  UINT uReserved,
								  CDataProcessTask* p_dptask,
							      DWORD dwReserved1,
								  DWORD dwReserved2)
{
	 srand( (unsigned)time( NULL ) );
     for(int i = 0; i < 41;i++ )
		 global.g_Data[i] = rand()%100;
	  SetEvent(p_dptask->hEventDataFinished);
}
