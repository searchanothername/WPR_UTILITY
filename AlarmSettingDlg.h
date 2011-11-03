#if !defined(AFX_ALARMSETTINGDLG_H__C4EDD4FF_21AA_419F_8C1C_FC9C6B966763__INCLUDED_)
#define AFX_ALARMSETTINGDLG_H__C4EDD4FF_21AA_419F_8C1C_FC9C6B966763__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmSettingDlg.h : header file
//
#include "Global_Advanced.h"
/////////////////////////////////////////////////////////////////////////////
// CAlarmSettingDlg dialog

class CAlarmSettingDlg : public CDialog
{
// Construction
public:
	CAlarmSettingDlg(CWnd* pParent = NULL);   // standard constructor
 	ALARMSETTING alarmsetting;
// Dialog Data
	//{{AFX_DATA(CAlarmSettingDlg)
	enum { IDD = IDD_ALARMSETTING_DIALOG };
	CEdit	m_ctrlMinEdit;
	CEdit	m_ctrlMaxEdit;
	CListBox	m_AlarmList;
	int		m_nLevel;
	float	m_minValue;
	float	m_maxValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int nIndex;
	CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CAlarmSettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeAlarmlist();
	afx_msg void OnDonotreport();
	afx_msg void OnNormal();
	afx_msg void OnHigh();
	afx_msg void OnChangeMaxvalue();
	afx_msg void OnChangeMinvalue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMSETTINGDLG_H__C4EDD4FF_21AA_419F_8C1C_FC9C6B966763__INCLUDED_)
