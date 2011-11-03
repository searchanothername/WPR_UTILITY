// DspSetting.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "DspSetting.h"
#include "Global_Advanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDspSetting dialog


CDspSetting::CDspSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDspSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDspSetting)
	m_nCenterFreq = 0;
	m_nSampleClock = 0;
	m_bIQReverse = FALSE;
	m_bDCRemoval = FALSE;
	m_nslider_rfgate = 0;
	m_nRFGate = 0;
	m_nslider_pccode = 0;
	m_nPCCode = 0;
	m_nslider_beginggate_h = 0;
	m_nslider_begingate_l = 0;
	m_nBeginGateH = 0;
	m_nBeginGateL = 0;
	m_nslider_rfgate_l = 0;
	m_nRFGateL = 0;
	//}}AFX_DATA_INIT
	windowSel = 0;
}


void CDspSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDspSetting)
	DDX_Control(pDX, IDC_SLIDER_RFGATEMOV_L, m_slider_rfgate_l);
	DDX_Control(pDX, IDC_SPIN_BEGINGATE_H, m_spin_begingate_h);
	DDX_Control(pDX, IDC_SLIDER_BEGINGATE_L, m_slider_begingate_l);
	DDX_Control(pDX, IDC_SLIDER_BEGINGATE_H, m_slider_beginggate_h);
	DDX_Control(pDX, IDC_SPIN_PCCODE, m_spin_pccode);
	DDX_Control(pDX, IDC_SLIDER_PCCODE_MOV, m_slider_pccode);
	DDX_Control(pDX, IDC_SPIN_RFGATE, m_spin_rfgate);
	DDX_Control(pDX, IDC_SLIDER_RFGATEMOV, m_slider_rfgate);
	DDX_Control(pDX, IDC_COMBO_WINDOW, m_Combo_Window);
	DDX_Text(pDX, IDC_EDIT_CENTER_FREQ, m_nCenterFreq);
	DDV_MinMaxLong(pDX, m_nCenterFreq, 0, 2000);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_CLOCK, m_nSampleClock);
	DDV_MinMaxLong(pDX, m_nSampleClock, 0, 60);
	DDX_Check(pDX, IDC_CHECK_IQREVERSE, m_bIQReverse);
	DDX_Check(pDX, IDC_CHECK_DCREMOVAL, m_bDCRemoval);
	DDX_Slider(pDX, IDC_SLIDER_RFGATEMOV, m_nslider_rfgate);
	DDX_Text(pDX, IDC_EDIT_RFGATE, m_nRFGate);
	DDX_Slider(pDX, IDC_SLIDER_PCCODE_MOV, m_nslider_pccode);
	DDX_Text(pDX, IDC_EDIT_PCCODE, m_nPCCode);
	DDX_Slider(pDX, IDC_SLIDER_BEGINGATE_H, m_nslider_beginggate_h);
	DDX_Slider(pDX, IDC_SLIDER_BEGINGATE_L, m_nslider_begingate_l);
	DDX_Text(pDX, IDC_EDIT_BEGINGGATE_H, m_nBeginGateH);
	DDX_Text(pDX, IDC_EDIT_BEGINGATE_L, m_nBeginGateL);
	DDX_Slider(pDX, IDC_SLIDER_RFGATEMOV_L, m_nslider_rfgate_l);
	DDX_Text(pDX, IDC_EDIT_RFGATE_L, m_nRFGateL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDspSetting, CDialog)
	//{{AFX_MSG_MAP(CDspSetting)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_WINDOW, OnSelchangeComboWindow)
	ON_WM_HSCROLL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RFGATE, OnDeltaposSpinRfgate)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PCCODE, OnDeltaposSpinPccode)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BEGINGATE_H, OnDeltaposSpinBegingateH)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BEGINGATE_L, OnDeltaposSpinBegingateL)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RFGATE_L, OnDeltaposSpinRfgateL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDspSetting message handlers

HBRUSH CDspSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CDspSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	m_nCenterFreq = global_advance.dspsetting.nCenterFreq;
	m_nSampleClock = global_advance.dspsetting.nSampleRate;
	m_bIQReverse = global_advance.dspsetting.nIQReverse;
	m_bDCRemoval = global_advance.dspsetting.nRemoveDC;
	windowSel = global_advance.dspsetting.nWindowType;

	CString str_win[3] = {"Hamming", "Hanning","Blackman"};
	for(int i=0; i<3; ++i)
	{
		m_Combo_Window.InsertString(i,str_win[i]);
		m_Combo_Window.SetItemData( i, i);
	}
	m_Combo_Window.SetCurSel(windowSel);

	//INITIALIZE THE SLIDER
	m_slider_rfgate.SetRange(0,255,TRUE);
	m_slider_rfgate_l.SetRange(0,255,TRUE);
	m_slider_pccode.SetRange(0,255,TRUE);
	m_slider_beginggate_h.SetRange(0,16,TRUE);
	m_slider_begingate_l.SetRange(0,16,TRUE);

	m_nslider_rfgate = m_nRFGate = global_advance.dspsetting.nRFGateMoveH;
	m_nslider_rfgate_l = m_nRFGateL = global_advance.dspsetting.nRFGateMoveL;
	m_nslider_pccode = m_nPCCode = global_advance.dspsetting.nPCCodeMove;
	m_nslider_beginggate_h = m_nBeginGateH = global_advance.dspsetting.nBeginGateMoveH;
	m_nslider_begingate_l = m_nBeginGateL = global_advance.dspsetting.nBeginGateMoveL;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDspSetting::OnSelchangeComboWindow() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	windowSel = m_Combo_Window.GetCurSel();
	return;

}

void CDspSetting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetDlgItem(IDC_SLIDER_RFGATEMOV) == pScrollBar)
	{	
		UpdateData(TRUE);
		m_nRFGate = this->m_nslider_rfgate;
		UpdateData(FALSE);
	}

	if(GetDlgItem(IDC_SLIDER_RFGATEMOV_L) == pScrollBar)
	{
		UpdateData(TRUE);
		m_nRFGateL = this->m_nslider_rfgate_l;
		UpdateData(FALSE);
	}

	if(	GetDlgItem(IDC_SLIDER_PCCODE_MOV) == pScrollBar){
		UpdateData(TRUE);
		m_nPCCode = this->m_nslider_pccode;
		UpdateData(FALSE);
	}

	if( GetDlgItem(IDC_SLIDER_BEGINGATE_H) == pScrollBar)
	{
		UpdateData(TRUE);
		m_nBeginGateH = this->m_nslider_beginggate_h;
		UpdateData(FALSE);
	}

	if( GetDlgItem(IDC_SLIDER_BEGINGATE_L) == pScrollBar)
	{
		UpdateData(TRUE);
		m_nBeginGateL = this->m_nslider_begingate_l;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDspSetting::OnDeltaposSpinRfgate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMUpDown->iDelta == -1)              
	{ 
		m_slider_rfgate.SetPos(m_slider_rfgate.GetPos()+1);
    }
    else if(pNMUpDown->iDelta == 1)
	{
		m_slider_rfgate.SetPos(m_slider_rfgate.GetPos()-1);
	}
	m_nRFGate = m_nslider_rfgate = m_slider_rfgate.GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}

void CDspSetting::OnDeltaposSpinPccode(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMUpDown->iDelta == -1)              
	{ 
		m_slider_pccode.SetPos(m_slider_pccode.GetPos()+1);
    }
    else if(pNMUpDown->iDelta == 1)
	{
		m_slider_pccode.SetPos(m_slider_pccode.GetPos()-1);
	}
	m_nPCCode = m_nslider_pccode = m_slider_pccode.GetPos();
	UpdateData(FALSE);

	*pResult = 0;
}

void CDspSetting::OnDeltaposSpinBegingateH(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMUpDown->iDelta == -1)              
	{ 
		m_slider_beginggate_h.SetPos(m_slider_beginggate_h.GetPos()+1);
    }
    else if(pNMUpDown->iDelta == 1)
	{
		m_slider_beginggate_h.SetPos(m_slider_beginggate_h.GetPos()-1);
	}
	m_nBeginGateH = m_nslider_beginggate_h = m_slider_beginggate_h.GetPos();
	UpdateData(FALSE);

	*pResult = 0;
}

void CDspSetting::OnDeltaposSpinBegingateL(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMUpDown->iDelta == -1)              
	{ 
		m_slider_begingate_l.SetPos(m_slider_begingate_l.GetPos()+1);
    }
    else if(pNMUpDown->iDelta == 1)
	{
		m_slider_begingate_l.SetPos(m_slider_begingate_l.GetPos()-1);
	}
	m_nBeginGateL = m_nslider_begingate_l = m_slider_begingate_l.GetPos();
	UpdateData(FALSE);

	*pResult = 0;
}

void CDspSetting::OnDeltaposSpinRfgateL(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMUpDown->iDelta == -1)              
	{ 
		m_slider_rfgate_l.SetPos(m_slider_rfgate_l.GetPos()+1);
    }
    else if(pNMUpDown->iDelta == 1)
	{
		m_slider_rfgate_l.SetPos(m_slider_rfgate_l.GetPos()-1);
	}
	m_nRFGateL = m_nslider_rfgate_l = m_slider_rfgate_l.GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}
