// RawdataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "RawdataDlg.h"
#include "Global.h"
#include "DataView.h"
#include "DataHandlor.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRawdataDlg dialog
extern CDataHandlor data; 

static int compare( const void *arg1, const void *arg2 ){
   return ( *(double*)arg1 - *(double*)arg2);
}

CRawdataDlg::CRawdataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRawdataDlg::IDD, pParent)
{
	nSpecId = -1;
	nBeamId = -1;
	fPwrMax = 0.0;
	fPwrMin= 0.0;
	fPhaseMax= 0.0;
	fPhaseMin= 0.0;
	fPhaseNoise_dB= 0.0;
	fPhaseNoise_deg= 0.0;
	fPwrMean = 0.0;
	fPhaseMean = 0.0;
	fPwrSum = 0.0;
	//{{AFX_DATA_INIT(CRawdataDlg)
	m_bSaveDetails = FALSE;
	m_bSaveResults = FALSE;
	m_bPause = FALSE;
	m_fPhaseNoiseDB = 0.0;
	m_fPhaseNoiseDeg = 0.0;
	m_fPwrAvg = 0.0;
	m_fPwrMM = 0.0;
	m_fPhaseMM = 0.0;
	m_fPhaseAvg = 0.0;
	m_fPwrSum = 0.0;
	m_fPwrVariance = 0.0;
	//}}AFX_DATA_INIT
}


void CRawdataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRawdataDlg)
	DDX_Control(pDX, IDC_CHECK_RAW_CONTROL, m_btn_Pause);
	DDX_Control(pDX, IDC_LIST_DAT, m_ListCtrl_DataInfo);
	DDX_Check(pDX, IDC_CHECK_SAVE_DETAILS, m_bSaveDetails);
	DDX_Check(pDX, IDC_CHECK_SAVE_RESULTS, m_bSaveResults);
	DDX_Check(pDX, IDC_CHECK_RAW_CONTROL, m_bPause);
	DDX_Text(pDX, IDC_EDIT_PHASE_NOISE_DB, m_fPhaseNoiseDB);
	DDX_Text(pDX, IDC_EDIT_PHASE_NOISE_DEG, m_fPhaseNoiseDeg);
	DDX_Text(pDX, IDC_EDIT_POWER_AVG, m_fPwrAvg);
	DDX_Text(pDX, IDC_EDIT_PWR_MM, m_fPwrMM);
	DDX_Text(pDX, IDC_EDIT_PHASE_MM, m_fPhaseMM);
	DDX_Text(pDX, IDC_EDIT_PHASE_AVG, m_fPhaseAvg);
	DDX_Text(pDX, IDC_EDIT_POWER_SUM, m_fPwrSum);
	DDX_Text(pDX, IDC_EDIT_PWR_VARIANCE, m_fPwrVariance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRawdataDlg, CDialog)
	//{{AFX_MSG_MAP(CRawdataDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_RAW_CONTROL, OnCheckRawControl)
	ON_MESSAGE(WM_SHOW_DATAINFO,ShowData)
	ON_BN_CLICKED(IDC_CHECK_SAVE_DETAILS, OnCheckSaveDetails)
	ON_BN_CLICKED(IDC_CHECK_SAVE_RESULTS, OnCheckSaveResults)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRawdataDlg message handlers

BOOL CRawdataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	//INITIALIZE THE LISTCTRL
	DWORD dwStyle = GetWindowLong(m_ListCtrl_DataInfo.m_hWnd,GWL_STYLE);
	SetWindowLong(m_ListCtrl_DataInfo.m_hWnd,GWL_STYLE,dwStyle|LVS_REPORT);
	DWORD style= m_ListCtrl_DataInfo.GetExtendedStyle();
	m_ListCtrl_DataInfo.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ListCtrl_DataInfo.SetBkColor(RGB(58,58,58));
	m_ListCtrl_DataInfo.SetTextBkColor(RGB(58,58,58));
	m_ListCtrl_DataInfo.SetTextColor(RGB(0,255,255));

	CRect rect;
	m_ListCtrl_DataInfo.GetWindowRect(&rect);
	int n_ColumnWidth[5] = {rect.Width() /12,
							rect.Width() /5,
							rect.Width() /5,
							rect.Width() *3/10,
							rect.Width() *13/60};
	char* str_Column[5] = {"ID","I data","Q data","Phase","Power"};
	for(int i=0; i<5; i++)
		m_ListCtrl_DataInfo.InsertColumn(i,str_Column[i],LVCFMT_LEFT,n_ColumnWidth[i]);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CRawdataDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
		if(nCtlColor == CTLCOLOR_STATIC 
		|| nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(0,255,255));
		
	}

	if(nCtlColor == CTLCOLOR_LISTBOX){
			//For Alarm list
        //pDC->SetBkColor(RGB(58,58,58));
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(0,255,255));
	}
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
}

void CRawdataDlg::ShowData(UINT wParam, UINT lParam)
{
	//GET SETTING FOR DISPLAY
	m_nFocusRangeBin = g_DataView->m_nFocusRangeBin;
	nSpecId = wParam;
	nBeamId = lParam;
	int i=0;
	if(nSpecId == -1 || nBeamId == -1)
		return;
	
	if(m_bPause == TRUE){
		return;
	}
    // REMOVE ALL THE LIST
	m_ListCtrl_DataInfo.SetRedraw(FALSE);
	for( i= 0; i<MAXFFTPOINTS; i++){
      m_ListCtrl_DataInfo.DeleteItem(i);
	}
	
	// CALCULATE THE DATA AT RANGEBIN 
	int rangebin = 0;
	int fftnum = data.nFFT;

	P_DATA buffer;
	if(nBeamId%2==1){
		rangebin = data._RANGEBIN_LOW;
		buffer	= (data._data_low+nSpecId)->datapage_l.nTimeSeries+0;
	}
	else{
		rangebin = data._RANGEBIN_HIGH;
		buffer	= (data._data_high+nSpecId)->datapage_h.nTimeSeries+0;
	}

	// CREATE FILE TO RECORD THE RESULT 
	char filename[50]="\0";
	char filename_result[50] = "\0";
	time_t ltime;
	time(&ltime);
    struct tm* now = localtime(&ltime);
	sprintf(filename,"DataAtRange_%d_%d_%d.txt",now->tm_mon+1,
												  now->tm_mday,
												  now->tm_hour);
	sprintf(filename_result,"Result_%d_%d_%d.txt",now->tm_mon+1,
												  now->tm_mday,
												  now->tm_hour);
	FILE* fp = NULL;
	FILE* fp1 = NULL;
    if(m_bSaveDetails){
		fp = fopen(filename,"a+");
	}
    if(m_bSaveResults){
		fp1 = fopen(filename_result,"a+");
	}

	// READ DATA FROM BUFFER
	for( i=0; i<fftnum;i++){
		CString str_Id;
		CString str_I;
		CString str_Q;
		CString str_Phase;
		CString str_Power;

		fIData[i] = (buffer+rangebin*i+m_nFocusRangeBin)->iData;
		fQData[i] = (buffer+rangebin*i+m_nFocusRangeBin)->qData;
		fPhase[i] = atan2(fIData[i],fQData[i])*180/PI;
		fPower[i] = 10*log10( pow(fIData[i]/COEF,2.0)+\
							pow(fQData[i]/COEF,2.0));
		fPwrSum += (pow(fIData[i]/COEF,2.0)+pow(fQData[i]/COEF,2.0));
		
		str_Id.Format("%d",i);
		str_I.Format("%d",(buffer+rangebin*i+m_nFocusRangeBin)->iData);
		str_Q.Format("%d",(buffer+rangebin*i+m_nFocusRangeBin)->qData);
		str_Phase.Format("%lf",fPhase[i]);
		str_Power.Format("%6.2lf",fPower[i]);

		if(m_bSaveDetails && fp){
			fprintf(fp,"Id:%d\t I:%d\t Q:%d\t Phase:%6.2lf\tPower:%6.2lf\n",
					i,fIData[i],fQData[i],fPhase[i],fPower[i]);
		}
		m_ListCtrl_DataInfo.DeleteItem(i);
		m_ListCtrl_DataInfo.InsertItem(i,str_Id);
		m_ListCtrl_DataInfo.SetItemText(i,1,str_I);
		m_ListCtrl_DataInfo.SetItemText(i,2,str_Q);
		m_ListCtrl_DataInfo.SetItemText(i,3,str_Phase);
		m_ListCtrl_DataInfo.SetItemText(i,4,str_Power);
	}
    m_ListCtrl_DataInfo.SetRedraw(TRUE);
	m_ListCtrl_DataInfo.Invalidate();

	calculate(fPhase, fPower, fftnum);

	if(m_bSaveDetails && fp){
	   fprintf(fp,"Current Time: %s\n",ctime(&ltime));
	   fprintf(fp,"PhaseNoiseInDeg: %6.4lf\n",fPhaseNoise_deg);
	   fprintf(fp,"PhaseNosieIndB : %6.2lf\n",fPhaseNoise_dB);
	   fprintf(fp,"==========================================\n");
	   fclose(fp);
   }

   if(m_bSaveResults && fp1){
       fprintf(fp1,"PhaseNoiseInDeg: %6.4lf\t",fPhaseNoise_deg);
       fprintf(fp1,"PhaseNosieIndB : %6.2lf\t",fPhaseNoise_dB);
	   fprintf(fp1,"Time: %d:%d:%d\n",localtime(&ltime)->tm_hour,
									  localtime(&ltime)->tm_min,
									  localtime(&ltime)->tm_sec);
	   fclose(fp1);
   }

    fPwrSum = 0;
	UpdateData(FALSE);
	return;
}

void CRawdataDlg::OnCheckRawControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bPause){
		m_btn_Pause.SetWindowText("START");
	}
	else{
		m_btn_Pause.SetWindowText("PAUSE");
	}
	UpdateData(FALSE);
}

void CRawdataDlg::calculate(double* phase,
							double* power,
							int length)
{

	double Anglesum = 0.0;
	double PowerSum = 0.0;
	double SumOfDif = 0.0;
	double PowSumOfDif = 0.0;

	for(int i=0; i<length; i++){	
		Anglesum += fPhase[i];
		PowerSum += fPower[i];
	}
	
	fPwrMean = PowerSum / length;
	fPhaseMean = Anglesum /= length;
	m_fPwrSum = 10*log10(fPwrSum);

    
	for( i=0; i<length; i++){     
		 SumOfDif += pow((fPhase[i]-fPhaseMean),2.0);
		 PowSumOfDif+=  pow((fPower[i]-fPwrMean),2.0);
	}
	SumOfDif /= length;
	PowSumOfDif /= length;

	fPhaseNoise_deg = pow(SumOfDif,0.5);
	fPhaseNoise_dB = -20 * log10(sin((fPhaseNoise_deg)*PI/180.0));
	qsort( fPower, length, sizeof(double), compare);
	qsort( fPhase, length, sizeof(double), compare);
	fPwrMin = fPower[0];
	fPwrMax = fPower[length-1];
	fPhaseMin = fPhase[0];
	fPhaseMax = fPhase[length-1];

	m_fPhaseNoiseDB = fPhaseNoise_dB;
	m_fPhaseNoiseDeg = fPhaseNoise_deg;
	m_fPwrVariance = pow(PowSumOfDif,0.5);
	m_fPwrAvg = fPwrMean;
	m_fPwrMM = (fPwrMax-fPwrMin);
	m_fPhaseMM = (fPhaseMax-fPhaseMin);
	m_fPhaseAvg = fPhaseMean;
	//UpdateData(FALSE);
	return;
}

void CRawdataDlg::OnCheckSaveDetails() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CRawdataDlg::OnCheckSaveResults() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
