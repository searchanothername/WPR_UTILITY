#if !defined(AFX_PF_SUNDRIES_2_H__4970E37E_3F58_4061_9862_221001E25BF7__INCLUDED_)
#define AFX_PF_SUNDRIES_2_H__4970E37E_3F58_4061_9862_221001E25BF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pf_sundries_2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPf_sundries_2 dialog

class CPf_sundries_2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPf_sundries_2)

// Construction
public:
	CPf_sundries_2();
	~CPf_sundries_2();

// Dialog Data
	//{{AFX_DATA(CPF_SUNDRIES_2)
	enum { IDD = IDD_PF_SUNDRIES_2 };
	CString	m_str_15V_PS;
	CString	m_str_28V_PS;
	CString	m_str_5V_PS;
	CString	m_str_5VDIGITAL_PS;
	CString	m_str_6V2P5_PS;
	CString	m_str_6V3A_PS;
	CString	m_str_CAB_INLET_AIR_TEMP;
	CString	m_str_CAB_OUTLET_AIR_TEMP;
	CString	m_str_DRV_MODULE1_TEMP;
	CString	m_str_DRV_MODULE2_TEMP;
	CString	m_str_DRV_RF_OUTPUT_POWER;
	CString	m_str_M15V_PS_SAMPLE;
	CString	m_str_M5V_PS_SAMPLE;
	CString	m_str_PS_28V_SAMPLE;
	CString	m_str_40V_SAMPLE;
	CString	m_str_SYSTEM_FORWARD_POWER;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPF_SUNDRIES_2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CPF_SUNDRIES_2)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    CString ShowData(float ch_data);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF_SUNDRIES_2_H__4970E37E_3F58_4061_9862_221001E25BF7__INCLUDED_)
