// BasicSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "BasicSettingDlg.h"
#include "Global.h"
#include "Global_CtrlWords.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasicSettingDlg dialog


CBasicSettingDlg::CBasicSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBasicSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBasicSettingDlg)
	m_nPRT_ObliqueHigh = 0;
	m_nPW_ObliqueHigh = 0;
	m_nTAvg_ObliqueHigh = 0;
	m_nPRT_ObliqueLow = 0;
	m_nPW_ObliqueLow = 0;
	m_nSAvg_ObliqueHigh = 0;
	m_nSAvg_ObliqueLow = 0;
	m_nTAvg_ObliqueLow = 0;
	m_nPRT_VerticalHigh = 0;
	m_nPW_VerticalHigh = 0;
	m_nSAvg_VerticalHigh = 0;
	m_nTAvg_VerticalHigh = 0;
	m_nPRT_VerticalLow = 0;
	m_nPW_VerticalLow = 0;
	m_nSAvg_VerticalLow = 0;
	m_nTAvg_VerticalLow = 0;
	m_nSTC_East = 0;
	m_nSTC_North = 0;
	m_nSTC_Vertical = 0;
	m_nSTC_South = 0;
	m_nSTC_West = 0;
	m_bWholeRange = FALSE;
	m_bPulseCompress = FALSE;
	m_bHighModeSetting = FALSE;
	m_bHighMode240mGateRange = FALSE;
	m_b25MSigClose = FALSE;
	//}}AFX_DATA_INIT
}


void CBasicSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBasicSettingDlg)
	DDX_Control(pDX, IDC_COMBO_PSC, m_PSC_ComboBox);
	DDX_Control(pDX, IDC_COMBO_FFT, m_nFFT_ComboBox);
	DDX_Control(pDX, IDC_RANGBIN_LIST, m_list_RangeBin);
	DDX_Text(pDX, IDC_OBLIQUE_HIGH_PRT, m_nPRT_ObliqueHigh);
	DDX_Text(pDX, IDC_OBLIQUE_HIGH_PW, m_nPW_ObliqueHigh);
	DDX_Text(pDX, IDC_OBLIQUE_HIGH_TAVG, m_nTAvg_ObliqueHigh);
	DDV_MinMaxUInt(pDX, m_nTAvg_ObliqueHigh, 0, 1000);
	DDX_Text(pDX, IDC_OBLIQUE_LOW_PRT, m_nPRT_ObliqueLow);
	DDX_Text(pDX, IDC_OBLIQUE_LOW_PW, m_nPW_ObliqueLow);
	DDX_Text(pDX, IDC_OBLIQUE_HIGH_SAVG, m_nSAvg_ObliqueHigh);
	DDV_MinMaxUInt(pDX, m_nSAvg_ObliqueHigh, 1, 60);
	DDX_Text(pDX, IDC_OBLIQUE_LOW_SAVG, m_nSAvg_ObliqueLow);
	DDV_MinMaxUInt(pDX, m_nSAvg_ObliqueLow, 1, 60);
	DDX_Text(pDX, IDC_OBLIQUE_LOW_TAVG, m_nTAvg_ObliqueLow);
	DDX_Text(pDX, IDC_VERTICAL_HIGH_PRT, m_nPRT_VerticalHigh);
	DDX_Text(pDX, IDC_VERTICAL_HIGH_PW, m_nPW_VerticalHigh);
	DDX_Text(pDX, IDC_VERTICAL_HIGH_SAVG, m_nSAvg_VerticalHigh);
	DDV_MinMaxUInt(pDX, m_nSAvg_VerticalHigh, 1, 60);
	DDX_Text(pDX, IDC_VERTICAL_HIGH_TAVG, m_nTAvg_VerticalHigh);
	DDX_Text(pDX, IDC_VERTICAL_LOW_PRT, m_nPRT_VerticalLow);
	DDX_Text(pDX, IDC_VERTICAL_LOW_PW, m_nPW_VerticalLow);
	DDX_Text(pDX, IDC_VERTICAL_LOW_SAVG, m_nSAvg_VerticalLow);
	DDV_MinMaxUInt(pDX, m_nSAvg_VerticalLow, 1, 60);
	DDX_Text(pDX, IDC_VERTICAL_LOW_TAVG, m_nTAvg_VerticalLow);
	DDX_Text(pDX, IDC_EAST, m_nSTC_East);
	DDV_MinMaxInt(pDX, m_nSTC_East, 0, 31);
	DDX_Text(pDX, IDC_NORTH, m_nSTC_North);
	DDV_MinMaxInt(pDX, m_nSTC_North, 0, 31);
	DDX_Text(pDX, IDC_VERTICAL, m_nSTC_Vertical);
	DDV_MinMaxInt(pDX, m_nSTC_Vertical, 0, 31);
	DDX_Text(pDX, IDC_SOUTH, m_nSTC_South);
	DDV_MinMaxInt(pDX, m_nSTC_South, 0, 31);
	DDX_Text(pDX, IDC_WEST, m_nSTC_West);
	DDV_MinMaxInt(pDX, m_nSTC_West, 0, 31);
	DDX_Check(pDX, IDC_WHOLERANGE, m_bWholeRange);
	DDX_Check(pDX, IDC_PULSECOMPRESS, m_bPulseCompress);
	DDX_Check(pDX, IDC_HIGHMODETOGGLE, m_bHighModeSetting);
	DDX_Check(pDX, IDC_HIGHMODE240, m_bHighMode240mGateRange);
	DDX_Check(pDX, IDC_25M_SIG_CLOSE, m_b25MSigClose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBasicSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CBasicSettingDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_FFT, OnSelchangeComboFft)
	ON_EN_CHANGE(IDC_EAST, OnChangeEast)
	ON_EN_CHANGE(IDC_NORTH, OnChangeNorth)
	ON_EN_CHANGE(IDC_VERTICAL, OnChangeVertical)
	ON_LBN_SELCHANGE(IDC_RANGBIN_LIST, OnSelchangeRangbinList)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_WEST, OnChangeWest)
	ON_EN_CHANGE(IDC_SOUTH, OnChangeSouth)
	ON_CBN_SELCHANGE(IDC_COMBO_PSC, OnSelchangeComboPsc)
	ON_BN_CLICKED(IDC_WHOLERANGE, OnWholerange)
	ON_BN_CLICKED(IDC_PULSECOMPRESS, OnPulsecompress)
	ON_BN_CLICKED(IDC_HIGHMODETOGGLE, OnHighmodetoggle)
	ON_BN_CLICKED(IDC_HIGHMODE240, OnHighmode240)
	ON_BN_CLICKED(IDC_25M_SIG_CLOSE, On25mSigClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasicSettingDlg message handlers

BOOL CBasicSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//For outlook
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	///////////////////////////////
    //Full fill the dialog
	m_nPRT_ObliqueHigh  = global.basic.basicinfo.oblique_struct.prt_high;
	m_nPW_ObliqueHigh   = global.basic.basicinfo.oblique_struct.pulse_width_high;
	m_nSAvg_ObliqueHigh = global.basic.basicinfo.oblique_struct.spec_domain_avg_high;
    m_nTAvg_ObliqueHigh = global.basic.basicinfo.oblique_struct.time_domain_avg_high;

	m_nPRT_ObliqueLow  = global.basic.basicinfo.oblique_struct.prt_low;
	m_nPW_ObliqueLow   = global.basic.basicinfo.oblique_struct.pulse_width_low;
	m_nSAvg_ObliqueLow = global.basic.basicinfo.oblique_struct.spec_domain_avg_low;
	m_nTAvg_ObliqueLow = global.basic.basicinfo.oblique_struct.time_domain_avg_low;

	m_nPRT_VerticalHigh  = global.basic.basicinfo.vertical_struct.prt_high;
	m_nPW_VerticalHigh   = global.basic.basicinfo.vertical_struct.pulse_width_high;
	m_nSAvg_VerticalHigh = global.basic.basicinfo.vertical_struct.spec_domain_avg_high;
	m_nTAvg_VerticalHigh = global.basic.basicinfo.vertical_struct.time_domain_avg_high;

	m_nPRT_VerticalLow  = global.basic.basicinfo.vertical_struct.prt_low;
	m_nPW_VerticalLow   = global.basic.basicinfo.vertical_struct.pulse_width_low;
	m_nSAvg_VerticalLow = global.basic.basicinfo.vertical_struct.spec_domain_avg_low;
	m_nTAvg_VerticalLow = global.basic.basicinfo.vertical_struct.time_domain_avg_low;

	//STC
	for(int i=0; i<24; i++){
		CString str1;
		if(i<10)
			str1.Format("Bin 0%d",i);
		else
			str1.Format("Bin %d",i);
		m_list_RangeBin.InsertString(i,str1);
		m_list_RangeBin.SetItemData(i,i);
	}
	m_list_RangeBin.SetCurSel(0);

	//HIGH MODE STC SETTING
	m_bHighModeSetting = global.basic.basicinfo.bHighModeSetting;
	if(m_bHighModeSetting){
		m_nSTC_East     = global.basic.basicinfo.stc_sturct_high.ch_stc[0][0];
		m_nSTC_North    = global.basic.basicinfo.stc_sturct_high.ch_stc[0][1];
		m_nSTC_Vertical = global.basic.basicinfo.stc_sturct_high.ch_stc[0][2];
		m_nSTC_West     = global.basic.basicinfo.stc_sturct_high.ch_stc[0][3];
		m_nSTC_South    = global.basic.basicinfo.stc_sturct_high.ch_stc[0][4];
	}
	else
	{
		m_nSTC_East     = global.basic.basicinfo.stc_struct.ch_stc[0][0];
		m_nSTC_North    = global.basic.basicinfo.stc_struct.ch_stc[0][1];
		m_nSTC_Vertical = global.basic.basicinfo.stc_struct.ch_stc[0][2];
		m_nSTC_West     = global.basic.basicinfo.stc_struct.ch_stc[0][3];
		m_nSTC_South    = global.basic.basicinfo.stc_struct.ch_stc[0][4];
	}

	//WHOLE RANGE STC SETTING
	m_bWholeRange = global.basic.basicinfo.bWholeRangeAddSTC;
	//FFT POINTS
	m_nFFT_ComboBox.InsertString(0,"128");
	m_nFFT_ComboBox.InsertString(1,"256");
	m_nFFT_ComboBox.InsertString(2,"512");
	m_nFFT_ComboBox.InsertString(3,"1024");
	m_nFFT_ComboBox.InsertString(4,"2048");

    m_nFFT_ComboBox.SetItemData(0,128);
    m_nFFT_ComboBox.SetItemData(1,256);
	m_nFFT_ComboBox.SetItemData(2,512);
    m_nFFT_ComboBox.SetItemData(3,1024);
	m_nFFT_ComboBox.SetItemData(4,2048);
	
	int nfft = global.basic.basicinfo.nfft;
	switch(nfft){
	case 128:
		m_nFFT_ComboBox.SetCurSel(0);
		break;
	case 256:
		m_nFFT_ComboBox.SetCurSel(1);
		break;
	case 512:
		m_nFFT_ComboBox.SetCurSel(2);
		break;
	case 1024:
		m_nFFT_ComboBox.SetCurSel(3);
		break;
	case 2048:
		m_nFFT_ComboBox.SetCurSel(4);
	default:
		break;
	};
	
	//PSC SEL
	m_PSC_ComboBox.InsertString(0,"EVERY SWEEP");
	m_PSC_ComboBox.SetItemData(0,0);
	m_PSC_ComboBox.InsertString(1,"EVERY RADIAL");
	m_PSC_ComboBox.SetItemData(1,1);
	int nPSCSel = global.basic.basicinfo.nPSCModeSel;
	switch(nPSCSel){
	case 0:
        m_PSC_ComboBox.SetCurSel(0);
		break;
	case 1:
		m_PSC_ComboBox.SetCurSel(1);
		break;
	default:
		break;
	}

	//PULSE COMPRESS
	m_bPulseCompress = global.basic.basicinfo.bPulseCompress;

	//FOR HIGH MODE GATE RANGE 240
	m_bHighMode240mGateRange = global.basic.basicinfo.bHighModeRange240m;

	//FOR NEW FREQENCE GENERATOR 25M CLOSE
	m_b25MSigClose = global.basic.basicinfo.b25MCLOSE;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
//FFT POINT SELECTION
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnSelchangeComboFft() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel_index = m_nFFT_ComboBox.GetCurSel();
	global.basic.basicinfo.nfft = m_nFFT_ComboBox.GetItemData(sel_index);
}

/////////////////////////////////////////////////////////////////////////////
//PSC SELECTION
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnSelchangeComboPsc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel_index = m_PSC_ComboBox.GetCurSel();
	global.basic.basicinfo.nPSCModeSel = m_PSC_ComboBox.GetItemData(sel_index);
}

/////////////////////////////////////////////////////////////////////////////
//STC EAST SETTING
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnChangeEast() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel_index = m_list_RangeBin.GetCurSel();
	int rangebin = m_list_RangeBin.GetItemData(sel_index);

	if(m_bHighModeSetting)
		global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][0] = m_nSTC_East;
	else
		global.basic.basicinfo.stc_struct.ch_stc[rangebin][0] = m_nSTC_East;
}

/////////////////////////////////////////////////////////////////////////////
//STC NORTH SETTING
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnChangeNorth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel_index = m_list_RangeBin.GetCurSel();
	int rangebin = m_list_RangeBin.GetItemData(sel_index);
	if(m_bHighModeSetting)
		global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][1] = m_nSTC_North;
	else
		global.basic.basicinfo.stc_struct.ch_stc[rangebin][1] = m_nSTC_North;
}

/////////////////////////////////////////////////////////////////////////////
//STC VERTICAL SETTING
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnChangeVertical() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel_index = m_list_RangeBin.GetCurSel();
	int rangebin = m_list_RangeBin.GetItemData(sel_index);
	if(m_bHighModeSetting)
		global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][2] = m_nSTC_Vertical;
	else
		global.basic.basicinfo.stc_struct.ch_stc[rangebin][2] = m_nSTC_Vertical;
}

/////////////////////////////////////////////////////////////////////////////
//STC WEST SETTING
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnChangeWest() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel_index = m_list_RangeBin.GetCurSel();
	int rangebin = m_list_RangeBin.GetItemData(sel_index);
	if(m_bHighModeSetting)
		global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][3] = m_nSTC_West;
	else
		global.basic.basicinfo.stc_struct.ch_stc[rangebin][3] = m_nSTC_West;
}

/////////////////////////////////////////////////////////////////////////////
//STC SOUTH SETTING
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnChangeSouth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel_index = m_list_RangeBin.GetCurSel();
	int rangebin = m_list_RangeBin.GetItemData(sel_index);
	if(m_bHighModeSetting)
		global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][4] = m_nSTC_South;
	else
		global.basic.basicinfo.stc_struct.ch_stc[rangebin][4] = m_nSTC_South;
}

/////////////////////////////////////////////////////////////////////////////
//STC SETTING FOR EVERY RANGE
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnSelchangeRangbinList() 
{
	// TODO: Add your control notification handler code here
	int sel_index = m_list_RangeBin.GetCurSel();
	int rangebin = m_list_RangeBin.GetItemData(sel_index);

	if(m_bHighModeSetting){
		m_nSTC_East =  global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][0];
		m_nSTC_North = global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][1];
		m_nSTC_Vertical = global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][2];
		m_nSTC_West = global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][3];
		m_nSTC_South = global.basic.basicinfo.stc_sturct_high.ch_stc[rangebin][4];
	}
	else{
		m_nSTC_East =  global.basic.basicinfo.stc_struct.ch_stc[rangebin][0];
		m_nSTC_North = global.basic.basicinfo.stc_struct.ch_stc[rangebin][1];
		m_nSTC_Vertical = global.basic.basicinfo.stc_struct.ch_stc[rangebin][2];
		m_nSTC_West = global.basic.basicinfo.stc_struct.ch_stc[rangebin][3];
		m_nSTC_South = global.basic.basicinfo.stc_struct.ch_stc[rangebin][4];
	}
	UpdateData(FALSE);
}

HBRUSH CBasicSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(255,255,0));
	}
	if(nCtlColor == CTLCOLOR_LISTBOX){
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(255,255,0));	
	}

	return m_bkBrush;
	// TODO: Return a different brush if the default is not desired
	//return hbr;
}

/////////////////////////////////////////////////////////////////////////////
//STC WHOLE RANGE CONTROL
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnWholerange() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    global.basic.basicinfo.bWholeRangeAddSTC = m_bWholeRange;
}

/////////////////////////////////////////////////////////////////////////////
//PULSE COMPRESS SELECTION
/////////////////////////////////////////////////////////////////////////////
void CBasicSettingDlg::OnPulsecompress() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    global.basic.basicinfo.bPulseCompress = m_bPulseCompress;
}

void CBasicSettingDlg::OnHighmodetoggle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	global.basic.basicinfo.bHighModeSetting = m_bHighModeSetting;
}

void CBasicSettingDlg::OnHighmode240() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	global.basic.basicinfo.bHighModeRange240m = m_bHighMode240mGateRange;
}

void CBasicSettingDlg::On25mSigClose() 
{
	// TODO: Add your control notification handler code here
	//FOR NEW FREQENCE GENERATOR 25M CLOSE
	UpdateData(TRUE);
	global.basic.basicinfo.b25MCLOSE = m_b25MSigClose;
}
