#if !defined(AFX_ALARMSHOWDLG_H__B5FBEFF2_3F4F_424E_B939_0CAE9F2B5A36__INCLUDED_)
#define AFX_ALARMSHOWDLG_H__B5FBEFF2_3F4F_424E_B939_0CAE9F2B5A36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmShowDlg.h : header file
//
#include "Global_Advanced.h"
/////////////////////////////////////////////////////////////////////////////
// CAlarmShowDlg dialog

class CAlarmShowDlg : public CDialog
{
// Construction
public:
	CAlarmShowDlg(CWnd* pParent = NULL);   // standard constructor
	CBrush m_bkBrush;


// Dialog Data
	//{{AFX_DATA(CAlarmShowDlg)
	enum { IDD = IDD_ALARMSHOW };
	CListCtrl	m_alarmlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    struct ALARM{
		CString str_Alarm[TOTAL_ALARNUM];
		BOOL bIsSerious[TOTAL_ALARNUM];
	}alarm;
    void AddAlarm(int nCount,BOOL bSerious,int Id,CString str);
	void EmptyAll();
	void Show();
	int nAlarmCount;
	int nAlarmId;
	
	CImageList m_ImageList;
	// Generated message map functions
	//{{AFX_MSG(CAlarmShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMSHOWDLG_H__B5FBEFF2_3F4F_424E_B939_0CAE9F2B5A36__INCLUDED_)
