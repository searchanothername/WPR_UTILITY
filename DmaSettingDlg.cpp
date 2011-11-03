// DmaSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "DmaSettingDlg.h"
#include "Global_Advanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDmaSettingDlg dialog

#define IDEventDMASlider 2000
CDmaSettingDlg::CDmaSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDmaSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDmaSettingDlg)
	m_nDMA_Low = 0;
	m_nDMA_High = 0;
	//}}AFX_DATA_INIT
}


void CDmaSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDmaSettingDlg)
	DDX_Control(pDX, IDC_LOWMODEDMA_SLIDER, m_DMA_slider_low);
	DDX_Control(pDX, IDC_HIGHMODEDMA_SLIDER, m_DMA_slider_high);
	DDX_Text(pDX, IDC_LOWMODE_DMA, m_nDMA_Low);
	DDV_MinMaxInt(pDX, m_nDMA_Low, 0, 82);
	DDX_Text(pDX, IDC_HIGHMODE_DMA, m_nDMA_High);
	DDV_MinMaxInt(pDX, m_nDMA_High, 0, 82);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDmaSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CDmaSettingDlg)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_LOWMODEDMA_SLIDER, OnOutofmemoryLowmodedmaSlider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDmaSettingDlg message handlers

BOOL CDmaSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//SET BACKGROUND
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	m_nDMA_Low = global_advance.dmasetting.nDMA_Low/2;
	m_nDMA_High = global_advance.dmasetting.nDMA_High/2;

	//SET SLIDER
	m_DMA_slider_low.SetRange(0,164,TRUE);
	m_DMA_slider_low.SetPageSize(2);
	m_DMA_slider_low.SetPos(global_advance.dmasetting.nDMA_Low);
	m_DMA_slider_high.SetRange(0,164,TRUE);
	m_DMA_slider_low.SetPageSize(2);
	m_DMA_slider_high.SetPos(global_advance.dmasetting.nDMA_High);

    SetTimer(IDEventDMASlider,100,NULL);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDmaSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(255,255,0));
	}
	if(nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(255,255,0));
	}

	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
	//return hbr;
}

void CDmaSettingDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == IDEventDMASlider)
	{
		int pos_low = m_DMA_slider_low.GetPos();
		int pos_high = m_DMA_slider_high.GetPos();
		m_nDMA_Low =  pos_low/2;
		m_nDMA_High = pos_high/2;
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);

}

void CDmaSettingDlg::OnOutofmemoryLowmodedmaSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDmaSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
