// AlarmSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "AlarmSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmSettingDlg dialog


CAlarmSettingDlg::CAlarmSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmSettingDlg)
	m_nLevel = -1;
	m_minValue = 0.0f;
	m_maxValue = 0.0f;
	//}}AFX_DATA_INIT
}


void CAlarmSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmSettingDlg)
	DDX_Control(pDX, IDC_MINVALUE, m_ctrlMinEdit);
	DDX_Control(pDX, IDC_MAXVALUE, m_ctrlMaxEdit);
	DDX_Control(pDX, IDC_ALARMLIST, m_AlarmList);
	DDX_Radio(pDX, IDC_DONOTREPORT, m_nLevel);
	DDX_Text(pDX, IDC_MINVALUE, m_minValue);
	DDV_MinMaxFloat(pDX, m_minValue, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_MAXVALUE, m_maxValue);
	DDV_MinMaxFloat(pDX, m_maxValue, -1000.f, 1000.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmSettingDlg)
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_ALARMLIST, OnSelchangeAlarmlist)
	ON_BN_CLICKED(IDC_DONOTREPORT, OnDonotreport)
	ON_BN_CLICKED(IDC_NORMAL, OnNormal)
	ON_BN_CLICKED(IDC_HIGH, OnHigh)
	ON_EN_CHANGE(IDC_MAXVALUE, OnChangeMaxvalue)
	ON_EN_CHANGE(IDC_MINVALUE, OnChangeMinvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmSettingDlg message handlers

BOOL CAlarmSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	memcpy(&(alarmsetting),&(global_advance.alarmsetting),sizeof(ALARMSETTING));
	// TODO: Add extra initialization here
	for(int i=0; i<ALARM_SIZE; i++){
		m_AlarmList.InsertString(i,alarm_table[i]);
	}
	
	nIndex = 0;
	m_AlarmList.SetCurSel(nIndex);
	OnSelchangeAlarmlist();
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAlarmSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(0,255,0));
	}
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
}


void CAlarmSettingDlg::OnSelchangeAlarmlist() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	nIndex = this->m_AlarmList.GetCurSel();
	m_nLevel = alarmsetting.nLevel[nIndex];
	
	if(bQuantityTable[nIndex]){
         m_minValue = alarmsetting.min[nIndex];
		 m_maxValue = alarmsetting.max[nIndex];
		 m_ctrlMinEdit.EnableWindow(TRUE);
		 m_ctrlMaxEdit.EnableWindow(TRUE);
	}
	else{
		m_minValue = 0;
		m_maxValue = 0;
	    m_ctrlMinEdit.EnableWindow(FALSE);
		m_ctrlMaxEdit.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CAlarmSettingDlg::OnDonotreport() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nLevel = 0;
	alarmsetting.nLevel[nIndex] = m_nLevel;
}

void CAlarmSettingDlg::OnNormal() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nLevel = 1;
	alarmsetting.nLevel[nIndex] = m_nLevel;
}

void CAlarmSettingDlg::OnHigh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nLevel = 2;
	alarmsetting.nLevel[nIndex] = m_nLevel;
}

void CAlarmSettingDlg::OnChangeMaxvalue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	alarmsetting.max[nIndex] = this->m_maxValue;
}

void CAlarmSettingDlg::OnChangeMinvalue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	alarmsetting.min[nIndex] = this->m_minValue;
}
