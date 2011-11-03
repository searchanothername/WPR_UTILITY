// Pf_hpa_and_pa_temp.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Pf_hpa_and_pa_temp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Global_SM.h"
/////////////////////////////////////////////////////////////////////////////
// CPf_hpa_and_pa_temp property page

IMPLEMENT_DYNCREATE(CPf_hpa_and_pa_temp, CPropertyPage)

CPf_hpa_and_pa_temp::CPf_hpa_and_pa_temp() : CPropertyPage(CPf_hpa_and_pa_temp::IDD)
{
	//{{AFX_DATA_INIT(CPf_hpa_and_pa_temp)
	m_str_HPA1_POWER = _T("");
	m_str_HPA10_POWER = _T("");
	m_str_HPA2_POWER = _T("");
	m_str_HPA3_POWER = _T("");
	m_str_HPA4_POWER = _T("");
	m_str_HPA5_POWER = _T("");
	m_str_HPA6_POWER = _T("");
	m_str_HPA7_POWER = _T("");
	m_str_HPA8_POWER = _T("");
	m_str_HPA9_POWER = _T("");
	m_str_PA1_TEMP = _T("");
	m_str_PA2_TEMP = _T("");
	m_str_PA3_TEMP = _T("");
	m_str_PA4_TEMP = _T("");
	m_str_PA5_TEMP = _T("");
	m_str_PA6_TEMP = _T("");
	m_str_PA7_TEMP = _T("");
	m_str_PA8_TEMP = _T("");
	m_str_PA9_TEMP = _T("");
	m_str_PA10_TEMP = _T("");
	//}}AFX_DATA_INIT
}

CPf_hpa_and_pa_temp::~CPf_hpa_and_pa_temp()
{
}

void CPf_hpa_and_pa_temp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPf_hpa_and_pa_temp)
	DDX_Text(pDX, IDC_HPA1_PWR_EDIT, m_str_HPA1_POWER);
	DDX_Text(pDX, IDC_HPA10_PWR_EDIT, m_str_HPA10_POWER);
	DDX_Text(pDX, IDC_HPA2_PWR_EDIT, m_str_HPA2_POWER);
	DDX_Text(pDX, IDC_HPA3_PWR_EDIT, m_str_HPA3_POWER);
	DDX_Text(pDX, IDC_HPA4_PWR_EDIT, m_str_HPA4_POWER);
	DDX_Text(pDX, IDC_HPA5_PWR_EDIT, m_str_HPA5_POWER);
	DDX_Text(pDX, IDC_HPA6_PWR_EDIT, m_str_HPA6_POWER);
	DDX_Text(pDX, IDC_HPA7_PWR_EDIT, m_str_HPA7_POWER);
	DDX_Text(pDX, IDC_HPA8_PWR_EDIT, m_str_HPA8_POWER);
	DDX_Text(pDX, IDC_HPA9_PWR_EDIT, m_str_HPA9_POWER);
	DDX_Text(pDX, IDC_PA1_TEMP_EDIT, m_str_PA1_TEMP);
	DDX_Text(pDX, IDC_PA2_TEMP_EDIT, m_str_PA2_TEMP);
	DDX_Text(pDX, IDC_PA3_TEMP_EDIT, m_str_PA3_TEMP);
	DDX_Text(pDX, IDC_PA4_TEMP_EDIT, m_str_PA4_TEMP);
	DDX_Text(pDX, IDC_PA5_TEMP_EDIT, m_str_PA5_TEMP);
	DDX_Text(pDX, IDC_PA6_TEMP_EDIT, m_str_PA6_TEMP);
	DDX_Text(pDX, IDC_PA7_TEMP_EDIT, m_str_PA7_TEMP);
	DDX_Text(pDX, IDC_PA8_TEMP_EDIT, m_str_PA8_TEMP);
	DDX_Text(pDX, IDC_PA9_TEMP_EDIT, m_str_PA9_TEMP);
	DDX_Text(pDX, IDC_PA10_TEMP_EDIT, m_str_PA10_TEMP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPf_hpa_and_pa_temp, CPropertyPage)
	//{{AFX_MSG_MAP(CPf_hpa_and_pa_temp)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPf_hpa_and_pa_temp message handlers

BOOL CPf_hpa_and_pa_temp::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	m_str_HPA1_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[0]);
	m_str_HPA2_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[1]);
	m_str_HPA3_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[2]);
	m_str_HPA4_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[3]);
	m_str_HPA5_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[4]);
	m_str_HPA6_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[5]);
	m_str_HPA7_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[6]);
	m_str_HPA8_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[7]);
	m_str_HPA9_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[8]);
	m_str_HPA10_POWER = Show_HPA_Power(status_scaled_analog.ch_hpa_rf_output_pwr[9]);

	m_str_PA1_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[0]);
	m_str_PA2_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[1]);
	m_str_PA3_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[2]);
	m_str_PA4_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[3]);
	m_str_PA5_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[4]);
	m_str_PA6_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[5]);
	m_str_PA7_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[6]);
	m_str_PA8_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[7]);
	m_str_PA9_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[8]);
    m_str_PA10_TEMP = Show_PA_TEMP(status_scaled_analog.ch_pwr_amp_module_temp[9]);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CPf_hpa_and_pa_temp::Show_HPA_Power(float ch_data)
{
	CString string;
	string.Format("%f",ch_data);
	return string;
}

CString CPf_hpa_and_pa_temp::Show_PA_TEMP(float ch_data)
{
	CString string;
	string.Format("%f",ch_data);
	return string;
}

HBRUSH CPf_hpa_and_pa_temp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
