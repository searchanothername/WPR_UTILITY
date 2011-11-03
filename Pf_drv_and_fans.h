#if !defined(AFX_PF_DRV_AND_FANS_H__4252C6CF_26C2_4038_A5C5_B641A0D9FAEC__INCLUDED_)
#define AFX_PF_DRV_AND_FANS_H__4252C6CF_26C2_4038_A5C5_B641A0D9FAEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pf_drv_and_fans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPf_drv_and_fans dialog

class CPf_drv_and_fans : public CPropertyPage
{
	DECLARE_DYNCREATE(CPf_drv_and_fans)

// Construction
public:
	CPf_drv_and_fans();
	~CPf_drv_and_fans();

// Dialog Data
	//{{AFX_DATA(CPf_drv_and_fans)
	enum { IDD = IDD_PF_DRV_AND_FANS };
	CString	m_str_DRV_A_SP_STATUS;
	CString	m_str_DRV_A_STATUS;
	CString	m_str_DRV_B_STATUS;
	CString	m_str_DRV_B_SP_STATUS;
	CString	m_str_Fan1;
	CString	m_str_Fan2;
	CString	m_str_Fan3;
	CString	m_str_Fan4;
	CString	m_str_Fan5;
	CString	m_str_Fan6;
	CString	m_str_Fan7;
	CString	m_str_Fan8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPf_drv_and_fans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CPf_drv_and_fans)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    CString ShowStatus1(char ch_data);
	CString ShowStatus2(char ch_data);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF_DRV_AND_FANS_H__4252C6CF_26C2_4038_A5C5_B641A0D9FAEC__INCLUDED_)
