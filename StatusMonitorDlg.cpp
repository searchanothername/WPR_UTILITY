// StatusMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "StatusMonitorDlg.h"
#include "global.h"
#include "Global_Advanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusMonitorDlg dialog

float f_min[TOTAL_ALARNUM] = {
-999,-999,-999,-999,
-999,-999,-999,-999,
-999,-999,-999,-999,
-999,-999,-999,-999,

-999,-999,-999,-999,
-999,-999,-999,-999,
-999,-999,-999,-999,
-999,-999,-999,-999,

-999,-999,-999,-999,
-999,-999,-999,-999,
-999,-999,-999,-999,
-999,-999,-999,-999
};
float f_max[TOTAL_ALARNUM] = {
999,999,999,999,
999,999,999,999,
999,999,999,999,
999,999,999,999,

999,999,999,999,
999,999,999,999,
999,999,999,999,
999,999,999,999,

999,999,999,999,
999,999,999,999,
999,999,999,999,
999,999,999,999,

999,999,999,999,
999,999,999,999,
999,999,999,999,
999,999,999,999
};
CStatusMonitorDlg::CStatusMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatusMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatusMonitorDlg)
	m_nNormalNum = 0;
	m_nWarnningNum = 0;
	m_nErrorNum = 0;
	//}}AFX_DATA_INIT
	memset(fValue, 0, sizeof(double)*TOTAL_ALARNUM);

}


void CStatusMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusMonitorDlg)
	DDX_Control(pDX, IDC_LIST_SM_LIST, m_sm_listctrl);
	DDX_Text(pDX, IDC_EDIT_NORMAL_NUM, m_nNormalNum);
	DDX_Text(pDX, IDC_EDIT_WARNNING_NUM, m_nWarnningNum);
	DDX_Text(pDX, IDC_EDIT_ERROR_NUM, m_nErrorNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatusMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CStatusMonitorDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusMonitorDlg message handlers

BOOL CStatusMonitorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));
	DWORD dwStyle = GetWindowLong(m_sm_listctrl.m_hWnd,GWL_STYLE);
	SetWindowLong(m_sm_listctrl.m_hWnd,GWL_STYLE,dwStyle|LVS_REPORT);
	DWORD style= m_sm_listctrl.GetExtendedStyle();

	m_sm_listctrl.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//m_sm_listctrl.SetBkColor(RGB(55,55,55));
	//m_sm_listctrl.SetTextBkColor(RGB(58,58,58));
	//m_sm_listctrl.SetTextColor(RGB(0,255,255));

	m_SMImageList.Create(16,16,ILC_COLOR32|ILC_MASK,0,0); 	
	m_SMImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON14)));   //YELLOW
	m_SMImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON15)));   //GREEN
	m_SMImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON16)));   //RED

	m_sm_listctrl.SetImageList(&m_SMImageList,LVSIL_SMALL);

	CRect rect;
	m_sm_listctrl.GetWindowRect(&rect);
	int n_ColumnWidth = rect.Width();
	CString strColumn[6] = {_T("LEVEL"),_T("NUMBER"),_T("STATUS ITEM"),_T("VALUE"),_T("MIN"),_T("MAX")};

	m_sm_listctrl.InsertColumn(0,strColumn[0],LVCFMT_LEFT,n_ColumnWidth*0.2);
	m_sm_listctrl.InsertColumn(1,strColumn[1],LVCFMT_LEFT,n_ColumnWidth*0.1);
	m_sm_listctrl.InsertColumn(2,strColumn[2],LVCFMT_LEFT,n_ColumnWidth*0.325);
	m_sm_listctrl.InsertColumn(3,strColumn[3],LVCFMT_LEFT,n_ColumnWidth*0.125);
	m_sm_listctrl.InsertColumn(4,strColumn[4],LVCFMT_LEFT,n_ColumnWidth*0.125);
	m_sm_listctrl.InsertColumn(5,strColumn[5],LVCFMT_LEFT,n_ColumnWidth*0.125);

	fValue[0] = status_data.tx_data.tx_50v;
	fValue[1] = status_data.tx_data.tx_36v;
	fValue[2] = status_data.tx_data.tx_28v;
	fValue[3] = status_data.tx_data.tx_15v;

	fValue[4] = status_data.tx_data.tx_m15v;
	fValue[5] = status_data.tx_data.tx_13v;
	fValue[6] = status_data.tx_data.tx_5v;
	fValue[7] = status_data.tx_data.input_power;

	fValue[8] = status_data.tx_data.output_power;
	fValue[9] = status_data.tx_data.temperature;
	fValue[10] = status_data.tx_data.reflect_power;

	fValue[11] = status_data.cab_data.cab_28v;
	fValue[12] = status_data.cab_data.cab_24v;
	fValue[13] = status_data.cab_data.cab_15v;
	fValue[14] = status_data.cab_data.cab_m15v;
	
	fValue[15] = status_data.cab_data.cab_12v;
	fValue[16] = status_data.cab_data.cab_9v;
	fValue[17] = status_data.cab_data.cab_6v1;
	fValue[18] = status_data.cab_data.cab_6v2;

	fValue[19] = status_data.cab_data.cab_5v1;
	fValue[20] = status_data.cab_data.cab_5v2;
	fValue[21] = status_data.cab_data.cab_5v3;
	fValue[22] = status_data.cab_data.cab_5v4;

	fValue[23] = status_data.cab_data.cab_neg5v;

	fValue[24] = status_data.cab_data.cab_3_3v;
	fValue[25] = status_data.cab_data.ant_pos_pwr;
	fValue[26] = status_data.cab_data.ant_neg_pwr;
	fValue[27] = status_data.cab_data.temp_outside;
	fValue[28] = status_data.cab_data.temp_inside;

	for(int i=0 ; i<ALARM_SIZE; i++)
	{
		CString strValue;
		strValue.Format("%6.2f",fValue[i]);
		CString strLevel = " OK";
		CString strNum;
		strNum.Format("%d",i);
		int level = Check(strLevel, fValue[i],i);
		m_sm_listctrl.InsertItem(i,strLevel,level);

		m_sm_listctrl.SetItemText(i,1,strNum);
		m_sm_listctrl.SetItemText(i,2,alarm_table[i]);	
		m_sm_listctrl.SetItemText(i,3,strValue);

		CString minVal;
		CString maxVal;
		minVal.Format("%6.2f",global_advance.alarmsetting.min[i]);
		maxVal.Format("%6.2f",global_advance.alarmsetting.max[i]);
		m_sm_listctrl.SetItemText(i,4,minVal);
		m_sm_listctrl.SetItemText(i,5,maxVal);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


int CStatusMonitorDlg::Check(CString& strLevel, float val, int id)
{
	int ret;
	if(val>global_advance.alarmsetting.min[id] && 
		val<global_advance.alarmsetting.max[id]){
		strLevel.Format(" OK");
		ret = 1;
		++m_nNormalNum;
		
	}
	else{
		if(global_advance.alarmsetting.nLevel[id] == LEVEL_NORMAL){
			strLevel.Format(" WARNINGS");
			ret = 0;
			++m_nWarnningNum;
			
		}
		else if(global_advance.alarmsetting.nLevel[id] == LEVEL_HIGH){
			strLevel.Format(" ERRORS");
			ret = 2;
			++m_nErrorNum;
		}
		else if(global_advance.alarmsetting.nLevel[id] == LEVEL_NONE){
			strLevel.Format(" OK");
			ret = 1;
			++m_nNormalNum;
		}
	}
	return ret;
}

HBRUSH CStatusMonitorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(0,255,255));
		
	}

	if(nCtlColor == CTLCOLOR_LISTBOX|| nCtlColor == CTLCOLOR_EDIT){
			//For Alarm list
        pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(0,255,255));
	}
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
}
