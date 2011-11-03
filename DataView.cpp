// DataView.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "DataView.h"
#include "WPR_UTILITIESDlg.h"
#include "Global.h"
#include "DataView.h"
#include "DataHandlor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataView dialog

extern CDataHandlor data;
CDataView::CDataView(CWnd* pParent /*=NULL*/)
	: CDialog(CDataView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataView)
	m_str_MarkerPower = _T("");
	m_bIData = TRUE;
	m_bQData = FALSE;
	m_bNum = FALSE;
	m_bSamp = FALSE;
	m_bSingle = TRUE ;
	m_bAvg = FALSE;
	m_nMarkerValue = 0;
	m_nValue = 0;
	m_str_MarkerPeak = _T("");
	m_str_SweepNum = _T("10");
	m_str_SweepStart = _T("0");
	m_str_FocusRange = _T("22");
	m_velocity = 0.0;
	m_bNoiseLevel = FALSE;
	m_bPeakS = FALSE;
	m_bPeakA = FALSE;
	//}}AFX_DATA_INIT

	m_nSweepStart = 0;
	m_nSweepNum = 10;
	m_nFocusRangeBin = 22;
	m_nBeamId = 0;
}


void CDataView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataView)
	DDX_Control(pDX, IDC_SLIDER_MARKER, m_MarkerCtrl);
	DDX_Control(pDX, IDC_PROGRESS_SPEC, m_progress);
	DDX_Control(pDX, IDC_TAB, m_DataViewTab);
	DDX_Text(pDX, IDC_EDIT_MARKER_POWER, m_str_MarkerPower);
	DDX_Check(pDX, IDC_CHECK_IDATA, m_bIData);
	DDX_Check(pDX, IDC_CHECK_QDATA, m_bQData);
	DDX_Check(pDX, IDC_CHECK_NUM, m_bNum);
	DDX_Check(pDX, IDC_CHECK_SAMP, m_bSamp);
	DDX_Check(pDX, IDC_CHECK_SPEC_SINGLE, m_bSingle);
	DDX_Check(pDX, IDC_CHECK_SPEC_AVG, m_bAvg);
	DDX_Slider(pDX, IDC_SLIDER_MARKER, m_nMarkerValue);
	DDX_Text(pDX, IDC_EDIT_MARKER, m_nValue);
	DDV_MinMaxInt(pDX, m_nValue, 0, 1024);
	DDX_Text(pDX, IDC_EDIT_MARKER_PEAK, m_str_MarkerPeak);
	DDX_Text(pDX, IDC_EDIT_SWEEP_NUM, m_str_SweepNum);
	DDX_Text(pDX, IDC_EDIT_SWEEP_START, m_str_SweepStart);
	DDX_Text(pDX, IDC_EDIT_FOCUS_RANGBIN, m_str_FocusRange);
	DDX_Text(pDX, IDC_EDIT_VELOCITY, m_velocity);
	DDX_Check(pDX, IDC_CHECK_NOISELEVEL, m_bNoiseLevel);
	DDX_Check(pDX, IDC_CHECK_PEAK_S, m_bPeakS);
	DDX_Check(pDX, IDC_CHECK_PEAK_A, m_bPeakA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataView, CDialog)
	//{{AFX_MSG_MAP(CDataView)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_IDATA, OnCheckIdata)
	ON_BN_CLICKED(IDC_CHECK_QDATA, OnCheckQdata)
	ON_BN_CLICKED(IDC_CHECK_SAMP, OnCheckSamp)
	ON_BN_CLICKED(IDC_CHECK_NUM, OnCheckNum)
	ON_BN_CLICKED(IDC_CHECK_SPEC_AVG, OnCheckSpecAvg)
	ON_BN_CLICKED(IDC_CHECK_SPEC_SINGLE, OnCheckSpecSingle)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_NOISELEVEL, OnCheckNoiselevel)
    ON_MESSAGE(WM_SHOW_DATA,ShowData)
	ON_MESSAGE(WM_SHOW_SPEC_SINGLE, ShowSpecSingle)
	ON_MESSAGE(WM_SHOW_SPEC_AVG, ShowSpecAvg)
	ON_BN_CLICKED(IDC_CHECK_PEAK_A, OnCheckPeakA)
	ON_BN_CLICKED(IDC_CHECK_PEAK_S, OnCheckPeakS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataView message handlers

BOOL CDataView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	bDataComming = FALSE;
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));
	m_DataViewTab.GetClientRect(rect);
	rect.top  += 10;
	rect.bottom -= 30;
	rect.left +=10;
	rect.right -= 10;

	this->m_DataViewTab.InsertItem(0,_T("TIME SERIES"));
	this->m_DataViewTab.InsertItem(1,_T("SPECTRA"));
	this->m_DataViewTab.InsertItem(2,_T("RAW DATA"));

	time_series_dlg.Create(IDD_DIALOG_TIME_SERIES,&m_DataViewTab);
	time_series_dlg.MoveWindow(rect);
	time_series_dlg.ShowWindow(SW_SHOW);
	time_series_dlg.setParent(this);

	freq_dlg.Create(IDD_DIALOG_FREQ,&m_DataViewTab);
	freq_dlg.MoveWindow(rect);
	freq_dlg.ShowWindow(SW_HIDE);
	freq_dlg.setParent(this);

	raw_dlg.Create(IDD_DIALOG_RAW,&m_DataViewTab);
	raw_dlg.MoveWindow(rect);
	raw_dlg.ShowWindow(SW_HIDE);
	raw_dlg.setParent(this);
	
	m_progress.SetBkColor(RGB(58,58,58));
	m_progress.SetRange(0,100);

	m_MarkerCtrl.SetRange(0,global.basic.basicinfo.nfft-1,TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDataView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CDataView::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	switch( m_DataViewTab.GetCurSel())
	{
	case 0:
		time_series_dlg.ShowWindow(SW_SHOW);
		freq_dlg.ShowWindow(SW_HIDE);
		raw_dlg.ShowWindow(SW_HIDE);
		break;
	case 1:
		time_series_dlg.ShowWindow(SW_HIDE);
		freq_dlg.ShowWindow(SW_SHOW);
		raw_dlg.ShowWindow(SW_HIDE);
		break;
	case 2:
		time_series_dlg.ShowWindow(SW_HIDE);
		freq_dlg.ShowWindow(SW_HIDE);
		raw_dlg.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CDataView::OnDestroy() 
{
	if(_utility)
	 _utility->bDataViewEnable = FALSE;
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

}

void CDataView::ShowData(UINT wParam, UINT lParam)
{

	//TRANS THE STRING TO NUMBER
    char* str_focus_range;
	char* str_sweep_num;
	char* str_start_sweep;
	int nLength;

	GetDlgItem(IDC_EDIT_FOCUS_RANGBIN)->GetWindowText(m_str_FocusRange);
	GetDlgItem(IDC_EDIT_SWEEP_NUM)->GetWindowText(m_str_SweepNum);
	GetDlgItem(IDC_EDIT_SWEEP_START)->GetWindowText(m_str_SweepStart);

	nLength = m_str_FocusRange.GetLength()+1;
	str_focus_range = m_str_FocusRange.GetBufferSetLength(nLength);
	m_nFocusRangeBin = atoi(str_focus_range);

	nLength = m_str_SweepNum.GetLength()+1;
	str_sweep_num = m_str_SweepNum.GetBufferSetLength(nLength);
	m_nSweepNum = atoi(str_sweep_num);

    nLength = m_str_SweepStart.GetLength()+1;
	str_start_sweep = m_str_SweepStart.GetBufferSetLength(nLength);
	m_nSweepStart = atoi(str_start_sweep);

	if(m_nSweepNum >global.basic.basicinfo.nfft||m_nSweepNum<0)
		m_nSweepNum = 0;
	if(m_nSweepStart+m_nSweepNum >global.basic.basicinfo.nfft||m_nSweepStart<0){
		m_nSweepStart = 0;
		m_nSweepNum = global.basic.basicinfo.nfft;
	}

	//GET THE BEAM ID 
	m_nBeamId = lParam;
	if(lParam%2==1){
		const int offset = global_advance.dspsetting.nBeginGateMoveL;
		if(m_nFocusRangeBin > global_advance.dmasetting.nDMA_Low/2-1-offset)
			m_nFocusRangeBin = 10;
	}else{
		const int offset = global_advance.dspsetting.nBeginGateMoveH;
		if(m_nFocusRangeBin > global_advance.dmasetting.nDMA_High/2-1-offset)
			m_nFocusRangeBin = 10;
	}
	
	bDataComming = TRUE;

	::PostMessage(time_series_dlg.m_hWnd, WM_SHOW_TIMESERIES, wParam,lParam);
	::PostMessage(raw_dlg.m_hWnd,WM_SHOW_DATAINFO, wParam, lParam);

	int max_spec = g_knumber_of_spectra[lParam];
	m_progress.SetPos((int)((wParam)*100.0/(max_spec-1)));
	return;
}


void CDataView::ShowSpecSingle(UINT wParam, UINT lParam)
{
	char* str_focus_range;
	int nLength;

	GetDlgItem(IDC_EDIT_FOCUS_RANGBIN)->GetWindowText(m_str_FocusRange);
	nLength = m_str_FocusRange.GetLength()+1;
	str_focus_range = m_str_FocusRange.GetBufferSetLength(nLength);
	m_nFocusRangeBin = atoi(str_focus_range);

	if(lParam%2==1){
		const int offset = global_advance.dspsetting.nBeginGateMoveL;
		if(m_nFocusRangeBin > global_advance.dmasetting.nDMA_Low/2-1-offset)
			m_nFocusRangeBin = 10;
	}else{
		const int offset = global_advance.dspsetting.nBeginGateMoveH;
		if(m_nFocusRangeBin > global_advance.dmasetting.nDMA_High/2-1-offset)
			m_nFocusRangeBin = 10;
	}
	double marker_power_single =*(data._spec_single->spectra+m_nFocusRangeBin*MAXFFTPOINTS+m_nValue);
	double marker_power_avg = *(data._spec_avged_cpy->spectra+m_nFocusRangeBin*MAXFFTPOINTS+m_nValue);
	m_str_MarkerPower.Format("%4.2f, %4.2f",marker_power_single,marker_power_avg);
	m_str_MarkerPeak.Format("%4.2f",global.spec_avg_limit.limit[m_nFocusRangeBin].max);
	UpdateData(FALSE);
	::PostMessage(freq_dlg.m_hWnd, WM_SHOW_SPEC_SINGLE_VIEW, wParam, lParam);
	return;
}


void CDataView::ShowSpecAvg(UINT wParam, UINT lParam)
{
	if(lParam%2==1){
		const int offset = global_advance.dspsetting.nBeginGateMoveL;
		if(m_nFocusRangeBin > global_advance.dmasetting.nDMA_Low/2-1-offset)
			m_nFocusRangeBin = 10;
	}else{
		const int offset = global_advance.dspsetting.nBeginGateMoveH;
		if(m_nFocusRangeBin > global_advance.dmasetting.nDMA_High/2-1-offset)
			m_nFocusRangeBin = 10;
	}
	::PostMessage(freq_dlg.m_hWnd, WM_SHOW_SPEC_AVG_VIEW, wParam, lParam);
	return;
}


void CDataView::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(_utility)
	 _utility->bDataViewEnable = FALSE;
	CDialog::OnClose();
}

void CDataView::setParent(CWPR_UTILITIESDlg* pParent)
{
	_utility = pParent;
}

void CDataView::OnCheckIdata() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDataView::OnCheckQdata() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDataView::OnCheckSamp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDataView::OnCheckNum() 
{
	// TODO: Add your control notification handler code here
   UpdateData(TRUE);
}

void CDataView::OnOK() 
{
	// TODO: Add extra validation here
	if(_utility)
	 _utility->bDataViewEnable = FALSE;
	CDialog::OnOK();
}

void CDataView::OnCheckSpecAvg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDataView::OnCheckSpecSingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDataView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	m_nValue = m_nMarkerValue;

	if(bDataComming){

		//Calcuate velocity
		int n_fft = data.nFFT;
		int prt = g_cur_prt[m_nBeamId];
		int tda = g_ktda_samples[m_nBeamId];

		double delta = (double) (1000000.0) / (double)(n_fft * prt * tda);
		double klambda = (double) (149891000) / (global_advance.dspsetting.nCenterFreq*1000.0); //1290000;
		double fibin = delta * (m_nValue-n_fft/2);	
		m_velocity = klambda * fibin;


		double marker_power_single =*(data._spec_single->spectra+m_nFocusRangeBin*MAXFFTPOINTS+m_nValue);
		double marker_power_avg = *(data._spec_avged_cpy->spectra+m_nFocusRangeBin*MAXFFTPOINTS+m_nValue);
		m_str_MarkerPower.Format("%6.2f, %6.2f",marker_power_single,marker_power_avg);	
		m_str_MarkerPeak.Format("%6.2f",global.spec_avg_limit.limit[m_nFocusRangeBin].max);
	}
	UpdateData(FALSE);
	::PostMessage(freq_dlg.m_hWnd,WM_UPDAE_MARKER,m_nValue,0);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDataView::OnCheckNoiselevel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDataView::OnCheckPeakA() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDataView::OnCheckPeakS() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
