#if !defined(AFX_UPSDLG_H__9AF152B4_E9DE_43F0_B4AC_D76356DE03E8__INCLUDED_)
#define AFX_UPSDLG_H__9AF152B4_E9DE_43F0_B4AC_D76356DE03E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UPSDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUPSDlg dialog

class CUPSDlg : public CDialog
{
// Construction
public:
	CUPSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUPSDlg)
	enum { IDD = IDD_DIALOG_UPS_STATUS };
	CStatic	m_static_BATTERY_LOW;
	CStatic	m_static_BYPASSBOOST;
	CStatic	m_static_ONLINE;
	CStatic	m_static_SHUT_DOWN_ACTIVE;
	CStatic	m_static_TEST_IN_PROGRESS;
	CStatic	m_static_UPS_FAIL;
	CStatic	m_static_UTILITY_FAIL;
	float	m_f_battery_voltage;
	float	m_f_ip_fault_voltage;
	float	m_f_ip_frequence;
	float	m_f_ip_voltage;
	float	m_f_op_load;
	float	m_f_op_voltage;
	float	m_f_temperature;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUPSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void show_status(CStatic& s, int status);
// Implementation
protected:
	CBrush m_bkBrush; 
	// Generated message map functions
	//{{AFX_MSG(CUPSDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPSDLG_H__9AF152B4_E9DE_43F0_B4AC_D76356DE03E8__INCLUDED_)
