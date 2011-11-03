#if !defined(AFX_STATUSMONITORDLG_H__B7595EDA_6D3C_434D_92F5_B71FD7ED6C84__INCLUDED_)
#define AFX_STATUSMONITORDLG_H__B7595EDA_6D3C_434D_92F5_B71FD7ED6C84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusMonitorDlg.h : header file
//
#include "Global_Advanced.h"
#include "ColoredListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CStatusMonitorDlg dialog
class CStatusMonitorDlg : public CDialog
{
// Construction
public:
	CStatusMonitorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatusMonitorDlg)
	enum { IDD = IDD_DIALOG_SM_MODIFIED };
	//CListCtrl	m_sm_listctrl;
	CColoredListCtrl m_sm_listctrl;
	int		m_nNormalNum;
	int		m_nWarnningNum;
	int		m_nErrorNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusMonitorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	CImageList m_SMImageList;
	double fValue[TOTAL_ALARNUM];
	int Check(CString& strLevel, float val, int id);
	// Generated message map functions
	//{{AFX_MSG(CStatusMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSMONITORDLG_H__B7595EDA_6D3C_434D_92F5_B71FD7ED6C84__INCLUDED_)
