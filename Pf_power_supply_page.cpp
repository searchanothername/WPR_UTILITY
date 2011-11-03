// Pf_power_supply_page.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Pf_power_supply_page.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Global_SM.h"
/////////////////////////////////////////////////////////////////////////////
// CPf_power_supply_page property page


IMPLEMENT_DYNCREATE(CPf_power_supply_page, CPropertyPage)

CPf_power_supply_page::CPf_power_supply_page() : CPropertyPage(CPf_power_supply_page::IDD)
{
	//{{AFX_DATA_INIT(CPf_power_supply_page)
	m_str_Neg12V_1 = _T("FAULT");
	m_str_Neg12V_2 = _T("FAULT");
	m_str_Neg5V_1 = _T("FAULT");
	m_str_Neg5V_2 = _T("FAULT");
	m_str_Pos12V_1 = _T("FAULT");
	m_str_Pos12V_2 = _T("FAULT");
	m_str_Pos28V_1 = _T("FAULT");
	m_str_Pos28V_2 = _T("FAULT");
	m_str_Pos40V_1 = _T("FAULT");
	m_str_Pos40V_2 = _T("FAULT");
	m_str_Pos40V_3 = _T("FAULT");
	m_str_Pos5V_1 = _T("FAULT");
	m_str_Pos5V_2 = _T("FAULT");
	m_str_Spare1 = _T("NA");
	m_str_Spare2 = _T("NA");
	m_str_Spare3 = _T("NA");
	//}}AFX_DATA_INIT
}

CPf_power_supply_page::~CPf_power_supply_page()
{
}

void CPf_power_supply_page::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPf_power_supply_page)
	DDX_Text(pDX, IDC_NEG_12V_1_EDIT, m_str_Neg12V_1);
	DDX_Text(pDX, IDC_NEG_12V_2_EDIT, m_str_Neg12V_2);
	DDX_Text(pDX, IDC_NEG_5V_1_EDIT, m_str_Neg5V_1);
	DDX_Text(pDX, IDC_NEG_5V_2_EDIT, m_str_Neg5V_2);
	DDX_Text(pDX, IDC_POS_12V_1_EDIT, m_str_Pos12V_1);
	DDX_Text(pDX, IDC_POS_12V_2_EDIT, m_str_Pos12V_2);
	DDX_Text(pDX, IDC_POS_28V_1_EDIT, m_str_Pos28V_1);
	DDX_Text(pDX, IDC_POS_28V_2_EDIT, m_str_Pos28V_2);
	DDX_Text(pDX, IDC_POS_40V_1_EDIT, m_str_Pos40V_1);
	DDX_Text(pDX, IDC_POS_40V_2_EDIT, m_str_Pos40V_2);
	DDX_Text(pDX, IDC_POS_40V_3_EDIT, m_str_Pos40V_3);
	DDX_Text(pDX, IDC_POS_5V_1_EDIT, m_str_Pos5V_1);
	DDX_Text(pDX, IDC_POS_5V_2_EDIT, m_str_Pos5V_2);
	DDX_Text(pDX, IDC_SPARE_EDIT1, m_str_Spare1);
	DDX_Text(pDX, IDC_SPARE_EDIT2, m_str_Spare2);
	DDX_Text(pDX, IDC_SPARE_EDIT3, m_str_Spare3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPf_power_supply_page, CPropertyPage)
	//{{AFX_MSG_MAP(CPf_power_supply_page)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPf_power_supply_page message handlers

BOOL CPf_power_supply_page::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));
/*
	m_str_Neg12V_1 = ShowStatus(g_sm_status.power_supply_2.m_12v_1);
	m_str_Neg12V_2 = ShowStatus(g_sm_status.power_supply_2.m_12v_2);
	m_str_Neg5V_1 = ShowStatus(g_sm_status.power_supply_2.m_5v_1);
	m_str_Neg5V_2 = ShowStatus(g_sm_status.power_supply_2.m_5v_2);
	m_str_Pos12V_1 = ShowStatus(g_sm_status.power_supply_1._12v_1);
	m_str_Pos12V_2 = ShowStatus(g_sm_status.power_supply_1._12v_2);
	m_str_Pos28V_1 = ShowStatus(g_sm_status.power_supply_1._28v_1);
	m_str_Pos28V_2 = ShowStatus(g_sm_status.power_supply_1._28v_2);
	m_str_Pos40V_1 = ShowStatus(g_sm_status.power_supply_1._40v_1);
	m_str_Pos40V_2 = ShowStatus(g_sm_status.power_supply_1._40v_2);
	m_str_Pos40V_3 = ShowStatus(g_sm_status.power_supply_1._40v_3);
	m_str_Pos5V_1 = ShowStatus(g_sm_status.power_supply_2._5v_1);
	m_str_Pos5V_2 = ShowStatus(g_sm_status.power_supply_2._5v_2);
	m_str_Spare1 = ShowStatus(g_sm_status.power_supply_1.spare);
	m_str_Spare2 = ShowStatus(g_sm_status.power_supply_2.spare0);
	m_str_Spare3 = ShowStatus(g_sm_status.power_supply_2.spare1);
*/
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CPf_power_supply_page::ShowStatus(unsigned char ch_data)
{
	CString str_status;
	str_status = ch_data==0 ? "GOOD": "FAULT";
	return str_status;
}


HBRUSH CPf_power_supply_page::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
	return hbr;
}
