#if !defined(AFX_ADVANCEDSETTINGDLG_H__A1A1CFF6_88FB_493B_95BA_E6F97D309711__INCLUDED_)
#define AFX_ADVANCEDSETTINGDLG_H__A1A1CFF6_88FB_493B_95BA_E6F97D309711__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvancedSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdvancedSettingDlg dialog

class CAdvancedSettingDlg : public CDialog
{
// Construction
public:
	CAdvancedSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdvancedSettingDlg)
	enum { IDD = IDD_ADVANCEDSETTING_DLG };
	CListCtrl	m_listctrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void ShowDMASetting();
	void ShowAlarmSetting();
	void ShowBeamSetting();
	void ShowDspSetting();

protected:
	CBrush m_bkBrush;
	CImageList m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(CAdvancedSettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkAdvancedsetList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDSETTINGDLG_H__A1A1CFF6_88FB_493B_95BA_E6F97D309711__INCLUDED_)
