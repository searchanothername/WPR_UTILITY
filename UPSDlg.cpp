// UPSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "UPSDlg.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUPSDlg dialog


CUPSDlg::CUPSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUPSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUPSDlg)
	m_f_battery_voltage = 0.0f;
	m_f_ip_fault_voltage = 0.0f;
	m_f_ip_frequence = 0.0f;
	m_f_ip_voltage = 0.0f;
	m_f_op_load = 0.0f;
	m_f_op_voltage = 0.0f;
	m_f_temperature = 0.0f;
	//}}AFX_DATA_INIT
}


void CUPSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUPSDlg)
	DDX_Control(pDX, IDC_STATIC_BATTERY_LOW, m_static_BATTERY_LOW);
	DDX_Control(pDX, IDC_STATIC_BYPASSBOOST, m_static_BYPASSBOOST);
	DDX_Control(pDX, IDC_STATIC_ONLINE, m_static_ONLINE);
	DDX_Control(pDX, IDC_STATIC_SHUT_DOWN_ACTIVE, m_static_SHUT_DOWN_ACTIVE);
	DDX_Control(pDX, IDC_STATIC_TEST_IN_PROGRESS, m_static_TEST_IN_PROGRESS);
	DDX_Control(pDX, IDC_STATIC_UPS_FAIL, m_static_UPS_FAIL);
	DDX_Control(pDX, IDC_STATIC_UTILITY_FAIL, m_static_UTILITY_FAIL);
	DDX_Text(pDX, IDC_EDIT_BATTERY_VOLTAGE, m_f_battery_voltage);
	DDX_Text(pDX, IDC_EDIT_IP_FAULT_VOLTAGE, m_f_ip_fault_voltage);
	DDX_Text(pDX, IDC_EDIT_IP_FREQUENCE, m_f_ip_frequence);
	DDX_Text(pDX, IDC_EDIT_IP_VOLTAGE, m_f_ip_voltage);
	DDX_Text(pDX, IDC_EDIT_OP_LOAD, m_f_op_load);
	DDX_Text(pDX, IDC_EDIT_OP_VOLTAGE, m_f_op_voltage);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE, m_f_temperature);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUPSDlg, CDialog)
	//{{AFX_MSG_MAP(CUPSDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUPSDlg message handlers

BOOL CUPSDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));


	m_f_ip_voltage = g_ups_data.ups_I_P_voltage;
	m_f_ip_fault_voltage = g_ups_data.ups_I_P_fault_voltage;
	m_f_op_voltage = g_ups_data.ups_O_P_voltage,
	m_f_op_load = g_ups_data.ups_O_P_load,
	m_f_ip_frequence = g_ups_data.ups_I_P_frquence,
	m_f_battery_voltage = g_ups_data.ups_Battery_voltage,
	m_f_temperature = g_ups_data.ups_Temperature,

	show_status(m_static_UTILITY_FAIL, g_ups_data.ups_status.status._utility_faild);
	show_status(m_static_BATTERY_LOW, g_ups_data.ups_status.status._battery_low);
	show_status(m_static_BYPASSBOOST, g_ups_data.ups_status.status._bypass_boot_active);
	show_status(m_static_UPS_FAIL, g_ups_data.ups_status.status._failed);
	show_status(m_static_ONLINE, g_ups_data.ups_status.status._standby);
	show_status(m_static_TEST_IN_PROGRESS, g_ups_data.ups_status.status._test_in_progress);
	show_status(m_static_SHUT_DOWN_ACTIVE, g_ups_data.ups_status.status._shut_down_active);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CUPSDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
	//return hbr;
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


void CUPSDlg::show_status(CStatic& s, int status)
{
	if(status==1)
		s.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON16));
	else if (status==0)
		s.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON15));
	return;
}