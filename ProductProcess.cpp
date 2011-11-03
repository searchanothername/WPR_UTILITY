// ProductProcess.cpp: implementation of the CProductProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "ProductProcess.h"
#include "Global.h"
#include "WPR_UTILITIESDlg.h"
#include "Global.h"
#include <math.h>
#include "ipps.h"
#include "ippcore.h"
#include "winbase.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CDataHandlor data;
DWORD WINAPI limit_cal(LPVOID lParam);
DWORD WINAPI spectra_cal(LPVOID lParam);
DWORD WINAPI products_cal(LPVOID lParam);
CRITICAL_SECTION spec_cs;
HANDLE g_hSpecsFinished = CreateEvent(0,0,0,0);
volatile bool bProductProcessing = false;

static int compare( const void *arg1, const void *arg2 ){
   return *(double *)arg1 > *(double *)arg2 ? 1 : -1; 
}

enum {
	WINDOW_HAMMING,
	WINDOW_HANNING,
	WINDOW_BLACKMAN
};

CProductProcess::CProductProcess()
{
	n_specId = 0;
	n_beamId = 0;
	n_rangebin = 0;
	n_fft = 0;
	InitializeCriticalSection(&spec_cs);
}

CProductProcess::~CProductProcess()
{
	this->Stop(NULL);
	bProductProcessing = false;
}

void CProductProcess::SetParent(CWPR_UTILITIESDlg* pWindow)
{
	g_utility = pWindow;
	return;
}


/*
*********************************************************
* START TO RETRIEVE THE DATA FROM DATA PROCESS. 
* DO PRODUCT GENERATION
*********************************************************
*/
DWORD CProductProcess::Run(void* pParam)
{

	
    while(!global.g_shutdown){
		if(global.cs_product.IsOn())
		{
			IRQ r;
			if(global.series_fifo.remove_head(&r))
			{
				n_specId = r.spec_id-1;
				n_beamId = r.beam_id;
				n_rangebin = r.rangebin;
				n_fft = r.fftnum;

				if(n_specId == 0)
					ZeroMemory(data._spec_avged,SIZE_SINGLE_SPEC);

				BOOL bStat = QueueUserWorkItem(limit_cal,this,0);
				bStat = QueueUserWorkItem(spectra_cal,this,0);	
				//calculateLimit();
				//calculateProducts();
			}
		}
		Sleep(50);
	};
	return 0;
}

DWORD CProductProcess::Stop(void* pParam)
{
		global.cs_product.TurnOff();
		this->Exit();
		return 0;
}

/*
************************************************************
* CREATE A THREAD TO CALCUATE THE LIMIT FOR TIME SERIES
************************************************************
*/
void CProductProcess::calculateLimit()
{
	DWORD nThreadId = 0;
	HANDLE hThread = CreateThread(NULL,0,limit_cal,this,0,&nThreadId);
	CloseHandle(hThread);
	return;
}

/*
************************************************************
* CREATE A THREAD TO GENERATE SPECTRAS
************************************************************
*/
void CProductProcess::calculateProducts()
{
	DWORD nThreadId = 0;
	HANDLE hThread = CreateThread(NULL,0,spectra_cal,this,0,&nThreadId);
	CloseHandle(hThread);
	return;
}

/*
************************************************************
* THREAD FUNCTION TO GET THE MAX AND MIN VALUE OF TIME SERIES
************************************************************
*/
DWORD WINAPI limit_cal(LPVOID lParam)
{
	CProductProcess* process = (CProductProcess*) lParam;

	int n_specId = process->n_specId;
	int n_beamId = process->n_beamId;
	int n_rangebin = process->n_rangebin;
	int n_fft = process->n_fft;

	global.ts_limit[n_specId].i_min = MININVALID;
	global.ts_limit[n_specId].q_min = MININVALID;
	global.ts_limit[n_specId].i_max = MAXINVALID ;
	global.ts_limit[n_specId].q_max = MAXINVALID;

	P_DATA buffer;
	if(n_beamId %2 == 1)
		buffer = (data._data_low+n_specId)->datapage_l.nTimeSeries+0;
	else
		buffer = (data._data_high+n_specId)->datapage_h.nTimeSeries+0;
	
	for(int i=0; i<n_rangebin*n_fft; i++)
	{
		if((buffer+i)->iData>global.ts_limit[n_specId].i_max)
			 global.ts_limit[n_specId].i_max = (buffer+i)->iData;
		if((buffer+i)->qData>global.ts_limit[n_specId].q_max)
			global.ts_limit[n_specId].q_max = (buffer+i)->qData;

		if((buffer+i)->iData<=global.ts_limit[n_specId].i_min)
			 global.ts_limit[n_specId].i_min = (buffer+i)->iData;
		if((buffer+i)->qData<=global.ts_limit[n_specId].q_min)
			 global.ts_limit[n_specId].q_min = (buffer+i)->qData;
	}

	double i_scalor = \
		fabs(global.ts_limit[n_specId].i_max-global.ts_limit[n_specId].i_min);
	global.ts_limit[n_specId].i_scalor = i_scalor;

	double q_scalor = \
		fabs(global.ts_limit[n_specId].q_max-global.ts_limit[n_specId].q_min);
	global.ts_limit[n_specId].q_scalor = q_scalor;
		
	::PostMessage((process->g_utility)->m_hWnd,WM_MYSHOW,n_specId,n_beamId);

	return 0;
}


/*
************************************************************
* CALCUALTE THE SINGLE SPECA AND AVERAGE THEM
************************************************************
*/
DWORD WINAPI spectra_cal(LPVOID lParam)
{
    const int WINDOWTYPE = global_advance.dspsetting.nWindowType;
	::EnterCriticalSection(&spec_cs);
	//FIRST WE NEED TO CALCUATE THE SPECTRA AND AVERAGE THEM.
	CProductProcess* process = (CProductProcess*) lParam;
	int n_specId = process->n_specId;
	int n_beamId = process->n_beamId;
	int n_rangebin = process->n_rangebin;
	int n_fft = process->n_fft;
	int j = 0;

	P_DATA buffer;
	if(n_beamId %2 == 1)
		buffer = (data._data_low+n_specId)->datapage_l.nTimeSeries+0;
	else
		buffer = (data._data_high+n_specId)->datapage_h.nTimeSeries+0;

	for(int i= 0; i<n_rangebin; i++)
	{	
		int m_order = log10((double)n_fft)/log10(2.0);
		int m_flag = IPP_FFT_DIV_FWD_BY_N;
		IppHintAlgorithm m_hint = ippAlgHintFast;
		IppsFFTSpec_C_64fc* pFFTSpec = NULL;
		ippsFFTInitAlloc_C_64fc((IppsFFTSpec_C_64fc**)&pFFTSpec, m_order, m_flag, m_hint);
		IppStatus stat;

		//GET THE THE RANGEBIN DATA.
		Ipp64fc* pInput_C = ::ippsMalloc_64fc(n_fft);
		Ipp64fc* pOutput_C = ::ippsMalloc_64fc(n_fft);
		Ipp8u* pBuffer = (Ipp8u*)ippMalloc(n_fft);
		
		double iDataAvg = 0.0;
		double qDataAvg = 0.0;
		if(!global_advance.dspsetting.nIQReverse){
			for(j=0; j<n_fft; j++)
			{
				(pInput_C+j)->im = (buffer+j*n_rangebin+i)->iData;
				(pInput_C+j)->re = (buffer+j*n_rangebin+i)->qData;
				iDataAvg+= (pInput_C+j)->im/n_fft;
			    qDataAvg+= (pInput_C+j)->re/n_fft;
			}
		}else{
			for(j=0; j<n_fft; j++)
			{
				(pInput_C+j)->im = (buffer+j*n_rangebin+i)->qData;
				(pInput_C+j)->re = (buffer+j*n_rangebin+i)->iData;
				iDataAvg+= (pInput_C+j)->im/n_fft;
			    qDataAvg+= (pInput_C+j)->re/n_fft;
			}
		}

		//REMOVE DC IF WE NEED
		if(global_advance.dspsetting.nRemoveDC)
		{
			for(j=0; j<n_fft; j++)
			{
				(pInput_C+j)->im-=iDataAvg;
				(pInput_C+j)->re-=qDataAvg;
			}
		}

		//ADD WINDOW
		//FAILD IN USING FUNCTION POINTER ARRAY
		if(global_advance.dspsetting.nWindowType == WINDOW_HAMMING)
			stat = ippsWinHamming_64fc(pInput_C, pInput_C, n_fft);
		else if(global_advance.dspsetting.nWindowType == WINDOW_HANNING)
			stat = ippsWinHann_64fc(pInput_C, pInput_C, n_fft);
		else if(global_advance.dspsetting.nWindowType == WINDOW_BLACKMAN)
			stat = ippsWinBlackman_64fc(pInput_C, pInput_C, n_fft,-0.16);
			

		//DO FFT
		stat = ippsFFTFwd_CToC_64fc(
			pInput_C,
			pOutput_C,
			pFFTSpec,
			pBuffer);

        double fmin = 99999.0;
		double fmax = -99999.0;
		int max_loc = 0;
		for(j=0; j<n_fft/2; j++)
		{
			double pwr_left =  10.0*log10((pOutput_C+j)->re * (pOutput_C+j)->re+
								(pOutput_C+j)->im *(pOutput_C+j)->im+1E-6);
			double pwr_right = 10.0*log10((pOutput_C+j+n_fft/2)->re * (pOutput_C+j+n_fft/2)->re+
								(pOutput_C+j+n_fft/2)->im *(pOutput_C+j+n_fft/2)->im+1E-6);
	
			if(pwr_left>fmax){
				fmax = pwr_left;
				max_loc = n_fft/2+j;
			}
			if(pwr_left<fmin)
				fmin = pwr_left;

			if(pwr_right>fmax){
				fmax = pwr_right;
				max_loc = j;
			}
			if(pwr_right<fmin)
				fmin = pwr_right;

			*(data._spec_avged->spectra+i*MAXFFTPOINTS+j) += pwr_right/g_knumber_of_spectra[n_beamId];
			*(data._spec_avged->spectra+i*MAXFFTPOINTS+j+n_fft/2) += pwr_left/g_knumber_of_spectra[n_beamId];
			
			//STORE THE SINGLE SPEC
			*(data._spec_single->spectra+i*MAXFFTPOINTS+j) = pwr_right;
			*(data._spec_single->spectra+i*MAXFFTPOINTS+j+n_fft/2) = pwr_left;

		}

		ippFree(pBuffer);
		ippsFree(pInput_C);
		ippsFree(pOutput_C);
		ippsFFTFree_C_64fc(pFFTSpec);

		global.spec_single_limit.limit[i].min = fmin;
		global.spec_single_limit.limit[i].max = fmax;
		global.spec_single_limit.limit[i].max_loc = max_loc;
	}
	::LeaveCriticalSection(&spec_cs);
	::PostMessage((process->g_utility)->m_hWnd,WM_SHOW_SPEC_SINGLE,n_specId,n_beamId);

	//SPEC CALCULATE FINISHED.
	if(n_specId == g_knumber_of_spectra[n_beamId]-1){
		memcpy(data._spec_avged_cpy,data._spec_avged,SIZE_SINGLE_SPEC);
        memcpy(data._spec_avged_comp,data._spec_avged,SIZE_SINGLE_SPEC);
		for(int i= 0; i<n_rangebin; i++)
		{
			//qsort( data._spec_avged_comp->spectra+i*MAXFFTPOINTS, n_fft, sizeof(double), compare);

			//IPPAPI(IppStatus, ippsMinMaxIndx_64f,(const Ipp64f* pSrc, int len, Ipp64f* pMin, int* pMinIndx,
            //                                                       Ipp64f* pMax, int* pMaxIndx))
			Ipp64f min_value, max_value;
			int min_index, max_index;
			IppStatus stat = ippsMinMaxIndx_64f(data._spec_avged_comp->spectra+i*MAXFFTPOINTS,
												 n_fft,
												 &min_value, &min_index,
												 &max_value, &max_index);

			global.spec_avg_limit.limit[i].min = min_value;//*(data._spec_avged_comp->spectra+i*MAXFFTPOINTS);
			global.spec_avg_limit.limit[i].max = max_value;//*(data._spec_avged_comp->spectra+i*MAXFFTPOINTS+n_fft-1);
			global.spec_avg_limit.limit[i].max_loc = max_index;
		}

		::PostMessage((process->g_utility)->m_hWnd,
			WM_SHOW_SPEC_AVG,
			n_specId,
			n_beamId);

	
		
		//DWORD nThreadId = 0;
		//HANDLE hThread = CreateThread(NULL,0,products_cal,process,0,&nThreadId);
		//CloseHandle(hThread);
		BOOL bStat = QueueUserWorkItem(products_cal,process,0);
	}

	return 0;
}

/*
************************************************************
* CALCUALTE THE PRODUCT INCLUDES SNR, NOISE LEVEL AND RVW
************************************************************
*/
DWORD WINAPI products_cal(LPVOID lParam)
{
	CProductProcess* process = (CProductProcess*) lParam;
	int n_specId = process->n_specId;
	int n_beamId = process->n_beamId;
	int n_rangebin = process->n_rangebin;
	int n_fft = process->n_fft;


	process->prt = g_cur_prt[n_beamId];
	process->tda =g_ktda_samples[n_beamId];
	
	for(int i= 0; i<n_rangebin; i++)
	{	
		process->cal_noise_level(i);
		process->cal_base_product(i);
	}
	//TELL THE WINDOW TO SHOW THE SPECTRAS
	::PostMessage((process->g_utility)->m_hWnd,
		WM_SHOW_SPEC_TOTAL,
		n_rangebin,
		n_beamId);
	SetEvent(g_hSpecsFinished);
	bProductProcessing = true;
		
	return 0;
}


/*
************************************************************
* CALCUALTE NOISE LEVEL AT EACH RANGEBIN
************************************************************
*/
void CProductProcess::cal_noise_level(const int rangebin)
{
	double* tpwrbuf = data._spec_avged_comp->spectra+rangebin*MAXFFTPOINTS;
	double* tmeanpwr = new double[n_fft];
	double sumsq=0;
    double total = 0;
    double ratio = 0;
    double variance = 0;
    double pmeansq = 0;
    int rgate = 0;
    int ibin = 0;
    int kount = 1;
    BOOL  b_found_noise = FALSE;      
    int i = 0;   
	
    double t_pmeansq = 0;
    double t_tmeanpwr = 0;
    int t_ibin = 0;
    int t_rgate = 0;
    int t_abi = 0;
	

	//INITIALIZE THE ARRAY USED TO STORE MEAN NOISE VALUES
	::ZeroMemory(tmeanpwr,sizeof(double)*n_fft);

	//LOOP THROUGH THE SORTED SPECTRA CALCULATING MEAN NOISE VALUE,
	//SIGNAL VARIANCE, AND THE RATIO OF SIGNAL VARIANCES	
	for( ibin = 0; ibin <n_fft; ibin ++) {
		total = total + tpwrbuf[ibin];
		tmeanpwr[ibin] = (double)(total) / (double)kount;
		kount = kount + 1;
		sumsq = sumsq + tpwrbuf[ibin] * tpwrbuf[ibin];
	}

	ibin = n_fft;
	while (b_found_noise == FALSE) 
	{
		ibin = ibin -1;
		if (ibin < 0)  
		{
			data._noise_level->noise_level[rangebin]= *(tpwrbuf+0); 
			b_found_noise = TRUE;                 
		}
		else if (tpwrbuf[ibin] != 0) 
		{       
			pmeansq = tmeanpwr[ibin] * tmeanpwr[ibin];
			variance = ((double)(sumsq) / (double)ibin) - pmeansq;
			sumsq = sumsq - tpwrbuf[ibin] * tpwrbuf[ibin];
			if ((variance > 0) && (pmeansq != 0)) 
			{
				ratio = variance / pmeansq;
				if (ratio < 1) 
				{	
					data._noise_level->noise_level[rangebin] = tmeanpwr[ibin];
					b_found_noise = TRUE;
				} 
			} 
		}   
	}   
	delete[] tmeanpwr;
	return;
}

/*
************************************************************
* CALCUALTE THE SIGNAL POWER, MEAN VELOCITY AND SPECTRA WIDTH
************************************************************
*/
void CProductProcess::cal_base_product(const int rangebin)
{
	int nLowBin = 0;
	int nHighBin = 0;
	int nPeakbin = 0;
	int i=0;
	double sig_pwr = 0.0;
	double rad_vel = 0.0;		
	double vel_var = 0.0;			
	double sig_remove_noise = 0.0;
	double noise_level =  data._noise_level->noise_level[rangebin];
	double klambda = (double) (149891000) / 1280000;
	double* pdata = data._spec_avged_cpy->spectra+rangebin*MAXFFTPOINTS;


	//FIND THE SIGNAL	
	findSignal(nLowBin,nHighBin, nPeakbin,rangebin);
	

	//CALCULATE THE SIGNAL POWER AND SNR
	for( i= nLowBin; i<nHighBin; i++){
		sig_remove_noise = pow(10.0,*(pdata+i)/10.0) - pow(10.0,noise_level/10.0);
		sig_pwr += sig_remove_noise;
	}

	data._signal_power->signal_power[rangebin] = 10*log10(sig_pwr);
	data._snr->snr[rangebin] = data._signal_power->signal_power[rangebin]\
		                        - noise_level;
	

	//CALCULATE THE MEAN VELOCITY
	for ( i = nLowBin; i<nHighBin; i++)
	{
		sig_remove_noise = pow(10.0,*(pdata+i)/10.0) - pow(10.0,noise_level/10.0);
		double temp = cal_velocity (i,klambda);
		double temp_1 = sig_remove_noise;
		rad_vel = rad_vel + (temp_1 * temp);
	}
	rad_vel = rad_vel / sig_pwr;
	data._mean_velocity->mean_velocity[rangebin] = rad_vel;

	
	//CALCULATE THE VELOCITY VARIANCE
	for (i = nLowBin; i <= nHighBin; i++)
	{
		sig_remove_noise = pow(10.0,*(pdata+i)/10.0) - pow(10.0,noise_level/10.0);
		vel_var  = vel_var + sig_remove_noise * pow((cal_velocity(i,klambda) - rad_vel),2.);
	}
	vel_var = vel_var / sig_pwr;
	data._spec_width->spec_width[rangebin] = vel_var;
	return;

}

/*
************************************************************
* FIND THE SIGNAL FOR NEXT PROCESS.
************************************************************
*/
void CProductProcess::findSignal(int &nlowBin,
								 int &nHighBin, 
								 int &nPeakbin,
								 const int rangebin)
{
	double lastsum =-8192.0;
	const int nWindowWidth = 5;
	int maxId = 0;
	int i,j;
	double* pdata = data._spec_avged_cpy->spectra+rangebin*MAXFFTPOINTS;


	int temp_peak=0;
	for(i = 0; i<n_fft-nWindowWidth ;i++)
	{  
        double cursum = 0.0;
		for( j = i; j<i+nWindowWidth; j++){
			cursum += pdata[j];
		}	
		if(cursum >lastsum){
			maxId = j-nWindowWidth;
			lastsum = cursum;
		}
	}

	//FIND THE PEAK
	double maxvalue = MAXINVALID;
	for(i = maxId; i< nWindowWidth+maxId-1; i++)
	{
		if( *(pdata+i)> maxvalue){
			maxId = i;
			maxvalue = *(pdata+i);
		}
	}

	global.spec_avg_limit.peak_loc[rangebin] = maxId;
	global.spec_avg_limit.peak_val[rangebin] = maxvalue;
    nPeakbin = maxId; //TOLD THE CALLER.

	//FIND LOW BIN
	for(i=maxId; i>0; i--){
		if(pdata[i] > data._noise_level->noise_level[rangebin])
			nlowBin = i;
		else
			break;
	}

	//FIND HIGH BIN
    for(i=maxId; i<n_fft; i++){
		 if(pdata[i] > data._noise_level->noise_level[rangebin])
			nHighBin = i;
		else
			break;
	}
	return;
}


/*
************************************************************
* CALCUALTE THE VELOCITY
************************************************************
*/
double CProductProcess::cal_velocity (int bin_no, double& klambda)
{

	double delta = (double) (1000000.0) / (double)(n_fft * prt * tda);
	double fibin = delta * (bin_no - n_fft/2);	
	double v = klambda * fibin;
	double velocity_result = v; 	
	return velocity_result;
}