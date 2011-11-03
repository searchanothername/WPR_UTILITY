// TotalSpecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "TotalSpecDlg.h"
#include "WPR_UTILITIESDlg.h"

#include "WPR_UTILITY_SPECView.h"
#include "WPR_UTILITY_SPECDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTotalSpecDlg dialog
//volatile BOOL bSpectrasViewEnable = FALSE;
//CCriticalSection cs;

CTotalSpecDlg::CTotalSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTotalSpecDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTotalSpecDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTotalSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTotalSpecDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTotalSpecDlg, CDialog)
	//{{AFX_MSG_MAP(CTotalSpecDlg)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTotalSpecDlg message handlers
extern 	CWPR_UTILITY_SPECView* pSpecView;
BOOL CTotalSpecDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//bSpectrasViewEnable = TRUE;

	dfvctrl.Create(this, IDC_SPECTRAS_PANE,
		IDR_MENU,
		RUNTIME_CLASS(CWPR_UTILITY_SPECDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CWPR_UTILITY_SPECView),
		WS_CHILD  | WS_VISIBLE, 0L);

	m_bkBrush.CreateSolidBrush(RGB(58,58,58));
	p = pSpecView;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CTotalSpecDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
	return hbr;
}

void CTotalSpecDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	//_utility->bSpectrasViewEnable = FALSE;
}

void CTotalSpecDlg::OnOK() 
{
	// TODO: Add extra validation here
	_utility->bSpectrasViewEnable = FALSE;
	CDialog::OnOK();
}

void CTotalSpecDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	_utility->bSpectrasViewEnable = FALSE;
	CDialog::OnClose();
}
