// BeamCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "BeamCodeDlg.h"
#include "Global_Advanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBeamCodeDlg dialog
CBeamCodeDlg::CBeamCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBeamCodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBeamCodeDlg)
	m_nSouth = 5;
	m_nVirtical = 4;
	m_nWest = 6;
	m_nNorth = 1;
	m_nEast = 2;
	//}}AFX_DATA_INIT
}


void CBeamCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBeamCodeDlg)
	DDX_Text(pDX, IDC_EDIT_SOUTH, m_nSouth);
	DDV_MinMaxInt(pDX, m_nSouth, 1, 6);
	DDX_Text(pDX, IDC_EDIT_VIRTICAL, m_nVirtical);
	DDV_MinMaxInt(pDX, m_nVirtical, 1, 6);
	DDX_Text(pDX, IDC_EDIT_WEST, m_nWest);
	DDV_MinMaxInt(pDX, m_nWest, 1, 6);
	DDX_Text(pDX, IDC_EDIT_NORTH, m_nNorth);
	DDV_MinMaxInt(pDX, m_nNorth, 1, 6);
	DDX_Text(pDX, IDC_EDIT_EAST, m_nEast);
	DDV_MinMaxInt(pDX, m_nEast, 1, 6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBeamCodeDlg, CDialog)
	//{{AFX_MSG_MAP(CBeamCodeDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeamCodeDlg message handlers

BOOL CBeamCodeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));
	m_nEast = global_advance.beamctrlsetting.nBeamDirection[0];
	m_nNorth = global_advance.beamctrlsetting.nBeamDirection[1];
	m_nVirtical = global_advance.beamctrlsetting.nBeamDirection[2];
	m_nWest = global_advance.beamctrlsetting.nBeamDirection[3];
	m_nSouth = global_advance.beamctrlsetting.nBeamDirection[4];
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CBeamCodeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC 
		|| nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(255,255,0));
		
	}

	if(nCtlColor == CTLCOLOR_LISTBOX){
			//For Alarm list
        //pDC->SetBkColor(RGB(58,58,58));
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(255,255,0));
	}
	return m_bkBrush;
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
