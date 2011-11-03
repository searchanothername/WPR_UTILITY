#if !defined(AFX_PF_HPA_AND_PA_TEMP_H__2C13205D_34AE_45A8_A6DC_A111577BE25C__INCLUDED_)
#define AFX_PF_HPA_AND_PA_TEMP_H__2C13205D_34AE_45A8_A6DC_A111577BE25C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pf_hpa_and_pa_temp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPf_hpa_and_pa_temp dialog

class CPf_hpa_and_pa_temp : public CPropertyPage
{
	DECLARE_DYNCREATE(CPf_hpa_and_pa_temp)

// Construction
public:
	CPf_hpa_and_pa_temp();
	~CPf_hpa_and_pa_temp();

// Dialog Data
	//{{AFX_DATA(CPf_hpa_and_pa_temp)
	enum { IDD = IDD_PF_HPA_AND_PA_TEMP };
	CString	m_str_HPA1_POWER;
	CString	m_str_HPA10_POWER;
	CString	m_str_HPA2_POWER;
	CString	m_str_HPA3_POWER;
	CString	m_str_HPA4_POWER;
	CString	m_str_HPA5_POWER;
	CString	m_str_HPA6_POWER;
	CString	m_str_HPA7_POWER;
	CString	m_str_HPA8_POWER;
	CString	m_str_HPA9_POWER;
	CString	m_str_PA1_TEMP;
	CString	m_str_PA2_TEMP;
	CString	m_str_PA3_TEMP;
	CString	m_str_PA4_TEMP;
	CString	m_str_PA5_TEMP;
	CString	m_str_PA6_TEMP;
	CString	m_str_PA7_TEMP;
	CString	m_str_PA8_TEMP;
	CString	m_str_PA9_TEMP;
	CString	m_str_PA10_TEMP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPf_hpa_and_pa_temp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CPf_hpa_and_pa_temp)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    CString Show_HPA_Power(float ch_data);
	CString Show_PA_TEMP(float ch_data);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF_HPA_AND_PA_TEMP_H__2C13205D_34AE_45A8_A6DC_A111577BE25C__INCLUDED_)
