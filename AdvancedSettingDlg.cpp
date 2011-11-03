// AdvancedSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "AdvancedSettingDlg.h"
#include "DmaSettingDlg.h"
#include "AlarmSettingDlg.h"
#include "Global_Advanced.h"
#include "BeamCodeDlg.h"
#include "DspSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedSettingDlg dialog


CAdvancedSettingDlg::CAdvancedSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvancedSettingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdvancedSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedSettingDlg)
	DDX_Control(pDX, IDC_ADVANCEDSET_LIST, m_listctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdvancedSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CAdvancedSettingDlg)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_ADVANCEDSET_LIST, OnDblclkAdvancedsetList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedSettingDlg message handlers

BOOL CAdvancedSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//SET BACKGROUND
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	//SET IMAGE LIST
	m_ImageList.Create(48,48,ILC_COLOR32|ILC_MASK,0,0);    
	for(int i=IDI_ICON7;i<=IDI_ICON11;i++)
	{
		m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(i))); 
	}
	m_listctrl.SetImageList(&m_ImageList,LVSIL_NORMAL);

	//SET ITEM COLOR
	m_listctrl.SetBkColor(RGB(255,255,255));
	m_listctrl.SetTextBkColor(RGB(255,255,255));
	m_listctrl.SetTextColor(RGB(0,0,0));

	m_listctrl.InsertItem(0,"DMA",0);
	m_listctrl.InsertItem(1,"ALARM",1);
	m_listctrl.InsertItem(2,"BEAM CTRL",2);
	m_listctrl.InsertItem(3,"DSP",3);
	m_listctrl.InsertItem(4,"SERVICE",4);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAdvancedSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
	//return hbr;
}



void CAdvancedSettingDlg::OnDblclkAdvancedsetList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

	switch(phdn->iItem)
	{
	case 0:
		ShowDMASetting();
		break;
	case 1:
		ShowAlarmSetting();
		break;
	case 2:
		ShowBeamSetting();
		break;
	case 3:
		ShowDspSetting();
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CAdvancedSettingDlg::ShowDMASetting()
{

	CDmaSettingDlg dlg;
    if(dlg.DoModal() == IDOK)
	{
		global_advance.dmasetting.nDMA_Low = dlg.m_nDMA_Low*2;
		global_advance.dmasetting.nDMA_High = dlg.m_nDMA_High*2;
	}
}

void CAdvancedSettingDlg::ShowAlarmSetting()
{
	CAlarmSettingDlg dlg;
	if(dlg.DoModal() == IDOK){
		memcpy( &(global_advance.alarmsetting),
			    &(dlg.alarmsetting),
			    sizeof(ALARMSETTING)
			   );
	}
}

void CAdvancedSettingDlg::ShowBeamSetting()
{
	enum{EAST, NORTH,VIRTICAL,WEST,SOUTH};
	CBeamCodeDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		//dlg.UpdateData(TRUE);
		global_advance.beamctrlsetting.nBeamDirection[EAST] = dlg.m_nEast;
		global_advance.beamctrlsetting.nBeamDirection[NORTH] = dlg.m_nNorth;
		global_advance.beamctrlsetting.nBeamDirection[VIRTICAL] = dlg.m_nVirtical;
		global_advance.beamctrlsetting.nBeamDirection[WEST] = dlg.m_nWest;
		global_advance.beamctrlsetting.nBeamDirection[SOUTH] = dlg.m_nSouth;
	}
}

void CAdvancedSettingDlg::ShowDspSetting()
{
    CDspSetting dlg;
	if(dlg.DoModal() == IDOK)
	{
		global_advance.dspsetting.nCenterFreq = dlg.m_nCenterFreq;
		global_advance.dspsetting.nSampleRate = dlg.m_nSampleClock;
		global_advance.dspsetting.nIQReverse = dlg.m_bIQReverse;
		global_advance.dspsetting.nRemoveDC = dlg.m_bDCRemoval;
		global_advance.dspsetting.nWindowType = dlg.windowSel;


		global_advance.dspsetting.nRFGateMoveH = dlg.m_nRFGate;
		global_advance.dspsetting.nRFGateMoveL = dlg.m_nRFGateL;

		global_advance.dspsetting.nPCCodeMove = dlg.m_nPCCode;
		global_advance.dspsetting.nBeginGateMoveH = dlg.m_nBeginGateH;
		global_advance.dspsetting.nBeginGateMoveL = dlg.m_nBeginGateL;


	}
	return;
}