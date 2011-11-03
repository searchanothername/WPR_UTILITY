#if !defined(AFX_PF_SUNDRIES_1_H__85265738_A39C_4B41_9A16_D8DD9EC70607__INCLUDED_)
#define AFX_PF_SUNDRIES_1_H__85265738_A39C_4B41_9A16_D8DD9EC70607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pf_sundries_1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPf_sundries_1 dialog

class CPf_sundries_1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPf_sundries_1)

// Construction
public:
	CPf_sundries_1();
	~CPf_sundries_1();

// Dialog Data
	//{{AFX_DATA(CPf_sundries_1)
	enum { IDD = IDD_PF_SUNDRIES_1 };
	CString	m_str_VSWR_FAULT;
	CString	m_str_SPS_STATUS;
	CString	m_str_RF_TEST_SIGNAL;
	CString	m_str_REFLECTED_POWER;
	CString	m_str_PS_6V3A;
	CString	m_str_PS_6V2p5A;
	CString	m_str_OUTSIDE_TEMP;
	CString	m_str_LO_SAMPLE;
	CString	m_str_INSIDE_TEMP;
	CString	m_str_IF_CLOCK;
	CString	m_str_FORWARDED_POWER;
	CString	m_str_DOOR_SWITCH;
	CString	m_str_DDC;
	CString	m_str_BSU_FAULT;
	CString	m_str_AD_CLOCK;
	CString	m_str_AntennaDumyPos;
	CString	m_str_RFD;
	CString	m_str_25M_CW;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPf_sundries_1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_bkBrush;
	// Generated message map functions
	//{{AFX_MSG(CPf_sundries_1)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    CString ShowStatus(unsigned char ndata);
	CString ShowData(float ndata);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF_SUNDRIES_1_H__85265738_A39C_4B41_9A16_D8DD9EC70607__INCLUDED_)
