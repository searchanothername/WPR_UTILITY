#if !defined(AFX_PF_POWER_SUPPLY_PAGE_H__9E40CBBF_8E8E_4030_9EDF_99144EAE81C0__INCLUDED_)
#define AFX_PF_POWER_SUPPLY_PAGE_H__9E40CBBF_8E8E_4030_9EDF_99144EAE81C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pf_power_supply_page.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPf_power_supply_page dialog

class CPf_power_supply_page : public CPropertyPage
{
	DECLARE_DYNCREATE(CPf_power_supply_page)

// Construction
public:
	CPf_power_supply_page();
	~CPf_power_supply_page();

// Dialog Data
	//{{AFX_DATA(CPf_power_supply_page)
	enum { IDD = IDD_PF_PWR_SUP };
	CString	m_str_Neg12V_1;
	CString	m_str_Neg12V_2;
	CString	m_str_Neg5V_1;
	CString	m_str_Neg5V_2;
	CString	m_str_Pos12V_1;
	CString	m_str_Pos12V_2;
	CString	m_str_Pos28V_1;
	CString	m_str_Pos28V_2;
	CString	m_str_Pos40V_1;
	CString	m_str_Pos40V_2;
	CString	m_str_Pos40V_3;
	CString	m_str_Pos5V_1;
	CString	m_str_Pos5V_2;
	CString	m_str_Spare1;
	CString	m_str_Spare2;
	CString	m_str_Spare3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPf_power_supply_page)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	CString ShowStatus(unsigned char ch_data);
	// Generated message map functions
	//{{AFX_MSG(CPf_power_supply_page)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF_POWER_SUPPLY_PAGE_H__9E40CBBF_8E8E_4030_9EDF_99144EAE81C0__INCLUDED_)
