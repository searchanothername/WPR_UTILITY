// Pf_drv_and_fans.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Pf_drv_and_fans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "Global_SM.h"
/////////////////////////////////////////////////////////////////////////////
// CPf_drv_and_fans property page

IMPLEMENT_DYNCREATE(CPf_drv_and_fans, CPropertyPage)

CPf_drv_and_fans::CPf_drv_and_fans() : CPropertyPage(CPf_drv_and_fans::IDD)
{
	//{{AFX_DATA_INIT(CPf_drv_and_fans)
	m_str_DRV_A_SP_STATUS = _T("");
	m_str_DRV_A_STATUS = _T("");
	m_str_DRV_B_STATUS = _T("");
	m_str_DRV_B_SP_STATUS = _T("");
	m_str_Fan1 = _T("");
	m_str_Fan2 = _T("");
	m_str_Fan3 = _T("");
	m_str_Fan4 = _T("");
	m_str_Fan5 = _T("");
	m_str_Fan6 = _T("");
	m_str_Fan7 = _T("");
	m_str_Fan8 = _T("");
	//}}AFX_DATA_INIT
}

CPf_drv_and_fans::~CPf_drv_and_fans()
{
}

void CPf_drv_and_fans::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPf_drv_and_fans)
	DDX_Text(pDX, IDC_DRV_A_SP_STATUS_EDIT, m_str_DRV_A_SP_STATUS);
	DDX_Text(pDX, IDC_DRV_A_STATUS_EDIT, m_str_DRV_A_STATUS);
	DDX_Text(pDX, IDC_DRV_B_STATUS_EDIT, m_str_DRV_B_STATUS);
	DDX_Text(pDX, IDC_MODULIDC_DRV_B_SP_STATUS_EDIT, m_str_DRV_B_SP_STATUS);
	DDX_Text(pDX, IDC_FAN1_EDIT, m_str_Fan1);
	DDX_Text(pDX, IDC_FAN2_EDIT, m_str_Fan2);
	DDX_Text(pDX, IDC_FAN3_EDIT, m_str_Fan3);
	DDX_Text(pDX, IDC_FAN4_EDIT, m_str_Fan4);
	DDX_Text(pDX, IDC_FAN5_EDIT, m_str_Fan5);
	DDX_Text(pDX, IDC_FAN6_EDIT, m_str_Fan6);
	DDX_Text(pDX, IDC_FAN7_EDIT, m_str_Fan7);
	DDX_Text(pDX, IDC_FAN8_EDIT, m_str_Fan8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPf_drv_and_fans, CPropertyPage)
	//{{AFX_MSG_MAP(CPf_drv_and_fans)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPf_drv_and_fans message handlers

BOOL CPf_drv_and_fans::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));
/*
	m_str_DRV_A_SP_STATUS = ShowStatus1(g_sm_status.driver_module.drv_module_a_switcher);
	m_str_DRV_B_SP_STATUS = ShowStatus1(g_sm_status.driver_module.drv_module_b_switcher);
	m_str_DRV_A_STATUS = ShowStatus2(g_sm_status.driver_module.drv_module_a);
	m_str_DRV_B_STATUS = ShowStatus2(g_sm_status.driver_module.drv_module_b);
	m_str_Fan1 = ShowStatus2(g_sm_status.fans_status.fan1);
	m_str_Fan2 = ShowStatus2(g_sm_status.fans_status.fan2);
	m_str_Fan3 = ShowStatus2(g_sm_status.fans_status.fan3);
	m_str_Fan4 = ShowStatus2(g_sm_status.fans_status.fan4);
	m_str_Fan5 = ShowStatus2(g_sm_status.fans_status.fan5);
	m_str_Fan6 = ShowStatus2(g_sm_status.fans_status.fan6);
	m_str_Fan7 = ShowStatus2(g_sm_status.fans_status.fan7);
	m_str_Fan8 = ShowStatus2(g_sm_status.fans_status.fan8);
*/
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CPf_drv_and_fans::ShowStatus1(char ch_data)
{
	CString string;
	string = (ch_data==0)?"SECONDARY":"PRIMARY";
	return string;
}

CString CPf_drv_and_fans::ShowStatus2(char ch_data)
{
	CString string;
	string  = (ch_data==0)?"GOOD":"FAULT";
	return string;
}

HBRUSH CPf_drv_and_fans::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
