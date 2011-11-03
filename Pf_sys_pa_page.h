#if !defined(AFX_PF_SYS_PA_PAGE_H__BF450ECC_E803_4873_898D_DF07B0AB44BF__INCLUDED_)
#define AFX_PF_SYS_PA_PAGE_H__BF450ECC_E803_4873_898D_DF07B0AB44BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pf_sys_pa_page.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPf_sys_pa_page dialog

class CPf_sys_pa_page : public CPropertyPage
{
	DECLARE_DYNCREATE(CPf_sys_pa_page)

// Construction
public:
	CPf_sys_pa_page();
	~CPf_sys_pa_page();

// Dialog Data
	//{{AFX_DATA(CPF_SYS_PA_PAGE)
	enum { IDD = IDD_PF_SYS_AND_PA };
	CString	m_str_SPARE;
	CString	m_str_DutyCycleRatio;
	CString	m_str_LRSwitch;
	CString	m_str_VSWR;
	CString	m_str_AirTemp;
	CString	m_str_ModuleFault;
	CString	m_str_DriverFault;
	CString	m_str_SystemFault;
	CString	m_str_HPA1_STATUS;
	CString	m_str_HPA10_STATUS;
	CString	m_str_HPA2_STATUS;
	CString	m_str_HPA3_STATUS;
	CString	m_str_HPA4_STATUS;
	CString	m_str_HPA5_STATUS;
	CString	m_str_HPA6_STATUS;
	CString	m_str_HPA7_STATUS;
	CString	m_str_HPA8_STATUS;
	CString	m_str_HPA9_STATUS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPF_SYS_PA_PAGE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	CString ShowStatus(unsigned char ch_data);
	// Generated message map functions
	//{{AFX_MSG(CPF_SYS_PA_PAGE)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF_SYS_PA_PAGE_H__BF450ECC_E803_4873_898D_DF07B0AB44BF__INCLUDED_)
