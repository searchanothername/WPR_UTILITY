// AlarmShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "AlarmShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmShowDlg dialog


CAlarmShowDlg::CAlarmShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CAlarmShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmShowDlg)
	DDX_Control(pDX, IDC_ALARMLIST, m_alarmlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmShowDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmShowDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmShowDlg message handlers

BOOL CAlarmShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));
	//nAlarmCount = 0;
	///////////////////////////////
	//FOR THE LIST CTRL
	DWORD dwStyle = GetWindowLong(m_alarmlist.m_hWnd,GWL_STYLE);
	SetWindowLong(m_alarmlist.m_hWnd,GWL_STYLE,dwStyle|LVS_REPORT);
	DWORD style= m_alarmlist.GetExtendedStyle();
	m_alarmlist.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_alarmlist.SetBkColor(RGB(58,58,58));
	m_alarmlist.SetTextBkColor(RGB(58,58,58));
	m_alarmlist.SetTextColor(RGB(255,255,0));

	CRect rect;
	const int nColumn = 3;
	m_alarmlist.GetWindowRect(&rect);
	int n_ColumnWidth[3] = {rect.Width() / 10,
							rect.Width() / 5,
							rect.Width() * 7 / 10,
							
	};
	const char* str_Column[nColumn] = {"LEVEL","NUMBER","ALARMCODE/ALARMNAME"};
	for(int i=0; i<nColumn; i++){
		m_alarmlist.InsertColumn(i,str_Column[i],LVCFMT_LEFT,n_ColumnWidth[i]);
	}
     
	Show();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
//Add Infomation
void CAlarmShowDlg::AddAlarm(int nCount,BOOL bSerious,int Id, CString str)
{
	alarm.str_Alarm[nCount] = str;
	alarm.bIsSerious[nCount] = bSerious;
	nAlarmCount = nCount;
	nAlarmId = Id;
	return;
}

/////////////////////////////////////////////////////////////////////////////
//SHOW THE ALARM. IF THE ALARM LEVEL IS HIGH , I WILL SHOW A RED FLAG, 
//OTHERWISE A YELLOW FALG. 
/////////////////////////////////////////////////////////////////////////////
void CAlarmShowDlg::Show()
{
	m_ImageList.Create(32,32,ILC_COLOR32|ILC_MASK,0,0);    
	for(int i=IDI_ICON12;i<=IDI_ICON13;i++)
	{
		m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(i))); 
	}
	m_alarmlist.SetImageList(&m_ImageList,LVSIL_SMALL);

	for(i=0; i<nAlarmCount+1;i++){
		CString str_Id;
		CString str_Data;
		str_Id.Format("%d",i);
	
		m_alarmlist.DeleteItem(i);
        if(alarm.bIsSerious[i]){
			m_alarmlist.InsertItem(i,"",1);//SERIOUS ALARM RED FLAG
		}
		else{
			m_alarmlist.InsertItem(i,"",0);//NORMAL ALARM YELLO FLAG
		}
		m_alarmlist.SetItemText(i,1,str_Id);
		m_alarmlist.SetItemText(i,2,alarm.str_Alarm[i]);		
	}
}

/////////////////////////////////////////////////////////////////////////////
//Empty All The Information
void CAlarmShowDlg::EmptyAll()
{
	memset(alarm.str_Alarm,0,sizeof(CString)*TOTAL_ALARNUM);
	memset(alarm.bIsSerious,0,sizeof(BOOL)*TOTAL_ALARNUM);
}

HBRUSH CAlarmShowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_LISTBOX){
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(255,255,0));
	}
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
}
