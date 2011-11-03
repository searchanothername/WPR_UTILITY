// Pf_sys_pa_page.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Pf_sys_pa_page.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Global_SM.h"
/////////////////////////////////////////////////////////////////////////////
// CPf_sys_pa_page property page

IMPLEMENT_DYNCREATE(CPf_sys_pa_page, CPropertyPage)

CPf_sys_pa_page::CPf_sys_pa_page() : CPropertyPage(CPf_sys_pa_page::IDD)
{
	//{{AFX_DATA_INIT(CPf_sys_pa_page)
	m_str_SPARE = _T("PREWARM");
	m_str_DutyCycleRatio = _T("FAULT");
	m_str_LRSwitch = _T("LOCAL");
	m_str_VSWR = _T("FAULT");
	m_str_AirTemp = _T("FAULT");
	m_str_ModuleFault = _T("FAULT");
	m_str_DriverFault = _T("FAULT");
	m_str_SystemFault = _T("FAULT");
	m_str_HPA1_STATUS = _T("FAULT");
	m_str_HPA10_STATUS = _T("FAULT");
	m_str_HPA2_STATUS = _T("FAULT");
	m_str_HPA3_STATUS = _T("FAULT");
	m_str_HPA4_STATUS = _T("FAULT");
	m_str_HPA5_STATUS = _T("FAULT");
	m_str_HPA6_STATUS = _T("FAULT");
	m_str_HPA7_STATUS = _T("FAULT");
	m_str_HPA8_STATUS = _T("FAULT");
	m_str_HPA9_STATUS = _T("FAULT");
	//}}AFX_DATA_INIT
}

CPf_sys_pa_page::~CPf_sys_pa_page()
{
}

void CPf_sys_pa_page::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPF_SYS_PA_PAGE)
	DDX_Text(pDX, IDC_SPARE_EDIT, m_str_SPARE);
	DDX_Text(pDX, IDC_DUTY_CYCLE_RATIO_EDIT, m_str_DutyCycleRatio);
	DDX_Text(pDX, IDC_LR_SWITCH_EDIT, m_str_LRSwitch);
	DDX_Text(pDX, IDC_VSWR_EDIT, m_str_VSWR);
	DDX_Text(pDX, IDC_AIR_TEMP_EDIT, m_str_AirTemp);
	DDX_Text(pDX, IDC_MODULE_FAULT_SUMMARY_EDIT, m_str_ModuleFault);
	DDX_Text(pDX, IDC_DRIVER_FAULT_SUMMARY_EDIT, m_str_DriverFault);
	DDX_Text(pDX, IDC_SYSTEM_FAULT_SUMMARY_EDIT, m_str_SystemFault);
	DDX_Text(pDX, IDC_HPA1_STATUS_EDIT, m_str_HPA1_STATUS);
	DDX_Text(pDX, IDC_HPA10_STATUS_EDIT, m_str_HPA10_STATUS);
	DDX_Text(pDX, IDC_HPA2_STATUS_EDIT, m_str_HPA2_STATUS);
	DDX_Text(pDX, IDC_HPA3_STATUS_EDIT, m_str_HPA3_STATUS);
	DDX_Text(pDX, IDC_HPA4_STATUS_EDIT, m_str_HPA4_STATUS);
	DDX_Text(pDX, IDC_HPA5_STATUS_EDIT, m_str_HPA5_STATUS);
	DDX_Text(pDX, IDC_HPA6_STATUS_EDIT, m_str_HPA6_STATUS);
	DDX_Text(pDX, IDC_HPA7_STATUS_EDIT, m_str_HPA7_STATUS);
	DDX_Text(pDX, IDC_HPA8_STATUS_EDIT, m_str_HPA8_STATUS);
	DDX_Text(pDX, IDC_HPA9_STATUS_EDIT, m_str_HPA9_STATUS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPf_sys_pa_page, CPropertyPage)
	//{{AFX_MSG_MAP(CPf_sys_pa_page)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPF_SYS_PA_PAGE message handlers

BOOL CPf_sys_pa_page::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));
/*
	m_str_SPARE = g_sm_status.sys_byte.spare?"READY":"PREWARM";
	m_str_DutyCycleRatio = ShowStatus(g_sm_status.sys_byte.dutycycleratio);
	m_str_LRSwitch    = (g_sm_status.sys_byte.lr_switch==0)?_T("REMOTE"):_T("LOCAL");
	m_str_VSWR		  = ShowStatus(g_sm_status.sys_byte.vswr);
	m_str_AirTemp	  = ShowStatus(g_sm_status.sys_byte.airtemp);
	m_str_ModuleFault = ShowStatus(g_sm_status.sys_byte.modulefaultsum);
	m_str_DriverFault = ShowStatus(g_sm_status.sys_byte.driverfaultsum);
	m_str_SystemFault = ShowStatus(g_sm_status.sys_byte.systemfaultsum);
	m_str_HPA1_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa1);
	m_str_HPA2_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa2);
	m_str_HPA3_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa3);
	m_str_HPA4_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa4);
	m_str_HPA5_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa5);
	m_str_HPA6_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa6);
	m_str_HPA7_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa7);
	m_str_HPA8_STATUS = ShowStatus(g_sm_status.pa_module_1.hpa8);
	m_str_HPA9_STATUS = ShowStatus(g_sm_status.pa_module_2.hpa9);
	m_str_HPA10_STATUS = ShowStatus(g_sm_status.pa_module_2.hpa10);
*/
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CPf_sys_pa_page::ShowStatus(unsigned char ch_data)
{
	CString str_status;
	str_status = ch_data==0 ? "GOOD": "FAULT";
	return str_status;
}

HBRUSH CPf_sys_pa_page::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
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
