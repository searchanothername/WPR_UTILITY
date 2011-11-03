// TestTask.cpp: implementation of the CTestTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "WPR_UTILITIESDlg.h"
#include "TestTask.h"
#include <time.h>
#include "Global.h"
#include "Global_CtrlWords.h"
#include "Global_SM.h"
#include "WPRDriverlib.h"
#include "A44_sm_handler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CWPR_UTILITIESDlg* g_utility;
extern int  g_nSpectraCount ;
//FOR COMMUNICATE WITH THIERRY
CTestTask::CTestTask()
{
}

CTestTask::~CTestTask()
{
	this->Stop(NULL);
}

void CTestTask::SetParent(CWPR_UTILITIESDlg* pWindow)
{
	g_utility = pWindow;
	dp_task.SetParent(pWindow);
}

DWORD CTestTask::Run(void* pParam){
    
		
	//START DP TASK.
	if(dp_task.IsStarted())
		dp_task.Stop(NULL);
	global.cs_dataprocess.TurnOn();
	dp_task.Start();

    while(global.cs_test.IsOn()){
		g_curbeamnum = g_test_strt;
        ProcessBeamCycle();
	}
	return 0;
}

DWORD CTestTask::Stop(void* pParam){

    if(dp_task.IsStarted())
		dp_task.Stop(NULL);
    global.cs_test.TurnOff();

	this->Exit();
	return 0;
}

void CTestTask::ProcessBeamCycle(){

	int j = 0;
	int k = 0;
	unsigned int stat = 0;

	//CONTROL 25M OUTPUT
	dhv_signal_generator_25M(global.basic.basicinfo.b25MCLOSE,stat);

    if(!g_bCycleCtrol){

		//FOR NEW FREQENCE GENERAGOR
		if(g_curbeamnum == VL || g_curbeamnum == VH)
			dhv_signal_generator_beamsel(FALSE, stat);
		else
			dhv_signal_generator_beamsel(TRUE, stat);

		for(j=0; j<g_knumber_of_spectra[g_curbeamnum]; j++){
			WaitForSingleObject(dp_task.h_eSpectraDataProcessed,INFINITE);
			SetEvent(dp_task.h_eSpectraDataProcessedResponse);
		}
		
		WaitForSingleObject(dp_task.h_eBeamDataProcessed,INFINITE);
		SetEvent(dp_task.h_eSpectraDataProcessedResponse);
	}
	else
	{
		g_curbeamnum = 0;
		for(int k=0; k<G_KMAXBEAMS; k++){
			//FOR NEW FREQENCE GENERAGOR
			if(g_curbeamnum == VL || g_curbeamnum == VH)
				dhv_signal_generator_beamsel(FALSE, stat);
			else
				dhv_signal_generator_beamsel(TRUE, stat);

			for( j=0; j<g_knumber_of_spectra[g_curbeamnum]; j++){
				WaitForSingleObject(dp_task.h_eSpectraDataProcessed,INFINITE);
				SetEvent(dp_task.h_eSpectraDataProcessedResponse);
			}
			WaitForSingleObject(dp_task.h_eBeamDataProcessed,INFINITE);
			SetEvent(dp_task.h_eSpectraDataProcessedResponse);
			g_curbeamnum++;
		}
	}

}

void CTestTask::SendDataToMainDlg(){

	return;
}

