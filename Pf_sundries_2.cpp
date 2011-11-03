// Pf_sundries_2.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Pf_sundries_2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "Global_SM.h"
/////////////////////////////////////////////////////////////////////////////
// CPf_sundries_2 property page

IMPLEMENT_DYNCREATE(CPf_sundries_2, CPropertyPage)

CPf_sundries_2::CPf_sundries_2() : CPropertyPage(CPf_sundries_2::IDD)
{
	//{{AFX_DATA_INIT(CPf_sundries_2)
	m_str_15V_PS = _T("");
	m_str_28V_PS = _T("");
	m_str_5V_PS = _T("");
	m_str_5VDIGITAL_PS = _T("");
	m_str_6V2P5_PS = _T("");
	m_str_6V3A_PS = _T("");
	m_str_CAB_INLET_AIR_TEMP = _T("");
	m_str_CAB_OUTLET_AIR_TEMP = _T("");
	m_str_DRV_MODULE1_TEMP = _T("");
	m_str_DRV_MODULE2_TEMP = _T("");
	m_str_DRV_RF_OUTPUT_POWER = _T("");
	m_str_M15V_PS_SAMPLE = _T("");
	m_str_M5V_PS_SAMPLE = _T("");
	m_str_PS_28V_SAMPLE = _T("");
	m_str_40V_SAMPLE = _T("");
	m_str_SYSTEM_FORWARD_POWER = _T("");
	//}}AFX_DATA_INIT
}

CPf_sundries_2::~CPf_sundries_2()
{
}

void CPf_sundries_2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPf_sundries_2)
	DDX_Text(pDX, IDC_15V_PS_SAMPLE_EDIT, m_str_15V_PS);
	DDX_Text(pDX, IDC_28V_PS_SAMPLE_EDIT, m_str_28V_PS);
	DDX_Text(pDX, IDC_5V_PS_SAMPLE_EDIT, m_str_5V_PS);
	DDX_Text(pDX, IDC_5VDIGITAL_PS_SAMPLE_EDIT, m_str_5VDIGITAL_PS);
	DDX_Text(pDX, IDC_6V2p5_PS_SAMPLE_EDIT, m_str_6V2P5_PS);
	DDX_Text(pDX, IDC_6V3A_PS_SAMPLE_EDIT, m_str_6V3A_PS);
	DDX_Text(pDX, IDC_CAB_INLET_AIR_TEMP_EDIT, m_str_CAB_INLET_AIR_TEMP);
	DDX_Text(pDX, IDC_CAB_OUTLET_AIR_TEMP_EDIT, m_str_CAB_OUTLET_AIR_TEMP);
	DDX_Text(pDX, IDC_DRV_MODULE1_TEMP_EDIT, m_str_DRV_MODULE1_TEMP);
	DDX_Text(pDX, IDC_DRV_MODULE2_TEMP_EDIT, m_str_DRV_MODULE2_TEMP);
	DDX_Text(pDX, IDC_DRV_RF_OUTPUT_POWER_EDIT, m_str_DRV_RF_OUTPUT_POWER);
	DDX_Text(pDX, IDC_M15V_PS_SAMPLE_EDIT, m_str_M15V_PS_SAMPLE);
	DDX_Text(pDX, IDC_M5V_PS_SAMPLE_EDIT, m_str_M5V_PS_SAMPLE);
	DDX_Text(pDX, IDC_PS_28V_SAMPLE_EDIT, m_str_PS_28V_SAMPLE);
	DDX_Text(pDX, IDC_PS_40V_SAMPLE_EDIT, m_str_40V_SAMPLE);
	DDX_Text(pDX, IDC_SYSTEM_FORWARD_POWER_EDIT, m_str_SYSTEM_FORWARD_POWER);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPf_sundries_2, CPropertyPage)
	//{{AFX_MSG_MAP(CPf_sundries_2)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPf_sundries_2 message handlers

BOOL CPf_sundries_2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	m_str_15V_PS = ShowData(status_scaled_analog.pos15_sys_supply);
	m_str_28V_PS = ShowData(status_scaled_analog.pos28_sys_supply);
	m_str_5V_PS  = ShowData(status_scaled_analog.pos5_am_sys_supply);
	m_str_5VDIGITAL_PS = ShowData(status_scaled_analog.pos5_digital_sys_supply);
	m_str_6V2P5_PS     = ShowData(status_scaled_analog.pos6_2p5a_sys_supply);
	m_str_6V3A_PS      = ShowData(status_scaled_analog.pos6_3a_sys_supply);
	m_str_CAB_INLET_AIR_TEMP  = ShowData(status_scaled_analog.cab_inlet_air_temp);
	m_str_CAB_OUTLET_AIR_TEMP = ShowData(status_scaled_analog.cab_outlet_air_temp);
	m_str_DRV_MODULE1_TEMP = ShowData(status_scaled_analog.drv_module1_temp);
	m_str_DRV_MODULE2_TEMP = ShowData(status_scaled_analog.drv_module2_temp);
	m_str_DRV_RF_OUTPUT_POWER = ShowData(status_scaled_analog.drv_rf_output_pwr);
	m_str_M15V_PS_SAMPLE = ShowData(status_scaled_analog.neg15_sys_supply);
	m_str_M5V_PS_SAMPLE  = ShowData(status_scaled_analog.neg5_sys_supply);
	m_str_PS_28V_SAMPLE  = ShowData(status_scaled_analog.ps_28v_sample);
	m_str_40V_SAMPLE     = ShowData(status_scaled_analog.ps_40v_sample);
	m_str_SYSTEM_FORWARD_POWER = ShowData(status_scaled_analog.sys_forward_pwr);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CPf_sundries_2::ShowData(float ch_data)
{
	CString string;
	string.Format("%f",ch_data);
	return string;
}

HBRUSH CPf_sundries_2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
