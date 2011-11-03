// PerformanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "PerformanceDlg.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerformanceDlg dialog


CPerformanceDlg::CPerformanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPerformanceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPerformanceDlg)
	m_Tx5v = 0.0f;
	m_Tx50v = 0.0f;
	m_Tx36v = 0.0f;
	m_Tx28v = 0.0f;
	m_Tx15v = 0.0f;
	m_Tx13v = 0.0f;
	m_Tx_Temp = 0.0f;
	m_Tx_Reflect = 0.0f;
	m_Tx_Output = 0.0f;
	m_Tx_Input = 0.0f;
	m_Psm15v = 0.0f;
	m_Ps9v = 0.0f;
	m_Ps6v = 0.0f;
	m_Ps5v4 = 0.0f;
	m_Ps5v3 = 0.0f;
	m_Ps5v2 = 0.0f;
	m_Ps5v1 = 0.0f;
	m_Ps3_3v = 0.0f;
	m_Ps24v = 0.0f;
	m_Ps15v = 0.0f;
	m_Ps12v = 0.0f;
	m_Txm15v = 0.0f;
	m_Psm5v = 0.0f;
	//}}AFX_DATA_INIT
}


void CPerformanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPerformanceDlg)
	DDX_Control(pDX, IDC_STATIC_Txm15v, m_static_txm15v);
	DDX_Control(pDX, IDC_STATIC_Tx5v, m_static_tx5v);
	DDX_Control(pDX, IDC_STATIC_Tx50v, m_static_tx50v);
	DDX_Control(pDX, IDC_STATIC_Tx36v, m_static_tx36v);
	DDX_Control(pDX, IDC_STATIC_Tx28v, m_static_tx28v);
	DDX_Control(pDX, IDC_STATIC_Tx15v, m_static_tx15v);
	DDX_Control(pDX, IDC_STATIC_Tx13v, m_static_tx13v);
	DDX_Control(pDX, IDC_STATIC_SW, m_static_sw);
	DDX_Control(pDX, IDC_STATIC_SP, m_static_sp);
	DDX_Control(pDX, IDC_STATIC_RF_FAULT, m_static_rf_fault);
	DDX_Control(pDX, IDC_STATIC_RF, m_static_rf);
	DDX_Control(pDX, IDC_STATIC_Psm5v, m_static_psm5v);
	DDX_Control(pDX, IDC_STATIC_Psm15v, m_static_psm15v);
	DDX_Control(pDX, IDC_STATIC_Ps9v, m_static_ps9v);
	DDX_Control(pDX, IDC_STATIC_Ps6v, m_static_ps6v);
	DDX_Control(pDX, IDC_STATIC_Ps5v4, m_static_ps5v4);
	DDX_Control(pDX, IDC_STATIC_Ps5v3, m_static_ps5v3);
	DDX_Control(pDX, IDC_STATIC_Ps5v2, m_static_ps5v2);
	DDX_Control(pDX, IDC_STATIC_Ps5v1, m_static_ps5v1);
	DDX_Control(pDX, IDC_STATIC_Ps24v, m_static_ps24v);
	DDX_Control(pDX, IDC_STATIC_Ps3_3v, m_static_ps3_3v);
	DDX_Control(pDX, IDC_STATIC_Ps15v, m_static_ps15v);
	DDX_Control(pDX, IDC_STATIC_Ps12v, m_static_ps12v);
	DDX_Control(pDX, IDC_STATIC_OVERTEMP, m_static_overtemp);
	DDX_Control(pDX, IDC_STATIC_OUTPUT, m_static_output);
	DDX_Text(pDX, IDC_EDIT_Tx5v, m_Tx5v);
	DDX_Text(pDX, IDC_EDIT_Tx50v, m_Tx50v);
	DDX_Text(pDX, IDC_EDIT_Tx36v, m_Tx36v);
	DDX_Text(pDX, IDC_EDIT_Tx28v, m_Tx28v);
	DDX_Text(pDX, IDC_EDIT_Tx15v, m_Tx15v);
	DDX_Text(pDX, IDC_EDIT_Tx13v, m_Tx13v);
	DDX_Text(pDX, IDC_EDIT_Tx_Temp, m_Tx_Temp);
	DDX_Text(pDX, IDC_EDIT_Tx_Reflect, m_Tx_Reflect);
	DDX_Text(pDX, IDC_EDIT_Tx_Output, m_Tx_Output);
	DDX_Text(pDX, IDC_EDIT_Tx_Input, m_Tx_Input);
	DDX_Text(pDX, IDC_EDIT_Psm15v, m_Psm15v);
	DDX_Text(pDX, IDC_EDIT_Ps9v, m_Ps9v);
	DDX_Text(pDX, IDC_EDIT_Ps6v, m_Ps6v);
	DDX_Text(pDX, IDC_EDIT_Ps5v4, m_Ps5v4);
	DDX_Text(pDX, IDC_EDIT_Ps5v3, m_Ps5v3);
	DDX_Text(pDX, IDC_EDIT_Ps5v2, m_Ps5v2);
	DDX_Text(pDX, IDC_EDIT_Ps5v1, m_Ps5v1);
	DDX_Text(pDX, IDC_EDIT_Ps3_3v, m_Ps3_3v);
	DDX_Text(pDX, IDC_EDIT_Ps24v, m_Ps24v);
	DDX_Text(pDX, IDC_EDIT_Ps15v, m_Ps15v);
	DDX_Text(pDX, IDC_EDIT_Ps12v, m_Ps12v);
	DDX_Text(pDX, IDC_EDIT_Txm15v, m_Txm15v);
	DDX_Text(pDX, IDC_EDIT_Psm5v, m_Psm5v);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPerformanceDlg, CDialog)
	//{{AFX_MSG_MAP(CPerformanceDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPerformanceDlg message handlers

HBRUSH CPerformanceDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC 
		|| nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(0,255,0));
		
	}

	if(nCtlColor == CTLCOLOR_LISTBOX){
			//For Alarm list
        //pDC->SetBkColor(RGB(58,58,58));
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(255,255,0));
	}
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CPerformanceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
/*	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	show_status(m_static_tx5v,SM_STATUS_TX5V);
	show_status(m_static_txm15v,SM_STATUS_TXM15V);
	show_status(m_static_tx50v,SM_STATUS_TX50V);
	show_status(m_static_tx36v,SM_STATUS_TX36V);

	show_status(m_static_tx28v,SM_STATUS_TX28V);
	show_status(m_static_tx15v,SM_STATUS_TX15V);
	show_status(m_static_tx13v,SM_STATUS_TX13V);
	show_status(m_static_sw,SM_STATUS_SW);

	show_status(m_static_sp,SM_STATUS_SP);
	show_status(m_static_rf_fault,SM_STATUS_RF_FAULT);
	show_status(m_static_rf,SM_STATUS_RF);
	show_status(m_static_psm5v,SM_STATUS_PSM5V);

	show_status(m_static_psm15v,SM_STATUS_PSM15V);
	show_status(m_static_ps9v,SM_STATUS_PS9V);
	show_status(m_static_ps6v,SM_STATUS_PS6V);
	show_status(m_static_ps5v4,SM_STATUS_PS5V4);

	show_status(m_static_ps5v3,SM_STATUS_PS5V3);
	show_status(m_static_ps5v2,SM_STATUS_PS5V2);
	show_status(m_static_ps5v1,SM_STATUS_PS5V1);
	show_status(m_static_ps24v,SM_STATUS_PS24V);

	show_status(m_static_ps3_3v,SM_STATUS_PS3_3V);
	show_status(m_static_ps15v,SM_STATUS_PS15V);
	show_status(m_static_ps12v,SM_STATUS_PS12V);
	show_status(m_static_overtemp,SM_STATUS_OVERTEMP);
	show_status(m_static_output,SM_STATUS_OUTPUT);

	
	m_Tx5v = status_data.tx_data.tx_5v;
	m_Tx50v = status_data.tx_data.tx_50v;
	m_Tx36v = status_data.tx_data.tx_36v;
	m_Tx28v = status_data.tx_data.tx_28v;
	m_Tx15v = status_data.tx_data.tx_15v;
	m_Txm15v = status_data.tx_data.tx_m15v;
	m_Tx13v = status_data.tx_data.tx_13v;
	m_Tx_Temp = status_data.tx_data.temperature;
	m_Tx_Reflect = status_data.tx_data.reflect_power;
	m_Tx_Output = status_data.tx_data.output_power;
	m_Tx_Input =  status_data.tx_data.input_power;
	
	m_Psm15v = status_data.cab_data.cab_m15v;
	m_Ps9v = status_data.cab_data.cab_9v;
	m_Ps6v = status_data.cab_data.cab_6v;
	m_Ps5v4 = status_data.cab_data.cab_5v4;
	m_Ps5v3 = status_data.cab_data.cab_5v3;
	m_Ps5v2 = status_data.cab_data.cab_5v2;
	m_Ps5v1 = status_data.cab_data.cab_5v1;
	m_Ps3_3v = status_data.cab_data.cab_3_3v;
	m_Ps24v = status_data.cab_data.cab_24v;
	m_Ps15v = status_data.cab_data.cab_15v;
	m_Ps12v = status_data.cab_data.cab_12v;
	m_Psm5v = status_data.cab_data.cab_m5v;

	UpdateData(false);
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPerformanceDlg::show_status(CStatic& s, const int index)
{
	/*
	if(g_sm_data[index]==1)
		s.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON16));
	else if (g_sm_data[index]==0)
		s.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON15));
		*/
	return;
}
