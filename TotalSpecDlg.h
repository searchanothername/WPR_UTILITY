#if !defined(AFX_TOTALSPECDLG_H__D5B11A94_E4F9_44DE_851E_7746C2FD16E2__INCLUDED_)
#define AFX_TOTALSPECDLG_H__D5B11A94_E4F9_44DE_851E_7746C2FD16E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TotalSpecDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTotalSpecDlg dialog
#include "DFVCtrl.h"
class CWPR_UTILITIESDlg;
class CWPR_UTILITY_SPECView;
class CTotalSpecDlg : public CDialog
{
// Construction
public:
	CTotalSpecDlg(CWnd* pParent = NULL);   // standard constructor
	void setParent(CWPR_UTILITIESDlg* pParent){_utility = pParent;}
	CDFVCtrl dfvctrl;

	CWPR_UTILITY_SPECView* p;

// Dialog Data
	//{{AFX_DATA(CTotalSpecDlg)
	enum { IDD = IDD_DIALOG_SPEC_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTotalSpecDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	CWPR_UTILITIESDlg* _utility;


	
	// Generated message map functions
	//{{AFX_MSG(CTotalSpecDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOTALSPECDLG_H__D5B11A94_E4F9_44DE_851E_7746C2FD16E2__INCLUDED_)
