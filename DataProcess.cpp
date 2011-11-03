// DataProcess.cpp: implementation of the CDataProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "DataProcess.h"
#include "WPRDriverlib.h"
#include "Global.h"
#include "Global_SM.h"
#include "Global_Advanced.h"
#include <math.h>
#include <mmsystem.h>
#include <winsock2.h>
#include "WPR_UTILITIESDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

volatile BOOL g_bPrepareSample  = FALSE;
volatile int  g_nInterrupt    = 0;
volatile int  g_nSpectraCount = 0;
UINT uID;               
UINT uTimerDuring = 5;   

enum{
	SINGLESPECTRAFINISHED =0,
	TOTALSPECTRASFINISHED =1
};

CEvent gEventSend(FALSE,FALSE,"SEND FINISHED",NULL);
CEvent gEventRecv(TRUE,FALSE,"RECV FINISHED",NULL);

HANDLE CDataProcess::h_eCtrlWordsDownloaded = CreateEvent(0,0,0,0);
HANDLE CDataProcess::h_eBeamDataProcessed   = CreateEvent(0,0,0,0);
HANDLE CDataProcess::h_eBeamDataProcessedResponse = CreateEvent(0,0,0,0);
HANDLE CDataProcess::h_eSpectraDataProcessed = CreateEvent(0,0,0,0);
HANDLE CDataProcess::h_eSpectraDataProcessedResponse = CreateEvent(0,0,0,0);
HANDLE CDataProcess::h_eSingleSpectraFinished = CreateEvent(0,0,0,0);
HANDLE CDataProcess::h_eTotalSpectrasFinished = CreateEvent(0,0,0,0);
HANDLE CDataProcess::h_eInterrupt[2] = {
	CDataProcess::h_eSingleSpectraFinished,
	CDataProcess::h_eTotalSpectrasFinished
};

HANDLE CDataProcess::h_eSingleSpectraSending = CreateEvent(0,0,0,0);

static int g_knumber_of_rangebin[G_BEAMNUMBERS]; 
static void DriverProc(void *Buff,int len); //RESPONSE TO THE INERRUPT
static void CALLBACK TimeProc(UINT	IDEvent,//I USE THIS CALLBACK FUNCTION TO DO SIMULATE
							  UINT  uReserved,
							  DWORD dw1,
							  DWORD dw2,
							  DWORD dw3);
extern volatile int cur_value;          
extern volatile int RFAttenuationChanged;
extern volatile int cur_rtac_value;		
extern volatile int RTACChanged;


static int sim_data_low[LOWDMANUM];
static int sim_data_high[HIGHDMANUM];


static void genLowData();
static void genHighData();
CDataHandlor data; 
IRQ rq;

CDataProcess::CDataProcess()
{
	const int RANGEBIN_HIGH = global_advance.dmasetting.nDMA_High/2;
    const int RANGEBIN_LOW = global_advance.dmasetting.nDMA_Low/2;
    data.setRangeBin(RANGEBIN_LOW, RANGEBIN_HIGH);

	for(int i=0; i<G_BEAMNUMBERS; i+=2){
		g_knumber_of_rangebin[i] = 	 RANGEBIN_HIGH;//global_advance.dmasetting.nDMA_High/2;
		g_knumber_of_rangebin[i+1] = RANGEBIN_LOW;//global_advance.dmasetting.nDMA_Low/2;
	}
	data.init();

	WPRAPI_Init();
	WPRAPI_InstallCallback(DriverProc);
} 

CDataProcess::~CDataProcess()
{
	//CLOSE HANDLES
	if(h_eCtrlWordsDownloaded)
		CloseHandle(h_eCtrlWordsDownloaded);

	if(h_eBeamDataProcessed)
		CloseHandle(h_eBeamDataProcessed);

	if(h_eBeamDataProcessedResponse)
		CloseHandle(h_eBeamDataProcessedResponse);

	if(h_eSpectraDataProcessed)
		CloseHandle(h_eSpectraDataProcessed);

	if(h_eSpectraDataProcessedResponse)
		CloseHandle(h_eSpectraDataProcessedResponse);

	if(h_eSingleSpectraFinished)
		CloseHandle(h_eSingleSpectraFinished);

	if(h_eTotalSpectrasFinished)
		CloseHandle(h_eTotalSpectrasFinished);

    this->Stop(NULL);
	WPRAPI_DisableInterrupt();
    WPRAPI_UninstallCallback();
    WPRAPI_Release();
}
/*
*********************************************************
* SAVE THE MAIN WINDOW'S POINTER.
*********************************************************
*/
void CDataProcess::SetParent(CWPR_UTILITIESDlg* pWindow)
{
	_utility = pWindow;
}

/*
*********************************************************
* CALLBACK FUNCTION FOR RETRIEVE DATA FROM DRIVER
*********************************************************
*/
static void DriverProc(void *Buff,int len){

	 int* pBuff=(int *)Buff;
	 int nTotalfftNum = \
			(global.basic.basicinfo.bHighModeRange240m==1)\
			?global.basic.basicinfo.nfft:global.basic.basicinfo.nfft/16; 
			//for no time domain averaging
			
	 if(g_bPrepareSample){

		//FINISH ONE DMA
		if(g_curbeamnum %2 == LOMODE_ID){
			//genLowData();
			data.setDataLow(g_nInterrupt,g_nSpectraCount,pBuff);
		}
		else if(g_curbeamnum %2 == HIMODE_ID){
			//genHighData();
			data.setDataHigh(g_nInterrupt,g_nSpectraCount,pBuff);
		}
	    ++g_nInterrupt;
 
		//FINISH ONE SPECTRA
		if(g_nInterrupt == nTotalfftNum){
			//NOTE: TIMEDOMAIN AVG IS DONE BY HARDWARE.
			++g_nSpectraCount;       //COUNT THE SPECTRA NUMBER 
			g_bPrepareSample = FALSE;//STOP SAMPLE.
			g_nInterrupt = 0;        //ZEROS THE INTERRUPT COUNT
	
		    rq.spec_id = g_nSpectraCount; //PUSH THE INFORMATION INTO FIFO
		    rq.beam_id  = g_curbeamnum;
			rq.fftnum = global.basic.basicinfo.nfft;

			if(g_curbeamnum %2 == LOMODE_ID)
			{
				rq.rangebin = g_knumber_of_rangebin[g_curbeamnum]\
					-global_advance.dspsetting.nBeginGateMoveL;
			}
			else if(g_curbeamnum %2 == HIMODE_ID)
			{
				rq.rangebin = g_knumber_of_rangebin[g_curbeamnum]\
					-global_advance.dspsetting.nBeginGateMoveH;
			}
	
			SetEvent(CDataProcess::h_eInterrupt[SINGLESPECTRAFINISHED]);
			
		}
        
		//FINISH TOTAL SPECTRA IN ONE BEAM
		if(g_nSpectraCount == g_knumber_of_spectra[g_curbeamnum]){
			  g_bPrepareSample = FALSE;//STOP SAMPLE.
			  g_nInterrupt = 0;        //ZEROS THE INTERRUPT COUNT
			  g_nSpectraCount = 0;     //ZEORS THE SPECTRA NUM COUNT.
			  SetEvent(CDataProcess::h_eInterrupt[TOTALSPECTRASFINISHED]);//MEAN ONE BEAM IS FINISHED.
		}
	
	}
	return;
}

/*
*********************************************************
* SIMULATION FOR THE INTERRUPT FROM PCI
*********************************************************
*/

void CALLBACK TimeProc(UINT	IDEvent,
					  UINT  uReserved,
					  DWORD dw1,
					  DWORD dw2,
					  DWORD dw3){

	if(g_bPrepareSample){

		//FINISH ONE DMA
		if(g_curbeamnum %2 == LOMODE_ID){
			genLowData();
			data.setDataLow(g_nInterrupt,g_nSpectraCount,sim_data_low);
		}
		else if(g_curbeamnum %2 == HIMODE_ID){
			genHighData();
			data.setDataHigh(g_nInterrupt,g_nSpectraCount,sim_data_high);
		}
	    ++g_nInterrupt;
 
		//FINISH ONE SPECTRA
		if(g_nInterrupt == global.basic.basicinfo.nfft){
			//NOTE: TIMEDOMAIN AVG IS DONE BY HARDWARE.
			++g_nSpectraCount;       //COUNT THE SPECTRA NUMBER 
			g_bPrepareSample = FALSE;//STOP SAMPLE.
			g_nInterrupt = 0;        //ZEROS THE INTERRUPT COUNT
			rq.spec_id = g_nSpectraCount; //PUSH THE INFORMATION INTO FIFO
		    rq.beam_id  = g_curbeamnum;
			rq.fftnum = global.basic.basicinfo.nfft;
			if(g_curbeamnum %2 == LOMODE_ID)
			{
				rq.rangebin = g_knumber_of_rangebin[g_curbeamnum]\
					-global_advance.dspsetting.nBeginGateMoveL;
			}
			else if(g_curbeamnum %2 == HIMODE_ID)
			{
				rq.rangebin = g_knumber_of_rangebin[g_curbeamnum]\
					-global_advance.dspsetting.nBeginGateMoveH;
			}
			SetEvent(CDataProcess::h_eInterrupt[SINGLESPECTRAFINISHED]);
			
		}
        
		//FINISH TOTAL SPECTRA IN ONE BEAM
		if(g_nSpectraCount == g_knumber_of_spectra[g_curbeamnum]){
			  g_bPrepareSample = FALSE;//STOP SAMPLE.
			  g_nInterrupt = 0;        //ZEROS THE INTERRUPT COUNT
			  g_nSpectraCount = 0;     //ZEORS THE SPECTRA NUM COUNT.
			  SetEvent(CDataProcess::h_eInterrupt[TOTALSPECTRASFINISHED]);//MEAN ONE BEAM IS FINISHED.
		}
	
	}

	return;

}

/*
*********************************************************
* START THIS THREAD FOR DATA PROCESSING
*********************************************************
*/
DWORD CDataProcess::Run(void* pParam){

#ifdef SIMULATE
    uID = timeSetEvent(uTimerDuring,10, (LPTIMECALLBACK)TimeProc,0, TIME_PERIODIC); 
#endif

	//CLEAR THE QUEUE
	global.series_fifo.clear();

	//OPERATE THE SYSTEM.
	while(global.cs_dataprocess.IsOn()){
		if(!g_bCycleCtrol)
			TestProcess();
		else
			OperateProcess();
	}
	return 0;
}

/*
*********************************************************
* TEST PROCESS FOR DOPLAR TEST
*********************************************************
*/
void CDataProcess::TestProcess()
{
		if(global.cs_test.IsOn()){

		int temp =0;
		
			//FIRST DOWNLOAD THE PARAMETERS ONCE
			if(b_firstdownload ){
				//AfxMessageBox("first download");
			    DownLoadCtrlWords(g_nomal_ctrlwrds);
                WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);
				b_firstdownload = FALSE;
			}
			else{
			//WHEN WE CHANGE THE BEAM. WE NEED TO CLOSE DRIVER FIRST
				if(g_last.cw0_flds.bmdirection != g_nomal_ctrlwrds.cw0_flds.bmdirection){
					g_nomal_ctrlwrds.cw0_flds.dptestctrl = 1;//CLOSE RF DIRVER
					DownLoadCtrlWords(g_nomal_ctrlwrds);
					//AfxMessageBox("RF driver off");
					WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);
					Sleep(500);
					g_nomal_ctrlwrds.cw0_flds.dptestctrl = 0;//OPEN RF DIRVER
					DownLoadCtrlWords(g_nomal_ctrlwrds);
					WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);
					//AfxMessageBox("RF driver on");
				}
				else if(g_last.cw0_flds.mode != g_nomal_ctrlwrds.cw0_flds.mode)
				{
					DownLoadCtrlWords(g_nomal_ctrlwrds);
					WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);
					//AfxMessageBox("high-low mode changed");
				}

				else if(b_nochanged){
					DownLoadCtrlWords(g_nomal_ctrlwrds);
					WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);
					b_nochanged = FALSE;
				}
			}
			memcpy(&g_last,&g_nomal_ctrlwrds,sizeof(control_word_0_6));

            //SET RF ATTENUATION
			if(RFAttenuationChanged){		
				temp = 103-(0-cur_value);//was -cur_value;
				g_nomal_ctrlwrds.cw1_flds.rfattenuation = (temp>63?temp+24:temp);
				DownLoadCtrlWords(g_nomal_ctrlwrds);
				WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);
				RFAttenuationChanged = 0;
			} 

			//SET RTAC ATTENUATION	
			//if(RTACChanged){
			//	
			//	temp = (0 - cur_rtac_value)/4;
			//	g_nomal_ctrlwrds.cw1_flds.rxtestsignalampctrl = temp;
			//	DownLoadCtrlWords(g_nomal_ctrlwrds);
			//	WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);
			//	RTACChanged = 0;
			//}

            g_bPrepareSample = TRUE;//CALLBACK FUNCTION START TO GET DATA.
			//b_CommunicationSel = g_communication_config.selection;//GET COMMUNICATION SEL
			GetOneBeamData();       //IT ALSO DO PROCESS THE DATA
				                    //AND TELL THE TEST TASK THE RESULT
			WaitForSingleObject(h_eSpectraDataProcessedResponse, INFINITE);
							        //NOTE: THE TEST TASK WILL SIGNAL THIS EVENT
			g_bPrepareSample = TRUE;
		}
}

/*
*********************************************************
* WORKING ON FIVE DIRECTION AS WHAT WPCS DOES.
*********************************************************
*/
void CDataProcess::OperateProcess()
{
	if(global.cs_test.IsOn())
	{
		int temp =0;
		DownLoadCtrlWords(g_submode_ctrlwrds[g_curbeamnum]);
		WaitForSingleObject(h_eCtrlWordsDownloaded,INFINITE);

		g_bPrepareSample = TRUE;//CALLBACK FUNCTION START TO GET DATA.

		//b_CommunicationSel = g_communication_config.selection;//GET COMMUNICATION SEL
		GetOneBeamData();       //IT ALSO DO PROCESS THE DATA
		
		//AND TELL THE TEST TASK THE RESULT
		WaitForSingleObject(h_eSpectraDataProcessedResponse, INFINITE);

		//NOTE: THE TEST TASK WILL SIGNAL THIS EVENT
		g_bPrepareSample = TRUE;
	}
	 
}

/*
*********************************************************
* STOP THE THREAD 
*********************************************************
*/
DWORD CDataProcess::Stop(void* pParam){

	global.cs_dataprocess.TurnOff();
	g_nSpectraCount = 0;

	//RESET THE EVENT
    ResetEvent(h_eBeamDataProcessed);
	ResetEvent(h_eBeamDataProcessedResponse);
    ResetEvent(h_eSpectraDataProcessed);
	ResetEvent(h_eSpectraDataProcessedResponse);

	WPRAPI_WriteData (WPR_DP_AD_BAR2,0x438,&Data2,1); // end timing   3xclk,stop hsp
	WPRAPI_WriteData (WPR_DP_AD_BAR2,0x438,&Data0,1); //
	
#ifdef SIMULATE
    timeKillEvent(uID);
#endif

	this->Exit();
	return 0;
}

/*
*********************************************************
* GET ONE BEAM DATA. 
*********************************************************
*/
void CDataProcess::GetOneBeamData(){

	//WAIT FOR DATA COMMING
	DWORD stat = WaitForMultipleObjects(2,h_eInterrupt,FALSE,INFINITE);
    switch (stat){
	   case WAIT_OBJECT_0+SINGLESPECTRAFINISHED:	
           DataProcess();
		   SetEvent(h_eSpectraDataProcessed);
		
		   break;
	   case WAIT_OBJECT_0+TOTALSPECTRASFINISHED:
		   SetEvent(h_eBeamDataProcessed);
	
		   break;

	   case WAIT_TIMEOUT://NO USE NOW
		   AfxMessageBox("DATA TRANS TIME OUT");
		   break;
		   
	   default:
		   break;
	};
	return ;
}

/*
*********************************************************
* DOWNLOAD CONTROL WORDS
*********************************************************
*/
void CDataProcess::DownLoadCtrlWords(control_word_0_6& g_controlwords){
	UINT CtrlCmdParams[14];
    
	CtrlCmdParams[0] = g_controlwords.cw0;//| 0x00000002;
	CtrlCmdParams[1] = g_controlwords.cw1;
	CtrlCmdParams[2] = g_controlwords.cw2;
	CtrlCmdParams[3] = g_controlwords.cw3_6[0].cw3_6_ui;
	CtrlCmdParams[4] = g_controlwords.cw3_6[1].cw3_6_ui;
	CtrlCmdParams[5] = g_controlwords.cw3_6[2].cw3_6_ui;
	CtrlCmdParams[6] = g_controlwords.cw3_6[3].cw3_6_ui;
	CtrlCmdParams[7] = g_controlwords.cw0_flds.tda_samples 
		               * (g_controlwords.cw0_flds.spectra_samples)
					   * (g_controlwords.cw0_flds.fftpts);  
	CtrlCmdParams[7] = CtrlCmdParams[7] & 0x0fffffff;
	//CW8~15
	CtrlCmdParams[8] = g_PC_code_moving & 0x000000ff;
	CtrlCmdParams[9] = 0;
	CtrlCmdParams[10] = 0;
	CtrlCmdParams[11] = 0;
	CtrlCmdParams[12] = 0;
	CtrlCmdParams[13] = 0;

	//End Timing
	bool stat = WPRAPI_WriteData (WPR_DP_AD_BAR2,0x438,&Data2,1); // end timing   3xclk,stop hsp

	//Write Parameters
	stat = WPRAPI_WriteData (WPR_DP_AD_BAR2,0x400,CtrlCmdParams,14);
				
	//Start transfer to HSP
	stat = WPRAPI_WriteData (WPR_DP_AD_BAR2,0x438,&Data1,1); // data trans   4xclk 

	//Set DMA
	if(global.basic.basicinfo.bHighModeRange240m==1)
		stat = WPRAPI_DMASet (g_knumber_of_rangebin[g_curbeamnum]*2);
	else
		stat = WPRAPI_DMASet (g_knumber_of_rangebin[g_curbeamnum]*2*16);//set dma 


	stat = WPRAPI_EnableInterrupt();
	stat = WPRAPI_WriteData (WPR_DP_AD_BAR2,0x438,&Data4,1); // start timing 2xclk , start hsp

	SetEvent(h_eCtrlWordsDownloaded);//by now, control words downloaded.

	//Create a file to log the control words
	time_t ltime;
	time(&ltime);
	
	char filename[50];
	sprintf(filename,"CtrlWrds_log.txt\0");
	FILE* fp = fopen(filename,"a+");
	if(!fp)
		return;
	fprintf(fp,"%s",ctime(&ltime));
	for(int i=0; i<8; i++)
	fprintf(fp,"CW-%d : %0x\n",i,CtrlCmdParams[i]);	
	fprintf(fp,"===========================\n");
    fclose(fp);

	return;
}

/*
*********************************************************
* PROCESS THE DATA AND SHARE THEM WITH OTHER SOFTWARE.
*********************************************************
*/
void CDataProcess::DataProcess(){
	if(COMM_SHAREDMEM == g_CommunicationSel){
		//USING SHARED MEMERY.
		BOOL bTimeout = gEventRecv.Lock(INFINITE);
		UploadData();
		gEventRecv.Unlock();
		gEventSend.SetEvent();//SEND DATA.
	}
	else if(COMM_NETWORK == g_CommunicationSel){
		//USING TCP
		//UploadData();
		//gEventSend.SetEvent();

		//TELL THE SERVER TO SEND THE DATA
		SetEvent(h_eSingleSpectraSending);
	}
	else if(COMM_NONE == g_CommunicationSel){
		//SetEvent(h_eSingleSpectraSending);
		global.series_fifo.append(rq);
	    
	}
}

/*
*********************************************************
* SHARE DATA WITH THE PROCESS ON THE LOCAL MACHINE OR 
* OTHERS ON THE NETWORK.
*********************************************************
*/
void CDataProcess::UploadData(){

}

/*
*********************************************************
* GENERATE THE DATA FOR SIMULATION
*********************************************************
*/
void genLowData()
{	
    srand( (unsigned)time( NULL ) );
	double f_rand = rand()%20*100;

	for(int i=0; i<LOWDMANUM; i+=2){
			sim_data_low[i] = f_rand*cos((2*PI+f_rand)/LOWDMANUM*2*i);
			sim_data_low[i+1] = f_rand*sin((2*PI+f_rand)/LOWDMANUM*2*i);
	}	
	return;
}

/*
*********************************************************
* GENERATE THE DATA FOR SIMULATION
*********************************************************
*/
void genHighData()
{
	srand( (unsigned)time( NULL ) );
	double f_rand = rand()%20*100;

	for(int i=0; i<HIGHDMANUM; i+=2){
			sim_data_high[i] = f_rand*cos((2*PI+f_rand)/HIGHDMANUM*2*i);
			sim_data_high[i+1] = f_rand*sin((2*PI+f_rand)/HIGHDMANUM*2*i);
	}
	return;
}