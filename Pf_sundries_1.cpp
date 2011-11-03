// Pf_sundries_1.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "Pf_sundries_1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Global_SM.h"
/////////////////////////////////////////////////////////////////////////////
// CPf_sundries_1 property page

IMPLEMENT_DYNCREATE(CPf_sundries_1, CPropertyPage)

CPf_sundries_1::CPf_sundries_1() : CPropertyPage(CPf_sundries_1::IDD)
{
	//{{AFX_DATA_INIT(CPf_sundries_1)
	m_str_VSWR_FAULT = _T("");
	m_str_SPS_STATUS = _T("");
	m_str_RF_TEST_SIGNAL = _T("");
	m_str_REFLECTED_POWER = _T("");
	m_str_PS_6V3A = _T("");
	m_str_PS_6V2p5A = _T("");
	m_str_OUTSIDE_TEMP = _T("");
	m_str_LO_SAMPLE = _T("");
	m_str_INSIDE_TEMP = _T("");
	m_str_IF_CLOCK = _T("");
	m_str_FORWARDED_POWER = _T("");
	m_str_DOOR_SWITCH = _T("");
	m_str_DDC = _T("");
	m_str_BSU_FAULT = _T("");
	m_str_AD_CLOCK = _T("");
	m_str_AntennaDumyPos = _T("");
	m_str_RFD = _T("");
	m_str_25M_CW = _T("");
	//}}AFX_DATA_INIT
}

CPf_sundries_1::~CPf_sundries_1()
{
}

void CPf_sundries_1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPf_sundries_1)
	DDX_Text(pDX, IDC_VSWR_FAULT_EDIT, m_str_VSWR_FAULT);
	DDX_Text(pDX, IDC_SPS_STATUS_EDIT, m_str_SPS_STATUS);
	DDX_Text(pDX, IDC_RF_TEST_SIGNAL_EDIT, m_str_RF_TEST_SIGNAL);
	DDX_Text(pDX, IDC_REFLECTED_POWER_EDIT, m_str_REFLECTED_POWER);
	DDX_Text(pDX, IDC_PS_6V3A_EDIT, m_str_PS_6V3A);
	DDX_Text(pDX, IDC_PS_6V2p5A_EDIT, m_str_PS_6V2p5A);
	DDX_Text(pDX, IDC_OUTSIDE_TEMP_EDIT, m_str_OUTSIDE_TEMP);
	DDX_Text(pDX, IDC_LO_SAMPLE_EDIT, m_str_LO_SAMPLE);
	DDX_Text(pDX, IDC_INSIDE_TEMP_EDIT, m_str_INSIDE_TEMP);
	DDX_Text(pDX, IDC_IF_CLOCK_EDIT, m_str_IF_CLOCK);
	DDX_Text(pDX, IDC_FORWARDED_POWER_EDIT, m_str_FORWARDED_POWER);
	DDX_Text(pDX, IDC_DOOR_SWITCH_EDIT, m_str_DOOR_SWITCH);
	DDX_Text(pDX, IDC_DDC_EDIT, m_str_DDC);
	DDX_Text(pDX, IDC_BSU_FAULT_EDIT, m_str_BSU_FAULT);
	DDX_Text(pDX, IDC_AD_CLOCK_EDIT, m_str_AD_CLOCK);
	DDX_Text(pDX, IDC_ANTENNADUMYLOAD_EDIT, m_str_AntennaDumyPos);
	DDX_Text(pDX, IDC_RFD_EDIT, m_str_RFD);
	DDX_Text(pDX, IDC_25M_CW_EDIT, m_str_25M_CW);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPf_sundries_1, CPropertyPage)
	//{{AFX_MSG_MAP(CPf_sundries_1)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPF_SUNDRIES_1 message handlers

BOOL CPf_sundries_1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));
/*
	//B53
	m_str_VSWR_FAULT = ShowStatus(g_sm_status.antenna_param.vswr_fault);
    m_str_BSU_FAULT = ShowStatus(g_sm_status.antenna_param.bsu_fault);
    m_str_AntennaDumyPos = g_sm_status.antenna_param.dumyload_switch?"DUMY":"ANTENNA";
	//B54
	//m_str_AD_CLOCK = ShowStatus(g_sm_status.exciter_status.ad_sample_clock);
	//m_str_RF_TEST_SIGNAL = ShowStatus(g_sm_status.exciter_status.rf_test_signal);
	//m_str_LO_SAMPLE = ShowStatus(g_sm_status.exciter_status.lo_sample);
	unsigned char status = 0;
	for(int i=0;i<4; i++)
	{
		
		if((g_sg_status[i] != 0xa3)
			&& (g_sg_status[i] != 0xaa)
			&& (g_sg_status[i] != 0xa5))
		{
			status = g_sg_status[i];
			break;
		}
	}

	m_str_AD_CLOCK = ShowStatus(!(status & S_60M_ALARM_MASK));
	m_str_RF_TEST_SIGNAL = ShowStatus(!(status & RFTEST_ALARM_MASK));
	m_str_LO_SAMPLE = ShowStatus(!(status & STALO_ALARM_MASK));
	m_str_RFD = ShowStatus(!(status & RFD_ALARM_MASK));
	m_str_25M_CW = ShowStatus (!(status & S_25M_ALRAM_MASK));

	//B55
	m_str_DOOR_SWITCH = ShowStatus(g_sm_status.site_shelter_status.door_switch);

	//B56
    m_str_DDC = ShowStatus(g_sm_status.if_and_sps.ddc);
    m_str_IF_CLOCK = ShowStatus(g_sm_status.if_and_sps.if_clock);
	m_str_SPS_STATUS = ShowStatus(g_sm_status.if_and_sps.sps_status);
	m_str_PS_6V3A = ShowStatus(g_sm_status.if_and_sps._6v_3a_sp	);
	m_str_PS_6V2p5A = ShowStatus(g_sm_status.if_and_sps._6v_2p5a_sp);

	m_str_OUTSIDE_TEMP = ShowData(status_scaled_analog.outside_temperature);
	m_str_INSIDE_TEMP = ShowData(status_scaled_analog.inside_temperature);
	m_str_FORWARDED_POWER = ShowData(status_scaled_analog.antenna_forward_power);
	m_str_REFLECTED_POWER = ShowData(status_scaled_analog.antenna_reflected_power);
*/		

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CPf_sundries_1::ShowStatus(unsigned char ndata)
{
	CString string;
	string = (ndata==0)?"GOOD":"FAULT";
	return string;
}
CString CPf_sundries_1::ShowData(float ndata)
{
	CString string;
	string.Format("%f",ndata);
	return string;
}

HBRUSH CPf_sundries_1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
